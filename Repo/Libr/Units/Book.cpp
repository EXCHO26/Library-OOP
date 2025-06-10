#include "Book.hpp"

void Book::print() const
{
    std::cout << "Key Words: ";
    for (int i = 0; i < this->keyWords.size(); ++i)
    {
        std::cout << this->keyWords[i];
        if (i < this->keyWords.size() - 1) std::cout << ", ";
    }
    std::cout << '\n';
}

void Book::save(std::ofstream &out) const
{
    size_t count = this->keyWords.size();
    out.write((char *)&count, sizeof(count));
    for (int i = 0; i < count; i++)
    {
        Papers::writeString(out, this->keyWords[i]);
    }
}

Book::Book(std::ifstream& file) : Papers(file)
{
    if (!file) throw std::invalid_argument("Cannot open the file for book creation!");

    size_t keyWordCount;
    file.read((char *)&keyWordCount, sizeof(keyWordCount));

    for (int i = 0; i < keyWordCount; i++)
    {
        std::string keyWord;
        Papers::readString(file, keyWord);
        this->keyWords.push_back(keyWord);
    }

    if (!file) throw std::runtime_error("Failed to read key words from file.");
}

Book::Book(const std::string &title, const std::string &publisher, const std::string &description, 
           const std::string &isbn, unsigned yearPublished, double rating, 
           const std::string &genre, const std::vector<std::string>& keyWords)
    : Papers(title, publisher, description, isbn, yearPublished, rating, genre)
{
    if (keyWords.empty()) throw std::invalid_argument("Key words cannot be empty.");
    this->keyWords = keyWords;
}

Book::Book(const Book &other) : Papers(other)
{
    this->keyWords = other.keyWords;
}

Book &Book::operator=(const Book &other)
{
    if (this != &other) 
    {
        Papers::operator=(other);
        this->keyWords = other.keyWords;
    }
    return *this;
}

void Book::setKeyWords(const std::vector<std::string>& keyWords)
{
    if (keyWords.empty()) throw std::invalid_argument("Key words cannot be empty.");
    this->keyWords = keyWords;
}

void Book::printInfo() const
{
    Papers::printInfo();
    this->print();
}

void Book::saveOnFile(std::ofstream &out) const
{
    if (!out) throw std::invalid_argument("Cannot open the file for saving book!");

    Type type = Papers::BOOK;
    out.write((char *)&type, sizeof(type));

    Papers::saveOnFile(out);
    this->save(out);
}

Papers *Book::clone() const
{
    return new Book(*this);
}

