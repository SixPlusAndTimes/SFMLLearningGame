#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "State.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
class PauseState : public State
{
    public:
        PauseState(StateStack &stack, Context context);
        virtual void    draw() override;
        virtual bool    update(sf::Time dt) override;
        virtual bool    handleEvent(const sf::Event& event) override;

    private:
        sf::Sprite      mBackGroudSprite;  // not used now
        sf::Text        mPauseText; 
        sf::Text        mInstructionText;
};

#endif // PAUSESTATE_H