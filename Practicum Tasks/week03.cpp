#include <iostream>
#include <fstream>
#include <sstream>

namespace zadachaEdno {
    namespace Globals {
        const int MAX_ROWS_COUNT = 100;
        const int MAX_COLLS_COUNT = 100;
    }

    struct Row
    {
        int field[Globals::MAX_COLLS_COUNT];
    };

    struct Matrix
    {
        Row rows[Globals::MAX_ROWS_COUNT];
        size_t rowsCount;
        size_t collsCount;
    };

    int parseToInt(const char* str)
    {
        if (!str) return -1;

        int result = 0;
        while (*str)
        {
            result *= 10;
            result += (*str - '0');

            str++;
        }
        return result;
    }

    void fillRow(Row& row, const char* data, size_t& collCount)
    {
        std::stringstream ss(data);
        collCount = 0;

        while (!ss.eof())
        {
            char buff[1024];
            ss.getline(buff, 1024, ',');
            row.field[collCount++] = parseToInt(buff);
        }
    }

    void printRow(const Row& row, size_t collCount)
    {
        for (int i = 0; i < collCount; i++)
        {
            std::cout << row.field[i] << ' ';
        }
        std::cout << std::endl;
    }

    void writeMtxToFile(std::ofstream& ofs, const Matrix& mtx)
    {
        for (size_t i = 0; i < mtx.rowsCount; i++)
        {
            for (size_t j = 0; j < mtx.collsCount - 1; j++)
            {
                ofs << mtx.rows[i].field[j] << ',';
            }
            ofs << mtx.rows[i].field[mtx.collsCount - 1];
            ofs << '|';
        }
    }
    void writeMtxToFile(const char* fileName, const Matrix& mtx)
    {
        std::ofstream ofs(fileName);
        if (!ofs.is_open()) return;
        writeMtxToFile(ofs, mtx);
    }

    Matrix readMatrix(std::ifstream& ifs)
    {
        Matrix mtx;
        unsigned currRow = 0;
        mtx.rowsCount = 0;

        while (!ifs.eof())
        {
            char buff[1024];
            ifs.getline(buff, 1024, '|');


            size_t collCount = 0;
            fillRow(mtx.rows[currRow++], buff, collCount);

            mtx.collsCount = collCount;
        }
        mtx.rowsCount = currRow;

        return mtx;
    }

    Matrix readMatrix(const char* fileName)
    {
        std::ifstream ifs(fileName);
        if (!ifs.is_open()) return {};

        return readMatrix(ifs);
    }

    Matrix multipliedMtx(const Matrix& first, const Matrix& second)
    {
        Matrix result;
        result.collsCount = second.collsCount;
        result.rowsCount = first.rowsCount;

        for (size_t k = 0; k < first.rowsCount; k++)
        {

            for (size_t i = 0; i < second.collsCount; i++)
            {
                int tempSum = 0;
                for (size_t j = 0; j < first.collsCount; j++)
                {
                    tempSum += (first.rows[k].field[j] * second.rows[j].field[i]);
                }
                result.rows[k].field[i] = tempSum;
            }

        }
        return result;
    }


    void printMatrix(const Matrix& mtx)
    {
        for (int i = 0; i < mtx.rowsCount; i++)
        {
            printRow(mtx.rows[i], mtx.collsCount);

        }
    }
}

#pragma warning(disable : 4996)


namespace zadachaChet {

    enum class PizzaType {
        margarita,
        calcone,
        buratta
    };

    struct Pizza {
        PizzaType type;
        char size;
        double price;
    };

    struct Order
    {
        int pizzaCount;
        Pizza pizzas[10];
        double total;
        char name[50];
        char telephone[20];
        char address[100];
    };


    void writeOrder(std::ofstream& ofs, const Order& order)
    {
        ofs.write((const char*)&order, sizeof(order));

        /*
        ofs.write((const char*)&order.pizzaCount, sizeof(int));
        ofs.seekp(4, std::ios::cur);
        ofs.write((const char*)order.pizzas, sizeof(Pizza) * 10);
        ofs.write((const char*)&order.total, sizeof(double));
        ofs.write((const char*)order.name, 50);
        ofs.seekp(6, std::ios::cur);
        ofs.write((const char*)order.telephone, 20);
        ofs.seekp(4, std::ios::cur);
        ofs.write((const char*)order.address, 100);*/
    }
    void writeOrder(const char* fileName, const Order& order)
    {
        std::ofstream ofs(fileName, std::ios::binary);
        if (!ofs.is_open()) return;
        writeOrder(ofs, order);
    }

