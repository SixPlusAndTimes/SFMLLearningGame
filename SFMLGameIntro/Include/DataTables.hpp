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

struct ProjectileData
{
	int                     damage;
	float                   speed;
	Textures::ID            texture;
};

struct PickupData
{
	std::function<void(Aircraft&)>	action;
	Textures::ID					texture;
};

std::vector<AircraftData>       initializeAircraftData();
std::vector<ProjectileData>     initializeProjectileData();
std::vector<PickupData>         initializePickupData();
#endif // DATATABLES_H