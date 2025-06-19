#include "AddCommand.hpp"

AddCommand::AddCommand(std::vector<std::string> &tokens) : tokens(tokens) {};

void AddCommand::addUser(LibrService& service) const
{
    if (tokens.size() == 6 && tokens[4] == "admin")
    {
        Admin *admin = new Admin(tokens[2], tokens[3], tokens[5]);
        try
        {
            service.addUser(admin);
        }
        catch(const std::exception& e)
        {
            delete admin;
            throw;
        }
    }
    else if (tokens.size() == 4)
    {
        Reader *reader = new Reader(tokens[2], tokens[3]);
        try
        {
            service.addUser(reader);
        }
        catch(const std::exception& e)
        {
            delete reader;
            throw;
        }
    }
}

void AddCommand::addPaper(LibrService& service) const
{
    std::string title, publisher, description, isbn, genre;
    unsigned yearPublished;
    double rating;

    readPaper(title, publisher, description, isbn, yearPublished, rating, genre);

    if (tokens.front() == "books")
    {
        std::vector<std::string> keywords;
        std::string autor;

        readBook(keywords, autor);

        Book *book = new Book(title, publisher, description, isbn, yearPublished, rating, genre, keywords, autor);

        try
        {
            service.addBook(book);
        }
        catch(const std::exception& e)
        {
            delete book;
            throw;
        }
        return;
    }

    if (tokens.front() == "newsletters")
    {
        unsigned month, issue;
        std::vector<Periodical::Article> articles;

        readPeri(month, issue, articles);

        Periodical *peri = new Periodical(title, publisher, description, isbn, yearPublished, rating, genre,
                                          month, issue, articles);

        try
        {
            service.addBook(peri);
        }
        catch(const std::exception& e)
        {
            delete peri;
            throw;
        }
        return;    
    }

    if (tokens.front() == "series")
    {
        std::vector<std::string> keywords;
        std::string autor;
        unsigned month, issue;
        std::vector<Periodical::Article> articles;

        readBook(keywords, autor);
        readPeri(month, issue, articles);

        Series *seri = new Series(title, publisher, description, isbn, yearPublished, rating, genre,
                                  month, issue, articles, keywords, autor);
        
        try
        {
            service.addBook(seri);
        }
        catch(const std::exception& e)
        {
            delete seri;
            throw;
        }
        return;
    }
}

void AddCommand::readPaper(std::string &title, std::string &publisher, std::string &description,
                       std::string &isbn, unsigned yearPublished, double rating, std::string &genre) const
{
    std::cout << "Please enter the information of the book: " << '\n';
    std::cout << "Title: ";
    std::getline(std::cin, title);

    std::cout << "Publisher: ";
    std::getline(std::cin, publisher);

    std::cout << "Description: ";
    std::getline(std::cin, description);

    std::cout << "ISBN: ";
    std::getline(std::cin, isbn);

    std::cout << "Genre: ";
    std::getline(std::cin, genre);

    std::cout << "Year Published: ";
    while (!(std::cin >> yearPublished)) {
        std::cout << "Invalid input. Please enter a valid year: ";
        std::cin.clear();
    }

    std::cout << "Rating (0.0 - 10.0): ";
    while (!(std::cin >> rating) || rating < 0.0 || rating > 10.0) {
        std::cout << "Invalid rating. Please enter a number between 0.0 and 5.0: ";
        std::cin.clear();
    }
}

void AddCommand::readBook(std::vector<std::string> &keyWords, std::string& autor) const
{
    std::cin.ignore();
    std::cout << "Autor: ";
    std::getline(std::cin, autor);

    std::string keyword;
    std::cout << "Enter keywords (enter empty line to finish):\n";
    while (true) 
    {
        std::getline(std::cin, keyword);
        if (keyword.empty()) break;
        keyWords.push_back(keyword);
    }
}

void AddCommand::readPeri(unsigned &month, unsigned &issue, std::vector<Periodical::Article> &articles) const
{
    std::cout << "Month (1-12): ";
    while (!(std::cin >> month) || month < 1 || month > 12) 
    {
        std::cout << "Invalid month. Please enter a number between 1 and 12: ";
        std::cin.clear();
    }

    std::cout << "Issue number: ";
    while (!(std::cin >> issue)) 
    {
        std::cout << "Invalid issue number. Please enter a valid number: ";
        std::cin.clear();
    }

    std::cin.ignore();
    std::cout << "Enter articles (empty title to stop):\n";
    while (true) 
    {
        Periodical::Article article;
        std::cout << "  Title: ";
        std::getline(std::cin, article.title);
        if (article.title.empty()) break;

        std::cout << "  Author: ";
        std::getline(std::cin, article.author);

        std::cout << "  Enter keywords (empty line to stop):\n";
        while (true) 
        {
            std::string kw;
            std::cout << "    Keyword: ";
            std::getline(std::cin, kw);
            if (kw.empty()) break;
            article.keyWords.push_back(kw);
        }

        articles.push_back(article);
    }
}

void AddCommand::execute(LibrService& service) const
{

    service.checkLogged();
    service.adminOnly();
    if (tokens.front() == "user") addUser(service);
    else addPaper(service);

} 