#ifndef RESOURCEIDENTIFIER_H
#define RESOURCEIDENTIFIER_H

namespace sf
{
    class Texture;
}

namespace Textures
{
    enum ID
    {
        Eagel,
        Raptor,
        Desert,
        Invalid
    };
}

template<typename ResourceType, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
#endif // RESOURCEIDENTIFIER_H