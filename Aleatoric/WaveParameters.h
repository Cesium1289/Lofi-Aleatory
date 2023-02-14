#include<map>
enum waveEnum { sine, saw, triangle, square };
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
			int rootKey = 45;
			int beatsPerMeasure = 8;
			float beatsPerMinute = 20.0f;
			float ramp = 0.5f;
			float accent = 5.0f;
			float volume = 8.0f;
			char key = 'a';
			waveEnum waveType = waveEnum::sine;
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
		
};

