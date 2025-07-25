#ifndef APPLICATION_H
#define APPLICATION_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include "ResourceIdentifier.hpp"
#include "ResourceHolder.hpp"
#include "StateStack.hpp"
#include "Player.hpp"
class Application
{
    public:
                Application();
        void    run();
        virtual ~Application();
    private:
        void    processInput();
        void    update(sf::Time dt);
        void    render();

        void    updateStatistics(sf::Time dt);
        void    registerStates();

    private:
        static const sf::Time   TimePerFrame;
        sf::RenderWindow        mWindow;
        TextureHolder           mTextures;
        FontHolder              mFonts;

        Player                  mPlayer;

        StateStack              mStateStack; 

        sf::Text                mStatisticsText;
        sf::Time                mStatisticsUpdateTime; 
        std::size_t             mStatisticFrameNums;
};


#endif // APPLICATION_H