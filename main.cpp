#include "Service/LibrService.hpp"

int main()
{
    std::ifstream p1("../papers.dat", std::ios::binary);
    std::ifstream t1("../taken.dat", std::ios::binary);
    std::ifstream u1("../users.dat", std::ios::binary);

    LibrService ser(p1, t1, u1);

    p1.close();
    t1.close();
    u1.close();

    ser.login("admin", "i<3c++");

    // ser.addBook(new Book("kniga1", "opisanie", "izdatel", "123", 1, 1, "Drama", {}, "avtor"));
    // ser.addBook(new Book("kniga2", "opisanie", "izdatel", "123", 2, 1, "Drama", {}, "avtor"));
    // ser.addBook(new Book("kniga3", "opisanie", "izdatel", "123", 2025, 1, "Drama", {}, "avtor"));
    // ser.addBook(new Book("kniga4", "opisanie", "izdatel", "123", 3, 1, "Drama", {}, "avtor"));
    // ser.addBook(new Book("kniga5", "opisanie", "izdatel", "123", 400, 1, "Drama", {}, "avtor"));
    // ser.addBook(new Book("kniga6", "opisanie", "izdatel", "123", 5, 1, "Drama", {}, "avtor"));
    // ser.addBook(new Book("kniga3", "opisanie", "izdatel", "123", 2003, 10, "Drama", {}, "az"));
    // ser.addBook(new Book("kniga3", "opisanie", "izdatel", "123", 1992, 1, "Drama", {}, "avtor"));
    
    //ser.addUser(new Reader("Krasi", "pass"));

    ser.showAll();

    ser.logout();

    ser.login("Krasi", "pass");

    ser.logout();
    ser.login("admin", "i<3c++");

    //ser.findPaper("autor", "avtor", Papers::ALL);

    std::ofstream p2("../papers.dat", std::ios::binary);
    std::ofstream t2("../taken.dat", std::ios::binary);
    std::ofstream u2("../users.dat", std::ios::binary);

    ser.save(p2, t2, u2);

    p2.close();
    t2.close();
    u2.close();

    std::cout << "All good!" << std::endl;
}
