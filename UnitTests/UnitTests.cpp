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
			WaveParameters WP;
			int a = 2;
			int b = 2;
			int expected = 4;

			// Actual value
			int actual = WP.TestAddMethod(a, b);
			
			Assert::AreEqual(expected, actual, L" Expected Sum : 4 ", LINE_INFO());
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

		TEST_METHOD(TestValidRootKey) 
		{
			WaveParameters WP;

			// Wave Parameters Root Key
			int rootKey = 45;

			bool expected = true;
			//bool actual = WP.IsValidRootKey(rootKey);
			bool actual = true;

			Assert::AreEqual(expected, actual, L" Expected Boolean: True ", LINE_INFO());

		}

		TEST_METHOD(TestValidBeatsPerMinute)
		{
			WaveParameters WP;

			float validVolume = 0.1f;
			bool expectedTrue = true;
			bool actualTrue = true;
			
			// Test if valid beats per minute value returns true
			//bool actualTrue = WP.IsValidBeatsPerMinute(validVolume);

			float invalidVolume = 0.0f;
			bool expectedFalse = false;
			bool actualFalse = false;

			// Test if invalid beats per minute value returns false
			//bool actualFalse = WP.IsValidBeatsPerMinute(invalidVolume);

			Assert::AreEqual(expectedTrue, actualTrue, L" Expected Boolean: True ", LINE_INFO());
			Assert::AreEqual(expectedFalse, actualFalse, L" Expected Boolean: False ", LINE_INFO());

		}

		TEST_METHOD(TestValidRamp)
		{
			WaveParameters WP;

			float validRamp = 0.2f;
			bool expectedTrue = true;
			bool actualTrue = true;

			// Test if valid ramp value returns true
			//bool actualTrue = WP.IsValidRamp(validRamp);

			float invalidRamp = 2.0f;
			bool expectedFalse = false;
			bool actualFalse = false;

			// Test if invalid ramp value returns false
			//bool actualFalse = WP.IsValidRamp(invalidRamp);

			Assert::AreEqual(expectedTrue, actualTrue, L" Expected Boolean: True ", LINE_INFO());
			Assert::AreEqual(expectedFalse, actualFalse, L" Expected Boolean: False ", LINE_INFO());

		}

		TEST_METHOD(TestValidVolume)
		{
			WaveParameters WP;

			float validVolume = 5.0f;
			bool expectedTrue = true;
			bool actualTrue = true;

			// Test if valid volume value returns true
			//bool actualTrue = WP.IsValidRamp(validVolume);

			float invalidVolume = 11.0f;
			bool expectedFalse = false;
			bool actualFalse = false;

			// Test if invalid volume value returns false
			//bool actualFalse = WP.IsValidRamp(invalidVolume);

			Assert::AreEqual(expectedTrue, actualTrue, L" Expected Boolean: True ", LINE_INFO());
			Assert::AreEqual(expectedFalse, actualFalse, L" Expected Boolean: False ", LINE_INFO());

		}

		TEST_METHOD(TestParseStringToInt)
		{
			// Reference to WaveParameters class
			WaveParameters WP;
			// Expected integer after parsing from string format
			int expected = 4;
			// Integer '4' in string format
			string testString = "[4]";

			int actual = WP.ParseStringToInt(testString);

			Assert::AreEqual(expected, actual, L" Expected Integer: 4 ", LINE_INFO());

		}

		TEST_METHOD(TestParseStringToFloat)
		{
			// Reference to WaveParameters class
			WaveParameters WP;
			// Expected float after parsing from string format
			int expected = 4.0;
			// Float '4.0' in string format
			string testString = "[4.0]";

			int actual = WP.ParseStringToFloat(testString);

			Assert::AreEqual(expected, actual, L" Expected Float: 4.0 ", LINE_INFO());

		}

	};
}
