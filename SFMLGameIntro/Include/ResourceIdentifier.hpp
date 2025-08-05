#ifndef RESOURCEIDENTIFIER_H
#define RESOURCEIDENTIFIER_H

namespace sf
{
    class Texture;
    class Font;
    class Shader;
}

namespace Textures
{
    enum ID
    {
        Entities,
        Jungle,
        Buttons,
        TitleScreen,
        Explosion,
        Particle,
        FinishLine,
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

namespace Shaders
{
	enum ID
	{
		BrightnessPass,
		DownSamplePass,
		GaussianBlurPass,
		AddPass,
	};
}

template<typename ResourceType, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>   TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>			FontHolder;
typedef ResourceHolder<sf::Shader, Shaders::ID>	    ShaderHolder;
#endif // RESOURCEIDENTIFIER_H