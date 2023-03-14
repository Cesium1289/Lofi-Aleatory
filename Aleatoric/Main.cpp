#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include"WaveParameters.h"
#include "Gui/Theme.hpp"
#include"WaveParameters.h"
#include"WaveGenerator.h"
#include "Gui/Gui.hpp"
using namespace std;

int main(int argc, char** argv)
{
	sf::SoundBuffer soundBuffer;
	sf::Sound sounds;
	WaveParameters params;
	WaveGenerator wave;
	bool randomize = false;
	bool playing = false;

	// Create the main window
	sf::RenderWindow app(sf::VideoMode(1200, 840), "Lofi-Aleatory", sf::Style::Close);
	app.setFramerateLimit(30);

	gui::Menu menu(app);
	menu.setPosition(0, 0);

	gui::Theme::loadFont("Assets/Georama-Semibold.ttf");
	gui::Theme::textSize = 65;
	gui::Theme::PADDING = 40.0f;
	gui::Theme::MARGIN = 10.0f;
	gui::Theme::windowBgColor = sf::Color(210, 230, 240, 255);

	//Title and description text
	gui::HBoxLayout* titleAndDescription = menu.addHBoxLayout();
	sf::Texture titleCardTexture;
	titleCardTexture.loadFromFile("Assets/title.png");
	gui::Image* titleCard = new gui::Image(titleCardTexture);
	sf::Texture descriptionCardTexture;
	descriptionCardTexture.loadFromFile("Assets/description.png");
	gui::Image* descriptionCard = new gui::Image(descriptionCardTexture);
	titleAndDescription->add(titleCard);
	titleAndDescription->add(descriptionCard);

	

	//Main interface
	gui::HBoxLayout* main = menu.addHBoxLayout();
	gui::VBoxLayout* col1 = main->addVBoxLayout();
	gui::VBoxLayout* col2 = main->addVBoxLayout();
	gui::VBoxLayout* col3 = main->addVBoxLayout();




	// Slider for root
	gui::HBoxLayout* rootSelector = col3->addHBoxLayout();
	gui::Slider* rootSlider = new gui::Slider(288.0f, gui::Horizontal);
	rootSlider->setStep(1);
	rootSlider->setValue(25);
	rootSlider->setCallback([&]() {
		int input = rootSlider->getValue() * 0.94 + 21;
		params.setRootKey(input);
		params.SetRootKeyCharacter(input);
	params.display();
		});

	sf::Texture rootLabelTexture;
	rootLabelTexture.loadFromFile("Assets/labels-10.png");
	gui::Image* rootLabel = new gui::Image(rootLabelTexture);

	rootSelector->add(rootLabel);
	rootSelector->add(rootSlider);




	// Slider for ramp
	gui::HBoxLayout* rampSelector = col3->addHBoxLayout();
	gui::Slider* rampSlider = new gui::Slider(288.0f, gui::Horizontal);
	rampSlider->setStep(1);
	rampSlider->setValue(100);
	rampSlider->setCallback([&]() {
		params.setRamp(rampSlider->getValue() * 0.005f);
	params.display();
		});

	sf::Texture rampLabelTexture;
	rampLabelTexture.loadFromFile("Assets/labels-07.png");
	gui::Image* rampLabel = new gui::Image(rampLabelTexture);

	rampSelector->add(rampLabel);
	rampSelector->add(rampSlider);


	// Slider for BMP
	gui::HBoxLayout* bpmSelector = col3->addHBoxLayout();
	gui::Slider* bpmSlider = new gui::Slider(288.0f, gui::Horizontal);
	bpmSlider->setStep(1);
	bpmSlider->setCallback([&]() {
		params.setBPM(bpmSlider->getValue() * 2.2 + 20);
	params.display();
		});

	sf::Texture bpmLabelTexture;
	bpmLabelTexture.loadFromFile("Assets/labels-08.png");
	gui::Image* bpmLabel = new gui::Image(bpmLabelTexture);

	bpmSelector->add(bpmLabel);
	bpmSelector->add(bpmSlider);


	// Slider for Volume
	gui::HBoxLayout* volSelector = col3->addHBoxLayout();
	gui::Slider* volSlider = new gui::Slider(288.0f, gui::Horizontal);
	volSlider->setStep(1);
	volSlider->setValue(80);
	volSlider->setCallback([&]() {
		params.setVolume(volSlider->getValue() * 0.1);
	params.display();
		});

	sf::Texture volLabelTexture;
	volLabelTexture.loadFromFile("Assets/labels-09.png");
	gui::Image* volLabel = new gui::Image(volLabelTexture);

	volSelector->add(volLabel);
	volSelector->add(volSlider);

	//Play button
	sf::Texture playButtonBackground;
	playButtonBackground.loadFromFile("Assets/playButtonSprites.png");
	gui::SpriteButton* playButton = new gui::SpriteButton(playButtonBackground);
	col2->add(playButton);
	playButton->setCallback([&]
		{
			if (sounds.getStatus() != sf::Sound::Playing)
			playing = true;
		});

	//Stop button
	sf::Texture stopButtonBackground;
	sf::Texture stopButtonActive;
	bool isStop = false;
	sf::Texture random;
	stopButtonBackground.loadFromFile("Assets/stopButtonSprites.png");
	stopButtonActive.loadFromFile("Assets/randomButtonSprites.png");
	gui::SpriteButton* stopButton = new gui::SpriteButton(stopButtonBackground);
	col2->add(stopButton);
	stopButton->setCallback([&]()
		{
			playing = false;
			stopButton->toggleTexture(stopButtonBackground);
			wave.stopWave(sounds);
		}
	);


	//Randomize button
	sf::Texture randomButtonBackground;
	randomButtonBackground.loadFromFile("Assets/randomButtonSprites.png");
	gui::SpriteButton* randomButton = new gui::SpriteButton(randomButtonBackground);
	randomButton->setTextSize(10);
	col2->add(randomButton);
	randomButton->setCallback([&] {
		std::cout << "click!" << std::endl;
	randomize = !randomize;
	params.setRandom(randomize);
	params.display();
		});

	sf::Texture toolTipCardTexture;
	toolTipCardTexture.loadFromFile("Assets/toolTipSprites.png");
	gui::Image* toolTipCard = new gui::Image(toolTipCardTexture);
	col2->add(toolTipCard);



	// Sine wave button
	sf::Texture sineWaveBackground;
	sineWaveBackground.loadFromFile("Assets/sineWaveSprite.png");
	gui::SpriteButton* sineWaveButton = new gui::SpriteButton(sineWaveBackground);
	sineWaveButton->setTextSize(10);
	col1->add(sineWaveButton);
	sineWaveButton->setCallback([&] {
		sineWaveButton->toggleTexture(sineWaveBackground);
	params.setWaveType("sine");
	params.display();
		});

	//Square wave button
	sf::Texture squareWaveBackground;
	squareWaveBackground.loadFromFile("Assets/squareWaveSprite.png");
	gui::SpriteButton* squareWaveButton = new gui::SpriteButton(squareWaveBackground);
	squareWaveButton->setTextSize(10);
	col1->add(squareWaveButton);
	squareWaveButton->setCallback([&] {
	params.setWaveType("square");
	params.display();
		});

	//Saw wave button
	sf::Texture sawWaveBackground;
	sawWaveBackground.loadFromFile("Assets/sawWaveSprite.png");
	gui::SpriteButton* sawWaveButton = new gui::SpriteButton(sawWaveBackground);
	sawWaveButton->setTextSize(10);
	col1->add(sawWaveButton);
	sawWaveButton->setCallback([&] {
	params.setWaveType("saw");
	params.display();
		});

	//Triangle wave button
	sf::Texture triangleWaveBackground;
	triangleWaveBackground.loadFromFile("Assets/triangleWaveSprite.png");
	gui::SpriteButton* triangleWaveButton = new gui::SpriteButton(triangleWaveBackground);
	triangleWaveButton->setTextSize(10);
	col1->add(triangleWaveButton);
	triangleWaveButton->setCallback([&] {
	params.setWaveType("triangle");
	params.display();
		});

	// Start the application loop
	while (app.isOpen())
	{
		// Process events
		sf::Event event;
		while (app.pollEvent(event))
		{
			// Send events to menu
			menu.onEvent(event);
			if (event.type == sf::Event::Closed)
				app.close();
		}

		// Clear screen
		app.clear(gui::Theme::windowBgColor);
		app.draw(menu);
		// Update the window
		while (playing && sounds.getStatus() != sf::Sound::Playing)
		{
			wave.playWave(params, soundBuffer);
			sounds.setBuffer(soundBuffer);
			sounds.play();
		}
		app.display();
	}

	return EXIT_SUCCESS;
}

