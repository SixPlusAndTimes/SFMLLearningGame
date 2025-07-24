#ifndef WORLD_H
#define WORLD_H
#include <array>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifier.hpp>
#include <SceneNode.hpp>
#include <Aircraft.hpp>
#include <CommandQueue.hpp>

class World : public sf::NonCopyable
{
    public:
        struct SpawnPoint
        {
            SpawnPoint(Aircraft::Type type, float x, float y)
            : type(type)
            , x(x)
            , y(y)
            {}

            Aircraft::Type type;
            float          x;
            float          y;
        };
        
    public:
                                            explicit World(sf::RenderWindow& window, FontHolder& fonts);
        void                                update(sf::Time dt);
        void                                draw();
        CommandQueue&                       getCommandQueue();

    private:
        void                                loadTextures();
        void                                buildScene();
        void								addEnemies();
		void								addEnemy(Aircraft::Type type, float relX, float relY);
        void                                spawnEnemies();
        sf::FloatRect						getViewBounds() const;
		sf::FloatRect						getBattlefieldBounds() const;
        void                                guideMissiles();

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
        FontHolder&							mFonts;
        SceneNode                           mSceneGragh;
        std::array<SceneNode*, LayerCount>  mSceneLayers;
        sf::FloatRect                       mWorldBounds;
        sf::Vector2f                        mSpawnPosition;
        float                               mScrollSpeed;
        Aircraft*                           mPlayerAircraft;
        CommandQueue                        mCommandQueue;
        std::vector<SpawnPoint>             mEnemySpawnPoints;
        std::vector<Aircraft*>              mActivateEnemies;
};
#endif // WORLD_HBlendNone