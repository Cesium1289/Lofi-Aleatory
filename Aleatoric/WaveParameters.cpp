#include "WaveGenerator.h"
#include<SFML/Audio.hpp>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include <stdlib.h>
#include <random>

const int NUM_SAMPLES = 48000;
const int NUM_KEYS = 7;
const float MIN_BEATS_PER_MINUTE = 0.1f;
const float MAX_RAMP = 0.5f;
const float MAX_VOLUME = 10.0f;
using std::cout;
using std::cerr;
using std::invalid_argument;
using std::endl;

WaveParameters::WaveParameters()
{
	parameters.rootKey = 45;
	parameters.beatsPerMinute = 20.0f;
	parameters.ramp = 0.5f;
	parameters.volume = 8.0f;
	parameters.key = 'a';
	parameters.waveType = saw;
	parameters.random = false;
	MapMidiValues();
}

bool WaveParameters::AreValidParameters()const
{
	return(IsValidRootKey(parameters.rootKey) &&
		IsValidBeatsPerMinute(parameters.beatsPerMinute) &&
		IsValidRamp(parameters.ramp) &&
		IsValidVolume(parameters.volume));
}
void WaveParameters::MapMidiValues()
{
	MidiKeyMap = { {'a', 21},{'a',33},{'a', 45},{'a',57},{'a', 69},{'a',81},{'a',93},{'a',105},
					   {'b', 23},{'b',35},{'b', 47},{'b',59},{'b', 71},{'b',83},{'b',95},{'b',107},
					   {'c', 24},{'c',36},{'c', 48},{'c',60},{'c', 72},{'c',84},{'c',96},{'c',108},
					   {'d', 26},{'d',38},{'d', 50},{'d',62},{'d', 74},{'d',86},{'d',98},{'d',110},
					   {'e', 28},{'e',40},{'e', 52},{'e',64},{'e', 76},{'e',88},{'e',100},{'e',112},
					   {'f', 29},{'f',41},{'f', 53},{'f',65},{'f', 77},{'f',89},{'f',101},{'f',113},
					   {'g', 31},{'g',43},{'g', 55},{'g',67},{'g', 79},{'g',91},{'g',103},{'g',115}
	};
}

//Checks whether or no 'val' is in the MidiKeyMap.
//Returns true if it was able to find the value, false if it was not
bool WaveParameters::IsValidRootKey(int val) const
{
	for (auto& it : MidiKeyMap)
	{
		if (it.second == val)
			return true;
	}
	std::cerr << "ERROR: invalid root key value of " << val << "! Enter a valid MIDI note between 21-115! ";
	return false;
}

bool WaveParameters::IsValidBeatsPerMinute(float val)const
{
	if (val >= MIN_BEATS_PER_MINUTE)
		return true;
	std::cerr << "ERROR: invalid beats per minute value of " << val << "! Enter beats per minute value greater than" << MIN_BEATS_PER_MINUTE << "!\n";
	return false;
}

bool WaveParameters::IsValidRamp(float val)const
{
	if (val >= 0.0f && val <= MAX_RAMP)
		return true;
	cerr << "ERROR: invalid ramp value of " << val << "! Enter ramp value between 0.0 and " << MAX_RAMP <<"!\n";
	return false;

}

bool WaveParameters::IsValidVolume(float val)const
{
	if (val >= 0.0f && val <= MAX_VOLUME)
		return true;
	cerr << "ERROR: invalid volume value of " << val << "! Enter volume value between 0.0 and 10.0!\n";
	return false;
}

//Sets the key parameter based on the value of 'val. If it is found, returns
//true, else it returns false
bool WaveParameters::SetRootKeyCharacter(int val)
{
	for (auto& it : MidiKeyMap)
	{
		if (it.second == val)
		{
			parameters.key = it.first;
			cout << parameters.key << std::endl;
			return true;
		}
	}
	return false;
}

