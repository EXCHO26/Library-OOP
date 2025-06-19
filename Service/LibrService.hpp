#ifndef LIBR_SERVICE_HEADER
#define LIBR_SERVICE_HEADER

#include "../Repo/Libr/LibrRepo.hpp"
#include "../Repo/Users/UserRepo.hpp"

class LibrService
{
    public:
        LibrService() = default;
        LibrService(std::ifstream &libr, std::ifstream& taken, std::ifstream &users);

        // Login/out methods
        void login(const std::string &username, const std::string &password);
        void logout();

        // Book info methods
        void showBooks() const;
        void showPerodical() const;
        void showSeries() const;
        void showAll() const;
        void getInfo(const std::string &isbn) const;

        // Book alter methods
        void addBook(Papers* book);
        void removeBook(unsigned id);
        void changeBook(unsigned id);

        // Book find methods
        void findPaper(const std::string &option, const std::string &value, Papers::Type type,
                       bool sorted = false, bool asc = true, const std::string &key = "", int top = 0);

        // User alter methods
        void addUser(User *user);
        void removeUser(User *user);
        void removeUser(const std::string &username);
        void changeSelfPass(const std::string &pass);
        void changeOtherPass(const std::string &username, const std::string &pass);

        // User find methods
        void findUserName(const std::string &name) const;
        void findUserId(unsigned id) const;
        void findUserStatus(const std::string &status) const;

        // Take/Return methods
        void take(unsigned id);
        void give(unsigned id);

        // Save method
        void save(std::ofstream &libr, std::ofstream& taken, std::ofstream &users);

        void adminOnly() const;
        void readerOnly() const;
        void checkLogged() const;
        
    private:
        LibrRepo books;
        LibrRepo taken;
        UserRepo users;

        User *loggedUser = nullptr;
};

#endif