#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "LoadingState.hpp"
#include "ResourceHolder.hpp"
#include "utils.hpp"

LoadingState::LoadingState(StateStack &stack, Context context)
: State(stack, context)
{
    sf::RenderWindow& window = *getContext().mWindow;
	sf::Font& font = context.mFonts->get(Fonts::Main);
	sf::Vector2f viewSize = window.getView().getSize();

    mLoadingText.setFont(font);
	mLoadingText.setString("Loading Resources");
	centerOrigin(mLoadingText);
	mLoadingText.setPosition(viewSize.x / 2.f, viewSize.y / 2.f + 50.f);

    mProcessBarBackground.setFillColor(sf::Color::White);
	mProcessBarBackground.setSize(sf::Vector2f(viewSize.x - 20, 10));
	mProcessBarBackground.setPosition(10, mLoadingText.getPosition().y + 40);

	mProcessBar.setFillColor(sf::Color(100,100,100));
	mProcessBar.setSize(sf::Vector2f(200, 10));
	mProcessBar.setPosition(10, mLoadingText.getPosition().y + 40);

	setCompletion(0.f);
}

void LoadingState::draw() 
{
    sf::RenderWindow& window = *getContext().mWindow;

    window.setView(window.getDefaultView());

    window.draw(mLoadingText);
    window.draw(mProcessBarBackground);
    window.draw(mProcessBar);
}

bool LoadingState::update(sf::Time dt) 
{
 	// // Update the progress bar from the remote task or finish it
	// if (mLoadingTask.isFinished())
	// {
	// 	requestStackPop();
	// 	requestStackPush(States::Game);
	// }
	// else
	// {
	// 	setCompletion(mLoadingTask.getCompletion());
	// }
	// return true;   
}

bool LoadingState::handleEvent(const sf::Event& event) 
{
    return true;
}


void LoadingState::setCompletion(float percent) {
	if (percent > 1.f) // clamp
		percent = 1.f;

	mProcessBar.setSize(sf::Vector2f(mProcessBarBackground.getSize().x * percent, mProcessBar.getSize().y));
}