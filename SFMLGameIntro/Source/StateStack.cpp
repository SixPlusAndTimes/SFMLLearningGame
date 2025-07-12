#include <cassert>
#include <iostream>
#include "StateStack.hpp"
StateStack::StateStack(State::Context context)
: mContext(context)
{
    
}

StateStack::PendingChange::PendingChange(Action action, States::ID id)
: mAction(action)
, mStateId(id)
{
}

State::Ptr StateStack::createState(States::ID stateID) 
{
    auto found = mFactory.find(stateID);
    assert(found != mFactory.end());
    return found->second();
}

void StateStack::handlleEvent(sf::Event& event) 
{
    // std::cout << "state stack handle event" << std::endl;
    for (auto iter = mStack.rbegin(); iter != mStack.rend(); ++iter)
    {
        // std::cout << "  state stack handle event iter1" << std::endl;
        if (!(*iter)->handleEvent(event))
            break;
    }
    applyPendingChanges();
}

void StateStack::update(sf::Time dt) 
{

    for (auto iter = mStack.rbegin(); iter != mStack.rend(); ++iter)
    {
        if (!(*iter)->update(dt))
            break;
    }
    applyPendingChanges();
}

void StateStack::draw() 
{
    for (auto& state : mStack)
    {
        state->draw();
    }
}


void StateStack::pushState(States::ID stateId) 
{
    mPendingList.push_back(PendingChange(Push, stateId));
}

void StateStack::popState() 
{
    mPendingList.push_back(PendingChange(Pop));
}

void StateStack::clearState() 
{
    mPendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() 
{
    return mStack.empty();
}

void StateStack::applyPendingChanges() 
{
    for (auto& pendingChange : mPendingList)
    {
        switch (pendingChange.mAction)
        {
            case Push:
                mStack.push_back(createState(pendingChange.mStateId));
                break;
            case Pop:
                mStack.pop_back();
                break;
            case Clear:
                mStack.clear();
                break;
            default:
                assert("invalid stateID");
                break;
        }
    }
    mPendingList.clear();
}
