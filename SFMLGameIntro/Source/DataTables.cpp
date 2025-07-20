#include "DataTables.hpp"
#include "Aircraft.hpp"
// why not std::array ?
std::vector<AircraftData> initializeAircraftData()
{
    std::vector<AircraftData> data(Aircraft::Acicraftcount);

    data[Aircraft::Eagle].hitpoints = 100;
    data[Aircraft::Eagle].speed = 200.f;
    data[Aircraft::Eagle].fireInterval = sf::seconds(1);
    data[Aircraft::Eagle].texture = Textures::Eagel;

    data[Aircraft::Raptor].hitpoints = 20;
    data[Aircraft::Raptor].speed = 80.f;
    data[Aircraft::Raptor].directions.emplace_back(+45.f, 80.f);
	data[Aircraft::Raptor].directions.emplace_back(-45.f, 160.f);
	data[Aircraft::Raptor].directions.emplace_back(+45.f, 80.f);
    data[Aircraft::Raptor].fireInterval = sf::Time::Zero;
    data[Aircraft::Raptor].texture = Textures::Raptor;

    data[Aircraft::Avenger].hitpoints = 40;
	data[Aircraft::Avenger].speed = 50.f;
	data[Aircraft::Avenger].texture = Textures::Avenger;
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f,  50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(  0.f,  50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(-45.f, 100.f));
	data[Aircraft::Avenger].directions.push_back(Direction(  0.f,  50.f));
	data[Aircraft::Avenger].directions.push_back(Direction(+45.f,  50.f));
	data[Aircraft::Avenger].fireInterval = sf::seconds(2);

    return data;
}