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


sf::Color hex2color(const std::string& hexcolor)
{
	sf::Color color = sf::Color::Black;
	if (hexcolor.size() == 7) // #ffffff
	{
		color.r = strtoul(hexcolor.substr(1, 2).c_str(), NULL, 16);
		color.g = strtoul(hexcolor.substr(3, 2).c_str(), NULL, 16);
		color.b = strtoul(hexcolor.substr(5, 2).c_str(), NULL, 16);
	}
	else if (hexcolor.size() == 4) // #fff
	{
		color.r = strtoul(hexcolor.substr(1, 1).c_str(), NULL, 16) * 17;
		color.g = strtoul(hexcolor.substr(2, 1).c_str(), NULL, 16) * 17;
		color.b = strtoul(hexcolor.substr(3, 1).c_str(), NULL, 16) * 17;
	}
	return color;
}

struct Theme
{
	sf::Color backgroundColor;
	std::string texturePath;
};

int main(int argc, char ** argv)
{
	sf::SoundBuffer sound;
	WaveParameters params;
	WaveGenerator wave;
	bool randomize = false;
	Theme defaultTheme = {
		hex2color("#eeeeee"),
		"Assets/texture-default.png"
	};

	// Create the main window
	sf::RenderWindow app(sf::VideoMode(1500, 1000), "SFML Widgets", sf::Style::Close);
	app.setFramerateLimit(60);

	gui::Menu menu(app);
	menu.setPosition(0, 200);

	gui::Theme::loadFont("Assets/Georama-Semibold.ttf");
	gui::Theme::loadTexture(defaultTheme.texturePath);
	gui::Theme::textSize = 60;
	gui::Theme::click.textColor = hex2color("#191B18");
	gui::Theme::click.textColorHover = hex2color("#191B18");
	gui::Theme::click.textColorFocus = hex2color("#000");
	gui::Theme::input.textColor = hex2color("#000");
	gui::Theme::input.textColorHover = hex2color("#fff");
	gui::Theme::input.textColorFocus = hex2color("#000");
	gui::Theme::input.textSelectionColor = hex2color("#8791AD");
	gui::Theme::input.textPlaceholderColor = hex2color("#8791AD");
	gui::Theme::PADDING = 0.f;
	gui::Theme::windowBgColor = defaultTheme.backgroundColor;

	//Header font
	sf::Font displayFont;
	// Load it from a file
	if (!displayFont.loadFromFile("Assets/Imprima-Regular.ttf")) {
		cout << "Couldn't load font" << endl;
	};

	gui::HBoxLayout* main = menu.addHBoxLayout();

	gui::VBoxLayout* col1 = main->addVBoxLayout();
	gui::VBoxLayout* col2 = main->addVBoxLayout();
	gui::VBoxLayout* col3 = main->addVBoxLayout();


	sf::Text titleText("Lofi-Aleatory", gui::Theme::getFont());
	titleText.setCharacterSize(60);
	titleText.setFont(displayFont);
	titleText.setFillColor(sf::Color(255, 255, 255));
	titleText.setPosition(50, 50);

	string description = "A simple program that generates parameterized sound waves.";
	sf::Text descriptionText(description, gui::Theme::getFont());
	descriptionText.setCharacterSize(30);
	descriptionText.setFont(displayFont);
	descriptionText.setFillColor(sf::Color(15, 140, 255));
	descriptionText.setPosition(560, 80);

	//Card for the title
	sf::RectangleShape titleCard(sf::Vector2f(500, 200));
	titleCard.setFillColor(sf::Color(15, 140, 255));
	titleCard.setPosition(sf::Vector2f(0, 0));

	//Card for the description
	sf::RectangleShape descriptionCard(sf::Vector2f(1000, 200));
	descriptionCard.setFillColor(sf::Color(218, 237, 255));
	descriptionCard.setPosition(sf::Vector2f(500, 0));


	//Root note selector
	gui::HBoxLayout* rootSelector = col2->addHBoxLayout();
	gui::TextBox* rootTextBox = new gui::TextBox();
	rootTextBox->setText("45");
	rootTextBox->setMaxLength(3);
	rootSelector->addLabel("ROOT");
	rootSelector->add(rootTextBox);

	gui::TextBox* textbox = new gui::TextBox();
		rootTextBox->setCallback([&]() {
			params.setRootKey(stoi(static_cast<string>(rootTextBox->getText())));
		params.display();
			});


	// Slider for ramp
	gui::HBoxLayout* rampSelector = col3->addHBoxLayout();
	gui::Slider* rampSlider = new gui::Slider(250.0f, gui::Horizontal);
	rampSlider->setStep(1);
	rampSlider->setCallback([&]() {
	params.setRamp(rampSlider->getValue() * 0.005f);
	params.display();
		});
	rampSelector->addLabel("RAMP");
	rampSelector->add(rampSlider);

	// Slider for BMP
	gui::HBoxLayout* bpmSelector = col3->addHBoxLayout();
	gui::Slider* bpmSlider = new gui::Slider(250.0f, gui::Horizontal);
	bpmSlider->setStep(1);
	bpmSlider->setCallback([&]() {
		params.setBPM(bpmSlider->getValue() * 2.4);
	params.display();
		});
	bpmSelector->addLabel("BPM");
	bpmSelector->add(bpmSlider);


	// Slider for BMP
	gui::HBoxLayout* volSelector = col3->addHBoxLayout();
	gui::Slider* volSlider = new gui::Slider(250.0f, gui::Horizontal);
	volSlider->setStep(1);
	volSlider->setCallback([&]() {
		params.setBPM(volSlider->getValue() * 2.4);
	params.display();
		});
	volSelector->addLabel("VOL");
	volSelector->add(volSlider);

	//Randomize checkbox
	gui::CheckBox* randomCheckBox = new gui::CheckBox();
	randomCheckBox->setCallback([&]() {
	if (randomCheckBox->isChecked())
		params.setRandom(true);
	else
		params.setRandom(false);
		});
	col2->add(randomCheckBox);


	//Play button
	sf::Texture playButtonBackground;
	playButtonBackground.loadFromFile("Assets/playButtonSprites.png");
	gui::SpriteButton* playButton = new gui::SpriteButton(playButtonBackground);
	col2->add(playButton);
	playButton->setCallback([&] {
		std::cout << "click!" << std::endl;
	params.setRootKey(stoi(static_cast<string>(rootTextBox->getText())));
	wave.playWave(params);
		});



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


	// Wave buttons
	sf::Texture sineWaveBackground;
	sineWaveBackground.loadFromFile("Assets/sineWaveSprite.png");
	gui::SpriteButton* sineWaveButton = new gui::SpriteButton(sineWaveBackground);
	sineWaveButton->setTextSize(10);
	col1->add(sineWaveButton);
	sineWaveButton->setCallback([&] {
		std::cout << "click!" << std::endl;
	params.setWaveType("sine");
	params.display();
		});


	sf::Texture squareWaveBackground;
	squareWaveBackground.loadFromFile("Assets/squareWaveSprite.png");
	gui::SpriteButton* squareWaveButton = new gui::SpriteButton(squareWaveBackground);
	squareWaveButton->setTextSize(10);
	col1->add(squareWaveButton);
	squareWaveButton->setCallback([&] {
		std::cout << "click!" << std::endl;
	params.setWaveType("square");
	params.display();
		});

	sf::Texture sawWaveBackground;
	sawWaveBackground.loadFromFile("Assets/sawWaveSprite.png");
	gui::SpriteButton* sawWaveButton = new gui::SpriteButton(sawWaveBackground);
	sawWaveButton->setTextSize(10);
	col1->add(sawWaveButton);
	sawWaveButton->setCallback([&] {
		std::cout << "click!" << std::endl;
	params.setWaveType("saw");
	params.display();
		});

	sf::Texture triangleWaveBackground;
	triangleWaveBackground.loadFromFile("Assets/triangleWaveSprite.png");
	gui::SpriteButton* triangleWaveButton = new gui::SpriteButton(triangleWaveBackground);
	triangleWaveButton->setTextSize(10);
	col1->add(triangleWaveButton);

	triangleWaveButton->setCallback([&] {
		std::cout << "click!" << std::endl;
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
		app.draw(titleCard);
		app.draw(descriptionCard);
		app.draw(titleText);
		app.draw(descriptionText);
		app.draw(menu);
		// Update the window
		app.display();
	}

	return EXIT_SUCCESS;
}
