#include<SFML/Audio.hpp>
#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;
/*
*Change the program arguments within this struct
*/
struct Arguments
{
	float squareWaveAmp = 0.0f;
	float sineWaveAmp =0.0f;
	int rootKey = 45;
	int sig = 8;
	float bpm = 20.0f;
	float ramp = 0.5f;
	float accent = 5.0f;
	float volume = 8.0f;
	char key = 'a';
};

void CalculateFrequency(float freqArray[], vector<int>& scaleArray, int RootKey);
void fillMajorArray(vector<int>& scaleArray, char key);
void GenerateSineWaves(float freqArray[], sf::SoundBuffer SineWaves[], Arguments& args);
void GenerateSquareWave(float freqArray[], sf::SoundBuffer& squareWave, Arguments& args);
void SetAmplitudes(Arguments& args);
void RampSamples(vector<sf::Int16>& sample, float frac);
int CheckKeyValue(int rootKey, char& character);
bool ValidArguments(Arguments& args);

const int NUM_SAMPLES = 48000;
const int NUM_KEYS = 7;

int main()
{
	sf::SoundBuffer sineSamples[NUM_KEYS]; 
	sf::SoundBuffer squareSample;
	sf::Sound sound;
	Arguments args;
	vector<int> scaleArray;
	float freqArray[NUM_KEYS];
	
	if (ValidArguments(args))
	{
		SetAmplitudes(args);
		fillMajorArray(scaleArray, args.key);
		CalculateFrequency(freqArray, scaleArray, args.rootKey);
		GenerateSineWaves(freqArray, sineSamples, args);
		GenerateSquareWave(freqArray, squareSample, args);
		cout << "\n-_-_-Values used-_-_-\n";
		cout << "Root: " << args.rootKey << endl;
		cout << "Beats per measure: " << args.sig << endl;
		cout << "BPM: " << args.bpm << endl;
		cout << "Ramp: " << args.ramp << endl;
		cout << "Accent: " << args.accent << endl;
		cout << "Volume: " << args.volume << endl;
		int i = 1;

		while (1)
		{
			//check if sound is playing
			while (sound.getStatus() == sf::Sound::Playing)		
				sf::sleep(sf::milliseconds(100));

			//check if square wave should be played
			if (i == args.sig)
			{
				sound.setBuffer(squareSample);
				sound.play();
				i = 0;
			}
			else
			{
				sound.setBuffer(sineSamples[rand() % NUM_KEYS]);
				sound.play();
			}
			++i;
		}
	}
}

//Check if the values the user provided are valid
bool ValidArguments(Arguments& args)
{
	if (!CheckKeyValue(args.rootKey, args.key))
		return false;
		
	else if (args.sig < 1)
	{
		cout << "Enter a beats value greater than 1!\n";
		return false;
	}
	else if (args.bpm < 0.1f)
	{
		cout << "Enter a bpm value greater than 0!\n";
		return false;
	}
	else if (args.ramp < 0.0f || args.ramp > 0.5f)
	{
		cout << "Enter a ramp value that is between 0.0 - 0.5!\n";
		return false;
	}
	else if (args.volume < 0.0f || args.volume > 10.0f)
	{
		cout << "Enter a volume value between 0.0 - 10.0!\n";
		return false;
	}
	else if (args.accent < 0.0f || args.accent > 10.0f)
	{
		cout << "Enter a accent value between 0.0 - 10.0!\n";
		return false;
	}
	return true;
}

//Calculate the freqency of the random keys that can be played
void CalculateFrequency(float freqArray[], vector<int>& scaleArray, int rootKey)
{
	int scaleOffset = 0;

	for (size_t i = 0; i < NUM_KEYS + 1; i++)
	{
		freqArray[i] = 440 * static_cast<float>(pow(2.0, ((rootKey + static_cast<float>(scaleArray.at(i) + scaleOffset) - 69) / 12)));
		scaleOffset += scaleArray[i];
	}
}

void GenerateSineWaves(float freqArray[], sf::SoundBuffer SineWaves[], Arguments& args)
{
	vector<sf::Int16> buffer;

	//generate sine waves
	for (size_t i = 1; i < NUM_KEYS + 1; i++)
	{
		buffer.clear();

		for (size_t j = 0; j < NUM_SAMPLES; j++)
			buffer.push_back(10000 * args.sineWaveAmp * sin(2 * 3.14 * freqArray[i] * (static_cast<float>(j) / NUM_SAMPLES)));

		//ramp the sample 
		RampSamples(buffer, args.ramp);

		//add sine wave to wave buffer
		SineWaves[i - 1].loadFromSamples(&buffer[0], buffer.size(), 1, NUM_SAMPLES * (args.bpm / 60));
	}
}

