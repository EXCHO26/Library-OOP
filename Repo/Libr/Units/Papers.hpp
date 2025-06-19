#ifndef PAPERS_HEADER
#define PAPERS_HEADER

#include <iostream>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <string>
#include <vector>

/// @brief Base class representing a general paper item in the library system.
class Papers
{
    public:
        /// @brief Enumeration of paper types.
        enum Type
        {
            BOOK,
            PERIODICAL,
            SERIES,
            ALL
        };

        /// @brief Constructs a Papers object by reading its data from a file.
        /// @param file Input file stream to read paper data.
        Papers(std::ifstream& file);

        /// @brief Constructs a Papers object with specified attributes.
        /// @param title The title of the paper.
        /// @param publisher The publisher's name.
        /// @param description Description or summary of the paper.
        /// @param isbn ISBN identifier string.
        /// @param yearPublished Year the paper was published.
        /// @param rating Rating of the paper.
        /// @param genre Genre category of the paper.
        Papers(const std::string &title, const std::string &publisher, const std::string &description, 
               const std::string &isbn, unsigned yearPublished, double rating, const std::string &genre);

        /// @brief Copy constructor.
        /// @param otherThe Papers object to copy from. 
        Papers(const Papers &other);

        /// @brief Assignment operator.
        /// @param other The Papers object to assign from.
        /// @return Reference to this object.
        Papers &operator=(const Papers &other);

        /// @brief Virtual destructor.
        virtual ~Papers() = default;

        /** @name Accessors */
        ///@{
        const std::string &getTitle() const       { return title; };
        const std::string &getPublisher() const   { return publisher; };
        const std::string &getDescription() const { return description; };
        const std::string &getISBN() const        { return isbn; };
        const std::string getGenre() const        { return genre; };
        unsigned getYearPublished() const         { return yearPublished; };
        unsigned getID() const                    { return id; };
        double getRating() const                  { return rating; };
        ///@}

        /// @brief Checks if the title matches the given string.
        /// @param title Title to match.
        /// @return true if titles match, false otherwise.
        bool matchTitle(const std::string &title) const;

        /// @brief Checks if the author matches the given string.
        /// @param autor Author name to match.
        /// @return true if authors match, false otherwise.
        virtual bool matchAutor(const std::string &autor) const { return false; }

        /// @brief Checks if tags match the given string.
        /// @param taggs Tags string to match.
        /// @return true if tags match, false otherwise.
        virtual bool matchTaggs(const std::string &taggs) const { return false; }

        /** @name Mutators */
        ///@{
        void setTitle(const std::string &title);
        void setPublisher(const std::string &publisher);
        void setDescription(const std::string &description);
        void setISBN(const std::string &isbn);
        void setYear(unsigned year);
        void setRating(double rating);
        void setGenre(const std::string &genre);
        ///@}

        /// @brief Prints a short summary of the paper.
        void printShort() const;

        /// @brief Prints detailed information about the paper.
        virtual void printInfo() const;

        /// @brief Saves the paper's data to a file.
        /// @param out Output file stream to write data.
        virtual void saveOnFile(std::ofstream &out) const;

        /// @brief Allows modification of the paper's attributes.
        virtual void change();
        
        /// @brief Returns the paper type.
        /// @return The paper's Type enum value.
        virtual Type getType() const = 0;

        /// @brief Creates a polymorphic copy of the paper.
        /// @return Pointer to the cloned Papers object.
        virtual Papers *clone() const = 0;

        /// @brief Compares two Papers objects by a specified value.
        /// @param first Pointer to the first Papers object.
        /// @param second Pointer to the second Papers object.
        /// @param value The attribute name to compare by (e.g., "title", "rating").
        /// @return true if first < second according to value; false otherwise.
        static bool compare(const Papers *first, const Papers *second, const std::string &value);

    private:
        /// @brief Copies data from another Papers object.
        /// @param other The source Papers object.
        void copy(const Papers &other);

        /// @brief Reads and returns an ID from the input file stream.
        /// @param in Input file stream.
        /// @return The ID read from the file.
        unsigned readId(std::ifstream &in) const;
        
    protected:
        /// @brief Reads a string from the input file stream.
        /// @param file Input file stream.
        /// @param str String to store the read data.
        static void readString(std::ifstream &file, std::string& str);

        /// @brief Writes a string to the output file stream.
        /// @param out Output file stream.
        /// @param str String to write.
        static void writeString(std::ofstream &out, const std::string &str);

    private:
        std::string title;          /**< Title of the paper */
        std::string publisher;      /**< Publisher name */
        std::string description;    /**< Description or summary */
        std::string isbn;           /**< ISBN identifier */
        std::string genre;          /**< Genre category */
        unsigned yearPublished;     /**< Year published */
        const unsigned id;          /**< Unique ID of the paper */
        double rating;              /**< Rating of the paper */

        static unsigned nextId;     /**< Static counter for generating unique IDs */
};

#endif