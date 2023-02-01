#include "WaveParameters.h"
#include<iostream>
WaveParameters::WaveParameters()
{
	parameters.waveTypeAmp = 0.0f;
	parameters.squareWaveAmp = 0.0f;
	parameters.rootKey = 45;
	parameters.beatsPerMeasure = 8;
	parameters.beatsPerMinute = 20.0f;
	parameters.ramp = 0.5f;
	parameters.accent = 5.0f;
	parameters.volume = 8.0f;
	parameters.key = 'a';
	parameters.waveType = sine;
}