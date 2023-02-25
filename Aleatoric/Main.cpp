#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<cmath>
#include<cstdlib>
#include"WaveParameters.h"
#include "Gui/Theme.hpp"
#include "Gui/Gui.hpp"
using namespace std;

#include"WaveParameters.h"
#include"WaveGenerator.h"


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

	/*if (params.ParseArguments(argc, argv))
	{
		wave.playWave(params);
	}*/

	Theme defaultTheme = {
		hex2color("#eeeeee"),
		"Assets/texture-default.png"
	};

	Theme win98Theme = {
		hex2color("#d4d0c8"),
		"Assets/texture-win98.png"
	};

	// Create the main window
	sf::RenderWindow app(sf::VideoMode(1500, 1000), "SFML Widgets", sf::Style::Close);
	app.setFramerateLimit(60);

	gui::Menu menu(app);
	menu.setPosition(10, 10);

	gui::Theme::loadFont("Assets/tahoma.ttf");
	gui::Theme::loadTexture(defaultTheme.texturePath);
	gui::Theme::textSize = 32;
	gui::Theme::click.textColor = hex2color("#191B18");
	gui::Theme::click.textColorHover = hex2color("#191B18");
	gui::Theme::click.textColorFocus = hex2color("#000");
	gui::Theme::input.textColor = hex2color("#000");
	gui::Theme::input.textColorHover = hex2color("#000");
	gui::Theme::input.textColorFocus = hex2color("#000");
	gui::Theme::input.textSelectionColor = hex2color("#8791AD");
	gui::Theme::input.textPlaceholderColor = hex2color("#8791AD");
	gui::Theme::PADDING = 10.f;
	gui::Theme::windowBgColor = defaultTheme.backgroundColor;

	gui::HBoxLayout* hbox = menu.addHBoxLayout();
	gui::FormLayout* form = hbox->addFormLayout();


	sf::Text text("Hello world!", gui::Theme::getFont());
	text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
	text.setPosition(480, 240);


	gui::TextBox* textbox2 = new gui::TextBox();
	textbox2->setText("80");
	textbox2->setMaxLength(3);
	form->addRow("Root Note", textbox2);

	// Slider for ramp
	gui::Slider* rampSlider = new gui::Slider(250.0f, gui::Horizontal);

	rampSlider->setStep(1);
	rampSlider->setCallback([&]() {
	params.setRamp(rampSlider->getValue() * 0.005f);
		});
	form->addRow("Ramp", rampSlider);

	// Slider for BMP
	gui::Slider* bpmSlider = new gui::Slider(250.0f, gui::Horizontal);

	bpmSlider->setStep(1);
	bpmSlider->setCallback([&]() {
		params.setBPM(bpmSlider->getValue() * 2.4);
		});
	form->addRow("BPM", bpmSlider);


	// OptionsBox for wave
	gui::OptionsBox<string>* opt = new gui::OptionsBox<string>();
	opt->addItem("Sine", "sine");
	opt->addItem("Saw", "saw");
	opt->addItem("Square", "square");
	opt->addItem("Triangle", "triangle");
	opt->setCallback([&]() {
		params.setWaveType(opt->getSelectedValue());
		});
	form->addRow("Wave Type", opt);

	// Checbkox
	gui::CheckBox* checkboxBold = new gui::CheckBox();
	checkboxBold->setCallback([&]() {
		int style = text.getStyle();
	if (checkboxBold->isChecked())
		style |= sf::Text::Bold;
	else
		style &= ~sf::Text::Bold;
	text.setStyle(style);
		});
	form->addRow("Bold text", checkboxBold);

	gui::CheckBox* randomCheckBox = new gui::CheckBox();
	randomCheckBox->setCallback([&]() {
		int style = text.getStyle();
	if (randomCheckBox->isChecked())
		params.setRandom(true);
	else
		params.setRandom(false);
		});
	form->addRow("Random", randomCheckBox);


	// Define a callback
	gui::Button* button = new gui::Button("Play");

	button->setCallback([&] {
		std::cout << "click!" << std::endl;
		wave.playWave(params);
		});

	form->addRow("Play button", button);


	gui::Button* printParamsButton = new gui::Button("Print params");

	printParamsButton->setCallback([&] {
		params.display();
		});

	form->addRow("Play button", printParamsButton);


	gui::VBoxLayout* vbox = hbox->addVBoxLayout();
	vbox->addLabel("Wave parameters");

	// Custom button
	sf::Texture sineWaveBackground;
	sf::Texture squareWaveBackground;
	sf::Texture sawWaveBackground;
	sf::Texture triangleWaveBackground;
	sineWaveBackground.loadFromFile("Assets/sinewave.png");
	squareWaveBackground.loadFromFile("Assets/squarewave.png");
	sawWaveBackground.loadFromFile("Assets/sawwave.png");
	triangleWaveBackground.loadFromFile("Assets/trianglewave.png");


	gui::SpriteButton* sineWaveButton = new gui::SpriteButton(sineWaveBackground);
	sineWaveButton->setTextSize(20);
	form->addRow("Sine", sineWaveButton);

	sineWaveButton->setCallback([&] {
		std::cout << "click!" << std::endl;
	params.setWaveType("sine");
	params.display();
		});


	gui::SpriteButton* squareWaveButton = new gui::SpriteButton(squareWaveBackground);
	squareWaveButton->setTextSize(20);
	form->addRow("Square", squareWaveButton);

	squareWaveButton->setCallback([&] {
		std::cout << "click!" << std::endl;
	params.setWaveType("square");
	params.display();
		});



	menu.addButton("Quit", [&]() {
		app.close();
		});



	sf::Texture texture;
	texture.loadFromFile("Assets/sfml.png");

	sf::Sprite sprite(texture);
	sprite.setOrigin(texture.getSize().x * 2, texture.getSize().y * 2);
	sprite.setPosition(300, 360);

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
		app.draw(text);
		// Update the window
		app.display();
	}

	return EXIT_SUCCESS;
}

