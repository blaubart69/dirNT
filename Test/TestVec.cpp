#include "pch.h"
#include "CppUnitTest.h"

#include "../dirNT/beeVector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBee
{
	TEST_CLASS(TestVec)
	{
	public:
		
		TEST_METHOD(create_instance)
		{
			bee::vector<char> v;
			Assert::IsTrue(0 == v.size());
		}
		TEST_METHOD(append_one_char)
		{
			bee::vector<char> v;
			Assert::IsTrue(0 == v.size());
			v.push_back('f');
			Assert::IsTrue(1 == v.size());
			Assert::IsTrue('f' == v[0]);
		}
		TEST_METHOD(push_back_two_DWORDs)
		{
			bee::vector<DWORD> v;
			Assert::IsTrue(0 == v.size());
			v.push_back(0xFF);
			Assert::IsTrue(1 == v.size());
			v.push_back(0xEE);
			Assert::IsTrue(2 == v.size());
			Assert::IsTrue(0xFF == v[0]);
			Assert::IsTrue(0xEE == v[1]);
		}
		TEST_METHOD(operator_idx)
		{
			bee::vector<DWORD> v;
			Assert::IsTrue(0 == v.size());
			v.push_back(0xFF);
			Assert::IsTrue(1 == v.size());
			Assert::IsTrue(0xFF == v[0]);
			v[0] = 0xAA;
			Assert::IsTrue(0xAA == v[0]);
		}
		TEST_METHOD(append_two_DWORDs)
		{
			bee::vector<DWORD> v;
			Assert::IsTrue(0 == v.size());

			//DWORD values[2] = { 0xFF, 0xEE };
			//v.append(values, 2);
			bee::vector<DWORD> v2;
			v2.push_back(0xff);
			v2.push_back(0xee);
			v.append(v2);

			Assert::IsTrue(2 == v.size());
			Assert::IsTrue(0xFF == v[0]);
			Assert::IsTrue(0xEE == v[1]);
		}
		TEST_METHOD(append_four_DWORDs)
		{
			bee::vector<DWORD> v;
			Assert::IsTrue(0 == v.size());

			//DWORD v1[2] = { 0xFF, 0xEE };
			//v.append(v1, 2);
			bee::vector<DWORD> v2;
			v2.push_back(0xff)
			  .push_back(0xee);
			v.append(v2);

			Assert::IsTrue(2 == v.size());
			Assert::IsTrue(0xFF == v[0]);
			Assert::IsTrue(0xEE == v[1]);

			v2.clear();
			v2.push_back(0xdd)
			  .push_back(0xcc);
			v.append(v2);

			Assert::IsTrue(4 == v.size());
			Assert::IsTrue(0xDD == v[2]);
			Assert::IsTrue(0xCC == v[3]);
		}
	};
}
