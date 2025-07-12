#ifndef MENUSTATE_H
#define MENUSTATE_H
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.hpp"
class MenuState : public State
{
    public:
        MenuState(StateStack &stack, Context context);

        virtual void    draw() override;
        virtual bool    update(sf::Time dt) override;
        virtual bool    handleEvent(const sf::Event& event) override;
    private:
        enum Options 
        {
            Play, 
            Exit
        };
        sf::Sprite              mBackGroudSprite;

        std::vector<sf::Text>   mOptions;
        std::size_t             mOptionIndex;
    private:
        void updateOptionText();
};

#endif // MENUSTATE_H