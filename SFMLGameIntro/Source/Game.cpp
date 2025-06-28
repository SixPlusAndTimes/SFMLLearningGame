#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <StringHelpers.hpp>
const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close)
, mWorld(mWindow)
, mPlayer()
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
{

	if (!mFont.loadFromFile("Media/Sansation.ttf")) {
		printf("load font failed\n");
	}
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
}

void Game::run() 
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processInput();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}


void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
							 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}

void Game::update(sf::Time deltaTime) 
{
	mWorld.update(deltaTime);
}
void Game::render()
{
	mWindow.clear();
	mWorld.draw();

	mWindow.draw(mStatisticsText);
	mWindow.display();
}


void Game::processInput()
{
	CommandQueue& commandQueue = mWorld.getCommandQueue();
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		mPlayer.handleEvent(event, commandQueue);

		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
		mPlayer.handleRealtimeInput(commandQueue);
	}
}