bool WaveParameters::ParseArguments(int argc, char* argv[])
{
	string* argvArray = new string[argc];
	for (size_t i = 0; i < argc; i++)
	{
		argvArray[i] = argv[i];
		cout << argvArray[i];
	}

	for (size_t i = 1; i < argc; i++) {
		if (!argvArray[i].find("--root"))
		{
			setRootKey(ParseStringToInt(argvArray[i]));
		}
		else if (!argvArray[i].find("--bpm"))
		{
			setBPM(ParseStringToFloat(argvArray[i]));

		}
		else if (!argvArray[i].find("--volume"))
		{
			setVolume(ParseStringToFloat(argvArray[i]));

		}
		else if (!argvArray[i].find("--ramp"))
		{
			setRamp(ParseStringToFloat(argvArray[i]));
			cout << argvArray[i];

		}
		else if (!argvArray[i].find("--wave"))
		{
			ParseStringToString(argvArray[i]);
			setWaveType(argvArray[i]);
		}
		else if (!argvArray[i].find("--random"))
		{	
			ParseStringToString(argvArray[i]);
			if (argvArray[i] == "true")
				setRandom(true);
			else
				setRandom(false);
		}
		else
		{
			cout << "ERORR: invalid argument " << argv[i] << endl;
			cout << "Closing program... \n";
			return false;
		}
	}

	return AreValidParameters();
}

int WaveParameters::ParseStringToInt(string& arg)
{
	size_t pos = arg.find("[");
	arg.erase(0, pos + 1);
	pos = arg.find("]");
	arg.erase(pos);

	try {
		return stoi(arg);
	}
	catch (invalid_argument const& error)
	{
		cout << "Invalid parameter value: " << error.what() << "\n";
		return -1.0;
	}
}

float WaveParameters::ParseStringToFloat(string& arg)
{
	size_t pos = arg.find("[");
	arg.erase(0, pos + 1);
	pos = arg.find("]");
	arg.erase(pos);

	try {
		return stof(arg);
	}
	catch (invalid_argument const& error)
	{
		cout << "Invalid parameter value: " << error.what() << "\n";
		return -1.0f;
	}
}


void WaveParameters::ParseStringToString(string& arg)
{
	size_t pos = arg.find("[");
	arg.erase(0, pos + 1);
	pos = arg.find("]");
	arg.erase(pos);
}

void WaveParameters::GenerateRandomParameters()
{
	// Generate a random key value and a corresponding root key value 
	GenerateRandomRootKeyAndKey();

	// Generate random beats per minute from 0.1 to 75
	GenerateRandomBeatsPerMinute();

	// Generate random beats per minute from 0.0 to 0.5
	GenerateRandomRamp();

	// Generate random wave type e.g. sine, square, saw, or triangle
	GenerateRandomWaveType();

	// Set random value boolean to true everytime this method is called
	parameters.random = true;
}


void WaveParameters::GenerateRandomBeatsPerMinute()
{
	// Use <random> library to create a random range in floats for bpm (20.f to 240.0f)
	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	std::uniform_real_distribution<float> distribution(20.0f, 240.0f);

	// Random volume
	float randBPM = distribution(generator);

	// Setting random WaveParameter to the random bpm
	parameters.beatsPerMinute = randBPM;
}

void WaveParameters::GenerateRandomRamp()
{
	// Use <random> library to create a random range in floats for ramp (0.0f to 0.5f)
	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	std::uniform_real_distribution<float> distribution(0.0f, 0.5f);

	// Random ramp 
	float randRamp = distribution(generator);

	// Setting random WaveParameter to the random ramp
	parameters.ramp = randRamp;
}

void WaveParameters::GenerateRandomWaveType()
{
	// Random integer between values 1 and 4
	int randWaveType = rand() % 4 + 1;

	// Change the parameter wave type depending on the value 1 through 4
	switch (randWaveType)
	{
	case 1:
		parameters.waveType = sine;
		break;
	case 2:
		parameters.waveType = square;
		break;
	case 3:
		parameters.waveType = saw;
		break;
	case 4:
		parameters.waveType = triangle;
		break;
	}

}

