#ifndef WaveGenerator_H
#define WaveGenerator_H
#include<SFML/Audio.hpp>
#include "WaveParameters.h"
using namespace std;

class WaveGenerator
{
public:
	void playWave(WaveParameters&);
private:
	void GenerateSawWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);
	void GenerateSineWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);
	void GenerateSquareWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);
	void GenerateTriangleWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);
	float GenerateAmplitude(float volume);
	void GenerateWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);

	void CalculateFrequency(float freqArray[], vector<int>& scaleArray, int rootKey);
	float WaveFunc(float pos, int type);
	void RampSamples(vector<sf::Int16>& sample, float frac);
	void fillMajorArray(vector<int>& scaleArray, char key);
	int CheckKeyValue(int rootKey, char& character);
    void GenerateRandomWave(float frequency, sf::SoundBuffer& Wave);
};
#endif
