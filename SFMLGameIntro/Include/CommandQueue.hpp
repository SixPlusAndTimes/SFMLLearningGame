#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H
#include <Command.hpp>
#include <queue>

class CommandQueue
{
    public:
        CommandQueue();
        void     push(const Command& command);
        Command  pop();
        Command&  top();
        bool     isEmpty() const;
    private:
        std::queue<Command> mQueue;
};

#endif // COMMANDQUEUE_H