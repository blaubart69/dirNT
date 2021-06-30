#include "pch.h"
#include "CppUnitTest.h"

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
	};
}
