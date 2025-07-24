#include "Aircraft.hpp"
#include <memory>
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
: Entity(Table[type].hitpoints)
, mType(type)
, mHealthDisplay(nullptr)
, mSprite(textures.get(Table[mType].texture))
, mTravelledDistance(0)
, mDirectionIndex(0)
, mIsFiring(false)
, mFireCountDown(sf::Time::Zero)
, mFireRateLevel(1)
, mSpreadLevel(1)
, mMissileAmmo(2)
, mIsLaunchingMissile(false)
, mFireCommand()
, mMissileCommand()
{
    centerOrigin(mSprite);

    mFireCommand.category = Category::SceneAirLayer;
    mFireCommand.action = 
    [this, &textures](SceneNode& node, sf::Time dt) {
        createBullets(node, textures);
    };

    mMissileCommand.category = Category::SceneAirLayer;
    mMissileCommand.action = 
    [this, &textures](SceneNode& node, sf::Time dt) {
        createProjectile(node, Projectile::Missile, 0.f, 0.5f, textures);
    };

    assert(type >= Eagle && type < Acicraftcount);
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    std::unique_ptr<TextNode> healthDisplay = std::make_unique<TextNode>(fonts, "");
    mHealthDisplay = healthDisplay.get(); 
    attachChild(std::move(healthDisplay));

    updateText();
}


void Aircraft::createBullets(SceneNode& node, const TextureHolder& textures) const 
{
    Projectile::Type type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

	switch (mSpreadLevel)
	{
		case 1:
			createProjectile(node, type, 0.0f, 0.5f, textures);
			break;

		case 2:
			createProjectile(node, type, -0.33f, 0.33f, textures);
			createProjectile(node, type, +0.33f, 0.33f, textures);
			break;

		case 3:
			createProjectile(node, type, -0.5f, 0.33f, textures);
			createProjectile(node, type,  0.0f, 0.5f, textures);
			createProjectile(node, type, +0.5f, 0.33f, textures);
			break;
	}
}

void Aircraft::createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const
{
    std::unique_ptr<Projectile> projectile = std::make_unique<Projectile>(type, textures);
    sf::Vector2f offset(xOffset * mSprite.getGlobalBounds().width, yOffset * mSprite.getGlobalBounds().height);
    sf::Vector2f velocity(0.f, projectile->getMaxSpeed());

    float sign = isAllied() ? -1.f : 1.f;
    projectile->setPosition(getWorldPosition() + offset * sign); // why here we need get world position ?
    projectile->setVelocity(velocity * sign);
    node.attachChild(std::move(projectile));

}

bool Aircraft::isAllied() const
{
    return mType == Eagle;
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Aircraft::updateCurrent(sf::Time dt, CommandQueue& commandQueue)
{
    checkProjectileLaunch(dt, commandQueue);
    updateText();
    updateMoveMentPattern(dt);
    Entity::updateCurrent(dt, commandQueue);
}

void Aircraft::checkProjectileLaunch(sf::Time dt, CommandQueue& commandQueue)
{
    if (!isAllied())
    {
        fire();
    }

    if (mIsFiring && mFireCountDown <= sf::Time::Zero)
    {
        commandQueue.push(mFireCommand);
        mFireCountDown += sf::seconds(1.f / mFireRateLevel + 1);
        mIsFiring = false;
    }
    else if (mFireCountDown >= sf::Time::Zero)
    {
        mFireCountDown -= dt;
    }

    if (mIsLaunchingMissile)
    {
        commandQueue.push(mMissileCommand);
        mIsLaunchingMissile = false;
    }

}

unsigned int Aircraft::getCategory() const
{
	if (isAllied())
		return Category::PlayerAircraft;
	else
		return Category::EnemyAircraft;
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

void Aircraft::fire() 
{
	// Only ships with fire interval != 0 are able to fire
	if (Table[mType].fireInterval != sf::Time::Zero) // does fireInterval only be used in here
    {
		mIsFiring = true;
    }
}

void Aircraft::launchMissile() 
{
	if (mMissileAmmo > 0)
	{
		mIsLaunchingMissile = true;
		--mMissileAmmo;
	}
}
