#ifndef INVOKER_HEADER
#define INVOKER_HEADER

#include "../Service/LibrService.hpp"
#include "./Units/SessionCommand.hpp"

class Invoker
{
    public:
        Invoker(std::ifstream &libr, std::ifstream& taken, std::ifstream &users);

        void run();

    private:
        static std::vector<std::string> tokenize(const std::string &input);
        void handleCommand(const std::string& line);

    private:
        LibrService service;
};

#endif