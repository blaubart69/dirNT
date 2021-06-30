#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestBee
{
	int instance_counter;

	class Dummy
	{
	public:
		int _val;

		Dummy()
		{
			++instance_counter;
		}
		Dummy(int val)
		{
			_val = val;
			++instance_counter;
		}

		~Dummy()
		{
			--instance_counter;
		}
	};

	TEST_CLASS(TestVec_ctor_dtor)
	{
	public:

		TEST_CLASS_INITIALIZE(init)
		{
			instance_counter = 0;
		}

		TEST_CLASS_CLEANUP(cleanup)
		{
			Assert::AreEqual(0, instance_counter);
		}
		TEST_METHOD(create_instance)
		{
			bee::vector<Dummy> v;
			Assert::IsTrue(0 == v.size());
		}
		TEST_METHOD(resize)
		{
			bee::vector<Dummy> v;
			v.resize(8);
		}
		TEST_METHOD(push_back)
		{
			bee::vector<Dummy> v;
			Dummy d1(17);
			v.push_back(d1);
			Dummy d2(18);
			v.push_back(d2);
			Assert::AreEqual(17, v[0]._val);
			Assert::AreEqual(18, v[1]._val);
		}
	};
}
