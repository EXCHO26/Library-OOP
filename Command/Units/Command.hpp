#ifndef COMMAND_HEADER
#define COMMAND_HEADER

#include "../../Service/LibrService.hpp"

class Command
{
    public:
        virtual ~Command() = default;
        virtual void execute(LibrService& service) = 0;
};

#endif
