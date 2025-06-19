#ifndef USER_REPO_HEADER
#define USER_REPO_HEADER

#include <cmath>

#include "Units/Reader.hpp"
#include "Units/Admin.hpp"

class UserRepo
{
    public:
        UserRepo();
        UserRepo(std::ifstream& in);
        UserRepo(const UserRepo &other);
        UserRepo &operator=(const UserRepo &other);
        ~UserRepo();

        void addUser(User *paper);
        void removeUser(const std::string& username);

        unsigned getSize() const { return size; }

        void showAllWithName(const std::string &name) const;
        void showAllWithBook(unsigned id) const;
        void showAllOverdue() const;
        void showAllReaders() const;
        void showAllInactive() const;

        void printUser(unsigned idx) const;
        void save(std::ofstream& out) const;

        User* operator[](const std::string &username);
        User* operator[](unsigned idx);

        int adminCount() const;

    private:
        User **copyRepo(const UserRepo &other, unsigned newCapacity);
        void resize();
        void free();
        bool uniqueUser(const std::string &name);

        User* factory(std::ifstream &in) const;

    private:
        User **repo;
        unsigned size;
        unsigned capacity;
};

#endif