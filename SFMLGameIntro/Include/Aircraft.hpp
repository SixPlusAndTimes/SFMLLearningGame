#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <Entity.hpp>
#include <ResourceIdentifier.hpp>
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
        virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void    updateCurrent(sf::Time dt);
    private:
        Type        mType;
        sf::Sprite  mSprite;
        TextNode*	mHealthDisplay;
        float       mTravelledDistance;
        int         mDirectionIndex;

    private:
        virtual Category::Type  getCategory() const override;
        void    updateText();
        void    updateMoveMentPattern(sf::Time dt);
        float   getMaxSpeed() const;
};


#endif // AIRCRAFT_H