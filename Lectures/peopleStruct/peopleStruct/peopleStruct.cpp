#include <iostream>


struct Person
{
    char* name = nullptr;
    int age;
};

struct People
{
    Person* arr;
    size_t size;
};




int main()
{
    People people;
    people.size = 1;
    people.arr = new Person[people.size];

    people.arr[0].name = new char[10];
    strcpy(people.arr[0].name, "Ivan");

}
