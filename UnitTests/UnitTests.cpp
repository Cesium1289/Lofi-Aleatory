#include "pch.h"
#include "CppUnitTest.h"
#include "../Aleatoric/WaveParameters.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestMethod)
		{
			WaveParameters WP;

			int test = WP.TestAddMethod(2, 2);
			int actual = 2 + 2;
		
			Assert::AreEqual(test, actual);
		}
	};
}
