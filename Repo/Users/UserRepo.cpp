#include "UserRepo.hpp"

User** UserRepo::copyRepo(const UserRepo &other, unsigned newCapacity)
{
    User** newRepo = new User*[newCapacity] {};
    try
    {
        for (unsigned i = 0; i < other.size; ++i)
        {
            newRepo[i] = other.repo[i]->clone();
        }
        return newRepo;
    }
    catch(const std::exception& e)
    {
        for (unsigned i = 0; i < other.size; ++i)
        {
            if (newRepo[i] != nullptr)
            {
                delete newRepo[i];
            }
        }
        delete[] newRepo;
        throw;
    }
}

void UserRepo::resize()
{
    User **newRepo = copyRepo(*this, this->capacity * 2);
    this->free();
    this->repo = newRepo;
    this->capacity *= 2;
}

void UserRepo::free()
{
    for (int i = 0; i < this->size; ++i)
    {
        delete this->repo[i];
    }
    delete[] this->repo;
    this->repo = nullptr;
}

bool UserRepo::uniqueUser(const std::string &name)
{
    for (int i = 0; i < size; i++)
    {
        if (repo[i]->getUsername() == name)
        {
            return false;
        }
    }
    return true;
}

User* UserRepo::factory(std::ifstream &in) const
{
    User::UserType type;
    in.read((char*)&type, sizeof(type));

    switch (type)
    {
        case User::READER :  return new Reader(in);
        case User::ADMIN  :  return new Admin(in);
        default : throw std::runtime_error("Unknown user type");
    }
}

UserRepo::UserRepo() : repo(nullptr), size(0), capacity(2)
{
    this->repo = new User*[capacity] {};
};

UserRepo::UserRepo(std::ifstream& in) : repo(nullptr), size(0), capacity(2)
{
    if (!in) throw std::invalid_argument("Cannot open the file to create user repo!");

    in.read((char*)&size, sizeof(size));

    if (size <= 1) 
    {
        this->repo = new User*[capacity] {};
    }
    else
    {
        unsigned t = std::ceil(log2(size));
        this->capacity = (1 << t);
        this->repo = new User*[this->capacity] {};
    }

    try
    {
        for (int i = 0; i < size; ++i)
        {
            this->repo[i] = this->factory(in);
        }
    }
    catch(const std::exception& e)
    {
        for (int i = 0; i < size; ++i)
        {
            if (this->repo[i] != nullptr)
            {
                delete this->repo[i];
            }
        }
        delete[] this->repo;
        throw;
    }
}

UserRepo::UserRepo(const UserRepo &other)
{
    this->capacity = other.capacity;
    this->size = other.size;
    this->repo = copyRepo(other, other.capacity);
}

UserRepo& UserRepo::operator=(const UserRepo &other)
{
    if (this != &other)
    {
        User** buffer = copyRepo(other, other.capacity);
        this->free();
        this->repo = buffer;
        this->size = other.size;
        this->capacity = other.capacity;
    }
    return *this;
}

UserRepo::~UserRepo()
{
    this->free();
}

void UserRepo::addUser(User *user)
{
    if (uniqueUser(user->getUsername()))
    {
        if (this->size >= this->capacity)
        {
            this->resize();
        }
        this->repo[this->size++] = user;
    }
    else throw std::invalid_argument("Username is already taken!");
}

void UserRepo::removeUser(const std::string& username)
{
    for (unsigned i = 0; i < this->size; ++i)
    {
        if (this->repo[i]->getUsername() == username)
        {
            delete this->repo[i];

            for (unsigned j = i; j < this->size - 1; ++j)
            {
                this->repo[j] = this->repo[j + 1];
            }

            this->repo[this->size - 1] = nullptr;
            this->size--;
            return;
        }
    }
}

void UserRepo::showAllWithName(const std::string &name) const
{
    for (int i = 0; i < size; i++)
    {
        if (repo[i]->getUsername() == name)
        {
            printUser(i);
            return;
        }
    }
}

void UserRepo::showAllWithBook(unsigned id) const
{
    for (int i = 0; i < size; i++)
    {
        if (repo[i]->getUserType() == User::READER)
        {
            const std::vector<User::BorrowedPaper> &temp = repo[i]->getBooksTaken();
            for (int j = 0; j < temp.size(); j++)
            {
                if (temp[j].paperID == id && temp[j].isReturned == false)
                {
                    printUser(i);
                    break;
                }
            }
        }
    }
}

void UserRepo::showAllOverdue() const
{
    const time_t oneDay = 60 * 60 * 24;
    const time_t yesterday = std::time(nullptr) - oneDay;

    for (int i = 0; i < size; i++)
    {
        if (repo[i]->getUserType() == User::READER)
        {
            const std::vector<User::BorrowedPaper> &temp = repo[i]->getBooksTaken();
            for (int j = 0; j < temp.size(); j++)
            {
                if (temp[j].isReturned == false && temp[j].dueAt < yesterday)
                {
                    printUser(i);
                    break;
                }
            }
        }
    }
}

void UserRepo::showAllReaders() const
{
    const time_t oneMonth = 60 * 60 * 24 * 30;
    const time_t monthAgo = std::time(nullptr) - oneMonth;
    int count;

    for (int i = 0; i < size; i++)
    {
        count = 0;
        if (repo[i]->getUserType() == User::READER)
        {
            const std::vector<User::BorrowedPaper> &temp = repo[i]->getBooksTaken();
            for (int j = 0; j < temp.size(); j++)
            {
                if (temp[j].borrowedAt > monthAgo) count++;
            }
            if (count >= 5) printUser(i);
        }
    }
}

void UserRepo::showAllInactive() const
{
    const time_t oneMonth = 60 * 60 * 24 * 30;
    const time_t threeMonthAgo = std::time(nullptr) - oneMonth * 3;
    bool active = false;

    for (int i = 0; i < size; i++)
    {
        active = false;
        if (repo[i]->getUserType() == User::READER)
        {
            const std::vector<User::BorrowedPaper> &temp = repo[i]->getBooksTaken();
            for (int j = 0; j < temp.size(); j++)
            {
                if (temp[j].borrowedAt > threeMonthAgo)
                {
                    active = true;
                    break;
                }
            }
            if (!active) printUser(i);
        }
    }
}

void UserRepo::printUser(unsigned idx) const
{
    if (idx >= this->size) return;

    time_t time = this->repo[idx]->getLastLoginAt();

    if (this->repo[idx]->getUserType() == User::ADMIN)
    {
        std::cout << "ADMIN - ";
    }
    std::cout << this->repo[idx]->getUsername() << " - ";
    std::cout << std::ctime(&time);
    std::cout << '\n';
}

void UserRepo::save(std::ofstream& out) const
{
    if (!out) throw std::invalid_argument("Cannot open the file to save the user repo!");

    out.write((const char*)&size, sizeof(size));

    for (int i = 0; i < this->size; ++i)
    {
        this->repo[i]->saveOnFile(out);
    }

    if (!out) throw std::invalid_argument("Failed to save the user repo!");
}

User* UserRepo::operator[](const std::string &username)
{
    for (unsigned i = 0; i < this->size; ++i)
    {
        if (this->repo[i]->getUsername() == username)
        {
            return this->repo[i];
        }
    }
    return nullptr;
}

User* UserRepo::operator[](unsigned idx)
{
    if (idx >= size) throw std::out_of_range("Index is out of range!");

    return repo[idx];
}

int UserRepo::adminCount() const
{
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        if (repo[i]->getUserType() == User::ADMIN) result++;
    }
    return result;
}


