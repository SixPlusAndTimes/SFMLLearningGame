#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <string>
#include <source_location>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
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

float length(sf::Vector2f vector);
sf::Vector2f unitVector(sf::Vector2f vector);

#endif // UTILS_H