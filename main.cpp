#include "Papers.hpp"
#include "Book.hpp"
#include "Periodical.hpp"
#include "Series.hpp"

int main()
{
    
    Series series("The Great Series", "Fiction House", "A thrilling series of adventures.",
                   "1234567890", 2023, 9.5, "Drama", 1, 1,
                   {{"First Article", "John Doe", {"adventure", "thrill"}},
                    {"Second Article", "Jane Smith", {"mystery", "suspense"}}},
                   {"keyword1", "keyword2"});

    Series anotherSeries = series; // Copy constructor
    anotherSeries.setTitle("Another Great Series");
    anotherSeries.setPublisher("Another House");
    anotherSeries.setDescription("A different thrilling series.");
    

    series.printInfo();
    anotherSeries.printInfo();

    std::ofstream outFile("series_data.bin", std::ios::binary);
    if (outFile.is_open())
    {
        series.saveOnFile(outFile);
        anotherSeries.saveOnFile(outFile);
        outFile.close();
    }
    else
    {
        std::cerr << "Error opening file for writing." << std::endl;
    }

    std::ifstream inFile("series_data.bin", std::ios::binary);
    if (inFile.is_open())
    {
        Series loadedSeries(inFile);
        Series anotherLoadedSeries(inFile);
        loadedSeries.printInfo();
        anotherLoadedSeries.printInfo();
        inFile.close();
    }
    else
    {
        std::cerr << "Error opening file for reading." << std::endl;
    }
    return 0;
}