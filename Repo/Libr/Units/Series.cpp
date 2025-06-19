#include "Series.hpp"

Series::Series(std::ifstream &file) : Papers(file), Book(file), Periodical(file) {};

Series::Series(const std::string &title, const std::string &publisher, const std::string &description,
               const std::string &isbn, unsigned yearPublished, double rating, 
               const std::string &genre, unsigned month, unsigned issueNumber,
               const std::vector<Periodical::Article> &articles,
               const std::vector<std::string> &keyWords,
               const std::string &autor)
    : Papers(title, publisher, description, isbn, yearPublished, rating, genre),
      Book(title, publisher, description, isbn, yearPublished, rating, genre, keyWords, autor),
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

void Series::change()
{
    unsigned month, issueNumber;
    std::vector<std::string> keyWords;
    std::string input;

    std::cout << " > Month: ";
    std::cin >> month;
    if (month < 1 || month > 12) throw std::invalid_argument("Month must be between 1 and 12.");

    std::cout << " > Issue Number: ";
    std::cin >> issueNumber;
    if (issueNumber == 0) throw std::invalid_argument("Issue number cannot be zero.");

    std::cout << "Enter keywords (empty line to stop):\n";
    while (true) 
    {
        std::getline(std::cin, input);
        if (input.empty()) break;
        keyWords.push_back(input);
    }

    this->Papers::change();

    setKeyWords(keyWords);
    setMonth(month);
    setIssueNumber(issueNumber);
}

bool Series::matchAutor(const std::string &autor) const
{
    return Book::matchAutor(autor);
}

bool Series::matchTaggs(const std::string &taggs) const
{
    return Book::matchTaggs(taggs) || Periodical::matchTaggs(taggs);
}
