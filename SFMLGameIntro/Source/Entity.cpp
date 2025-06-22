#include <Entity.hpp>
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

void Entity::updateCurrent(sf::Time dt) 
{
    move(mVelocity * dt.asSeconds()); // fun move() inherite from transformable
}

sf::Vector2f SceneNode::getWorldPosition() const 
{
    return getWorldTransform() * sf::Vector2f(); // why default Vector2f
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

