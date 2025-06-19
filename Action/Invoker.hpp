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

/// @brief Responsible for parsing input commands and executing them using LibrService.
class Invoker
{
    public:
        /// @brief Default constructor for Invoker.
        Invoker();

        /// @brief Starts the command processing loop.
        void run();

    private:
        /// @brief Tokenizes a raw input string into command tokens.
        /// @param input The raw input line to tokenize.
        /// @return A vector of strings representing the separated tokens.
        static std::vector<std::string> tokenize(const std::string &input);

        /// @brief Parses and handles a single command line input.
        /// @param line The input command line string.
        void handleCommand(const std::string& line);

        /// @brief Prints help information or available commands to the user.
        void printHelp() const;

    private:
        /// @brief The library service instance to operate on.
        LibrService service;

        /// @brief Tracks whether the last login attempt failed.
        bool failedLogin = false;
};

#endif