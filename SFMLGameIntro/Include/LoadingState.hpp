#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H
#include "State.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "ParallelTask.hpp"
class LoadingState : public State
{
    public:
        LoadingState(StateStack &stack, Context context);

        void    draw() override;
        bool    update(sf::Time dt) override;
        bool    handleEvent(const sf::Event& event) override;

        void    setCompletion(float percent);

    private:
        sf::Text    mLoadingText; 
        sf::RectangleShape mProcessBarBackground;
        sf::RectangleShape mProcessBar;

        ParallelTask mLoadingTask;
};

#endif // LOADINGSTATE_H