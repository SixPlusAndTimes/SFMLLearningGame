#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <Entity.hpp>
#include <ResourceIdentifier.hpp>
#include "Projectile.hpp"
class TextNode;
class Aircraft : public Entity
{
    public:
        enum Type
        {
            Eagle,
            Raptor,
            Avenger,
            Acicraftcount,
        };

    public:
        explicit        Aircraft(Type type, const TextureHolder& textures, const FontHolder& fonts);
        virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void    updateCurrent(sf::Time dt, CommandQueue& commandQueue) override;
        void            fire();
        void            launchMissile();
        virtual unsigned int getCategory() const override;

        void            increaseFireRate();
		void            increaseSpread();
		void            collectMissiles(unsigned int count);

		virtual sf::FloatRect	getBoundingRect() const override;
    private:
        Type        mType;
        sf::Sprite  mSprite;
        TextNode*	mHealthDisplay;
        float       mTravelledDistance;
        int         mDirectionIndex;
        bool        mIsFiring;
        sf::Time    mFireCountDown;
        int         mFireRateLevel;
        int         mSpreadLevel;
        int         mMissileAmmo;
        bool        mIsLaunchingMissile;
        Command     mFireCommand;
		Command     mMissileCommand;
        bool        mIsMarkedForRemoval;
        Command     mDropPickupCommand;
    private:
        void            updateText();
        void            updateMoveMentPattern(sf::Time dt);
        float           getMaxSpeed() const;
        void            checkProjectileLaunch(sf::Time dt, CommandQueue& commandQueue);
        void            createProjectile(SceneNode& node, Projectile::Type type, float xOffset, float yOffset, const TextureHolder& textures) const;
        void            createBullets(SceneNode& node, const TextureHolder& textures) const;
        bool            isAllied() const;
        virtual bool    isMarkedForRemoval() const;
        void            checkPickupDrop(CommandQueue& commands);
        void            createPickup(SceneNode& node, const TextureHolder& textures) const;
};

#endif // AIRCRAFT_H