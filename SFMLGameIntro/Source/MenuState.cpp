#include <SFML/Graphics/RenderWindow.hpp>
#include "MenuState.hpp"
#include "ResourceHolder.hpp"
#include "Button.hpp"
#include "utils.hpp"

MenuState::MenuState(StateStack &stack, Context context)
: State(stack, context)
, mBackGroudSprite()
, mGUIContainer()
{
    sf::Texture& texture = context.mTextures->get(Textures::TitleScreen);
	mBackGroudSprite.setTexture(texture);

	auto playButton = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);
	playButton->setPosition(100, 250);
	playButton->setText("Play");
	playButton->setCallback([this] ()
	{
		requestStackPop();
		requestStackPush(States::Game);
	});

	auto settingsButton = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);
	settingsButton->setPosition(100, 300);
	settingsButton->setText("Settings");
	settingsButton->setCallback([this] ()
	{
		 requestStackPush(States::Settings);
	});

	auto exitButton = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);
	exitButton->setPosition(100, 350);
	exitButton->setText("Exit");
	exitButton->setCallback([this] ()
	{
		requestStackPop();
	});

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(settingsButton);
	mGUIContainer.pack(exitButton);
}


void MenuState::draw() 
{
	sf::RenderWindow& window = *getContext().mWindow;
    window.setView(window.getDefaultView());
	window.draw(mBackGroudSprite);
    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time dt) 
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) 
{
    mGUIContainer.handleEvent(event);
    return true;
}
