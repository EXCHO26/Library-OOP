#include "Series.hpp"

Series::Series(std::ifstream &file) : Papers(file), Book(file), Periodical(file) {};

Series::Series(const std::string &title, const std::string &publisher, const std::string &description,
               const std::string &isbn, unsigned yearPublished, double rating, 
               const std::string &genre, unsigned month, unsigned issueNumber,
               const std::vector<Periodical::Article> &articles,
               const std::vector<std::string> &keyWords)
    : Papers(title, publisher, description, isbn, yearPublished, rating, genre),
      Book(title, publisher, description, isbn, yearPublished, rating, genre, keyWords),
      Periodical(title, publisher, description, isbn, yearPublished, rating, genre, month, issueNumber, articles) {};

Series::Series(const Series &other) : Papers(other), Book(other), Periodical(other) {};

Series &Series::operator=(const Series &other)
{
    if (this != &other)
    {
        Papers::operator=(other);
        this->setKeyWords(other.getKeyWords());
        this->setMonth(other.getMonth());
        this->setIssueNumber(other.getIssueNumber());
        this->setArticle(other.getArticles());
    }
    return *this;
}

void Series::printInfo() const
{
    Papers::printInfo();
    Book::print();
    Periodical::print();
}

void Series::saveOnFile(std::ofstream &out) const
{
    Type type = Papers::SERIES;
    out.write((const char*)&type, sizeof(type));

    Papers::saveOnFile(out);
    Book::save(out);
    Periodical::save(out);
}

Papers *Series::clone() const
{
    return new Series(*this);
}

