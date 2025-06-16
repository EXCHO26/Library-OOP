#include "Reader.hpp"

void Reader::readBorrowedPaper(std::ifstream &in, BorrowedPaper& borr)
{
    if (!in) throw std::invalid_argument("Cannot open file for reading borrowed paper");

    in.read((char *)&borr.paperID, sizeof(borr.paperID));
    in.read((char *)&borr.borrowedAt, sizeof(borr.borrowedAt));
    in.read((char *)&borr.dueAt, sizeof(borr.dueAt));
    in.read((char *)&borr.isReturned, sizeof(borr.isReturned));

    if (!in) throw std::invalid_argument("Failed to read borrowed paper");
}

void Reader::writeBorrowedPaper(std::ofstream &out, const BorrowedPaper& borr) const
{
    if (!out) throw std::invalid_argument("Cannot open file for writing borrowed paper");

    out.write((const char *)&borr.paperID, sizeof(borr.paperID));
    out.write((const char *)&borr.borrowedAt, sizeof(borr.borrowedAt));
    out.write((const char *)&borr.dueAt, sizeof(borr.dueAt));
    out.write((const char *)&borr.isReturned, sizeof(borr.isReturned));

    if (!out) throw std::invalid_argument("Failed to write borrowed paper");
}

Reader::Reader(std::ifstream& file) : User(file)
{
    if (!file) throw std::invalid_argument("Cannot open file to create a reader");

    unsigned borrowedCount;
    file.read((char *)&borrowedCount, sizeof(borrowedCount));

    borrowedPapers.resize(borrowedCount);

    for (int i = 0; i < borrowedCount; i++)
    {
        readBorrowedPaper(file, borrowedPapers[i]);
    }

    if (!file) throw std::invalid_argument("Failed to create the reader");
}

Reader::Reader(const std::string &username, const std::string &password) : User(username, password) {};

void Reader::borrowPaper(int paperID, time_t due)
{
    BorrowedPaper borr;
    borr.paperID = paperID;
    borr.dueAt = due;
    borr.borrowedAt = std::time(nullptr);
    borr.isReturned = false;

    borrowedPapers.push_back(borr);
}

void Reader::returnPaper(int paperID)
{
    for (int i = 0; i < borrowedPapers.size(); i++)
    {
        if (borrowedPapers[i].paperID == paperID && !borrowedPapers[i].isReturned)
        {
            borrowedPapers[i].isReturned = true;
            borrowedPapers[i].dueAt = std::time(nullptr);
            return;
        }
    }

    throw std::invalid_argument("Reader does not have this book!");
}

void Reader::printInfo() const
{
    this->User::printInfo();

    char timeBuffer[20];
    for (int i = 0; i < borrowedPapers.size(); i++)
    {
        std::cout << "Book ID: " << borrowedPapers[i].paperID << " - ";
        if (!borrowedPapers[i].isReturned)
        {
            std::cout << "Not returned, due: ";

            std::tm* tmPtr = std::localtime(&borrowedPapers[i].dueAt);
            std::strftime(timeBuffer, sizeof(timeBuffer), "%d.%m.%Y", tmPtr);
            std::cout << timeBuffer << '\n';
        }
        else std::cout << "Returned" << '\n';
    }
}

void Reader::saveOnFile(std::ofstream &out) const
{
    if (!out) throw std::invalid_argument("Cannot open file to save the reader!");

    UserType type = getUserType();
    out.write((const char *)&type, sizeof(type));

    this->User::saveOnFile(out);

    unsigned borrowedCount = borrowedPapers.size();
    out.write((const char *)&borrowedCount, sizeof(borrowedCount));

    for (int i = 0; i < borrowedCount; i++)
    {
        writeBorrowedPaper(out, borrowedPapers[i]);
    }

    if (!out) throw std::invalid_argument("Failed to save the reader!");
}

User* Reader::clone() const
{
    return new Reader(*this);
}

void Reader::takeBook(unsigned id)
{
    time_t now = std::time(nullptr);
    time_t dueAt = now + 30 * 24 * 60 * 60; // Every reader must return the book in 30 days
    BorrowedPaper entry{id, now, dueAt, false};
    borrowedPapers.push_back(entry);
}

void Reader::giveBook(unsigned id)
{
    for (int i = 0; i < borrowedPapers.size(); i++)
    {
        if (borrowedPapers[i].paperID == id && !borrowedPapers[i].isReturned)
        {
            borrowedPapers[i].isReturned = true;
            borrowedPapers[i].dueAt = std::time(nullptr);
            return;
        }
    }
}