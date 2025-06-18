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

    ser.addBook(new Book("kniga", "opisanie", "izdatel", "123", 1, 1, "Drama", {}));
    ser.addUser(new Reader("Krasi", "pass"));

    ser.showAll();

    ser.logout();
    ser.login("Krasi", "pass");

    ser.give(1);
    ser.give(2);

    ser.showAll();

    std::ofstream p2("../papers.dat", std::ios::binary);
    std::ofstream t2("../taken.dat", std::ios::binary);
    std::ofstream u2("../users.dat", std::ios::binary);

    ser.save(p2, t2, u2);

    p2.close();
    t2.close();
    u2.close();

    std::cout << "All good!" << std::endl;
}
