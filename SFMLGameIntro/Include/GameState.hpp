#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.hpp"
#include "World.hpp"
class GameState : public State
{
    public:
                        GameState(StateStack& stack, Context context);

        virtual void    draw() override;
        virtual bool    update(sf::Time dt) override;
        virtual bool    handleEvent(const sf::Event& event) override;

    private:
        World           mWorld;
        Player&         mPlayer;
};

#endif // GAMESTATE_H