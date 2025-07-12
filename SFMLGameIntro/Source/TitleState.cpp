#include <SFML/Graphics/RenderWindow.hpp>
#include "TitleState.hpp"
#include "ResourceHolder.hpp"
#include "utils.hpp"
TitleState::TitleState(StateStack &stack, Context context)
: State(stack, context)
, mText()
, mBShowText(true)
, mTextEffectTime(sf::Time::Zero)
{
    mBackGroudSprite.setTexture(context.mTextures->get(Textures::TitleScreen));

    mText.setFont(context.mFonts->get(Fonts::Main));
    mText.setString("Press any key to start");
    centerOrigin(mText);
    mText.setPosition(context.mWindow->getView().getSize() / 2.f);
}
bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return true;
}


bool TitleState::update(sf::Time dt) 
{
    mTextEffectTime += dt;
    if (mTextEffectTime >= sf::seconds(0.5f))
    {
        mBShowText = !mBShowText;
        mTextEffectTime = sf::Time::Zero;
    }
    return true;
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().mWindow;
    window.draw(mBackGroudSprite);
    if (mBShowText)
    {
        window.draw(mText);
    }
}