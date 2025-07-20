#include <memory>
#include <Aircraft.hpp>
#include <ResourceHolder.hpp>
#include <cmath>

#include "DataTables.hpp"
#include "TextNode.hpp"
#include "utils.hpp"
namespace 
{
    const std::vector<AircraftData> Table = initializeAircraftData();
} // namespace 

Textures::ID toTextureId(Aircraft::Type type)
{
    switch (type)
    {
        case Aircraft::Eagle:
            return Textures::Eagel;
        case Aircraft::Raptor:
            return Textures::Raptor; 
        default:
            return  Textures::Invalid;
    }
}

Aircraft::Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts) 
: mType(type)
, mSprite(textures.get(Table[mType].texture))
{
    assert(type >= Eagle && type < Acicraftcount);
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    std::unique_ptr<TextNode> healthDisplay = std::make_unique<TextNode>(fonts, "");
    mHealthDisplay = healthDisplay.get(); 
    attachChild(std::move(healthDisplay));

    updateText();
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Aircraft::updateCurrent(sf::Time dt)
{

    updateText();
    updateMoveMentPattern(dt);
    Entity::updateCurrent(dt);
}

Category::Type Aircraft::getCategory() const 
{
    switch (mType)
    {
        case Eagle:
            return Category::PlayerAircraft;
        default:
            return Category::EnemyAircraft;
    }
}

void Aircraft::updateMoveMentPattern(sf::Time dt)
{
     
    const auto& directions = Table[mType].directions;
    if (!directions.empty())
    {
        float distanceToTravel = directions[mDirectionIndex].distance;
        if (mTravelledDistance > distanceToTravel)
        {
            mDirectionIndex = (mDirectionIndex + 1) % directions.size();
            mTravelledDistance = 0.f;
        }

        float radiances = toRadian(directions[mDirectionIndex].angle + 90.f);
        float vx = getMaxSpeed() * std::cos(radiances);
        float vy = getMaxSpeed() * std::sin(radiances);
        setVelocity(vx, vy);
        mTravelledDistance += getMaxSpeed() * dt.asSeconds();
    }


}

void Aircraft::updateText() 
{

    mHealthDisplay->setString(std::to_string(getHitpoints()) +  "HP");
    mHealthDisplay->setPosition(0.f, 50.f);
    mHealthDisplay->setRotation(-getRotation());
}

float Aircraft::getMaxSpeed() const
{
	return Table[mType].speed;
}