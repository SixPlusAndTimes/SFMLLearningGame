#include<SFML/Graphics.hpp>
#ifndef GAME_H
#define GAME_H
class Game {
    public:
        Game();
        void run();
    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void updateStatistics(sf::Time elapsedTime);
    private: 
        static const float PlayerSpeed;
        static const sf::Time  TimePerFrame;
        sf::RenderWindow mWindow;
        sf::Texture mTexture;
        sf::Sprite  mPlayer;
        
        sf::Font				mFont;
		sf::Text				mStatisticsText;
		sf::Time				mStatisticsUpdateTime;
		std::size_t				mStatisticsNumFrames;

		bool mIsMovingUp;
		bool mIsMovingDown;
		bool mIsMovingLeft;
		bool mIsMovingRight;
};


#endif // GAME_H