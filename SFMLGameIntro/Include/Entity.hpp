#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/System/Vector2.hpp>
#include <SceneNode.hpp>
#include "CommandQueue.hpp"
class Entity : public SceneNode
{
    public:
        Entity(int hitpoints);
        void            setVelocity(sf::Vector2f velocity);
        void            setVelocity(float vx, float vy);
        sf::Vector2f    getVelocity();
        virtual void    updateCurrent(sf::Time dt, CommandQueue& commandQueue) override;
        void            accelerate(sf::Vector2f velocity);
        void            accelerate(float vx, float vy);

        void            repair(int points);
        void            damage(int points);
        void            destroy();
        int             getHitpoints() const;
        virtual bool    isDestroyed() const override;
    private:
        sf::Vector2f    mVelocity;
        int             mHitpoints;
};

#endif // ENTITY_H