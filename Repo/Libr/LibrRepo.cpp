#include "LibrRepo.hpp"

Papers** LibrRepo::copyRepo(const LibrRepo &other, unsigned newCapacity)
{
    Papers** newRepo = new Papers*[newCapacity] {};
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

void LibrRepo::resize()
{
    Papers **newRepo = copyRepo(*this, this->capacity * 2);
    this->free();
    this->repo = newRepo;
    this->capacity *= 2;
}

void LibrRepo::free()
{
    for (int i = 0; i < this->size; ++i)
    {
        delete this->repo[i];
    }
    delete[] this->repo;
    this->repo = nullptr;

    // Dont reset size because it is used in resize()
}

Papers* LibrRepo::factory(std::ifstream &in) const
{
    Papers::Type type;
    in.read((char*)&type, sizeof(type));

    switch (type)
    {
        case Papers::BOOK:       return new Book(in);
        case Papers::PERIODICAL: return new Periodical(in);
        case Papers::SERIES:     return new Series(in);
        default : throw std::runtime_error("Unknown paper type");
    }
}

LibrRepo::LibrRepo() : repo(nullptr), size(0), capacity(2)
{
    this->repo = new Papers*[capacity] {};
};

LibrRepo::LibrRepo(std::ifstream& in) : repo(nullptr), size(0), capacity(2)
{
    if (!in) throw std::invalid_argument("Cannot open file to create libr repo!");

    in.read((char*)&size, sizeof(size));

    if (size <= 1) 
    {
        this->repo = new Papers*[capacity] {};
    }
    else
    {
        // Capacity = closest power of 2 greater than or equal to count
        this->capacity = std::ceil(log2(size));
        this->repo = new Papers*[this->capacity] {};
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

LibrRepo::LibrRepo(const LibrRepo &other)
{
    this->capacity = other.capacity;
    this->size = other.size;
    this->repo = copyRepo(other, other.capacity);
}

LibrRepo& LibrRepo::operator=(const LibrRepo &other)
{
    if (this != &other)
    {
        Papers** buffer = copyRepo(other, other.capacity);
        this->free();
        this->repo = buffer;
        this->size = other.size;
        this->capacity = other.capacity;
    }
    return *this;
}

LibrRepo::~LibrRepo()
{
    this->free();
}

void LibrRepo::addPaper(Papers *paper)
{
    if (this->size >= this->capacity)
    {
        this->resize();
    }
    this->repo[this->size++] = paper;
}

void LibrRepo::removePaper(int id)
{
    for (unsigned i = 0; i < this->size; ++i)
    {
        if (this->repo[i]->getID() == id)
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

void LibrRepo::transfer(unsigned id, LibrRepo &other)
{
   for (unsigned i = 0; i < this->size; ++i)
    {
        if (this->repo[i]->getID() == id)
        {
            other.addPaper(this->repo[i]);

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

unsigned LibrRepo::getCopies(std::string &isbn) const
{
    unsigned copies = 0;
    for (int i = 0; i < size; i++)
    {
        if (repo[i]->getISBN() == isbn) copies++;
    }
    return copies;
}

void LibrRepo::showType(Papers::Type type) const
{
    for (int i = 0; i < size; i++)
    {
        if (repo[i]->getType() == type)
        {
            printBook(i);
        }
    }
}
void LibrRepo::showAll() const
{
    for (int i = 0; i < size; i++)
    {
        printBook(i);
    }
}

void LibrRepo::showDetailedInfo(const std::string &isbn) const
{
    for (int i = 0; i < size; i++)
    {
        if (repo[i]->getISBN() == isbn)
        {
            repo[i]->printInfo();
        }
    }
}

void LibrRepo::printBook(unsigned idx) const
{
    if (idx >= this->size) return;

    std::cout << "ID: " << this->repo[idx]->getID() << " - ";
    std::cout << this->repo[idx]->getTitle() << " - ";
    std::cout << this->repo[idx]->getPublisher() << " - ";
    std::cout << "ISBN: " << this->repo[idx]->getISBN() << '\n';
}

void LibrRepo::save(std::ofstream& out) const
{
    out.write((const char*)&this->size, sizeof(this->size));
    for (int i = 0; i < this->size; ++i)
    {
        this->repo[i]->saveOnFile(out);
    }
}

const Papers* LibrRepo::operator[](const std::string &title) const
{
    for (unsigned i = 0; i < this->size; ++i)
    {
        if (this->repo[i]->getTitle() == title)
        {
            return this->repo[i];
        }
    }
    return nullptr;
}

const Papers* LibrRepo::operator[](int id) const
{
    for (unsigned i = 0; i < this->size; ++i)
    {
        if (this->repo[i]->getID() == id)
        {
            return this->repo[i];
        }
    }
    return nullptr;
}