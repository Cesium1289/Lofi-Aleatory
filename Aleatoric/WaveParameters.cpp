#include "WaveParameters.h"
#include<iostream>
const int MIN_BEATS_PER_MEASURE = 1;
const float MIN_BEATS_PER_MINUTE = 0.1f;
const float MAX_RAMP = 0.5f;
const float MAX_VOLUME = 10.0f;
const float MAX_ACCENT = 10.0f;

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

	MapMidiValues();
}

bool WaveParameters::AreValidParameters()const
{
	return(IsValidRootKey(parameters.rootKey) &&
		IsValidBeatsPerMeasure(parameters.beatsPerMeasure) &&
		IsValidBeatsPerMinute(parameters.beatsPerMinute) &&
		IsValidRamp(parameters.ramp) &&
		IsValidAccent(parameters.accent) &&
		IsValidVolume(parameters.volume));
}
void WaveParameters::MapMidiValues()
{
	MidiKeyMap = { {'a', 21},{'a',33},{'a', 45},{'a',57},{'a', 69},{'a',81},{'a',93},{'a',105},
					   {'b', 23},{'b',35},{'b', 47},{'b',59},{'b', 71},{'b',83},{'b',95},{'b',107},
					   {'c', 24},{'c',36},{'c', 48},{'c',60},{'c', 72},{'c',84},{'c',96},{'c',108},
					   {'d', 26},{'d',38},{'d', 50},{'d',62},{'d', 74},{'d',86},{'d',98},{'d',110},
					   {'e', 28},{'e',40},{'e', 52},{'e',64},{'e', 76},{'e',88},{'e',100},{'e',112},
					   {'f', 29},{'f',41},{'f', 53},{'f',65},{'f', 77},{'f',89},{'f',101},{'f',113},
					   {'g', 31},{'g',43},{'g', 55},{'g',67},{'g', 79},{'g',91},{'g',103},{'g',115}
	};
}

//Checks whether or no 'val' is in the MidiKeyMap.
//Returns true if it was able to find the value, false if it was not
bool WaveParameters::IsValidRootKey(int val) const
{
	for (auto& it : MidiKeyMap)
	{
		if (it.second == val)
			return true;
	}
	std::cerr << "ERROR: invalid root key value of " << val << "! Enter a valid MIDI note between 21-115! ";
	return false;
}

bool WaveParameters::IsValidBeatsPerMeasure(int val)const
{
	if (val >= MIN_BEATS_PER_MEASURE)
		return true;
	std::cerr << "ERROR: invalid beats per measure value of " << val << "! Enter beats per measure value greater than "<< MIN_BEATS_PER_MEASURE <<"!\n";
	return false;
}

bool WaveParameters::IsValidBeatsPerMinute(float val)const
{
	if (val >= MIN_BEATS_PER_MINUTE)
		return true;
	std::cerr << "ERROR: invalid beats per minute value of " << val << "! Enter beats per minute value greater than" << MIN_BEATS_PER_MINUTE << "!\n";
	return false;
}

bool WaveParameters::IsValidRamp(float val)const
{
	if (val >= 0.0f && val <= MAX_RAMP)
		return true;
	std::cerr << "ERROR: invalid ramp value of " << val << "! Enter ramp value between 0.0 and " << MAX_RAMP <<"!\n";
	return false;

}

bool WaveParameters::IsValidAccent(float val)const
{
	if (val >= 0.0f && val <= MAX_ACCENT)
		return true;
	std::cerr << "ERROR: invalid accent value of " << val << "! Enter accent value between 0.0 and " << MAX_ACCENT << "!\n";
	return false;

}

bool WaveParameters::IsValidVolume(float val)const
{
	if (val >= 0.0f && val <= MAX_VOLUME)
		return true;
	std::cerr << "ERROR: invalid volume value of " << val << "! Enter volume value between 0.0 and 10.0!\n";
	return false;
}

//Sets the key parameter based on the value of 'val. If it is found, returns
//true, else it returns false
bool WaveParameters::SetRootKeyCharacter(int val)
{
	for (auto& it : MidiKeyMap)
	{
		if (it.second == val)
		{
			parameters.key = it.first;
			std::cout << parameters.key << std::endl;
			return true;
		}
	}
	return false;
}

