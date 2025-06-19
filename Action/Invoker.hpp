#ifndef INVOKER_HEADER
#define INVOKER_HEADER

#include "../Service/LibrService.hpp"
#include "./Units/SessionCommand.hpp"
#include "./Units/InfoCommand.hpp"
#include "./Units/AddCommand.hpp"
#include "./Units/RemoveCommand.hpp"
#include "./Units/FindCommand.hpp"
#include "./Units/ChangeCommand.hpp"
#include "./Units/TakeCommand.hpp"
#include "./Units/ReturnCommand.hpp"

class Invoker
{
    public:
        Invoker();

        void run();

    private:
        static std::vector<std::string> tokenize(const std::string &input);
        void handleCommand(const std::string& line);
        void printHelp() const;

    private:
        LibrService service;
        bool failedLogin = false;
};

#endif