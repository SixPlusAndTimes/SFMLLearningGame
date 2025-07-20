#include <iostream>
#include "GameState.hpp"
#include "Player.hpp"

GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.mWindow, *context.mFonts)
, mPlayer(*context.mPlayer)
{ }

void GameState::draw() 
{
    mWorld.draw();
}

bool GameState::update(sf::Time dt) 
{
    mWorld.update(dt);
    CommandQueue& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event& event) 
{
    CommandQueue& commandQueue = mWorld.getCommandQueue();
    mPlayer.handleEvent(event, commandQueue);

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        requestStackPush(States::Pause);
    }

    return true;
}
