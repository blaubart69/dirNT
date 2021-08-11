#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "../dirNT/nt.h"

namespace TestNT
{
	TEST_CLASS(TestNTprintf)
	{
	public:
		TEST_METHOD(swprintf_hex)
		{
			WCHAR buf[32];
			int charsWritten = nt::swprintf_s(buf, sizeof(buf) / sizeof(WCHAR), L"0x%X", 10);
			Assert::IsTrue(charsWritten == 3);
			Assert::AreEqual(L"0xA", buf);
		}
		TEST_METHOD(swprintf_pointer)
		{
			WCHAR buf[32];
			int charsWritten = nt::swprintf_s(buf, sizeof(buf) / sizeof(WCHAR), L"%p", 0xAffE);
			Assert::AreEqual(L"000000000000AFFE", buf);
		}
		TEST_METHOD(swprintf_error)
		{
			WCHAR buf[8];
			int charsWritten = nt::swprintf_s(buf, sizeof(buf) / sizeof(WCHAR), L"%d hallo", 1724);
			Assert::AreEqual(L"000000000000AFFE", buf);
		}
	};
}