#include <iostream>
#include <fstream>

constexpr int MAX_NAME = 50;
constexpr int MAX_TASKS = 20;
constexpr int MAX_TEXT_SIZE = 100;
constexpr int MAX_TITLE_SIZE = 64;
constexpr int MAX_GAMES_COUNT = 64;

#pragma warning(disable : 4996)

enum class Subject {
    Math,
    English,
    IT,
    undefined
};

class Teacher
{
    char name[MAX_NAME] = "";
    int age = 0;
    Subject subject = Subject::undefined;
    unsigned salary = 0;
public:
    Teacher(const char* n, int a, Subject sub, unsigned sal)
    {
        setName(n);
        setAge(a);
        setSubject(sub);
        setSalary(sal);
    }

    Teacher()
    {

    }

    
    void setName(const char* n)
    {
        if(strlen(n) < MAX_NAME && n)
            strcpy(this->name, n);
    }

    void setAge(int a)
    {
        if (a >= 18 && a <= 70)
            this->age = a;
    }
    
    void setSubject(Subject s)
    {
        this->subject = s;
    }

    void setSalary(unsigned sal)
    {
        if (sal > 500)
            this->salary = sal;
    }

    const char* getName() const
    {
        return this->name;
    }
    int getAge() const
    {
        return this->age;
    }

    Subject getSubject() const
    {
        return this->subject;
    }

    unsigned getSalary() const
    {
        return this->salary;
    }

};


class Task {
    char description[MAX_TEXT_SIZE];
    char rightAnswer;
    int points;
    char password[MAX_TEXT_SIZE];

    Task(const char* desc, char ans, int p, const char* pass)
    {
        setDescription(desc);
        setRightAnswer(ans);
        setPoints(p);
        setPassword(pass);
    }
    Task()
    {

    }


public:
    void setDescription(const char* desc)
    {
        if (strlen(desc) < MAX_TEXT_SIZE && desc)
            strcpy(this->description, desc);
    }

    void setRightAnswer(char ans)
    {
        if (ans == 'a' || ans == 'b' || ans == 'v' || ans == 'g')
            this->rightAnswer = ans;
    }

    void setPoints(int p)
    {
        this->points = p;
    }

    void setPassword(const char* pass)
    {
        if (strlen(pass) < MAX_TEXT_SIZE && pass)
            strcpy(this->description, pass);
    }

    int getPoints() const
    {
        return this->points;
    }

    const char* getDescription() const
    {
        return this->description;
    }


    void editDescription(const char* pass, const char* newDesc)
    {
        if (!strcmp(pass, this->password))
            setDescription(newDesc);
    }
    void editRightAnswer(const char* pass, char newAns)
    {
        if (!strcmp(pass, this->password))
            setRightAnswer(newAns);
    }
    void editPoints(const char* pass, int newPoints)
    {
        if (!strcmp(pass, this->password))
            setPoints(newPoints);
    }


};


class Exam {
    Task tasks[MAX_TASKS];

    void writeExamToFile(const char* fileName) {
        std::ofstream ofs(fileName);
        ofs.write((const char*)this, sizeof(Exam));
    }

    int getPoints()
    {
        int total = 0;
        for (size_t i = 0; i < MAX_TASKS; i++)
        {
            total += tasks[i].getPoints();
        }
        return total;
    }
};

void readExamFromFile(Exam& exam,const char* fileName)
{
    std::ifstream ifs(fileName,std::ios::binary);
    ifs.read((char*) & exam, sizeof(exam));
}

class Game
{
    char title[MAX_TITLE_SIZE] = "";
    int price = -1;
    bool isAvailable = false;

public:

    void setTitle(const char* t)
    {
        if (strlen(t) <= MAX_TITLE_SIZE)
        {
            strcpy(this->title, t);
        }
    }

    void setPrice(int p)
    {
        if (p >= 0)
        {
            this->price = p;
        }
    }

    void setIsAvailable(bool a)
    {
        this->isAvailable = a;
    }

    const char* getTitle() const
    {
        return title;
    }
    int getPrice() const
    {
        return price;
    }
    bool getIsAvailable()
    {
        return isAvailable;
    }

    
    Game(const char* t, int p, bool a)
    {
        setTitle(t);
        setPrice(p);
        setIsAvailable(a);
    }

    Game()
    {

    }




    bool isFree()
    {
        return getPrice() == 0;
    }
    void print()
    {
        std::cout << title << ' ' << price << ' ' << isAvailable << std::endl;
    }

    void printToFile(std::ofstream& ofs)
    {
        ofs << title << '\n' << price << '\n' << isAvailable << std::endl;
    }

};

class GamePlatform
{
    Game games[MAX_GAMES_COUNT];
    size_t gamesCount = 0;
public:
    void addGame(const Game& g)
    {
        if (gamesCount < MAX_GAMES_COUNT)
            games[gamesCount++] = g;
    }

    void printGameByIndex(int ind)
    {
        if(ind <= gamesCount && ind >= 0)
            games[ind].print();
    }

    void printAllGames()
    {
        for (size_t i = 0; i < gamesCount; i++)
        {
            games[i].print();
        }
    }

    void printCheapestGame()
    {
        int bestPrice = games[0].getPrice();
        Game bestPriceGame = games[0];
        for (size_t i = 1; i < gamesCount; i++)
        {
            int currPrice = games[i].getPrice();
            if (bestPrice > currPrice)
            {
                bestPrice = currPrice;
                bestPriceGame = games[i];
            }
        }

        bestPriceGame.print();
    }
    void printMostExpensiveGame()
    {
        int bestPrice = games[0].getPrice();
        Game bestPriceGame = games[0];
        for (size_t i = 1; i < gamesCount; i++)
        {
            int currPrice = games[i].getPrice();
            if (bestPrice < currPrice)
            {
                bestPrice = currPrice;
                bestPriceGame = games[i];
            }
        }

        bestPriceGame.print();
    }

    void printFreeGames()
    {
        for (size_t i = 0; i < gamesCount; i++)
        {
            if(games[i].getPrice() == 0)
                games[i].print();
        }
    }

    void removeGame(int index)
    {
        for (size_t i = index; i < gamesCount-1; i++)
        {
            games[i] = games[i + 1];
        }
        gamesCount--;
    }

    void saveDataToFile(const char* fileName)
    {
        std::ofstream ofs(fileName);
        if (!ofs.is_open()) return;

        for (size_t i = 0; i < gamesCount; i++)
        {
            games[i].printToFile(ofs);
        }
    }

    void readDataFromFile(const char* fileName)
    {
        std::ifstream ifs(fileName);
        if (!ifs.is_open()) return;

        int currInd = 0;

        while (!ifs.eof())
        {
            char title[1024];
            ifs >> title;
            games[currInd].setTitle(title);
            
            if (ifs.eof()) break;

            int price;
            ifs >> price;
            games[currInd].setPrice(price);

            bool isAvailable;
            ifs >> isAvailable;
            games[currInd].setIsAvailable(isAvailable);
            currInd++;
        }
        gamesCount = currInd;
    }

};


int main()
{


    return 0;

}
