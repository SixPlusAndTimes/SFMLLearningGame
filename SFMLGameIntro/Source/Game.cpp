#include <Game.hpp>
#include <SFML/Graphics.hpp>
#include <StringHelpers.hpp>
const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game()
: mWindow(sf::VideoMode(640, 480), "SFML Application", sf::Style::Close)
, mTexture()
, mPlayer() 
, mFont()
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticsNumFrames(0)
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
{
	if (!mTexture.loadFromFile("Media/Texture/Eagle.png")) {
		printf("load texture failed\n");
	}
	mPlayer.setTexture(mTexture);
	mPlayer.setPosition(100.f, 100.f);

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

			processEvents();
			update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processEvents() 
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::KeyPressed: 
			{
				printf("KeyBoard[%d] pressd\n", event.key.code);
				handlePlayerInput(event.key.code, true);
				break;
			}
			case sf::Event::KeyReleased: 
			{
				printf("KeyBoard[%d] released\n", event.key.code);
				handlePlayerInput(event.key.code, false);
				break;
			}
			case sf::Event::Closed: 
			{
				mWindow.close();
				break;
			}
			default:
				break;
		}
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
	sf::Vector2f movement(0.f, 0.f);
	if (mIsMovingUp)
		movement.y -= 1.f * PlayerSpeed;
	if (mIsMovingDown)
		movement.y += 1.f * PlayerSpeed;
	if (mIsMovingLeft)
		movement.x -= 1.f * PlayerSpeed;
	if (mIsMovingRight)
		movement.x += 1.f * PlayerSpeed;
	
	// printf("update movement.x[%f] movement.y[%f], deltaTime.asSeconds()[%f]\n", movement.x, movement.y, deltaTime.asSeconds());
	mPlayer.move(movement * deltaTime.asSeconds());
}
void Game::render()
{
	mWindow.clear();
	mWindow.draw(mPlayer);
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::W)
		mIsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		mIsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		mIsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		mIsMovingRight = isPressed;
}