#ifndef TITLESTATE_H
#define TITLESTATE_H
#include "State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
class TitleState : public State
{
    public:
        TitleState(StateStack &stack, Context context);
        
        virtual void    draw();
        virtual bool    update(sf::Time dt) override;
        virtual bool    handleEvent(const sf::Event& event);
    private:
        sf::Sprite      mBackGroudSprite;
        sf::Text        mText;
        bool            mBShowText;
        sf::Time        mTextEffectTime;
};

#endif // TITLESTATE_H