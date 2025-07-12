#ifndef STATE_H
#define STATE_H
#include <memory>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "StateIdentifier.hpp"
#include "ResourceIdentifier.hpp"

namespace sf
{
	class RenderWindow;
}
class StateStack;
class Player;

class State
{
    public:
        typedef std::unique_ptr<State> Ptr;
        struct Context
        {
            Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);
            sf::RenderWindow*   mWindow;
            TextureHolder*      mTextures;
            FontHolder*         mFonts;
            Player*				mPlayer;
        };

    public:
                    State(StateStack &stack, Context context);
        virtual     ~State();
        virtual     void draw() = 0;
        virtual     bool update(sf::Time dt) = 0;
        virtual     bool handleEvent(const sf::Event &event) = 0;

    protected:
        void        requestStackPush(States::ID);
        void        requestStackPop();
        void        requestStackClear();
        Context     getContext() const;

    private:
        StateStack *mStateStack;
        Context mContext;
};

#endif // STATE_H