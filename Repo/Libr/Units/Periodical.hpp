#ifndef PERIODICAL_HEADER
#define PERIODICAL_HEADER

#include "Papers.hpp"

class Periodical : virtual public Papers
{
    public:

        struct Article
        {
            std::string title;
            std::string author;
            std::vector<std::string> keyWords;
        };

        // Constructors
        Periodical(std::ifstream& file);
        Periodical(const std::string &title, const std::string &publisher, const std::string &description,
                   const std::string &isbn, unsigned yearPublished, double rating, 
                   const std::string &genre, unsigned month, unsigned issueNumber,
                   const std::vector<Article> &articles);

        Periodical(const Periodical &other);
        Periodical &operator=(const Periodical &other);
        ~Periodical() {};

        // Selectors
        unsigned getMonth() const { return month; }
        unsigned getIssueNumber() const { return issueNumber; }
        const std::vector<Article> &getArticles() const { return articles; }

        // Mutators
        void setIssueNumber(unsigned issueNumber);
        void setMonth(unsigned month);
        void setArticle(const std::vector<Article> &articles);
        
        void printInfo() const override;
        void saveOnFile(std::ofstream &out) const override;
        void change() override;

        Type getType() const override { return Papers::PERIODICAL; }
        Papers *clone() const override;

    protected:
        void readArticle(std::ifstream &in, Article &article);
        void writeArticle(std::ofstream &out, const Article &article) const;

        void print() const;
        void save(std::ofstream &out) const;

    private:
        unsigned month;
        unsigned issueNumber;
        std::vector<Article> articles;

};
#endif