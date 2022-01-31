#include "pch.h"
#include "CppUnitTest.h"

#include "../dirNT/beewstring.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBee
{
	TEST_CLASS(TestBeeWString)
	{
	public:

		TEST_METHOD(create_instance)
		{
			bee::wstring v;
			Assert::IsTrue(0 == v.length());
		}
		TEST_METHOD(c_str)
		{
			bee::wstring s;
			s.push_back('b');
			const WCHAR* cs = s.c_str();
			Assert::IsTrue(1 == s.length());
			Assert::AreEqual(L"b", cs);
		}
		TEST_METHOD(int_to_string)
		{
			bee::wstring s;
			s.append_ll(17);
			Assert::AreEqual(L"17", s.c_str());
		}
		TEST_METHOD(negative_int_to_string)
		{
			bee::wstring s;
			s.append_ll(-17);
			Assert::AreEqual(L"-17", s.c_str());
		}
		TEST_METHOD(Nui_schaumma_si_a_au)
		{
			bee::wstring s;
			s.append_ll(0);
			Assert::AreEqual(L"0", s.c_str());
		}
		TEST_METHOD(ULONGLONG_to_string)
		{
			bee::wstring s;
			s.append_ull(17);
			Assert::IsTrue(s.length() == 2);
			Assert::AreEqual(L"17", s.c_str());
		}
		TEST_METHOD(sprintf_s)
		{
			bee::wstring s;
			s.sprintf(L"%s", L"bumsti");
			Assert::AreEqual(L"bumsti", s.c_str());
		}
		TEST_METHOD(sprintf_c)
		{
			bee::wstring s;
			s.sprintf(L"%c", L'b');
			Assert::AreEqual(L"b", s.c_str());
		}
		TEST_METHOD(sprintf_04u)
		{
			bee::wstring s;
			s.sprintf(L"%04u", 17);
			Assert::AreEqual(L"0017", s.c_str());
		}
		TEST_METHOD(sprintf_04u_5stellig)
		{
			bee::wstring s;
			s.sprintf(L"%04u", 32800);
			Assert::AreEqual(L"32800", s.c_str());
		}
		TEST_METHOD(sprintf_12I64u)
		{
			bee::wstring s;
			s.sprintf(L"%12I64u", 1);
			Assert::AreEqual(L"           1", s.c_str());
		}
		TEST_METHOD(appendf_12I64u)
		{
			bee::wstring s(L"0");
			s.appendf(L"%12I64u", 1);
			Assert::AreEqual(L"0           1", s.c_str());
		}
		TEST_METHOD(appendf_Hello_world)
		{
			bee::wstring s;
			s.appendf(L"%s", L"Hello");
			s.appendf(L" %s", L"world");
			Assert::AreEqual(L"Hello world", s.c_str());
		}
		TEST_METHOD(appendf_0_999)
		{
			bee::wstring s;

			for (int i = 0; i < 1000; ++i)
			{
				s.appendf(L"%03d", i);
			}
			Assert::IsTrue(3000 == s.length());
		}
	};
}
