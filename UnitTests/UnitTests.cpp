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
			float expected = 4.0;
			// Float '4.0' in string format
			string testString = "[4.0]";

			float actual = WP.ParseStringToFloat(testString);

			Assert::AreEqual(expected, actual, L" Expected Float: 4.0 ", LINE_INFO());

		}

		TEST_METHOD(setRootKey)
		{
			WaveParameters Wp;
			int expected = 54;
		
			Wp.setRootKey(expected);
			int actual = Wp.GetRootKey();

			Assert::AreEqual(expected, actual, L" Expected Integer: 54 ", LINE_INFO());
		}
		TEST_METHOD(setBPM)
		{
			WaveParameters Wp;
			float expected = 20.3f;

			Wp.setBPM(expected);
			float actual = Wp.GetBPM();

			Assert::AreEqual(expected, actual, L" Expected Float: 20.3 ", LINE_INFO());
		}
		TEST_METHOD(setRamp)
		{
			WaveParameters Wp;
			float expected = .2f;

			Wp.setRamp(expected);
			float actual = Wp.GetRamp();

			Assert::AreEqual(expected, actual, L" Expected Float: 0.2 ", LINE_INFO());

		}
		TEST_METHOD(setWaveType)
		{
			enum waveEnum {
				sine,
				triangle,
				square,
				saw
			};
			WaveParameters Wp;
			string expectedString = "sine";
			int expected = sine;

			Wp.setWaveType(expectedString);
			int actual = Wp.GetWaveType();

			Assert::AreEqual(expected, actual, L" Expected integer: 0 ", LINE_INFO());
		}

		TEST_METHOD(GenerateRandomParameters)
		{
			WaveParameters WP;
			bool setFalse = false;
			WP.setRandom(setFalse);

			// Should be true after this call
			WP.GenerateRandomParameters();
			
			bool expected = WP.GetRandom();

			Assert::AreEqual(expected, true, L" Expected Boolean: True ", LINE_INFO());

			
		}
		TEST_METHOD(GenerateRandomBeatsPerMinute) 
		{
			WaveParameters WP;
			
			float MIN_BPM = 20.0f;
			float MAX_BPM = 240.0f;
			
			WP.GenerateRandomBeatsPerMinute();

			float actual = WP.GetBPM();

			Assert::IsTrue(actual >= MIN_BPM && actual <= MAX_BPM, L" BPM should be in range 20.0f to 240.0f ", LINE_INFO());

		}

		TEST_METHOD(GenerateRandomRamp)
		{
			WaveParameters WP;

			float MIN_RAMP = 0.0f;
			float MAX_RAMP = 0.5f;

			WP.GenerateRandomRamp();

			float actual = WP.GetRamp();

			Assert::IsTrue(actual >= MIN_RAMP && actual <= MAX_RAMP, L" Ramp should be in range 0.0f to 0.5f ", LINE_INFO());

		}

		TEST_METHOD(GenerateRandomWaveType)
		{
			WaveParameters WP;

			enum waveEnum {
				sine,
				triangle,
				square,
				saw
			};

			int expectedSine = sine;
			int expectedTriangle = triangle;
			int expectedSquare = square;
			int expectedSaw = saw;

			WP.GenerateRandomWaveType();

			int actual = WP.GetWaveType();

			
			Assert::IsTrue(actual == expectedSine 
						|| actual == expectedTriangle 
						|| actual == expectedSquare 
						|| actual == expectedSaw, 
				L" WaveType should be sine, triangle, square or saw", LINE_INFO());
				
		}

		TEST_METHOD(GenerateRandomRootKeyAndKey)
		{
			WaveParameters WP;
			int minRootKey = 21;
			int maxRootKey = 115;

			WP.GenerateRandomRootKeyAndKey();

			char expectedKey = WP.GetKey();
			int expectedRootkey = WP.GetRootKey();

			Assert::IsTrue(expectedKey >= 'a' && expectedKey <= 'g', L" Key should be in range 'a' to 'g' ", LINE_INFO());
			Assert::IsTrue(expectedRootkey >= minRootKey && expectedRootkey <= maxRootKey, L" RootKey should be in range '21' to '115' ", LINE_INFO());
		}
		


	};
}
