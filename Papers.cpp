#include "Papers.hpp"

unsigned Papers::nextId = 0;

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
    out.write((char *)&len, sizeof(len));
    out.write(str.c_str(), len);

    if (!out) throw std::runtime_error("Failed to write string.");
}

Papers::Genre Papers::stringToGenre(const std::string &text)
{
    if (text == "Drama") return Papers::DRAMA;
    if (text == "Horror") return Papers::HORROR;
    if (text == "Mystery") return Papers::MYSTERY;
    return Papers::UNKNOWN;
}

const char* Papers::genreToString(Genre genre)
{
    switch (genre) 
    {
        case DRAMA: return "Drama";
        case HORROR: return "Horror";
        case MYSTERY: return "Mystery";
        default: return "UNKNOWN";
    }
}

Papers::Papers(std::ifstream& file) : id(nextId++)
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

    readString(file, genre);
    this->genre = stringToGenre(genre);
}

Papers::Papers(const std::string &title, const std::string &publisher, const std::string &description, 
               const std::string &isbn, unsigned yearPublished, double rating, const std::string &genre)
    : title(title), publisher(publisher), description(description), isbn(isbn),
      yearPublished(yearPublished), id(nextId++), rating(rating), genre(stringToGenre(genre))
{
    if (title.empty()) throw std::invalid_argument("Title cannot be empty.");
    if (publisher.empty()) throw std::invalid_argument("Publisher cannot be empty.");
    if (rating < 0.0 || rating > 10.0) throw std::invalid_argument("Rating must be between 0.0 and 10.0.");
    if (stringToGenre(genre) == UNKNOWN) throw std::invalid_argument("Invalid genre provided.");      
}


Papers::Papers(const Papers &other) : id(nextId++)
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
    if (year < 0) throw std::invalid_argument("Year cannot be negative.");
    this->yearPublished = year;
}

void Papers::setRating(double rating)
{
    if (rating < 0.0 || rating > 10.0) throw std::invalid_argument("Rating must be between 0.0 and 10.0.");
    this->rating = rating;
}

void Papers::setGenre(const std::string &genre)
{
    Genre newGenre = stringToGenre(genre);
    if (newGenre == UNKNOWN) throw std::invalid_argument("Invalid genre provided.");
    this->genre = newGenre;
}

void Papers::printInfo() const
{
    std::cout << "Title: " << this->title << '\n'
              << "Publisher: " << this->publisher << '\n'
              << "Description: " << this->description << '\n'
              << "ISBN: " << this->isbn << '\n'
              << "Year Published: " << this->yearPublished << '\n'
              << "Rating: " << this->rating << '\n'
              << "Genre: ";
    
    switch (this->genre) {
        case DRAMA: std::cout << "Drama"; break;
        case HORROR: std::cout << "Horror"; break;
        case MYSTERY: std::cout << "Mystery"; break;
        default: std::cout << "Unknown"; break;
    }
    std::cout << '\n';
}

void Papers::saveOnFile(std::ofstream &out) const
{
    if (!out) throw std::invalid_argument("Cannot open the file for saving paper!");

    writeString(out, this->title);
    writeString(out, this->publisher);
    writeString(out, this->description);
    writeString(out, this->isbn);

    out.write((char *)&yearPublished, sizeof(yearPublished));
    out.write((char *)&rating, sizeof(rating));

    std::string genreStr = genreToString(this->genre);
    writeString(out, genreStr);
}