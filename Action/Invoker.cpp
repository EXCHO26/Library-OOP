#include "Invoker.hpp"

Invoker::Invoker()
{
    std::ifstream p1("../papers.dat", std::ios::binary);
    std::ifstream t1("../taken.dat", std::ios::binary);
    std::ifstream u1("../users.dat", std::ios::binary);

    this->service = LibrService(p1, t1, u1);

    p1.close();
    t1.close();
    u1.close();
}

void Invoker::printHelp() const
{
    std::cout << "---Available commands---" << '\n' << '\n';

    std::cout << "-Session commands-" << '\n';
    std::cout << "> login <username> <password>" << '\n';
    std::cout << "> logout" << '\n';
    std::cout << "> exit" << '\n' << '\n';

    std::cout << "-Information commands-" << '\n';
    std::cout << "> <{books, newsletters, series, list}> all" << '\n';
    std::cout << "> list info <isbn>" << '\n' << '\n';

    std::cout << "-Find commands-" << '\n';
    std::cout << "> <{books, newsletters, series, list}> find <option> <option_string> [sort <key> [asc|desc] ] [top <val>]" << '\n';
    std::cout << "> user find <option> <option_string>" << '\n' << '\n';

    std::cout << "-Add/remove commands-" << '\n';
    std::cout << "> <{books, newsletters, series, list}> add" << '\n';
    std::cout << "> user add <username> <password> [admin]" << '\n';
    std::cout << "> list remove id" << '\n';
    std::cout << "user remove <user>" << '\n' << '\n';

    std::cout << "-Change commands-" << '\n';
    std::cout << "> list change <id>" << '\n' << '\n';
    std::cout << "> user change [<name>] <password>" << '\n' << '\n';

    std::cout << "Take/return commads-" << '\n';
    std::cout << "> take <ID>" << '\n';
    std::cout << "> return <ID>" << '\n' << '\n';
}



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

        if (line == "help")
        {
            std::system("cls");
            printHelp();
            continue;
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

std::vector<std::string> Invoker::tokenize(const std::string &input)
{
    std::vector<std::string> tokens;
    std::string current;
    char ch;
    size_t length = input.length();

    for (int i = 0; i < length; i++)
    {
        ch = input[i];

        if (ch == ' ')
        {
            if (!current.empty())
            {
                tokens.push_back(current);
                current.clear();
            }
        }
        else current += ch;
    }

    if (!current.empty()) tokens.push_back(current);

    return tokens;
}

void Invoker::handleCommand(const std::string& line)
{
    std::vector<std::string> tokens = tokenize(line);
    if (tokens.empty()) return;

    if (tokens.front() == "login" && tokens.size() == 3)
    {
        if (failedLogin)
        {
            std::cout << "Loggin had failed, please exit the system!" << '\n';
            return;
        }

        SessionCommand login(SessionCommand::LOGIN, tokens[1], tokens[2]);
        try
        {
            login.execute(service);
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            failedLogin = true;
        }
        return;
    }
    else if (tokens.size() == 1 && tokens.front() == "logout")
    {
        SessionCommand logout(SessionCommand::LOGOUT);
        logout.execute(service);
        return;
    }
    else if (tokens.size() == 2 && tokens.back() == "all" ||
            (tokens.size() == 3 && tokens[1] == "info"))
    {
        InfoCommand info(tokens);
        info.execute(service);
        return;
    }
    else if ((tokens.size() == 2 && tokens.back() == "add") ||
            ((tokens.size() == 4 || tokens.size() == 6) && tokens[0] == "user" && tokens[1] == "add"))
    {
        AddCommand add(tokens);
        add.execute(service);
        return;
    }
    else if (tokens.size() == 3 && tokens[1] == "remove")
    {
        RemoveCommand remove(tokens);
        remove.execute(service);
        return;
    }
    else if (tokens.size() > 1 && tokens[1] == "find")
    {
        FindCommand find(tokens);
        find.execute(service);
        return;
    }
    else if (tokens.size() > 1 && tokens[1] == "change")
    {
        ChangeCommand change(tokens);
        change.execute(service);
        return;
    }
    else if (tokens.size() == 2 && tokens[0] == "take")
    {
        TakeCommand take(tokens);
        take.execute(service);
        return;
    }
    else if (tokens.size() == 2 && tokens[0] == "return")
    {
        ReturnCommand ret(tokens);
        ret.execute(service);
        return;
    }
    else std::cout << "Unknown or wrong command.\n";
}