#ifndef DATATABLES_H
#define DATATABLES_H
#include <SFML/System/Time.hpp>
#include <vector>
#include "ResourceIdentifier.hpp"

struct Direction
{
    Direction(float angle, float distance)
    : angle(angle)
    , distance(distance){}

    // zero degree points to the right
    float   angle;
    float   distance;
};

struct AircraftData
{
    int                     hitpoints;
    float                   speed;
    Textures::ID            texture;
    sf::Time                fireInterval;
    std::vector<Direction>  directions;
};

std::vector<AircraftData> initializeAircraftData();
#endif // DATATABLES_H