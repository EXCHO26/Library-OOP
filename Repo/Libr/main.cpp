#include "LibrRepo.hpp"

int main()
{

    Book book("The Great Book", "Fiction House", "A fascinating book about life.",
                "1234567890", 2023, 9.5, "Drama", {"keyword1", "keyword2"});

    Periodical per("Monthly Magazine", "Fiction House", "A monthly magazine with various articles.",
                    "0987654321", 2023, 8.0, "Mystery", 5, 12,
                    {{"Article One", "Alice Smith", {"mystery", "intrigue"}},
                     {"Article Two", "Bob Johnson", {"suspense", "thrill"}}});
    
    Series series("The Great Series", "Fiction House", "A thrilling series of adventures.",
                   "1234567890", 2023, 9.5, "Drama", 1, 1,
                   { {"First Article", "John Doe", {"adventure", "thrill"} },
                     {"Second Article", "Jane Smith", {"mystery", "suspense"} } },
                   {"keyword1", "keyword2"});


    LibrRepo repo;
    repo.addPaper(book.clone());
    repo.addPaper(per.clone());
    repo.addPaper(series.clone());


    for (unsigned i = 0; i < repo.getSize(); ++i)
    {
        repo.printBook(i);
    }

    repo.removePaper(7);

    std::ofstream outFile("library_data.dat", std::ios::binary);
    if (outFile.is_open())
    {
        repo.save(outFile);
        outFile.close();
    }

    std::cout << "Saved!" << std::endl;

    std::ifstream inFile("library_data.dat", std::ios::binary);
    if (inFile.is_open())
    {
        LibrRepo loadedRepo(inFile);
        inFile.close();

        for (unsigned i = 0; i < loadedRepo.getSize(); ++i)
        {
            loadedRepo.printBook(i);
        }
    }

}