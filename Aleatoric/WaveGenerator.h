#pragma once
#include<SFML/Audio.hpp>
#include "WaveParameters.h"
using namespace std;

class WaveGenerator
{
public:
	void playWave(WaveParameters&);
private:

	void CalculateFrequency(float freqArray[], vector<int>& scaleArray, int rootKey);

	float WaveFunc(float pos, int type);

	void GenerateWave(float freq, sf::SoundBuffer& Wave, WaveParameters& args, int waveType);

	void SetAmplitudes(WaveParameters& args);

	void RampSamples(vector<sf::Int16>& sample, float frac);
	
	void fillMajorArray(vector<int>& scaleArray, char key);

	int CheckKeyValue(int rootKey, char& character);

    void GenerateRandomWave(float frequency, sf::SoundBuffer& Wave);

};

