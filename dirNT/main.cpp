#include "NtEnum.h"

#include "beevector.h"
#include "beewstring.h"
#include "Write.h"

DWORD GetFullName(LPCWSTR filename, bee::wstring* fullname)
{
	DWORD rc = 0;
	DWORD lenNeededPlusZero;
	if ((lenNeededPlusZero = GetFullPathNameW(filename, 0, NULL, NULL)) == 0)
	{
		rc = GetLastError();
	}
	else {
		fullname->resize(lenNeededPlusZero);
		if (GetFullPathNameW(filename, (DWORD)fullname->length(), (LPWSTR)(fullname->data()), NULL) == 0)
		{
			rc = GetLastError();
		}
		fullname->resize(lenNeededPlusZero - 1);
	}
	return rc;
}


int beeMain(int argc, WCHAR* argv[])
{
	DWORD rc = 0;
	bee::wstring dirname;

	if (argc != 2)
	{
		rc = 999;
	}
	else if ((rc = GetFullName(argv[1], &dirname)) != 0)
	{
	}
	else if (DWORD attrs; (attrs = GetFileAttributesW(dirname.c_str())) == INVALID_FILE_ATTRIBUTES)
	{
		rc = GetLastError();
	}
	else if ((attrs & FILE_ATTRIBUTE_DIRECTORY) == 0)
	{
		rc = 1;
		bee::Writer::Err().Write(L"E not a directory");
	}
	else
	{
		bee::LastError err;
		bee::wstring tmp;
		size_t sum_filesize = 0;
		size_t sum_files    = 0;
		
		NtEnum enumerator(
		[&sum_files, &sum_filesize, &tmp, &err]
		(bee::wstring& dir, size_t rootDirLen, nt::FILE_DIRECTORY_INFORMATION* info)
		{
			tmp.append(dir);
			tmp.push_back(L'\\');
			tmp.append(&(info->FileName[0]), info->FileNameLength / sizeof(WCHAR));
			tmp.appendA("\r\n");

			if (tmp.length() > 4096)
			{
				bee::Writer::Out().Write(tmp, &err);
				tmp.resize(0);
			}

			sum_filesize += info->EndOfFile.QuadPart;
			sum_files += 1;
		});
		enumerator.Run(dirname);
		

		if (tmp.length() > 0)
		{
			bee::Writer::Out().Write(tmp, &err);
		}

		tmp.resize(0);
		tmp.appendA("entries: ");	tmp.append_ull(sum_files);
		tmp.appendA("\tsize: ");	tmp.append_ull(sum_filesize);
		tmp.appendA("\r\n");
		bee::Writer::Out().Write(tmp);
	}

	return rc;
}
