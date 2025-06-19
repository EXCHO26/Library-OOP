#ifndef COMMAND_HEADER
#define COMMAND_HEADER

#include "../../Service/LibrService.hpp"

class Command
{
    public:
        virtual ~Command() = default;
        virtual void execute(LibrService& service) const = 0;

    protected:
        static unsigned stringToIndex(const std::string &line);
};

#endif
