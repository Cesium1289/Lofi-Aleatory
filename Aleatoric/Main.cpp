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
	sf::RenderWindow app(sf::VideoMode(1210, 840), "Lofi-Aleatory", sf::Style::Close);
	app.setFramerateLimit(60);

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

	
	sf::Texture emptyButtonTexture;
	emptyButtonTexture.loadFromFile("Assets/emptyButtonSprite.png");
	gui::SpriteButton* activeWaveButton = new gui::SpriteButton(emptyButtonTexture, emptyButtonTexture);

	//Main interface
	gui::HBoxLayout* main = menu.addHBoxLayout();
	gui::VBoxLayout* col1 = main->addVBoxLayout();
	gui::VBoxLayout* col2 = main->addVBoxLayout();
	gui::VBoxLayout* col3 = main->addVBoxLayout();

	//---- Column 1 buttons: Wave Selector ----//

	// Sine wave button
	sf::Texture sineWaveBackground;
	sf::Texture sineWaveActiveBackground;
	sineWaveBackground.loadFromFile("Assets/sineWaveSprite.png");
	sineWaveActiveBackground.loadFromFile("Assets/sineWaveActiveSprite.png");
	gui::SpriteButton* sineWaveButton = new gui::SpriteButton(sineWaveBackground, sineWaveActiveBackground);
	sineWaveButton->setTextSize(10);
	col1->add(sineWaveButton);
	

	//Square wave button
	sf::Texture squareWaveBackground;
	sf::Texture squareWaveActiveBackground;
	squareWaveBackground.loadFromFile("Assets/squareWaveSprite.png");
	squareWaveActiveBackground.loadFromFile("Assets/squareWaveActiveSprite.png");
	gui::SpriteButton* squareWaveButton = new gui::SpriteButton(squareWaveBackground, squareWaveActiveBackground);
	squareWaveButton->setTextSize(10);
	col1->add(squareWaveButton);
	

	//Saw wave button
	sf::Texture sawWaveBackground;
	sf::Texture sawWaveActiveBackground;
	sawWaveBackground.loadFromFile("Assets/sawWaveSprite.png");
	sawWaveActiveBackground.loadFromFile("Assets/sawWaveActiveSprite.png");
	gui::SpriteButton* sawWaveButton = new gui::SpriteButton(sawWaveBackground, sawWaveActiveBackground);
	sawWaveButton->setTextSize(10);
	col1->add(sawWaveButton);
	

	//Triangle wave button
	sf::Texture triangleWaveBackground;
	sf::Texture triangleWaveActiveBackground;
	triangleWaveBackground.loadFromFile("Assets/triangleWaveSprite.png");
	triangleWaveActiveBackground.loadFromFile("Assets/triangleWaveActiveSprite.png");
	gui::SpriteButton* triangleWaveButton = new gui::SpriteButton(triangleWaveBackground, triangleWaveActiveBackground);
	triangleWaveButton->setTextSize(10);
	col1->add(triangleWaveButton);
	

	//---- Column 2 buttons: Sound control ----//

	//Play button
	sf::Texture playButtonBackground;
	sf::Texture playButtonActiveBackground;
	playButtonBackground.loadFromFile("Assets/playButtonSprites.png");
	playButtonActiveBackground.loadFromFile("Assets/playButtonActiveSprites.png");
	gui::SpriteButton* playButton = new gui::SpriteButton(playButtonBackground, playButtonActiveBackground);

	//Stop button
	sf::Texture stopButtonBackground;
	sf::Texture stopButtonActiveBackground;
	stopButtonBackground.loadFromFile("Assets/stopButtonSprites.png");
	stopButtonActiveBackground.loadFromFile("Assets/stopButtonActiveSprites.png");
	gui::SpriteButton* stopButton = new gui::SpriteButton(stopButtonBackground, stopButtonActiveBackground);

	//Randomize button
	sf::Texture randomButtonBackground;
	sf::Texture randomButtonActiveBackground;
	randomButtonBackground.loadFromFile("Assets/randomButtonSprites.png");
	randomButtonActiveBackground.loadFromFile("Assets/randomButtonActiveSprites.png");
	gui::SpriteButton* randomButton = new gui::SpriteButton(randomButtonBackground, randomButtonActiveBackground);

	col2->add(playButton);
	col2->add(stopButton);
	col2->add(randomButton);
	

	sf::Texture toolTipCardTexture;
	toolTipCardTexture.loadFromFile("Assets/toolTipSprites.png");
	gui::Image* toolTipCard = new gui::Image(toolTipCardTexture);
	col2->add(toolTipCard);


	//---- Column 3 sliders: change sound parameters ----//

	// Slider for root
	gui::HBoxLayout* rootSelector = col3->addHBoxLayout();
	gui::Slider* rootSlider = new gui::Slider(288.0f, gui::Horizontal);
	rootSlider->setStep(1);
	rootSlider->setValue(25);
	

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

	sf::Texture rampLabelTexture;
	rampLabelTexture.loadFromFile("Assets/labels-07.png");
	gui::Image* rampLabel = new gui::Image(rampLabelTexture);

	rampSelector->add(rampLabel);
	rampSelector->add(rampSlider);


	// Slider for BMP
	gui::HBoxLayout* bpmSelector = col3->addHBoxLayout();
	gui::Slider* bpmSlider = new gui::Slider(288.0f, gui::Horizontal);
	bpmSlider->setStep(1);
	
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
	
	sf::Texture volLabelTexture;
	volLabelTexture.loadFromFile("Assets/labels-09.png");
	gui::Image* volLabel = new gui::Image(volLabelTexture);

	volSelector->add(volLabel);
	volSelector->add(volSlider);

	//-- Callbacks for buttons and sliders
	sineWaveButton->setCallback([&] {
		activeWaveButton->toggle();
	activeWaveButton = sineWaveButton;
	activeWaveButton->toggle();
	params.setWaveType("sine");
	params.display();
		});

	squareWaveButton->setCallback([&] {
		activeWaveButton->toggle();
	activeWaveButton = squareWaveButton;
	activeWaveButton->toggle();
		params.setWaveType("square");
	params.display();
		});

	sawWaveButton->setCallback([&] {
		activeWaveButton->toggle();
	activeWaveButton = sawWaveButton;
	activeWaveButton->toggle();
	params.setWaveType("saw");
	params.display();
		});

	triangleWaveButton->setCallback([&] {
		params.setWaveType("triangle");
	activeWaveButton->toggle();
	activeWaveButton = triangleWaveButton;
	activeWaveButton->toggle();
	params.display();
		});

	playButton->setCallback([&] {
		if (sounds.getStatus() != sf::Sound::Playing) {
			playing = true;
			playButton->toggle();
		};
	if (stopButton->isActive())
		stopButton->toggle();
		});

	stopButton->setCallback([&]() {
		playing = false;
	stopButton->toggle();
	playButton->toggle();
	wave.stopWave(sounds);
		});

	randomButton->setCallback([&] {
		std::cout << "click!" << std::endl;
	randomize = !randomize;
	params.GenerateRandomParameters();
	bpmSlider->setValue((params.GetBPM() - 20) / 2.2);
	rootSlider->setValue((params.GetRootKey() - 21) * 100 / 82);
	rampSlider->setValue(params.GetRamp() * 200);
	int waveType = params.GetWaveType();
	activeWaveButton->toggle();
	switch (waveType) {
		case 0:
			activeWaveButton = sineWaveButton;
			break;
		case 1:
			activeWaveButton = squareWaveButton;
			break;
		case 2:
			activeWaveButton = triangleWaveButton;
			break;
		case 3:
			activeWaveButton = sawWaveButton;
			break;
	}
	activeWaveButton->toggle();
	params.display();
		});

	rootSlider->setCallback([&]() {
		int input = rootSlider->getValue() * 0.82 + 21;
	params.setRootKey(input);
	params.SetRootKeyCharacter(input);
	params.display();
		});

	rampSlider->setCallback([&]() {
		params.setRamp(rampSlider->getValue() * 0.005f);
	params.display();
		});

	bpmSlider->setCallback([&]() {
		params.setBPM(bpmSlider->getValue() * 2.2 + 20);
	params.display();
		});

	volSlider->setCallback([&]() {
		params.setVolume(volSlider->getValue() * 0.1);
	params.display();
		});

	activeWaveButton = sawWaveButton;
	activeWaveButton->toggle();
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

