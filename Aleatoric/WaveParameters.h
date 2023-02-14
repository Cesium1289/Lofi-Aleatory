#pragma once
#include <string>

enum waveEnum { 
	sine = 1, 
	triangle = 2,
	square = 3,
	saw = 4
};
class WaveParameters
{
	friend class WaveGenerator;
	private:
		struct Parameters
		{
			float waveTypeAmp = 5.0f;
			float squareWaveAmp = 5.0f;
			int sig = 8;
			int rootKey = 52;
			int beatsPerMeasure = 8;
			float beatsPerMinute = 120.0f;
			float ramp = 0.5f;
			float accent = 5.0f;
			float volume = 8.0f;
			char key = 'a';
			int scale = 1;
			waveEnum waveType = sine;
			bool random = false;
		};

	public:
		WaveParameters();
		WaveParameters(WaveParameters const &);
		void setRootKey(float);
		void setBPM(float);
		void setVolume(float);
		void setRamp(float);
		void setWaveType(const std::string&);
		void setScaleType(const std::string&);
		void setRandom();
		Parameters parameters;

};

