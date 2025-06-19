#include "Command.hpp"

unsigned Command::stringToIndex(const std::string &line)
{
    unsigned result = 0;

    if (line.empty()) throw std::invalid_argument("Empty string cannot be converted to index");

    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] < '0' || '9' < line[i]) throw std::invalid_argument("String contains non digit symbols");
    }

    for (int i = 0; i < line.size(); i++)
    {
        result = result * 10 + (line[i] - '0');
    }

    return result;
}