    void readOrder(std::ifstream& ifs, const Order& order)
    {
        ifs.read((char*)&order, sizeof(order));
    }
    void readOrder(const char* fileName, const Order& order)
    {
        std::ifstream ifs(fileName, std::ios::binary);
        if (!ifs.is_open()) return;
        readOrder(ifs, order);
    }

    void printOrderToConsole(const Order& order)
    {
        std::cout << order.pizzaCount << ":\n";
        std::cout << (int)order.pizzas[0].type << "\n";
        std::cout << order.pizzas[0].size << "\n";
        std::cout << order.pizzas[0].price << ";\n";
        std::cout << (int)order.pizzas[1].type << "\n";
        std::cout << order.pizzas[1].size << "\n";
        std::cout << order.pizzas[1].price << ";\n";
        std::cout << order.name << "\n";
        std::cout << order.telephone << "\n";
        std::cout << order.address << "\n";
        std::cout << order.total << "\n";
    }
}

namespace zadachaDve {

    struct Student
    {
        char firstName[16];
        char lastName[16];
        int fn;
        char hairColor;
        double averageGrade;
    };

    struct Group
    {
        size_t studentsCount = 0;
        Student students[1024];
    };



    void writeGroup(std::ofstream& ofs, const Group& group)
    {
        ofs.write((const char*)&group, sizeof(group));
    }

    void writeGroup(const char* fileName, const Group& group)
    {
        std::ofstream ofs(fileName, std::ios::binary);
        if (!ofs.is_open()) return;
        writeGroup(ofs, group);
    }

    void readGroup(std::ifstream& ifs, const Group& group)
    {
        ifs.read((char*)&group, sizeof(group));
    }

    void readGroup(const char* fileName, const Group& group)
    {
        std::ifstream ifs(fileName, std::ios::binary);
        if (!ifs.is_open()) return;
        readGroup(ifs, group);
    }
}

struct Offer
{
    char companyName[25];
    int colleguesCount;
    int daysFree;
    long long money;
};

void writeOffer(std::ofstream& ofs, const Offer& offer)
{
    ofs.write((const char*)&offer, sizeof(offer));   
}

Offer readOffer(std::ifstream& ifs)
{
    Offer of;
    ifs.read((char*)&of, sizeof(of));
    return of;
}

void readOffersFromConsole()
{
    int n = 0;
    std::cin >> n;

    std::ofstream ofs("offers.dat", std::ios::app | std::ios::binary);

    for (size_t i = 0; i < n; i++)
    {
        Offer inputOffer;
        std::cin >> inputOffer.companyName >> inputOffer.colleguesCount >> inputOffer.daysFree >> inputOffer.money;
        writeOffer(ofs, inputOffer);
    }
    ofs.close();
}

void printOffer(const Offer& offer)
{
    std::cout << "Company: " << offer.companyName << '\n';
    std::cout << "Collegues Count: " << offer.colleguesCount << '\n';
    std::cout << "Days Free: " << offer.daysFree << '\n';
    std::cout << "Money: " << offer.money << '\n';
}

size_t getFileSize(std::ifstream& f) {
    size_t currentPos = f.tellg();
    f.seekg(0, std::ios::end);
    size_t size = f.tellg();

    f.seekg(currentPos);
    return size;
}

void filterOffers(const char* filePath, long long minSalary)
{
    std::ifstream ifs(filePath,std::ios::binary);

    size_t count = getFileSize(ifs) / sizeof(Offer);
    for (size_t i = 0; i < count; i++)
    {
        Offer curr = readOffer(ifs);
        if (curr.money >= minSalary) printOffer(curr);
    }

}
bool existOffer(const char* filePath, const char* name)
{
    std::ifstream ifs(filePath, std::ios::binary);

    size_t count = getFileSize(ifs) / sizeof(Offer);
    for (size_t i = 0; i < count; i++)
    {
        Offer curr = readOffer(ifs);
        if (!strcmp(curr.companyName,name)) return true;
    }
    return false;
}


int main()
{
    readOffersFromConsole();


    std::ifstream ifs("offers.dat");


    filterOffers("offers.dat", 0);
    return 0;
}

