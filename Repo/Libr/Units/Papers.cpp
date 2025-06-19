#include "Papers.hpp"

unsigned Papers::nextId = 1;

void Papers::copy(const Papers &other)
{
    this->title = other.title;
    this->publisher = other.publisher;
    this->description = other.description;
    this->isbn = other.isbn;
    this->yearPublished = other.yearPublished;
    this->rating = other.rating;
    this->genre = other.genre;
}

unsigned Papers::readId(std::ifstream &in) const
{
    if (!in) throw std::invalid_argument("Cannot read the id of a book!");

    unsigned result;
    in.read((char *)&result, sizeof(result));

    if (!in) throw std::invalid_argument("Failed to read the id of a book!");

    return result;
}

void Papers::readString(std::ifstream &file, std::string& str)
{
    if (!file) throw std::invalid_argument("Cannot open the file for reading string.");
    
    size_t len;
    file.read((char *)&len, sizeof(len));
    if (!file) throw std::runtime_error("Failed to read string length.");

    str.resize(len);
    
    file.read(&str[0], len);
    if (!file) throw std::runtime_error("Failed to read string.");
}

void Papers::writeString(std::ofstream &out, const std::string &str)
{
    if (!out) throw std::invalid_argument("Cannot open the file for writing string.");

    size_t len = str.size();
    out.write((const char *)&len, sizeof(len));
    out.write(str.c_str(), len);

    if (!out) throw std::runtime_error("Failed to write string.");
}

Papers::Papers(std::ifstream& file) : id(readId(file))
{
    if (!file) throw std::invalid_argument("Cannot open the file for paper creation!");

    std::string genre;

    readString(file, this->title);
    readString(file, this->publisher);
    readString(file, this->description);
    readString(file, this->isbn);

    file.read((char *)&yearPublished, sizeof(yearPublished));
    if (!file) throw std::runtime_error("Failed to read year published.");

    file.read((char *)&rating, sizeof(rating));
    if (!file) throw std::runtime_error("Failed to read rating.");

    readString(file, this->genre);

    nextId = this->id + 1;
}

Papers::Papers(const std::string &title, const std::string &publisher, const std::string &description, 
               const std::string &isbn, unsigned yearPublished, double rating, const std::string &genre)
    : title(title), publisher(publisher), description(description), isbn(isbn),
      yearPublished(yearPublished), id(nextId++), rating(rating), genre(genre)
{
    if (title.empty()) throw std::invalid_argument("Title cannot be empty.");
    if (publisher.empty()) throw std::invalid_argument("Publisher cannot be empty.");
    if (rating < 0.0 || rating > 10.0) throw std::invalid_argument("Rating must be between 0.0 and 10.0.");    
}


Papers::Papers(const Papers &other) : id(other.id)
{
    this->copy(other);
}

Papers &Papers::operator=(const Papers &other)
{
    if (this != &other) 
    {
        this->copy(other);
    }
    return *this;
}

void Papers::setTitle(const std::string &title)
{
    if (title.empty()) throw std::invalid_argument("Title cannot be empty.");
    this->title = title;
}

void Papers::setPublisher(const std::string &publisher)
{
    if (publisher.empty()) throw std::invalid_argument("Publisher cannot be empty.");
    this->publisher = publisher;
}

void Papers::setDescription(const std::string &description)
{
    if (description.empty()) throw std::invalid_argument("Description cannot be empty.");
    this->description = description;
}

void Papers::setISBN(const std::string &isbn)
{
    this->isbn = isbn;
}

void Papers::setYear(unsigned year)
{
    this->yearPublished = year;
}

void Papers::setRating(double rating)
{
    if (rating < 0.0 || rating > 10.0) throw std::invalid_argument("Rating must be between 0.0 and 10.0.");
    this->rating = rating;
}

void Papers::setGenre(const std::string &genre)
{
    this->genre = genre;
}

void Papers::printShort() const
{
    std::cout << "ID: " << id << " - ";
    std::cout << title << " - ";
    std::cout << publisher << " - ";
    std::cout << "Year: " << yearPublished << " - ";
    std::cout << "ISBN: " << isbn << '\n';
}

void Papers::printInfo() const
{
    std::cout << "Id: " << this->id << '\n';
    std::cout << "Title: " << this->title << '\n'
              << "Publisher: " << this->publisher << '\n'
              << "Description: " << this->description << '\n'
              << "ISBN: " << this->isbn << '\n'
              << "Year Published: " << this->yearPublished << '\n'
              << "Rating: " << this->rating << '\n'
              << "Genre: " << this->genre << '\n';
    std::cout << '\n';
}

void Papers::saveOnFile(std::ofstream &out) const
{
    if (!out) throw std::invalid_argument("Cannot open the file for saving paper!");

    out.write((const char *)&id, sizeof(id));

    writeString(out, this->title);
    writeString(out, this->publisher);
    writeString(out, this->description);
    writeString(out, this->isbn);

    out.write((const char *)&yearPublished, sizeof(yearPublished));
    out.write((const char *)&rating, sizeof(rating));

    writeString(out, this->genre);
}

void Papers::change()
{
    std::string title, publisher, description, isbn, genre;
    double rating;

    std::cout << " > Title: ";
    std::getline(std::cin, title);

    std::cout << " > Publisher: ";
    std::getline(std::cin, publisher);

    std::cout << " > Description: ";
    std::getline(std::cin, description);

    if (title.empty() || publisher.empty() || description.empty())
    {
        throw std::invalid_argument("Invalid arguments!");
    }

    std::cout << " > ISBN: ";
    std::getline(std::cin, isbn);

    std::cout << " > Rating: ";
    std::cin >> rating;

    if (rating < 0.0 || rating > 10.0)
    {
        throw std::invalid_argument("Invalid rating!");
    }

    std::cin.ignore();
    std::cout << " > Genre: ";
    std::getline(std::cin, genre);

    setTitle(title);
    setPublisher(publisher);
    setDescription(description);
    setISBN(isbn);
    setYear(yearPublished);
    setRating(rating);
    setGenre(genre);
}

bool Papers::compare(const Papers *first, const Papers *second, const std::string &value)
{
    if (value == "id")      return first->getID() < second->getID();
    if (value == "title")   return first->getTitle() < second->getTitle();
    if (value == "year")    return first->getYearPublished() < second->getYearPublished();
    if (value == "rating")  return first->getRating() < second->getRating();

    throw std::invalid_argument("Cannot compare by the given value!");
}

bool Papers::matchTitle(const std::string &title) const
{
    return this->title == title;
}