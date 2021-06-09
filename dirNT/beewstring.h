#pragma once

#include "bee_basic_string.h"
#include "nt.h"

namespace bee
{
	class wstring : public basic_string<WCHAR>
	{
	public:
		wstring() : basic_string() {}
		wstring(LPCWSTR str) : basic_string()
		{
			this->appendW(str);
		}
		wstring& appendW(const wchar_t* str)
		{
			for (int i = 0; str[i] != L'\0'; ++i)
			{
				this->push_back(str[i]);
			}
			return *this;
		}
		wstring& appendA(const char* str)
		{
			for (int i = 0; str[i] != '\0'; ++i)
			{
				WCHAR c = str[i];
				this->push_back(c);
			}
			return *this;
		}
		wstring& append_ull(ULONGLONG val) {

			reserve(length() + 32);

			nt::UNICODE_STRING ucs;
			ucs.Length			= 0;
			ucs.MaximumLength	= 32;
			ucs.Buffer			= data() + length();

			nt::NTSTATUS status = nt::RtlInt64ToUnicodeString(val, 10, &ucs);

			this->_len += ucs.Length / sizeof(WCHAR);

			return *this;
		}
		wstring& append_ll(LONGLONG val) {

			if (val < 0)
			{
				this->push_back(L'-');
				val = -val;
			}

			return append_ull((ULONGLONG)val);
		}

	private:

	};
}