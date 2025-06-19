#include "TakeCommand.hpp"

TakeCommand::TakeCommand(std::vector<std::string> &tokens) : tokens(tokens) {};

void TakeCommand::execute(LibrService &service) const
{
    service.take(stringToIndex(tokens[1]));
}