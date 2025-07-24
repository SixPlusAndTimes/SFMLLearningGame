#include <Player.hpp>
#include <Aircraft.hpp>
#include <Command.hpp>
#include <iostream>
const float playerSpeed  = 200.f;
struct AirCraftMover
{
    AirCraftMover(float x, float y)
    : velocity(x, y)
    {

    }
    void operator()(Aircraft& node, sf::Time dt) const 
    {
        node.accelerate(velocity);
    }

    sf::Vector2f velocity;
};

Player::Player()
{
    // std::map<sf::Keyboard::Key, Action> mKeyBinding;
    // std::map<Action, Command>           mActionBinding;
    mKeyBinding = {{sf::Keyboard::Left, MoveLeft},
                   {sf::Keyboard::Right, MoveRight},
                   {sf::Keyboard::Up, MoveUp},
                   {sf::Keyboard::Down, MoveDown},
                   {sf::Keyboard::Space, Fire},
                   {sf::Keyboard::M, LaunchMissile}};


    initializeActions();

    for (auto& [_, cmd] : mActionBinding)
    {
        cmd.category = Category::PlayerAircraft;
    }
}

void Player::initializeActions()
{
	mActionBinding[MoveLeft].action      = derivedAction<Aircraft>(AirCraftMover(-playerSpeed,  0));
	mActionBinding[MoveRight].action     = derivedAction<Aircraft>(AirCraftMover(+playerSpeed,  0));
	mActionBinding[MoveUp].action        = derivedAction<Aircraft>(AirCraftMover( 0, -playerSpeed));
	mActionBinding[MoveDown].action      = derivedAction<Aircraft>(AirCraftMover( 0, +playerSpeed));

    mActionBinding[Fire].action          = derivedAction<Aircraft>([] (Aircraft& a, sf::Time){ a.fire(); });
    mActionBinding[LaunchMissile].action = derivedAction<Aircraft>([] (Aircraft& a, sf::Time){ a.launchMissile(); });
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commandQueue)
{
    if (event.type == sf::Event::KeyPressed)
    {
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commandQueue.push(mActionBinding[found->second]);
    }
}

void Player::handleRealtimeInput(CommandQueue& commandQueue)
{
    for (auto& [key, actionType] : mKeyBinding)
    {
        if (sf::Keyboard::isKeyPressed(key) && isRealtimeAction(actionType))
        {
            commandQueue.push(mActionBinding[actionType]);
        }
    }
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    for (auto& [key, rAction] : mKeyBinding)
    {
        if (rAction == action)
        {
            return key;
        }
    }
    return sf::Keyboard::Unknown;
}

bool Player::isRealtimeAction(Action action)
{
    switch (action)
    {
        case MoveLeft:
        case MoveRight:
        case MoveDown:
        case MoveUp:
        case Fire:
            return true;
        default:
            return false;
    }
}
