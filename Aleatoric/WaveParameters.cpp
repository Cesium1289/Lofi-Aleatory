#include "WaveParameters.h"
#include<iostream>
WaveParameters::WaveParameters()
{
	parameters.waveTypeAmp = 3.0f;
	parameters.squareWaveAmp = 3.0f;
	parameters.sineWaveAmp = 3.0f;
	parameters.triangleWaveAmp = 3.0f;
	parameters.sawWaveAmp = 3.0f;
	parameters.rootKey = 45;
	parameters.beatsPerMeasure = 8;
	parameters.beatsPerMinute = 120.0f;
	parameters.ramp = 0.5f;
	parameters.accent = 5.0f;
	parameters.volume = 8.0f;
	parameters.key = 'a';
	parameters.waveType = sine;
}


//Get amplitued based on given type of wave.
float WaveParameters::GetAmp(waveEnum waveType)
{
	if (waveType == sine) {
		return parameters.sineWaveAmp;
	}
	else if (waveType == square) {
		return parameters.squareWaveAmp;
	}
	else if (waveType == triangle) {
		return parameters.triangleWaveAmp;
	}
	else if (waveType == saw) {
		return parameters.sawWaveAmp;
	}
	else {
		return -1.0f;
	}
}

//Get ramp factor
float WaveParameters::GetRamp()
{
	return parameters.ramp;
}

//Get beats per minute
float WaveParameters::GetBPM()
{
	return parameters.beatsPerMinute;
}

