#include<map>
enum waveEnum { sine, saw, triangle, square };
class WaveParameters
{
	friend class WaveGenerator;
	public:
		WaveParameters();
		bool AreValidParameters()const;
		bool SetRootKeyCharacter(int val);

	private:
		struct Parameters
		{
			float waveTypeAmp = 5.0f;
			float sineWaveAmp = 5.0f;
			float squareWaveAmp = 5.0f;
			float triangleWaveAmp = 5.0f;
			float sawWaveAmp = 5.0f;
			int sig = 8;
			int rootKey = 45;
			int beatsPerMeasure = 8;
			float beatsPerMinute = 120.0f;
			float ramp = 0.5f;
			float accent = 5.0f;
			float volume = 8.0f;
			char key = 'a';
			waveEnum waveType = waveEnum::sine;
		};

	public:
		WaveParameters();
		float GetAmp(waveEnum);
		float GetRamp();
		float GetBPM();

		Parameters parameters;

		std::multimap<const char, int> MidiKeyMap;

		void MapMidiValues();
		bool IsValidBeatsPerMeasure(int val)const;
		bool IsValidBeatsPerMinute(float val)const;
		bool IsValidRamp(float val)const;
		bool IsValidAccent(float val)const;
		bool IsValidVolume(float val)const;
		bool IsValidRootKey(int val)const;
		

};