void GenerateSquareWave(float freqArray[], sf::SoundBuffer& squareWave, Arguments& args)
{
	vector<sf::Int16> buffer;

	//generate square wave
	for (size_t i = 0; i < NUM_SAMPLES; i++)
	{
		if (sin(2 * 3.14 * freqArray[0] * (static_cast<float>(i) / NUM_SAMPLES)) > 0)
			buffer.push_back(10000 * args.squareWaveAmp);
		else
			buffer.push_back(-10000 * args.squareWaveAmp);
	}

	//ramp square wave sample
	RampSamples(buffer, args.ramp);

	//place sample into square wave buffer
	squareWave.loadFromSamples(&buffer[0], buffer.size(), 1, NUM_SAMPLES * (args.bpm / 60));	
}

//Set the amplitudes for the square and sine waves based on volume levels
void SetAmplitudes(Arguments& args)
{
	args.squareWaveAmp =  pow(10,(-6 * (10 - args.accent) / 20));
	args.sineWaveAmp = pow(10, (-6 * (10 - args.volume) / 20));
}

//Calculate the beat time for the attack and release time for the note envelope
void RampSamples(vector<sf::Int16>& sample, float frac)
{
	int rampSamples = NUM_SAMPLES * frac;
	float dampen;
	float n = 0;
	float temp;

	//apply the left half of a triangle window to the first 'NUM_SAMPLES * frac' samples,
	//where n is the current sample
	for (size_t i = 0; i < rampSamples; i++)
	{ 
		//apply triangle window formula to sample and store that value into temp
		temp = n - ((static_cast<float>(rampSamples)));
		temp /= (static_cast<float>(rampSamples));

		//calculate amount to dampen
		dampen = 1 - abs(temp);

		//dampen audio sample
		sample.at(i) *= dampen;
		++n;
	}
	
	n = rampSamples - 1;

	//apply the right half of a triangle window to last 'NUM_SAMPLES * frac' samples,
	//where n is the current sample
	for (size_t i = NUM_SAMPLES - rampSamples; i < NUM_SAMPLES; i++)
	{
		//apply triangle window formula to sample and store that value into temp
		temp = n - ((static_cast<float>(rampSamples)));
		temp /= (static_cast<float>(rampSamples));

		//calculate amount to dampen
		dampen = 1 - abs(temp);

		//dampen audio sample
		sample.at(i) *= dampen;
		--n;
	}
}

//Fill the scaleVector with the proper key offsets so a proper frequency can be acquired for 
//each key
void fillMajorArray(vector<int>& scaleArray, char key)
{
	switch (key)
	{
	case('a'):
		scaleArray.insert(scaleArray.end(), { 0,2,1,2,2,1,2,2 });
		break;
	case('b'):
		scaleArray.insert(scaleArray.end(), { 0,1,2,2,1,2,2,2 });
		break;
	case('c'):
		scaleArray.insert(scaleArray.end(), { 0,2,2,1,2,2,2,1 });
		break;
	case('d'):
		scaleArray.insert(scaleArray.end(), { 0,2,1,2,2,2,1,2 });
		break;
	case('e'):
		scaleArray.insert(scaleArray.end(), { 0,1,2,2,2,1,2,2 });
		break;
	case('f'):
		scaleArray.insert(scaleArray.end(), { 0,2,2,2,1,2,2,1 });
		break;
	case('g'):
		scaleArray.insert(scaleArray.end(), { 0,2,2,1,2,2,1,2 });
		break;
	default:
		cout << "ERROR: unable to generate major array\n";
		break;
	}
}

//Check if the MIDI value the user gave is valid. If so, assign that value with a root key
int CheckKeyValue(int rootKey, char& character)
{
	if (rootKey == 21 || rootKey == 33 || rootKey == 45 || rootKey == 57 || rootKey == 69 || rootKey == 81 || rootKey == 93 || rootKey == 105)
		character = 'a';
	else if (rootKey == 23 || rootKey == 35 || rootKey == 47 || rootKey == 59 || rootKey == 71 || rootKey == 83 || rootKey == 95 || rootKey == 107)
		character = 'b';
	else if (rootKey == 24 || rootKey == 36 || rootKey == 48 || rootKey == 60 || rootKey == 72 || rootKey == 84 || rootKey == 96 || rootKey == 108)
		character = 'c';
	else if (rootKey == 26 || rootKey == 38 || rootKey == 50 || rootKey == 62 || rootKey == 74 || rootKey == 86 || rootKey == 98 || rootKey == 110)
		character = 'd';
	else if (rootKey == 28 || rootKey == 40 || rootKey == 52 || rootKey == 64 || rootKey == 76 || rootKey == 88 || rootKey == 100 || rootKey == 112)
		character = 'e';
	else if (rootKey == 29 || rootKey == 41 || rootKey == 53 || rootKey == 65 || rootKey == 77 || rootKey == 89 || rootKey == 101 || rootKey == 113)
		character = 'f';
	else if (rootKey == 31 || rootKey == 43 || rootKey == 55 || rootKey == 67 || rootKey == 79 || rootKey == 91 || rootKey == 103 || rootKey == 115)
		character = 'g';
	else
	{
		cout << "\n\nINVALID KEY VALUE: " << rootKey << ". Enter a valid MIDI note between 21-115! ";
		return 0;
	}
	return 1;
}