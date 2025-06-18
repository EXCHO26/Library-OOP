#include "Invoker.hpp"

Invoker::Invoker(std::ifstream &libr, std::ifstream &taken, std::ifstream &users)
    : service(libr, taken, users) {};

void Invoker::run()
{
    std::string line;
    while (true)
    {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) continue;

        if (line == "exit")
        {
            SessionCommand exit(SessionCommand::EXIT);
            exit.execute(service);
            break;
        }

        try
        {
            handleCommand(line);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

void Invoker::handleCommand(const std::string& line)
{
    std::vector<std::string> tokens = tokenize(line);
}