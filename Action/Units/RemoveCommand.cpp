#include "RemoveCommand.hpp"

RemoveCommand::RemoveCommand(std::vector<std::string> &tokens) : tokens(tokens) {};

void RemoveCommand::execute(LibrService& service) const
{
    if (tokens.front() == "user")
    {
        service.removeUser(tokens[2]);
        return;
    }

    if (tokens.front() == "list")
    {
        
        service.removeBook(stringToIndex(tokens[2]));
    }
}