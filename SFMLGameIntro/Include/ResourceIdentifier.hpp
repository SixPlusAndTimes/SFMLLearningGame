#ifndef RESOURCEIDENTIFIER_H
#define RESOURCEIDENTIFIER_H

namespace sf
{
    class Texture;
    class Font;
}

namespace Textures
{
    enum ID
    {
        Eagel,
        Raptor,
        Desert,
        ButtonNormal,
        ButtonSelected,
        ButtonPressed,
        TitleScreen,
        Invalid,
    };
}
namespace Fonts
{
    enum ID
    {
        Main
    };
}

template<typename ResourceType, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;
#endif // RESOURCEIDENTIFIER_H