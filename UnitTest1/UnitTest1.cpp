#include "pch.h"
#include "CppUnitTest.h"
#include "../lab_11_4/lab_11_4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			ofstream f("test.dat", ios::binary);
			Goods goods;
			goods.price = 200.0;
			f.write((char*)&goods, sizeof(Goods));
			f.close();
			ifstream file("test.dat", ios::binary);
			bool x = FiltrPrice("test.dat", 10.0, 1000.0);
			Assert::AreEqual(x, true);
			f.close();
		}
	};
}
