#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Window/Event.hpp>
#include <CommandQueue.hpp>
#include <map>
class Player
{
    public:
        enum Action
        {
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            ActionCount
        };
        Player();
        void                assignKey(Action action, sf::Keyboard::Key key);
        sf::Keyboard::Key   getAssignedKey(Action action) const;
        void                handleEvent(const sf::Event& event, CommandQueue& commandQueue);
        void                handleRealtimeInput(CommandQueue& commandQueue);
    private:
        static bool         isRealtimeAction(Action action);
    private:
        std::map<sf::Keyboard::Key, Action> mKeyBinding;
        std::map<Action, Command>           mActionBinding;

};

#endif // PLAYER_H