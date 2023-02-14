#pragma once
#define _USE_MATH_DEFINES

#include "WaveGenerator.h"
#include<SFML/Audio.hpp>
#include<iostream>
#include<cmath>
#include<cstdlib>
using namespace std;

const int NUM_SAMPLES = 48000;
const int NUM_KEYS = 8;

void WaveGenerator::play(WaveParameters& args)
{

	vector<int> scaleArray;
	float freqArray[NUM_KEYS];
	sf::SoundBuffer Samples[NUM_KEYS];
	sf::Sound sound;

	GenerateSequence(Samples, args);

	int i = 0;
	while (1)
	{
		//check if sound is playing
		while (sound.getStatus() == sf::Sound::Playing)
			sf::sleep(sf::milliseconds(100));

		if (args.parameters.random)
			sound.setBuffer(Samples[rand() % NUM_KEYS]);
		else
			sound.setBuffer(Samples[i % NUM_KEYS]);

		sound.play();

		++i;
	}
}

//Generate the sequence of notes to be played 
void WaveGenerator::GenerateSequence(sf::SoundBuffer * samples, WaveParameters& args)
{

	vector<int> scaleArray;
	float freqArray[NUM_KEYS];

	WaveParameters::Parameters param = args.parameters;
	SetAmplitudes(args);
	CheckKeyValue(param.rootKey, param.key);
	fillScaleArray(scaleArray, param.scale);
	CalculateFrequency(freqArray, scaleArray, param.rootKey);

	for (int i = 0; i < NUM_KEYS; i++) {
		GenerateWave(freqArray[i], samples[i], args, param.waveType);
	}

}

//Calculate the frequencies in a scale starting from root note
void WaveGenerator::CalculateFrequency(float freqArray[], vector<int>& scaleArray, int rootKey)
{
	int scaleOffset = 0;

	for (size_t i = 0; i < NUM_KEYS; i++)
	{
		int pos = i % scaleArray.size() ;
		freqArray[i] = 440 * static_cast<float>(pow(2.0, ((rootKey + static_cast<float>(scaleArray.at(pos) + scaleOffset) - 69) / 12)));
		scaleOffset += scaleArray[pos];
	}
}

//Calculate the correct amplitude given a position in the sample for a given wave type.
float WaveGenerator::WaveFunc(float pos, int waveType)
{
	//sine wave
	if (waveType == 1)
		return sin(pos * 2 * M_PI);

	//triangle wave
	else if (waveType == 2)
		return 1 - fabs(pos - 0.5) * 4;

	//square wave
	else if (waveType == 3)
		return (sin(pos * M_PI * 2) > 0) ? 1.0 : -1.0;

	//saw wave
	else if (waveType == 4)
		return pos * 2 - 1;

	else
		return -1.0;
}


//Given a type of wave and a frequency, generate a wave and store in a buffer
void WaveGenerator::GenerateWave(float frequency, sf::SoundBuffer& Wave, WaveParameters& args, int waveType) {

	vector<sf::Int16> buffer;
	WaveParameters::Parameters param = args.parameters;

	for (size_t i = 0; i < NUM_SAMPLES; i++) {
		float pos = fmod((static_cast<float>(i) * frequency) / NUM_SAMPLES, 1.0);
		buffer.push_back(10000 * WaveFunc(pos, waveType) * param.waveTypeAmp);
	}

	//ramp the sample
	RampSamples(buffer, param.ramp);

	//place sample into wave buffer
	Wave.loadFromSamples(&buffer[0], buffer.size(), 1, NUM_SAMPLES * (param.beatsPerMinute / 60));

}

//Set the amplitudes for the square and sine waves based on volume levels
void WaveGenerator::SetAmplitudes(WaveParameters& args)
{
	WaveParameters::Parameters param = args.parameters;
	param.squareWaveAmp = pow(10, (-6 * (10 - param.accent) / 20));
	param.waveTypeAmp = pow(10, (-6 * (10 - param.volume) / 20));
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

//Fill the scaleVector with the proper key offsets
//depending on type of scale (major, minor)
void WaveGenerator::fillScaleArray(vector<int>& scaleArray, int scaleType)
{
	switch (scaleType)
	{
		//major scale
		case(1):
			scaleArray.insert(scaleArray.end(), { 0,2,2,1,2,2,2,1 });
			break;
		//minor scale
		case(2):
			scaleArray.insert(scaleArray.end(), { 0,2,1,2,2,1,2,2 });
			break;
		//pentatonic scale
		case(3):
			scaleArray.insert(scaleArray.end(), { 0,2,3,2,2,3 });
			break;
		default:
			cout << "ERROR: unable to generate major array\n";
			break;
	}
}

//Fill the scaleVector with the proper key offsets so a proper frequency can be acquired for 
//each key
//void WaveGenerator::fillMajorArray(vector<int>& scaleArray, char key)
//{
//	switch (key)
//	{
//	case('a'):
//		scaleArray.insert(scaleArray.end(), { 0,2,1,2,2,1,2,2 });
//		break;
//	case('b'):
//		scaleArray.insert(scaleArray.end(), { 0,1,2,2,1,2,2,2 });
//		break;
//	case('c'):
//		scaleArray.insert(scaleArray.end(), { 0,2,2,1,2,2,2,1 });
//		break;
//	case('d'):
//		scaleArray.insert(scaleArray.end(), { 0,2,1,2,2,2,1,2 });
//		break;
//	case('e'):
//		scaleArray.insert(scaleArray.end(), { 0,1,2,2,2,1,2,2 });
//		break;
//	case('f'):
//		scaleArray.insert(scaleArray.end(), { 0,2,2,2,1,2,2,1 });
//		break;
//	case('g'):
//		scaleArray.insert(scaleArray.end(), { 0,2,2,1,2,2,1,2 });
//		break;
//	default:
//		cout << "ERROR: unable to generate major array\n";
//		break;
//	}
//}



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