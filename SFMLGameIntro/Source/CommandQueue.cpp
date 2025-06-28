#include <CommandQueue.hpp>
#include <cassert>
CommandQueue::CommandQueue()
:mQueue()
{

}

void CommandQueue::push(const Command& command)
{
    mQueue.push(command);
}

Command CommandQueue::pop()
{
    if (isEmpty())
    {
        assert("CommandQueue is empty!");
        return Command();
    }
    
    Command ret = mQueue.front();
    mQueue.pop();
    return ret;
}

Command& CommandQueue::top()
{
    if (isEmpty())
    {
        assert("CommandQueue is empty!");
    }
    return mQueue.front();
} 
bool CommandQueue::isEmpty() const
{
    return mQueue.empty();
}
