#ifndef BOOK_HEADER
#define BOOK_HEADER

#include "Papers.hpp"


/// @brief Represents a book, derived from Papers, with additional author and keywords.
class Book : virtual public Papers
{
    public:
        /// @brief Constructs a Book object by reading data from a file.
        /// @param file Input file stream to read the book data.
        Book(std::ifstream& file);

        /// @brief Constructs a Book object with given attributes.
        /// @param title Title of the book.
        /// @param publisher Publisher's name.
        /// @param description Description or summary of the book.
        /// @param isbn ISBN identifier string.
        /// @param yearPublished Year the book was published.
        /// @param rating Rating of the book.
        /// @param genre Genre category.
        /// @param keyWords Vector of keywords associated with the book.
        /// @param autor Author of the book.
        Book(const std::string &title, const std::string &publisher, const std::string &description,
             const std::string &isbn, unsigned yearPublished, double rating, 
             const std::string &genre, const std::vector<std::string>& keyWords, const std::string& autor);

        /// @brief Copy constructor.
        /// @param other The Book object to copy from.
        Book(const Book &other);

        /// @brief Assignment operator.
        /// @param other The Book object to assign from.
        /// @return Reference to this Book.
        Book &operator=(const Book &other);

        /// @brief Destructor.
        ~Book() {};

        /** @name Accessors */
        ///@{
        const std::vector<std::string>& getKeyWords() const { return keyWords; }
        const std::string getAutor() const                  { return autor;    }
        ///@}

        /** @name Mutators */
        ///@{
        void setKeyWords(const std::vector<std::string> &keyWords);
        void setAutor(const std::string &autor);
        void change() override;
        ///@}

        /// @brief Saves the book data to a file.
        void printInfo() const override;

        /// @brief Saves the book data to a file.
        /// @param out Output file stream.
        void saveOnFile(std::ofstream &out) const override;

        /// @brief Checks if the author matches the given string.
        /// @param autor Author string to match.
        /// @return true if author matches, false otherwise.
        bool matchAutor(const std::string &autor) const override;

        /// @brief Checks if the tags match the given string (matching keywords).
        /// @param taggs Tag string to match.
        /// @return true if any keyword matches, false otherwise.
        bool matchTaggs(const std::string &taggs) const override;
        
        /// @brief Returns the type of the paper.
        /// @return Papers::BOOK enum value.
        Type getType() const override { return Papers::BOOK; }

        /// @brief Creates a polymorphic clone of the book.
        /// @return Pointer to a new Book object copied from this one.
        Papers *clone() const override;
    
    protected:
        /// @brief Prints the book (internal helper).
        void print() const;

        /// @brief Saves the book to file (internal helper).
        /// @param out Output file stream.
        void save(std::ofstream &out) const;

    private:
        /// @brief Keywords associated with the book
        std::vector<std::string> keyWords;

        /// @brief Author of the book
        std::string autor;
};
#endif