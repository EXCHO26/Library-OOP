#include "FindCommand.hpp"

FindCommand::FindCommand(std::vector<std::string> &tokens) : tokens(tokens) {};

void FindCommand::findUser(LibrService& service) const
{
    if (tokens.size() != 4) return;
    if (tokens[2] == "name")
    {
        service.findUserName(tokens[3]);
        return;
    }
    if (tokens[2] == "ID")
    {
        service.findUserId(stringToIndex(tokens[3]));
        return;
    }
    if (tokens[2] == "state")
    {
        service.findUserStatus(tokens[3]);
        return;
    }
}

void FindCommand::findBook(LibrService& service) const
{
    bool isSorted = false;
    bool isTop = false;
    bool asc;
    std::string key;
    int top = -1;

    for (int i = 4; i < tokens.size(); i++)
    {
        if (tokens[i] == "sort")
        {
            isSorted = true;
            if (tokens.size() > i + 1)
            {
                key = tokens[i + 1];
            }
            else throw std::invalid_argument("Bad sort command!");
            if (tokens.size() > i + 2 && (tokens[i + 2] == "asc" || tokens[i + 2] == "desc"))
            {
                asc = tokens[i + 2] == "asc";
            }
        }
        if (tokens[i] == "top")
        {
            isTop = true;
            if (tokens.size() > i + 1)
            {
                top = stringToIndex(tokens[i + 1]);
            }
            else throw std::invalid_argument("Bad sort command!");
        }
    }

    if (tokens[0] == "books")
    {
        service.findPaper(tokens[2], tokens[3], Papers::BOOK, isSorted, asc, key, top);
        return;
    }
    if (tokens[0] == "newsletters")
    {
        service.findPaper(tokens[2], tokens[3], Papers::PERIODICAL, isSorted, asc, key, top);
        return;
    }
    if (tokens[0] == "series")
    {
        service.findPaper(tokens[2], tokens[3], Papers::SERIES, isSorted, asc, key, top);
        return;
    }
    if (tokens[0] == "list")
    {
        service.findPaper(tokens[2], tokens[3], Papers::ALL, isSorted, asc, key, top);
        return;
    }
}

void FindCommand::execute(LibrService &service) const
{
    if (tokens.front() == "user") findUser(service);
    else findBook(service);
}