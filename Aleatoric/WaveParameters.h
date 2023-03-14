#ifndef WaveParamters_H
#define WaveParamters_H
#include<map>
#include <string>
#include<vector>
#include<SFML/Audio.hpp>

using std::string;
using std::vector;

enum waveEnum {
	sine,
	triangle,
	square,
	saw
};

class WaveParameters
{
	friend class WaveGenerator;
	public:
		WaveParameters();
		bool AreValidParameters()const;
		bool SetRootKeyCharacter(int val);
		bool ParseArguments(int argc, char* argv[]);
		float ParseStringToFloat(string& arg);
		int ParseStringToInt(string& arg);
		void ParseStringToString(string& arg);
		void GenerateRandomWave(float frequency, sf::SoundBuffer& Wave);
		void GenerateRandomParameters();
		void GenerateRandomRootKeyAndKey();
		void GenerateRandomBeatsPerMinute();
		void GenerateRandomRamp();
		void GenerateRandomWaveType();
		void setRootKey(int);
		void setBPM(float);
		void setVolume(float);
		void setRamp(float);
		void setWaveType(const std::string&);
		void setScaleType(const std::string&);
		void setRandom(bool);
		float GetRamp();
		float GetBPM();
		void RampSamples(vector<sf::Int16>& sample, float frac);
		float WaveFunc(float pos, int type);
		void display();
		int TestAddMethod(int a, int b);
	private:
		struct Parameters
		{
			int rootKey;
			float beatsPerMinute;
			float ramp;
			float volume;
			char key;
			int scale;
			waveEnum waveType;
			bool random;
		};
	
		Parameters parameters;
		std::multimap<const char, int> MidiKeyMap;
		void MapMidiValues();
		bool IsValidBeatsPerMinute(float val)const;
		bool IsValidRamp(float val)const;
		bool IsValidAccent(float val)const;
		bool IsValidVolume(float val)const;
		bool IsValidRootKey(int val)const;
};
#endif