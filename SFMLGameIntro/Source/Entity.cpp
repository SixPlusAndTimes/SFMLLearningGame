#include <Entity.hpp>
Entity::Entity(int hitpoints)
: mVelocity()
, mHitpoints(hitpoints)
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity()
{
    return mVelocity;
}

void Entity::updateCurrent(sf::Time dt, CommandQueue& commandQueue) 
{
    move(mVelocity * dt.asSeconds()); // function move() inherite from transformable
}

sf::Vector2f SceneNode::getWorldPosition() const 
{
    return getWorldTransform() * sf::Vector2f(); // why using default Vector2f? I mean why dimension is a since transform matrix is 3 * 3 -- May be converted to Homogeneous coordinates autimatically
}

sf::Transform SceneNode::getWorldTransform() const 
{
    sf::Transform  transform = sf::Transform::Identity;
    for (const SceneNode* node = this; node != nullptr; node = node->mParent)
    {
        transform = node->getTransform() * transform;
    }
    return transform;
}


void Entity::accelerate(sf::Vector2f velocity)
{
    mVelocity += velocity;
}

void Entity::accelerate(float vx, float vy)
{
    mVelocity.x += vx;
    mVelocity.y += vy;
}

void Entity::repair(int points) 
{
	assert(points > 0);

	mHitpoints += points;
}

void Entity::damage(int points) 
{
	assert(points > 0);

	mHitpoints -= points;
}

void Entity::destroy() 
{
	mHitpoints = 0;
}

int  Entity::getHitpoints() const 
{
    return mHitpoints;
}

bool Entity::isDestroyed() const 
{
	return mHitpoints <= 0;
}
