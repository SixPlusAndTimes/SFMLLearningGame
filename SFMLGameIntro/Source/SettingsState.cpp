#include <cassert>
#include <SFML/Graphics/RenderWindow.hpp>
#include "SettingsState.hpp"
#include "ResourceHolder.hpp"
#include "State.hpp"
#include "utils.hpp"
SettingsState::SettingsState(StateStack& stack, Context context)
: State(stack, context)
, mGUIContainer()
{
    mBackGroudSprite.setTexture(context.mTextures->get(Textures::TitleScreen));

    addButtonAndLabel(Player::MoveLeft, 150.f, "Move Left", context);
    addButtonAndLabel(Player::MoveRight, 200.f, "Move Right", context);
    addButtonAndLabel(Player::MoveUp, 250.f, "Move Up", context);
    addButtonAndLabel(Player::MoveDown, 300.f, "Move Down", context);

    updateLabels();

	auto backButton = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);
	backButton->setPosition(80.f, 375.f);
	backButton->setText("Back");

	backButton->setCallback([this](){
        requestStackPop();
    });

	mGUIContainer.pack(backButton);
}

bool SettingsState::handleEvent(const sf::Event& event)
{
	bool isKeyBinding = false;
	
	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t action = 0; action < Player::ActionCount; ++action)
	{
		if (mBindingButtons[action]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().mPlayer->assignKey(static_cast<Player::Action>(action), event.key.code);
				mBindingButtons[action]->deactivate();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
		updateLabels();
	else
		mGUIContainer.handleEvent(event);

	return false;
}

bool SettingsState::update(sf::Time dt) 
{
    return true;
}

void SettingsState::updateLabels()
{
	Player& player = *getContext().mPlayer;

	for (std::size_t i = 0; i < Player::ActionCount; ++i)
	{
		sf::Keyboard::Key key = player.getAssignedKey(static_cast<Player::Action>(i));
		mBindingLabels[i]->setText(toString(key));
	}
}
void SettingsState::draw()
{
	sf::RenderWindow& window = *getContext().mWindow;

	window.draw(mBackGroudSprite);
	window.draw(mGUIContainer);
}

void SettingsState::addButtonAndLabel(Player::Action action, float y, const std::string& text, Context context) 
{
    mBindingButtons[action] = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);
    mBindingButtons[action]->setPosition(80.f, y);
	mBindingButtons[action]->setText(text);
	mBindingButtons[action]->setToggle(true);

    mBindingLabels[action] = std::make_shared<GUI::Label>("", *context.mFonts);

    mBindingLabels[action]->setPosition(300.f, y + 15.f);
	mGUIContainer.pack(mBindingButtons[action]);
	mGUIContainer.pack(mBindingLabels[action]);
}