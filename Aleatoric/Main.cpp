#include<SFML/Audio.hpp>
#include<iostream>
#include"WaveGenerator.h"
#include <string>
using namespace std;

bool ParseArguments(WaveParameters & param, int argc,const char* argv[]);
float ParseSubString(string& arg);
void ParseStringToString(string& arg);

int main(int argc, const char* argv[])
{
	WaveParameters args;
	ParseArguments(args, argc, argv);
	WaveGenerator soundBox;
	soundBox.play(args);
}

bool ParseArguments(WaveParameters & param, int argc, const char* argv[])
{
	string* argvArray = new string[argc];
	for (size_t i = 0; i < argc; i++)
	{
		argvArray[i] = argv[i];
		cout << argvArray[i];
	}

	for (size_t i = 1; i < argc; i++) {
		if (!argvArray[i].find("--root"))
		{
			param.setRootKey(ParseSubString(argvArray[i]));
		}
		
		else if (!argvArray[i].find("--bpm"))
		{
			param.setBPM(ParseSubString(argvArray[i]));

		}
		else if (!argvArray[i].find("--volume"))
		{
			param.setVolume(ParseSubString(argvArray[i]));

		}
		else if (!argvArray[i].find("--ramp"))
		{
			param.setRamp(ParseSubString(argvArray[i]));
			cout << argvArray[i];

		}
		else if (!argvArray[i].find("--wave"))
		{
			ParseStringToString(argvArray[i]);
			param.setWaveType(argvArray[i]);
		}
		else if (!argvArray[i].find("--scale"))
		{
			ParseStringToString(argvArray[i]);
			param.setScaleType(argvArray[i]);
		}
		else if (!argvArray[i].find("--random"))
		{
			param.setRandom();
		}
		else
		{
			cout << "ERORR: invalid argument " << argv[i] << endl;
			cout << "Closing program... \n";
		}
	}

	return true;
}

float ParseSubString(string& arg)
{
	size_t pos = arg.find("[");
	arg.erase(0, pos + 1);
	pos = arg.find("]");
	arg.erase(pos);

	try {
		return stof(arg);
	}
	catch (invalid_argument const& error)
	{
		cout << "Invalid parameter value: " << error.what() << endl;
		return -1.0;
	}
}

void ParseStringToString(string& arg)
{
	size_t pos = arg.find("[");
	arg.erase(0, pos + 1);
	pos = arg.find("]");
	arg.erase(pos);
}