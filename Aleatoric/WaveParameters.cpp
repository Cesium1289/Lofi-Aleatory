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
		else if (!argvArray[i].find("--scale"))
		{
			ParseStringToString(argvArray[i]);
			setScaleType(argvArray[i]);
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
	// Generate random beats per minute from 0.1 to 75
	GenerateRandomBeatsPerMinute();

	// Generate random beats per minute from 0.0 to 0.5
	GenerateRandomRamp();

	// Keep volume at 5 so it is audible every time random sound is created
	parameters.volume = 5.0f;

	// Generate random wave type e.g. sine, square, saw, or triangle
	GenerateRandomWaveType();

	// Set random value boolean to true everytime this method is called
	parameters.random = true;
}

void WaveParameters::GenerateRandomBeatsPerMinute()
{
	// Use <random> library to create a random range in floats for bpm (0.1f to 75.0f)
	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	std::uniform_real_distribution<float> distribution(0.1f, 75.0f);

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
	parameters.beatsPerMinute = randRamp;
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

void WaveParameters::GenerateRandomWave(float frequency, sf::SoundBuffer& Wave)
{
	std::vector<sf::Int16> buffer;

	// Create random BPM for wave
	// EXTERNAL CITATION: https://stackoverflow.com/questions/686353/random-float-number-generation
	srand(static_cast <unsigned> (time(0)));
	float randBPM = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 240 - 1));
	// Random wave type between 1 and 4
	int randWaveType = rand() % 4 + 1;

	for (size_t i = 0; i < NUM_SAMPLES; i++) {
		float pos = fmod((static_cast<float>(i) * frequency) / NUM_SAMPLES, 1.0);
		buffer.push_back(10000 * WaveFunc(pos, randWaveType) * 3.0f);
	}

	//ramp square wave sample
	RampSamples(buffer, 0.5f);

	//place sample into square wave buffer
	Wave.loadFromSamples(&buffer[0], buffer.size(), 1, NUM_SAMPLES * (randBPM / 60));
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

void WaveParameters::setScaleType(const std::string& type)
{
	if (type == "major")
		parameters.scale = 1;
	else if (type == "minor")
		parameters.scale = 2;
	else if (type == "pent")
		parameters.scale = 3;
	else
		std::cout << "Invalid scale type. Enter either 'major' or 'minor'";
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

float WaveParameters::WaveFunc(float pos, int type)
{
	//sine wave
	if (type == 1)
		return sin(pos * 2 * 3.14);
	//square wave
	else if (type == 2)
		return (sin(pos * 3.14 * 2) > 0) ? 1.0 : -1.0;
	//saw wave
	else if (type == 3)
		return pos * 2 - 1;
	//triangle wave
	else if (type == 4)
		return 1 - fabs(pos - 0.5) * 4;
	return 0;
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

int WaveParameters::TestAddMethod(int a, int b)
{
	return a + b;
}
