#include "ReturnCommand.hpp"

ReturnCommand::ReturnCommand(std::vector<std::string> &tokens) : tokens(tokens) {};

void ReturnCommand::execute(LibrService &service) const
{
    service.give(stringToIndex(tokens[1]));
}