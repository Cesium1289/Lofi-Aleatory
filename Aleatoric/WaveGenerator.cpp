#pragma once
#include "WaveGenerator.h"
#include<SFML/Audio.hpp>
#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;
const int NUM_SAMPLES = 48000;
const int NUM_KEYS = 7;

//Play the wave that was generated
void WaveGenerator::playWave(WaveParameters& args, sf::SoundBuffer& lofiSample)
{
	srand(time(NULL));
	vector<int> scaleArray;
	vector<float> freqArray;

	fillMajorArray(scaleArray, args.parameters.key);
	CalculateFrequency(freqArray, scaleArray, args.parameters.rootKey);

	cout << "\n-_-_-Values used-_-_-\n";
	cout << "Root: " << args.parameters.rootKey << endl;
	cout << "BPM: " << args.parameters.beatsPerMinute << endl;
	cout << "Ramp: " << args.parameters.ramp << endl;
	cout << "Volume: " << args.parameters.volume << endl;
	cout <<"Key: "<< args.parameters.key << endl;
	cout <<"waveType: " << args.parameters.waveType << endl;
	cout << "Random: " << args.parameters.random << endl;

	GenerateWave(args, freqArray.at(rand() % 7), lofiSample);
}


void WaveGenerator::stopWave() {
	if (sound.getStatus() == sf::Sound::Playing)
		sound.stop();
}


void WaveGenerator::GenerateSawWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer)
{
	vector<sf::Int16> saw;
	vector<sf::Int16> samples;
	float amplitude = GenerateAmplitude(params.parameters.volume);

	for (int i = 0; i < NUM_SAMPLES; ++i)
	{
		samples.push_back(10000 * amplitude * sin((2 * 3.1415 * freq) * (static_cast<float>(i) / NUM_SAMPLES)));
		if (samples.back() >= 0)
			saw.push_back(samples.back());
		else
			saw.push_back(0);
	}

	RampSamples(samples, params.parameters.ramp);
	buffer.loadFromSamples(&saw[0], saw.size(), 1, NUM_SAMPLES * (params.parameters.beatsPerMinute / 60));
}

void WaveGenerator::GenerateSineWave(WaveParameters& args, float freq, sf::SoundBuffer& sound)
{
	vector<sf::Int16> buffer;
	const double amplitude = GenerateAmplitude(args.parameters.volume);

	// Sine Wave Oscillator
	for (int i = 0; i < NUM_SAMPLES; ++i)
	{
		buffer.push_back(10000 * amplitude * sin(2 * 3.141 * freq * (static_cast<float>(i) / NUM_SAMPLES)));
	}
	RampSamples(buffer, args.parameters.ramp);

	sound.loadFromSamples(&buffer[0], buffer.size(), 1, NUM_SAMPLES * (args.parameters.beatsPerMinute / 60));
}

void WaveGenerator::GenerateSquareWave(WaveParameters& params, float freq, sf::SoundBuffer& sound)
{
	vector<sf::Int16> buffer;
	float amplitude = GenerateAmplitude(params.parameters.volume);

	for (size_t i = 0; i < NUM_SAMPLES; i++)
	{
		if (sin(2 * 3.14 * freq * (static_cast<float>(i) / NUM_SAMPLES)) > 0)
			buffer.push_back(10000 * amplitude);
		else
			buffer.push_back(-10000 * amplitude);
	}

	//ramp square wave sample
	RampSamples(buffer, params.parameters.ramp);

	//place sample into square wave buffer
	sound.loadFromSamples(&buffer[0], buffer.size(), 1, NUM_SAMPLES * (params.parameters.beatsPerMinute / 60));
}

void WaveGenerator::GenerateTriangleWave(WaveParameters& params, float freq, sf::SoundBuffer& sound)
{
	vector<sf::Int16> buffer;
	for (size_t i = 0; i < NUM_SAMPLES; i++) {
		buffer.push_back(10000 * (1 - fabs(fmod((static_cast<float>(i) * freq) / NUM_SAMPLES, 1.0) - 0.5) * 4) * GenerateAmplitude(params.parameters.volume));
	}
	//ramp square wave sample
	RampSamples(buffer, params.parameters.ramp);

	//place sample into square wave buffer
	sound.loadFromSamples(&buffer[0], buffer.size(), 1, NUM_SAMPLES * (params.parameters.beatsPerMinute / 60));
	
}

float WaveGenerator::GenerateAmplitude(float volume)
{
	return pow(10, (-6 * (10 - volume)) / 20);
}

void WaveGenerator::GenerateWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer)
{
	if (params.parameters.random)
		params.parameters.waveType = static_cast<waveEnum>(rand() % 4);
	if (params.parameters.waveType == sine)
		GenerateSineWave(params, freq, buffer);
	else if (params.parameters.waveType == triangle)
		GenerateTriangleWave(params, freq, buffer);
	else if (params.parameters.waveType == saw)
		GenerateSawWave(params, freq, buffer);
	else if (params.parameters.waveType == square)
		GenerateSquareWave(params, freq, buffer);
	else cout << "ERROR: Invalid wave type!\n";
}

//Calculate the frequency of the random keys that can be played
void WaveGenerator::CalculateFrequency(vector<float>&freqArray, vector<int>& scaleArray, int rootKey)
{
	int scaleOffset = 0;

	for (size_t i = 0; i < NUM_KEYS + 1; i++)
	{
		freqArray.push_back(440 * static_cast<float>(pow(2.0, ((rootKey + static_cast<float>(scaleArray.at(i) + scaleOffset) - 69) / 12))));
		scaleOffset += scaleArray[i];
	}
}

//Calculate the correct amplitude given a position in the sample for a given wave type.
float WaveGenerator::WaveFunc(float pos, int waveType)
{
	//sine wave
	if (waveType == 1)
		return sin(pos * 2 * 3.14);

	//triangle wave
	else if (waveType == 2)
		return 1 - fabs(pos - 0.5) * 4;

	//square wave
	else if (waveType == 3)
		return (sin(pos * 3.14 * 2) > 0) ? 1.0 : -1.0;

	//saw wave
	else if (waveType == 4)
		return pos * 2 - 1;

	else
		return -1.0;
}

//Calculate the beat time for the attack and release time for the note envelope
void WaveGenerator::RampSamples(vector<sf::Int16>& sample, float frac)
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
void WaveGenerator::fillMajorArray(vector<int>& scaleArray, char key)
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
int WaveGenerator::CheckKeyValue(int rootKey, char& character)
{
	if ((rootKey - 21) % 12 == 0)
		character = 'a';
	else if ((rootKey - 23) % 12 == 0)
		character = 'b';
	else if ((rootKey - 24) % 12 == 0)
		character = 'c';
	else if ((rootKey - 26) % 12 == 0)
		character = 'd';
	else if ((rootKey - 28) % 12 == 0)
		character = 'e';
	else if ((rootKey - 29) % 12 == 0)
		character = 'f';
	else if ((rootKey - 31) % 12 == 0)
		character = 'g';
	else
	{
		cout << "\n\nINVALID KEY VALUE: " << rootKey << ". Enter a valid MIDI note between 21-115! ";
		return 0;
	}
	return 1;
}

// Randomize a frequency, generate a random wave and store in a buffer
void WaveGenerator::GenerateRandomWave(float frequency, sf::SoundBuffer &Wave)
{
    vector<sf::Int16> buffer;

    // Create random BPM for wave
    // EXTERNAL CITATION: https://stackoverflow.com/questions/686353/random-float-number-generation
    srand(static_cast <unsigned> (time(0)));
    float randBPM = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/240-1));
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