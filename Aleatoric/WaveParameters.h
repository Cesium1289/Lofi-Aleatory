#include<map>

enum waveEnum {
	sine = 1,
	triangle = 2,
	square = 3,
	saw = 4
};

class WaveParameters
{
	public:
		WaveParameters();
		bool AreValidParameters()const;
		bool SetRootKeyCharacter(int val);
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
			bool random = true;
		};
		Parameters parameters;
		std::multimap<const char, int> MidiKeyMap;

		void MapMidiValues();
		bool IsValidBeatsPerMeasure(int val)const;
		bool IsValidBeatsPerMinute(float val)const;
		bool IsValidRamp(float val)const;
		bool IsValidAccent(float val)const;
		bool IsValidVolume(float val)const;
		bool IsValidRootKey(int val)const;

		void setRootKey(float);
		void setBPM(float);
		void setVolume(float);
		void setRamp(float);
		void setWaveType(const std::string&);
		void setScaleType(const std::string&);
		void setRandom();
		
};

