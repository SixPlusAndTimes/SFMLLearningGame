#include "PauseState.hpp"
#include "utils.hpp"
#include "ResourceHolder.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
PauseState::PauseState(StateStack &stack, Context context)
: State(stack, context)
, mBackGroudSprite()
, mPauseText()
, mInstructionText()
{
	sf::Font& font = context.mFonts->get(Fonts::Main);
	sf::Vector2f viewSize = context.mWindow->getView().getSize();

	mPauseText.setFont(font);
	mPauseText.setString("Game Paused");	
	mPauseText.setCharacterSize(70);
	centerOrigin(mPauseText);
	mPauseText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString("(Press Backspace to return to the main menu)");	
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);
}

void PauseState::draw() 
{
    sf::RenderWindow& window = *getContext().mWindow;
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(window.getView().getSize()); 

    window.draw(backgroundShape);
    window.draw(mPauseText);
    window.draw(mInstructionText);
}

bool PauseState::update(sf::Time dt) 
{
    return false;
}

bool PauseState::handleEvent(const sf::Event& event) 
{
    if (event.type != sf::Event::KeyPressed)
    {
        return false;
    }

    if (event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop();
    }

    if (event.key.code == sf::Keyboard::Backspace)
    {
        requestStackClear();
        requestStackPush(States::Menu);
    }
    // return false to prevent any layer under the pausestate from being updated
    // so we pause the game literally
    return false;
}