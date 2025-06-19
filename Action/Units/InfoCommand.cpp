#include "InfoCommand.hpp"

InfoCommand::InfoCommand(std::vector<std::string> &tokens) : tokens(tokens) {};

void InfoCommand::execute(LibrService& service) const
{
    if (tokens.size() == 2)
    {
        if (tokens.front() == "books") service.showBooks();
        else if (tokens.front() == "newsletters") service.showPerodical();
        else if (tokens.front() == "series") service.showSeries();
        else if (tokens.front() == "list") service.showAll();
    }
    else if (tokens.size() == 3)
    {
        service.getInfo(tokens.back());
    }
}