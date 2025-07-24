#include "Application.hpp"
#include "GameState.hpp"
#include "TitleState.hpp"
#include "PauseState.hpp"
#include "MenuState.hpp"
#include "SettingsState.hpp"
const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);

Application::Application()
: mWindow(sf::VideoMode(640, 480), "States", sf::Style::Close)
, mTextures()
, mFonts()
, mPlayer()
, mStateStack(State::Context(mWindow, mTextures, mFonts, mPlayer))
, mStatisticsText()
, mStatisticsUpdateTime()
, mStatisticFrameNums(0)
{
    mWindow.setKeyRepeatEnabled(false);

    mFonts.load(Fonts::Main, "Media/Sansation.ttf");
    mTextures.load(Textures::TitleScreen, "Media/Textures/TitleScreen.png");
	mTextures.load(Textures::ButtonNormal,		"Media/Textures/ButtonNormal.png");
	mTextures.load(Textures::ButtonSelected,	"Media/Textures/ButtonSelected.png");
	mTextures.load(Textures::ButtonPressed,		"Media/Textures/ButtonPressed.png");

	mStatisticsText.setFont(mFonts.get(Fonts::Main));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10u);

	registerStates();
	mStateStack.pushState(States::Title);
}

Application::~Application()
{

}

void Application::run()
{
    sf::Clock clock;
    sf::Time  timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);
            if (mStateStack.isEmpty())
            {
                // if no states in statestack, it is time to exit
                mWindow.close();
            }
        }
        render();
    }
}

void Application::processInput() 
{
    sf::Event event;
    while (mWindow.pollEvent(event)) 
    {
        mStateStack.handlleEvent(event);

        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }
}

void Application::update(sf::Time dt) 
{
    mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();
    mStateStack.draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticsText);
    mWindow.display();
}

void Application::updateStatistics(sf::Time dt)
{
    mStatisticsUpdateTime += dt;
	mStatisticFrameNums += 1;
	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString("FPS: " + std::to_string(mStatisticFrameNums));

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticFrameNums = 0;
	}
}

void    Application::registerStates()
{
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<PauseState>(States::Pause);
    mStateStack.registerState<SettingsState>(States::Settings);
}
