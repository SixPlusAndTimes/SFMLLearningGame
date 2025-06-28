#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <World.hpp>
#include <Player.hpp>
class Game {
    public:
        Game();
        void run();
    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();
        void updateStatistics(sf::Time elapsedTime);
        void processInput();
    private: 
        static const float PlayerSpeed;
        static const sf::Time  TimePerFrame;
        sf::RenderWindow    mWindow;
        World               mWorld;
        Player              mPlayer;
        sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;
};


#endif // GAME_H