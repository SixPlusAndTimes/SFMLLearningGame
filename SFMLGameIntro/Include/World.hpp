#ifndef WORLD_H
#define WORLD_H
#include <array>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifier.hpp>
#include <SceneNode.hpp>
#include <Aircraft.hpp>

class World : public sf::NonCopyable
{
    public:
        explicit World(sf::RenderWindow& window);
        void update(sf::Time dt);
        void draw();

    private:
        void loadTextures();
        void buildScene();

    private:
        enum 
        {
            Background,
            Air,
            LayerCount
        };
    private:
        sf::RenderWindow&                   mWindow;
        sf::View                            mWorldView;
        TextureHolder                       mTextures; 
        SceneNode                           mSceneGragh;
        std::array<SceneNode*, LayerCount>  mSceneLayers;
        sf::FloatRect                       mWorldBounds;
        sf::Vector2f                        mSpawnPosition;
        float                               mScrollSpeed;
        Aircraft*                           mPlayerAircraft;
};
#endif // WORLD_HBlendNone