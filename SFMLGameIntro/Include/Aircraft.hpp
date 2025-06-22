#ifndef AIRCRAFT_H
#define AIRCRAFT_H
#include <Entity.hpp>
#include <ResourceIdentifier.hpp>
class Aircraft : public Entity
{
    public:
        enum Type
        {
            Eagle,
            Raptor
        };

    public:
        explicit        Aircraft(Type type, const TextureHolder& textures);
        virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    private:
        Type        mType;
        sf::Sprite  mSprite;
};


#endif // AIRCRAFT_H