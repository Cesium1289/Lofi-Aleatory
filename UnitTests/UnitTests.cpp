#include "pch.h"
#include "CppUnitTest.h"
#include "../Aleatoric/WaveParameters.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			WaveParameters WP;
			int expected = 4;
			int actual = WP.TestAddMethod(2, 2);
			

			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(TestMethod2)
		{
			int testA = 2;
			int testB = 2;

			int actual = testA + testB;

			Assert::AreEqual(4, actual);
		}
	};
}
