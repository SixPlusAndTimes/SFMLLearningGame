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
                   {sf::Keyboard::Right, MoveRight}};

    mActionBinding[MoveLeft] = {Category::PlayerAircraft, [](SceneNode& node, sf::Time dt){
        node.move(-playerSpeed * dt.asSeconds(), 0.f); }
    };

    mActionBinding[MoveRight] = {Category::PlayerAircraft, [](SceneNode& node, sf::Time dt){
        node.move(playerSpeed * dt.asSeconds(), 0.f); }
    };
}
void Player::handleEvent(const sf::Event& event, CommandQueue& commandQueue)
{
    if (event.type == sf::Event::KeyPressed
        || event.key.code == sf::Keyboard::P)
    {
        Command output;
        output.category = Category::PlayerAircraft;
        output.action = [](SceneNode& node, sf::Time dt) {
            std::cout << node.getPosition().x << ","
                      << node.getPosition().y << "\n";
        };
        commandQueue.push(output);
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
            return true;
        default:
            return false;
    }
}
