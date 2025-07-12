#include "State.hpp"
#include "StateStack.hpp"
State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player)
: mWindow(&window)
, mTextures(&textures)
, mFonts(&fonts)
, mPlayer(&player)
{ }

State::State(StateStack& stack, Context context)
: mStateStack(&stack)
, mContext(context)
{ }

State::~State() { }


void State::requestStackPush(States::ID id) 
{
    mStateStack->pushState(id);
}

void State::requestStackPop() 
{
    mStateStack->popState();
}

void State::requestStackClear() 
{
    mStateStack->clearState();
}

State::Context State::getContext() const 
{
    return mContext;
}
