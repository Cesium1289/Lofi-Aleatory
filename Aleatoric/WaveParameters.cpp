#include "WaveParameters.h"
#include<iostream>
#include <string>
WaveParameters::WaveParameters()
{
	parameters.waveTypeAmp = 3.0f;
	parameters.squareWaveAmp = 3.0f;
	parameters.rootKey = 57;
	parameters.beatsPerMeasure = 8;
	parameters.beatsPerMinute = 240.0f;
	parameters.ramp = 0.5f;
	parameters.accent = 5.0f;
	parameters.volume = 8.0f;
	parameters.key = 'a';
	parameters.waveType = sine;
}

WaveParameters::WaveParameters(const WaveParameters& copy)
{
	parameters.waveTypeAmp = copy.parameters.waveTypeAmp;
	parameters.squareWaveAmp = copy.parameters.squareWaveAmp;
	parameters.sig = copy.parameters.sig;
	parameters.rootKey = copy.parameters.rootKey;
	parameters.beatsPerMeasure = copy.parameters.beatsPerMeasure;
	parameters.ramp = copy.parameters.ramp;
	parameters.accent = copy.parameters.accent;
	parameters.volume = copy.parameters.volume;
	parameters.key = copy.parameters.key;
	parameters.waveType = copy.parameters.waveType;
	
}

void WaveParameters::setRootKey(float rootKey)
{
	parameters.rootKey = rootKey;
}

void WaveParameters::setBPM(float bpm)
{
	parameters.beatsPerMinute = bpm;
}

void WaveParameters::setVolume(float vol)
{
	parameters.volume = vol;
}

void WaveParameters::setRamp(float ramp)
{
	parameters.ramp = ramp;
}

void WaveParameters::setWaveType(const std::string& type)
{
	if (type == "sine")
		parameters.waveType = sine;
	else if (type == "square")
		parameters.waveType = square;
	else if (type == "saw")
		parameters.waveType = saw;
	else if (type == "triangle")
		parameters.waveType = triangle;
	else
		std::cout << "Invalid wave type";
}

void WaveParameters::setScaleType(const std::string& type)
{
	if (type == "major")
		parameters.scale = 1;
	else if (type == "minor")
		parameters.scale = 2;
	else if (type == "pent")
		parameters.scale = 3;
	else
		std::cout << "Invalid scale type. Enter either 'major' or 'minor'";
}

void WaveParameters::setRandom()
{
	parameters.random = true;
}

