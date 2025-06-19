#ifndef INFO_COMMAND
#define INFO_COMMAND

#include "Command.hpp"

class InfoCommand : public Command
{
    public:
        InfoCommand(std::vector<std::string> &tokens);

        void execute(LibrService &service) const override;

    private:
        std::vector<std::string> &tokens;
};

#endif