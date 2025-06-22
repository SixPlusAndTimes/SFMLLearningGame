#include <Aircraft.hpp>
#include <ResourceHolder.hpp>
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
Aircraft::Aircraft(Type type, const TextureHolder& textures) 
: mType(type)
, mSprite(textures.get(toTextureId(type)))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Aircraft::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}