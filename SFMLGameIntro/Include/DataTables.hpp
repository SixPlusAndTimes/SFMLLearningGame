#ifndef DATATABLES_H
#define DATATABLES_H
#include <SFML/System/Time.hpp>
#include <vector>
#include "ResourceIdentifier.hpp"
#include "Aircraft.hpp"
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
    sf::IntRect						textureRect;
    sf::Time                fireInterval;
    std::vector<Direction>  directions;
    bool					hasRollAnimation;
};

struct ProjectileData
{
	int                     damage;
	float                   speed;
	Textures::ID            texture;
    sf::IntRect             textureRect;
};

struct PickupData
{
	std::function<void(Aircraft&)>	action;
	Textures::ID					texture;
    sf::IntRect                     textureRect;
};

std::vector<AircraftData>       initializeAircraftData();
std::vector<ProjectileData>     initializeProjectileData();
std::vector<PickupData>         initializePickupData();
#endif // DATATABLES_H