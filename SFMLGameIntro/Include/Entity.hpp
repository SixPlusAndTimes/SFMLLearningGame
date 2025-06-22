#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/System/Vector2.hpp>
#include <SceneNode.hpp>
class Entity : public SceneNode
{
    public:
        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float vx, float vy);
        sf::Vector2f getVelocity();
        virtual void updateCurrent(sf::Time dt) override;

    private:
        sf::Vector2f mVelocity;
};

#endif // ENTITY_H