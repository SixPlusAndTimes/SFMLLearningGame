#include <World.hpp>
#include <SpriteNode.hpp>
#include <iostream>
#include <format>
#include <cmath>
World::World(sf::RenderWindow& window, FontHolder& fonts)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mFonts(fonts)
, mSceneGragh() // root node
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
, mPlayerAircraft(nullptr)
, mCommandQueue()
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

    mPlayerAircraft->setVelocity(0.f, 0.f); // note here, player speed set zero first before each rendering

    // Forward commands to the scene gragh
    while (!mCommandQueue.isEmpty())
    {
        mSceneGragh.onCommand(mCommandQueue.pop(), dt);
    }

    // diagonal speed should be devided by sqrt2
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();
    if(velocity.x != 0 && velocity.y != 0)
    {
        mPlayerAircraft->setVelocity(velocity / std::sqrt(2.0f));
    }
    mPlayerAircraft->accelerate(0.f, mScrollSpeed);

    spawnEnemies();
    // update scenenodes
    mSceneGragh.update(dt, mCommandQueue);

    // restrict player position in bounds
    sf::FloatRect viewBounds{mWorldView.getCenter() - mWorldView.getSize() / 2.0f, mWorldView.getSize()};
    const float borderDistance = 40.f;
    sf::Vector2f position = mPlayerAircraft->getPosition();
    position.x = std::max(position.x,
        viewBounds.left + borderDistance);
    position.x = std::min(position.x,
        viewBounds.left + viewBounds.width - borderDistance);    position.y = std::max(position.y,
        viewBounds.top + borderDistance);
    position.y = std::min(position.y,
        viewBounds.top + viewBounds.height - borderDistance);    mPlayerAircraft->setPosition(position);
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGragh);
}


void World::loadTextures()
{
    mTextures.load(Textures::Eagel, "Media/Textures/Eagle.png");
    mTextures.load(Textures::Desert, "Media/Textures/Desert.png");
    mTextures.load(Textures::Raptor, "Media/Textures/Raptor.png");
    mTextures.load(Textures::Avenger, "Media/Textures/Avenger.png");
    mTextures.load(Textures::Bullet, "Media/Textures/Bullet.png");
    mTextures.load(Textures::Missile, "Media/Textures/Missile.png");
}

void World::buildScene()
{
    // Create SCeneLayerNode, and attach them to the root node 
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();

        mSceneGragh.attachChild(std::move(layer));
    }

    // setup desert background
    sf::Texture& texture =  mTextures.get(Textures::Desert);
    texture.setRepeated(true);
    sf::IntRect textureRect(mWorldBounds);
    SceneNode::Ptr backgroundSprinte = std::make_unique<SpriteNode>(texture, textureRect);
    backgroundSprinte->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprinte));

    // player aircraft
    std::unique_ptr<Aircraft> leader = std::make_unique<Aircraft>(Aircraft::Eagle, mTextures, mFonts);
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(0.f, mScrollSpeed);
    mSceneLayers[Air]->attachChild(std::move(leader));

    addEnemies();
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

sf::FloatRect World::getViewBounds() const
{
    return sf::FloatRect(mWorldView.getCenter() - mWorldView.getSize() / 2.0f, mWorldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const
{
    sf::FloatRect bounds = getViewBounds();
    bounds.top -= 100.f;
    bounds.height += 100.f;
    return bounds;
}

void World::addEnemies() 
{
	addEnemy(Aircraft::Raptor,    0.f,  100.f);
	// addEnemy(Aircraft::Raptor,    0.f, 1000.f);
	// addEnemy(Aircraft::Raptor, +100.f, 1100.f);
	// addEnemy(Aircraft::Raptor, -100.f, 1100.f);
	// addEnemy(Aircraft::Avenger, -70.f, 1100.f);
	// addEnemy(Aircraft::Avenger, -70.f, 1600.f);
	// addEnemy(Aircraft::Avenger,  70.f, 1400.f);
	// addEnemy(Aircraft::Avenger,  70.f, 1600.f);

	std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(), [] (SpawnPoint lhs, SpawnPoint rhs)
	{
		return lhs.y < rhs.y;
	});
}

void World::addEnemy(Aircraft::Type type, float relX, float relY) 
{
    SpawnPoint spawn(type, mSpawnPosition.x + relX, mSpawnPosition.y - relY);
	mEnemySpawnPoints.push_back(spawn); 
}

void World::spawnEnemies() 
{
    while (!mEnemySpawnPoints.empty() && mEnemySpawnPoints.back().y > getBattlefieldBounds().top) 
    {
        SpawnPoint spawn = mEnemySpawnPoints.back();

        std::unique_ptr<Aircraft> enemy = std::make_unique<Aircraft>(spawn.type, mTextures, mFonts);
        enemy->setPosition(spawn.x, spawn.y);
        enemy->setRotation(180.f);
        mSceneLayers[Air]->attachChild(std::move(enemy));

        mEnemySpawnPoints.pop_back();
    }
}
