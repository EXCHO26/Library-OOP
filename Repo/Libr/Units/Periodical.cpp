#include "Periodical.hpp"

void Periodical::readArticle(std::ifstream &in, Article &article)
{
    Papers::readString(in, article.title);
    Papers::readString(in, article.author);

    size_t keyWordCount;
    in.read((char *)&keyWordCount, sizeof(keyWordCount));
    if (!in) throw std::runtime_error("Failed to read article key word count.");

    article.keyWords.resize(keyWordCount);
    for (int i = 0; i < keyWordCount; i++)
    {
        Papers::readString(in, article.keyWords[i]);
    }

    if (!in) throw std::runtime_error("Failed to read article key words.");
}

void Periodical::writeArticle(std::ofstream &out, const Article &article) const
{
    if (!out) throw std::invalid_argument("Cannot open the file for writing article.");

    Papers::writeString(out, article.title);
    Papers::writeString(out, article.author);

    size_t keyWordCount = article.keyWords.size();
    out.write((const char *)&keyWordCount, sizeof(keyWordCount));
    if (!out) throw std::runtime_error("Failed to write article key word count.");

    for (int i = 0; i < keyWordCount; i++)
    {
        Papers::writeString(out, article.keyWords[i]);
    }

    if (!out) throw std::runtime_error("Failed to write article key words.");
}

void Periodical::print() const
{
    std::cout << "Month: " << month << '\n';
    std::cout << "Issue Number: " << issueNumber << '\n';
    std::cout << "Articles:" << '\n';

    for (int i = 0; i < articles.size(); i++)
    {
        std::cout << "  Title: " << articles[i].title << '\n';
        std::cout << "  Author: " << articles[i].author << '\n';
        std::cout << "  Key Words: ";
        for (int j = 0; j < articles[i].keyWords.size(); j++)
        {
            std::cout << articles[i].keyWords[j];
            if (j < articles[i].keyWords.size() - 1) std::cout << ", ";
        }
        std::cout << '\n';
        std::cout << '\n';
    }
}

void Periodical::save(std::ofstream &out) const
{
    out.write((const char *)&month, sizeof(month));
    out.write((const char *)&issueNumber, sizeof(issueNumber));

    size_t articleCount = articles.size();
    out.write((const char *)&articleCount, sizeof(articleCount));
    for (int i = 0; i < articleCount; i++)
    {
        writeArticle(out, articles[i]);
    }
}

Periodical::Periodical(std::ifstream& file) : Papers(file)
{
    if (!file) throw std::invalid_argument("Cannot open the file for periodical creation!");

    file.read((char *)&month, sizeof(month));
    file.read((char *)&issueNumber, sizeof(issueNumber));

    size_t articleCount;
    file.read((char *)&articleCount, sizeof(articleCount));

    articles.resize(articleCount);
    for (size_t i = 0; i < articleCount; ++i)
    {
        readArticle(file, articles[i]);
    }

    if (!file) throw std::runtime_error("Failed to read articles from file.");
}

Periodical::Periodical(const std::string &title, const std::string &publisher, const std::string &description,
                       const std::string &isbn, unsigned yearPublished, double rating, 
                       const std::string &genre, unsigned month, unsigned issueNumber,
                       const std::vector<Article> &articles)
    : Papers(title, publisher, description, isbn, yearPublished, rating, genre), 
      month(month), issueNumber(issueNumber), articles(articles)
{
    if (month < 1 || month > 12) throw std::invalid_argument("Month must be between 1 and 12.");
    if (issueNumber == 0) throw std::invalid_argument("Issue number cannot be zero.");
}

Periodical::Periodical(const Periodical &other) : Papers(other), 
    month(other.month), issueNumber(other.issueNumber), articles(other.articles)
{};

Periodical &Periodical::operator=(const Periodical &other)
{
    if (this != &other) 
    {
        Papers::operator=(other);
        month = other.month;
        issueNumber = other.issueNumber;
        articles = other.articles;
    }
    return *this;
}

void Periodical::setIssueNumber(unsigned issueNumber)
{
    if (issueNumber == 0) throw std::invalid_argument("Issue number cannot be zero.");
    this->issueNumber = issueNumber;
}

void Periodical::setMonth(unsigned month)
{
    if (month < 1 || month > 12) throw std::invalid_argument("Month must be between 1 and 12.");
    this->month = month;
}

void Periodical::setArticle(const std::vector<Article> &articles)
{
    this->articles = articles;
}

void Periodical::printInfo() const
{
    Papers::printInfo();
    this->print();
}

void Periodical::saveOnFile(std::ofstream &out) const
{
    if (!out) throw std::invalid_argument("Cannot open the file for saving periodical!");

    Type type = Papers::PERIODICAL;
    out.write((const char *)&type, sizeof(type));

    Papers::saveOnFile(out);
    this->save(out);

    if (!out) throw std::runtime_error("Failed to save periodical to file.");
}

Papers *Periodical::clone() const
{
    return new Periodical(*this);
}