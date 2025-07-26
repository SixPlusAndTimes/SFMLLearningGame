#include "World.hpp"
#include <SpriteNode.hpp>
#include <iostream>
#include <format>
#include <cmath>
#include "Pickup.hpp"
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

bool matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	// Make sure first pair entry has category type1 and second has type2
	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type1 & category2 && type2 & category1)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}
	else
	{
		return false;
	}
}

void World::update(sf::Time dt)
{
    mWorldView.move(0.f, mScrollSpeed * dt.asSeconds());

    destroyEntitiesOutsideView();

	guideMissiles();

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

    handleCollisions();
    mSceneGragh.removeWrecks();

    spawnEnemies();

    mSceneGragh.update(dt, mCommandQueue);

    adaptPlayerPosition();
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

    mTextures.load(Textures::HealthRefill, "Media/Textures/HealthRefill.png");
    mTextures.load(Textures::MissileRefill, "Media/Textures/MissileRefill.png");
    mTextures.load(Textures::FireSpread, "Media/Textures/FireSpread.png");
    mTextures.load(Textures::FireRate, "Media/Textures/FireRate.png");
}

void World::buildScene()
{
    // Create SCeneLayerNode, and attach them to the root node 
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        Category::Type category = (i == Air) ? Category::SceneAirLayer : Category::None;
        SceneNode::Ptr layer = std::make_unique<SceneNode>(category);
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
	addEnemy(Aircraft::Raptor,    0.f, 700.f);
	addEnemy(Aircraft::Avenger, -70.f, 800.f);
	addEnemy(Aircraft::Raptor, +100.f, 1100.f);
	addEnemy(Aircraft::Raptor, -100.f, 1100.f);
	addEnemy(Aircraft::Avenger, -70.f, 1600.f);
	addEnemy(Aircraft::Avenger,  70.f, 1400.f);
	addEnemy(Aircraft::Avenger,  70.f, 1600.f);

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

void World::guideMissiles()
{
    Command enemyCollector;
    enemyCollector.category = Category::EnemyAircraft;
    enemyCollector.action = derivedAction<Aircraft>([this](Aircraft& node, sf::Time dt) 
    {
        if (!node.isDestroyed())
        {
            mActivateEnemies.push_back(&node);
        }
    });

    Command missileGuider;
    missileGuider.category = Category::Projectile;
    missileGuider.action = derivedAction<Projectile>([this](Projectile& missile, sf::Time dt)
        {
            if (!missile.isGuided())
            {
                return ;
            }

            float minDistance = std::numeric_limits<float>::max();
            Aircraft* closestEnemy = nullptr;
            for(Aircraft* enemy : mActivateEnemies)
            {
                float enemyDistance = distance(missile, *enemy);
                if (enemyDistance < minDistance)
                {
                    closestEnemy = enemy;
                    minDistance = enemyDistance;
                }
            }

            if (closestEnemy)
            {
                missile.guideTowards(closestEnemy->getWorldPosition());
            }
        });
        mCommandQueue.push(enemyCollector);
        mCommandQueue.push(missileGuider);
        mActivateEnemies.clear();
}

void World::handleCollisions()
{
	std::set<SceneNode::Pair> collisionPairs;
	mSceneGragh.checkSceneCollision(mSceneGragh, collisionPairs);

    //if (collisionPairs.size() != 0) {
        //std::cout << "collect collision pair, size = " << collisionPairs.size()<< std::endl;
   //     for (auto& [type1, type2] : collisionPairs)
   //     {
			//std::cout << "collision between " << type1->getCategory() << " and " << type2->getCategory() << std::endl;
   //     }
   // } 
    for (SceneNode::Pair pair : collisionPairs)
	{
		if (matchesCategories(pair, Category::PlayerAircraft, Category::EnemyAircraft))
		{
            std::cout << "collision between PlayerAircraft and Enemy Aircraft" << std::endl;;
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& enemy = static_cast<Aircraft&>(*pair.second);

			player.damage(enemy.getHitpoints());
			enemy.destroy();
		}
		else if (matchesCategories(pair, Category::PlayerAircraft, Category::Pickup))
		{
            std::cout << "collision between PlayerAircraft and Pickup" << std::endl;
			auto& player = static_cast<Aircraft&>(*pair.first);
			auto& pickup = static_cast<Pickup&>(*pair.second);

			// Apply pickup effect to player, destroy projectile
			pickup.apply(player);
			pickup.destroy();
		}
		else if (matchesCategories(pair, Category::EnemyAircraft, Category::AlliedProjectile)
			  || matchesCategories(pair, Category::PlayerAircraft, Category::EnemyProjectile))
		{
            std::cout << "collision between aircraft and projectile" << std::endl;
			auto& aircraft = static_cast<Aircraft&>(*pair.first);
			auto& projectile = static_cast<Projectile&>(*pair.second);

			// Apply projectile damage to aircraft, destroy projectile
            //std::cout << "damage :" << projectile.getDamage();
			aircraft.damage(projectile.getDamage());
			projectile.destroy();
		}
	}
}

void World::destroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Projectile | Category::EnemyAircraft;
	command.action = derivedAction<Entity>([this] (Entity& e, sf::Time)
	{
		if (!getBattlefieldBounds().intersects(e.getBoundingRect()))
			e.destroy();
	});

	mCommandQueue.push(command);
}

void World::adaptPlayerPosition()
{
	// Keep player's position inside the screen bounds, at least borderDistance units from the border
	sf::FloatRect viewBounds = getViewBounds();
	const float borderDistance = 40.f;

	sf::Vector2f position = mPlayerAircraft->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayerAircraft->setPosition(position);
}