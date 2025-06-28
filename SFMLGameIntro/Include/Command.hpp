#ifndef COMMAND_H
#define COMMAND_H
#include <functional>
#include <cassert>
#include <SFML/System/Time.hpp>
//#include <SceneNode.hpp>
 class SceneNode;

template <typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
    return [fn](SceneNode& node, sf::Time dt){
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        return fn(static_cast<GameObject&>(node), dt);
    };
}

struct Command
{
    Command();
    Command(unsigned int c, std::function<void(SceneNode&, sf::Time)> a);
    unsigned int category;    
    std::function<void(SceneNode&, sf::Time)> action;
};

#endif // COMMAND_H