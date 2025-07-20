#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <source_location>
#include <SFML/Window/Keyboard.hpp>
namespace sf
{
    class Sprite;
    class Text;
} // namespace sf

enum class LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

void centerOrigin(sf::Sprite& sprite);
void centerOrigin(sf::Text& text);

std::string toString(sf::Keyboard::Key key);

float toDegree(float radian);
float toRadian(float degree);


#endif // UTILS_H