#include "pch.h"
#include "CppUnitTest.h"

#include "../dirNT/LastError.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBee
{
	TEST_CLASS(TestLastError)
	{
	public:

		TEST_METHOD(sizeofLastError)
		{
			int s = sizeof(bee::LastError);
			Assert::AreEqual(24, s);
		}
	};
}
