#include <Command.hpp>
#include <functional>


Command::Command()
: category()
, action()
{

}
Command::Command(unsigned int c, std::function<void(SceneNode&, sf::Time)> a)
: category(c)
, action(a)
{

}