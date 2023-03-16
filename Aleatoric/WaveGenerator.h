#ifndef WaveGenerator_H
#define WaveGenerator_H
#include<SFML/Audio.hpp>
#include "WaveParameters.h"
using std::vector;

class WaveGenerator
{
public:
	void playWave(WaveParameters& args, sf::SoundBuffer& lofiSample);
	void stopWave(sf::Sound& sound);
private:
	sf::SoundBuffer lofiSample;
	sf::Sound sound;
	void GenerateSawWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);
	void GenerateSineWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);
	void GenerateSquareWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);
	void GenerateTriangleWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);
	float GenerateAmplitude(float volume);
	void GenerateWave(WaveParameters& params, float freq, sf::SoundBuffer& buffer);
	void CalculateFrequency(vector<float>& freqArray, vector<int>& scaleArray, int rootKey);
	void RampSamples(vector<sf::Int16>& sample, float frac);
	void fillMajorArray(vector<int>& scaleArray, char key);
	int CheckKeyValue(int rootKey, char& character);
};
#endif
