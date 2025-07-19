#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H
#include <array>
#include <SFML/Graphics/Sprite.hpp>
#include "State.hpp"
#include "Container.hpp"
#include "Button.hpp"
#include "Label.hpp"
#include "Player.hpp"
class SettingsState : public State
{
    public:
        SettingsState(StateStack& stack, Context context);
        virtual void    draw() override;
        virtual bool    update(sf::Time dt) override;
        virtual bool    handleEvent(const sf::Event& event) override;

    private:
		void							updateLabels();
		void							addButtonAndLabel(Player::Action action, float y, const std::string& text, Context context);

    private:
        GUI::Container  mGUIContainer;
        sf::Sprite              mBackGroudSprite;
        std::array<GUI::Button::Ptr, Player::ActionCount> mBindingButtons;
        std::array<GUI::Label::Ptr, Player::ActionCount>  mBindingLabels;
};


#endif // SETTINGSSTATE_H