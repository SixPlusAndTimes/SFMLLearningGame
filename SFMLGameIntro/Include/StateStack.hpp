#ifndef STATESTACK_H
#define STATESTACK_H
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <functional>
#include <map>
#include "State.hpp"
#include "StateIdentifier.hpp"
class StateStack : public sf::NonCopyable
{
    public:
        enum Action
        {
            Push,
            Pop,
            Clear
        };

    public:
        explicit StateStack(State::Context context);
        

        void    update(sf::Time dt);
        void    draw();
        void    handlleEvent(sf::Event& event);

        void    pushState(States::ID stateId);
        void    popState();
        void    clearState();
        bool    isEmpty();

        template <typename T>
        void    registerState(States::ID stateId);

    private:
        State::Ptr createState(States::ID stateID);
        void       applyPendingChanges();
    private:
        struct PendingChange
        {
            explicit    PendingChange(Action action, States::ID id = States::None);
            Action      mAction;
            States::ID  mStateId;
        };
    private:
        std::vector<State::Ptr> mStack;
        std::vector<PendingChange>  mPendingList;

        State::Context  mContext;
        std::map<States::ID, std::function<State::Ptr()>> mFactory;
};

// to be understanded
template <typename T>
void StateStack::registerState(States::ID stateId) {
    // 1. this refer to what? -- refer to statestack NOT the caller
    // 2. what if we do not capture this? -- lambda cannot capture lambda implicitly
    mFactory[stateId] = [this]() {
        return State::Ptr(std::make_unique<T>(*this, mContext));
	};
}

#endif // STATESTACK_H