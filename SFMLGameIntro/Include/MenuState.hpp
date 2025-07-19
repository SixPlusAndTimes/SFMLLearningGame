#ifndef MENUSTATE_H
#define MENUSTATE_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"
#include "Container.hpp"
class MenuState : public State
{
    public:
        MenuState(StateStack &stack, Context context);

        virtual void    draw() override;
        virtual bool    update(sf::Time dt) override;
        virtual bool    handleEvent(const sf::Event& event) override;
    private:
        sf::Sprite              mBackGroudSprite;
        GUI::Container          mGUIContainer;
};
#endif // MENUSTATE_H