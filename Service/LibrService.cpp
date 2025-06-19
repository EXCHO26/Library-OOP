#include "LibrService.hpp"

void LibrService::adminOnly() const
{
    if (loggedUser->getUserType() != User::ADMIN)
    {
        throw std::invalid_argument("Only an admin can do this!");
    }
}

void LibrService::readerOnly() const
{
    if (loggedUser->getUserType() != User::READER)
    {
        throw std::invalid_argument("Only an reader can do this!");
    }
}

void LibrService::checkLogged() const
{
    if (!loggedUser) throw std::logic_error("No user is logged in!");
}

LibrService::LibrService(std::ifstream &libr, std::ifstream& taken, std::ifstream &users)
    : books(libr), taken(taken), users(users)
{
    if (this->users.getSize() == 0)
    {
        std::cout << "There are no users! Added system user! Username: admin, Password: i<3c++" << '\n';
        this->users.addUser(new Admin("admin", "i<3c++", "email@.com"));
    }
}

void LibrService::login(const std::string &username, const std::string &password)
{
    if (loggedUser) throw std::invalid_argument("Someone is already logged!");
    if (!users[username]) throw std::invalid_argument("No such user!");

    if (users[username]->login(password))
    {
        loggedUser = users[username];
        std::cout << "Welcome " << username << "!" << '\n';
    }
    else throw std::invalid_argument("Invalid password or username!");
}

void LibrService::logout()
{
    checkLogged();
    std::cout << "Goodbye! " << loggedUser->getUsername() << '\n';
    loggedUser = nullptr;
}

void LibrService::showBooks() const
{
    books.showType(Papers::Type::BOOK);
}

void LibrService::showPerodical() const
{
    books.showType(Papers::Type::PERIODICAL);
}

void LibrService::showSeries() const
{
    books.showType(Papers::Type::SERIES);
}

void LibrService::showAll() const
{
    books.showType(Papers::ALL);
}

void LibrService::getInfo(const std::string &isbn) const
{
    checkLogged();
    books.showDetailedInfo(isbn);
}

void LibrService::addBook(Papers* book)
{
    checkLogged();
    adminOnly();
    books.addPaper(book);
}

void LibrService::removeBook(unsigned id)
{
    checkLogged();
    adminOnly();
    books.removePaper(id);
    taken.removePaper(id);

    for (int i = 0; i < users.getSize(); i++)
    {
        if (users[i]->getUserType() == User::READER)
        {
            std::vector<User::BorrowedPaper>& temp = users[i]->getBooksTaken();
            for (int j = 0; j < temp.size();)
            {
                if (temp[j].paperID == id)
                {
                    temp.erase(temp.begin() + j);
                }
                else j++;
            }
        }
    }
}

void LibrService::changeBook(unsigned id)
{
    books[id]->change();
}

void LibrService::findPaper(const std::string& option, const std::string &value, Papers::Type type,
                       bool sorted, bool asc, const std::string &key, int top)
{
    checkLogged();
    books.find(option, value, type, sorted, asc, key, top);
}

void LibrService::addUser(User *user)
{
    checkLogged();
    adminOnly();
    users.addUser(user);
}

void LibrService::removeUser(User *user)
{
    if (!user) return;

    checkLogged();
    adminOnly();

    bool perm = false;

    if (user == loggedUser) 
    {
        if (users.adminCount() == 1)
        {
            std::cout << "Cannot remove all users!" << '\n';
            logout();
            return;
        }
        logout();
    }

    if (user->getUserType() == User::READER)
    {
        for (int i = 0; i < user->getBooksTaken().size(); i++)
        {
            if (user->getBooksTaken()[i].isReturned == false)
            {
                if (!perm)
                {
                    char ch;
                    std::cout << "User have unreturned book! Countinue: (Y/N) :";
                    std::cin >> ch;
                    if (std::toupper(ch) != 'Y') return;
                    perm = true;
                }
                taken.removePaper(user->getBooksTaken()[i].paperID);
            }
        }
    }
    
    users.removeUser(user->getUsername());
}

void LibrService::removeUser(const std::string &username)
{
    removeUser(users[username]);
}

void LibrService::changeSelfPass(const std::string &pass)
{
    checkLogged();
    loggedUser->setPassword(pass);
}

void LibrService::changeOtherPass(const std::string &username, const std::string &pass)
{
    checkLogged();
    adminOnly();
    if (users[username])
    {
        users[username]->setPassword(pass);
    }
    else throw std::invalid_argument("No such user!");
}

void LibrService::take(unsigned id)
{
    checkLogged();
    readerOnly();

    if (!books[id]) throw std::invalid_argument("No book with such id!");

    books.transfer(id, taken);
    loggedUser->takeBook(id);
}

void LibrService::give(unsigned id)
{
    checkLogged();
    readerOnly();

    for (int i = 0; i < loggedUser->getBooksTaken().size(); i++)
    {
        if (loggedUser->getBooksTaken()[i].paperID == id)
        {
            taken.transfer(id, books);
            loggedUser->giveBook(id);
            return;
        }
    }
}

void LibrService::findUserName(const std::string &name) const
{
    checkLogged();
    adminOnly();

    users.showAllWithName(name);
}

void LibrService::findUserId(unsigned id) const
{
    checkLogged();
    adminOnly();

    users.showAllWithBook(id);
}

void LibrService::findUserStatus(const std::string &status) const
{
    checkLogged();
    adminOnly();

    if (status == "overdue") 
    {
        users.showAllOverdue();
        return;
    }

    if (status == "reader")
    {
        users.showAllReaders();
        return;
    } 

    if (status == "inactive") 
    {
        users.showAllInactive();
        return;
    }

    throw std::invalid_argument("Invalid status!");
}

void LibrService::save(std::ofstream &libr, std::ofstream& taken, std::ofstream &users)
{
    this->books.save(libr);
    this->taken.save(taken);
    this->users.save(users);
}


