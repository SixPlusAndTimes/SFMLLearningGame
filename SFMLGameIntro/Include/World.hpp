#ifndef WORLD_H
#define WORLD_H
#include <array>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "ResourceHolder.hpp"
#include "ResourceIdentifier.hpp"
#include "SceneNode.hpp"
#include "Aircraft.hpp"
#include "BloomEffect.hpp"
#include "CommandQueue.hpp"

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
		explicit							World(sf::RenderTarget& outputTarget, FontHolder& fonts);
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
        void                                handleCollisions();
        void                                adaptPlayerPosition();
        void								destroyEntitiesOutsideView();
    private:
        enum 
        {
            Background,
            LowerAir,
            HigherAir,
            LayerCount
        };

    private:
		sf::RenderTarget&					mTarget;
        sf::RenderTexture					mSceneTexture;

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

        BloomEffect							mBloomEffect;
};
#endif // WORLD_HBlendNone