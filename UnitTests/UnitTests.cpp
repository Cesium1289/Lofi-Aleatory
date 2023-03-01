#include "pch.h"
#include "CppUnitTest.h"
#include "../Aleatoric/WaveParameters.h"
#include "../Aleatoric/WaveParameters.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestAddMethod)
		{
			//WaveParameters WP;
			int a = 2;
			int b = 2;
			int expected = 4;

			// Actual value
			//int actual = WP.TestAddMethod(a, b);
			
			Assert::AreEqual(expected, 4, L" Expected Sum : 4 ", LINE_INFO());
		}

		TEST_METHOD(TestSimpleAdd)
		{
			int testA = 2;
			int testB = 2;
			int expected = 4;

			// Actual Value
			int actual = testA + testB;

			Assert::AreEqual(expected, actual, L" Expected Sum: 4 ", LINE_INFO());
		}
	};
}
