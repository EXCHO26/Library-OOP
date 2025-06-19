#ifndef REMOVE_COMMAND
#define REMOVE_COMMAND

#include "Command.hpp"

class RemoveCommand : public Command
{
    public:
        RemoveCommand(std::vector<std::string> &tokens);

        void execute(LibrService& service) const override;

    private:
        std::vector<std::string> tokens;
};

#endif