void WaveParameters::GenerateRandomRootKeyAndKey()
{
	// RootKey 'a' values
	int rootKeyA[] = { 21, 33, 45, 57, 69, 81, 93, 105 };
	// RootKey 'b' values
	int rootKeyB[] = { 23, 35, 47, 59, 71, 83, 95, 107 };
	// RootKey 'c' values
	int rootKeyC[] = { 24, 36, 48, 60, 72, 84, 96, 108 };
	// RootKey 'd' values
	int rootKeyD[] = { 26, 38, 50, 62, 74, 86, 98, 110 };
	// RootKey 'e' values
	int rootKeyE[] = { 28, 40, 52, 64, 76, 88, 100, 112 };
	// RootKey 'f' values
	int rootKeyF[] = { 29, 41, 53, 65, 77, 89, 101, 113 };
	// RootKey 'g' values
	int rootKeyG[] = { 31, 43, 55, 67, 79, 91, 103, 115 };


	// Random integer between values 1 and 7
	int randKey = rand() % 7 + 1;

	// Random integer between values 0 and 7 
	// This random value is used to select a random index out of each rootKey array with their corresponding value
	int randRootKey = rand() % 8;

	// Change the parameter key type depending on the value 1 through 7 along with a random rootKey value
	switch (randKey)
	{
		case 1:
			parameters.key = 'a';
			parameters.rootKey = rootKeyA[randRootKey];
			break;
		case 2:
			parameters.key = 'b';
			parameters.rootKey = rootKeyB[randRootKey];
			break;
		case 3:
			parameters.key = 'c';
			parameters.rootKey = rootKeyC[randRootKey];
			break;
		case 4:
			parameters.key = 'd';
			parameters.rootKey = rootKeyD[randRootKey];
			break;
		case 5:
			parameters.key = 'e';
			parameters.rootKey = rootKeyE[randRootKey];
			break;
		case 6:
			parameters.key = 'f';
			parameters.rootKey = rootKeyF[randRootKey];
			break;
		case 7:
			parameters.key = 'g';
			parameters.rootKey = rootKeyG[randRootKey];
			break;
	}

}

void WaveParameters::setRootKey(int rootKey)
{
	parameters.rootKey = rootKey;
}

void WaveParameters::setBPM(float bpm)
{
	parameters.beatsPerMinute = bpm;
}

void WaveParameters::setVolume(float vol)
{
	parameters.volume = vol;
}

void WaveParameters::setRamp(float ramp)
{
	parameters.ramp = ramp;
}

void WaveParameters::setWaveType(const std::string& type)
{
	if (type == "sine")
		parameters.waveType = sine;
	else if (type == "square")
		parameters.waveType = square;
	else if (type == "saw")
		parameters.waveType = saw;
	else if (type == "triangle")
		parameters.waveType = triangle;
	else
		std::cout << "Invalid wave type";
}

void WaveParameters::setRandom(bool val)
{
	parameters.random = val;
}


float WaveParameters::GetRamp()
{
	return parameters.ramp;
}

float WaveParameters::GetBPM()
{
	return parameters.beatsPerMinute;
}


int WaveParameters::GetRootKey()
{
	return parameters.rootKey;
}

int WaveParameters::GetWaveType()
{
	return parameters.waveType;
}

void WaveParameters::display()
{
	cout << "\n-_-_-Values used-_-_-\n";
	cout << "Root: " << parameters.rootKey << endl;
	cout << "BPM: " << parameters.beatsPerMinute << endl;
	cout << "Ramp: " << parameters.ramp << endl;
	cout << "Volume: " << parameters.volume << endl;
	cout << "Key: " << parameters.key << endl;
	cout << "waveType: " << parameters.waveType << endl;
	cout << "Random: " << parameters.random << endl;
}

//Calculate the beat time for the attack and release time for the note envelope
void WaveParameters::RampSamples(vector<sf::Int16>& sample, float frac)
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
