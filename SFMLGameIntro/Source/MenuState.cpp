#include <SFML/Graphics/RenderWindow.hpp>
#include "MenuState.hpp"
#include "ResourceHolder.hpp"
#include "utils.hpp"

MenuState::MenuState(StateStack &stack, Context context)
: State(stack, context)
, mBackGroudSprite()
, mOptions()
, mOptionIndex(0)
{
    sf::Texture& texture = context.mTextures->get(Textures::TitleScreen);
	sf::Font& font = context.mFonts->get(Fonts::Main);

	mBackGroudSprite.setTexture(texture);
    
    sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.mWindow->getView().getSize() / 2.f);
	mOptions.push_back(playOption);

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition() + sf::Vector2f(0.f, 30.f));
	mOptions.push_back(exitOption);

    updateOptionText();
}

void MenuState::updateOptionText()
{
    if (mOptions.empty())
    {
        return;
    }
    for (auto& text : mOptions)
    {
        text.setFillColor(sf::Color::White);
    }

    mOptions[mOptionIndex].setFillColor(sf::Color::Red);
}

void MenuState::draw() 
{
	sf::RenderWindow& window = *getContext().mWindow;
    window.setView(window.getDefaultView());
	window.draw(mBackGroudSprite);
	for (const auto& text : mOptions)
	{
		window.draw(text);
	}
}

bool MenuState::update(sf::Time dt) 
{
    return true;
}

bool MenuState::handleEvent(const sf::Event& event) 
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
        if (mOptionIndex > 0)
        {
            --mOptionIndex;
        }
        else
        {
            mOptionIndex = mOptions.size() - 1;
        }
        updateOptionText();
    }
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
    {
        if (mOptionIndex < mOptions.size() - 1)
        {
            ++mOptionIndex;
        }
        else 
        {
            mOptionIndex = 0;
        }
        updateOptionText();
    }
    else if (event.key.code == sf::Keyboard::Return)
    {
        if (mOptionIndex == Play)
        {
            requestStackPop();
            requestStackPush(States::Game);
        }
        else if (mOptionIndex == Exit)
        {
            requestStackPop();
        }
        else
        {
            printf("unknown option index\n");
            assert(false);
        }
    }

    return true;
}
