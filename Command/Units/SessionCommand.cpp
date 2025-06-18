#include "SessionCommand.hpp"

SessionCommand::SessionCommand(Action act, const std::string &username, const std::string &pass)
    : act(act), username(username), password(pass) {};

void SessionCommand::execute(LibrService &service)
{
    switch (act)
    {
    case LOGIN:
        service.login(username, password);
        break;

    case LOGOUT:
        service.logout();
        break;

    case EXIT:
    {
        std::ofstream books("../papers.dat", std::ios::binary);
        std::ofstream taken("../taken.dat", std::ios::binary);
        std::ofstream users("../users.dat", std::ios::binary);

        service.save(books, taken, users);

        books.close();
        taken.close();
        users.close();

        break;
    }
    default:
        break;
    }
}