#include <World.hpp>
#include <SpriteNode.hpp>
World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mTextures()
, mSceneGragh() // root node
, mSceneLayers()
, mWorldBounds(0.f, 0.f, mWorldView.getSize().x, 2000.f)
, mSpawnPosition(mWorldView.getSize().x / 2.f, mWorldBounds.height - mWorldView.getSize().y / 2.f)
, mScrollSpeed(-50.f)
, mPlayerAircraft(nullptr)
{
	loadTextures();
	buildScene();

	// Prepare the view
	mWorldView.setCenter(mSpawnPosition);
}

void World::update(sf::Time dt)
{
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

    sf::Vector2f position = mPlayerAircraft->getPosition();
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if (position.x <= mWorldBounds.left + 150
        || position.x >= mWorldBounds.left + mWorldBounds.width - 150)    
    {
        velocity.x = -velocity.x;
        mPlayerAircraft->setVelocity(velocity);
    }
    mSceneGragh.update(dt);
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

    // setup aircrafts
    std::unique_ptr<Aircraft> leader = std::make_unique<Aircraft>(Aircraft::Eagle, mTextures);
    mPlayerAircraft = leader.get();
    mPlayerAircraft->setPosition(mSpawnPosition);
    mPlayerAircraft->setVelocity(40.f, mScrollSpeed);
    mSceneLayers[Air]->attachChild(std::move(leader));

    std::unique_ptr<Aircraft> rightEscort = std::make_unique<Aircraft>(Aircraft::Raptor, mTextures);
    rightEscort->setPosition(80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(rightEscort));

    std::unique_ptr<Aircraft> leftEscort = std::make_unique<Aircraft>(Aircraft::Raptor, mTextures);
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerAircraft->attachChild(std::move(leftEscort));
}