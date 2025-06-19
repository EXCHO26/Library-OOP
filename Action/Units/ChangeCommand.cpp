#include "ChangeCommand.hpp"

ChangeCommand::ChangeCommand(std::vector<std::string> &tokens) : tokens(tokens) {};

void ChangeCommand::execute(LibrService &service) const
{
    if (tokens[0] == "list")
    {
        service.changeBook(stringToIndex(tokens[2]));
    }
    if (tokens[0] == "user")
    {
        if (tokens.size() == 4)
        {
            service.changeOtherPass(tokens[2], tokens[3]);
        }
        if (tokens.size() == 3)
        {
            service.changeSelfPass(tokens[2]);
        }
    }
}