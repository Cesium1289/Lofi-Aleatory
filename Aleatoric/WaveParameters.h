enum waveEnum { sine, saw, triangle, square };
class WaveParameters
{
	public:
		WaveParameters();

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
			waveEnum waveType = sine;
		};
		Parameters parameters;
};

