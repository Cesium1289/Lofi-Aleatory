#include"WaveParameters.h"
#include"WaveGenerator.h"

int main(int argc, char* argv[])
{
	sf::SoundBuffer sound;
	WaveParameters params;
	WaveGenerator wave;

	if (params.ParseArguments(argc, argv))
	{
		wave.playWave(params);
	}
}