// In-Class Exercise 9/25

#include <string>
#include <iostream>
using namespace std;

class Pet
{
private:
    float weight;
    string name;

public:
    Pet(float weight, string name)
    {
        cout << "In pet constructor: weight= " << weight;
        cout << " name = " << name << endl;
        this->weight = weight;
        this->name = name;
    }

    void greeting(string saying)
    {
        cout << name << " (" << weight << ") pounds";
        cout << " says " << saying << endl;
    }
};

class Cat : public Pet
{
public:
    // Note: the line below is correct.
    // to call a non-default parent constructor - use
    // an initialization list.
    Cat(float weight, string name) : Pet(weight, name) {}
    Cat(float weight, string name, bool kitty) : Pet(weight, name)
    {
        if (kitty)
            cout << "This cat is also a kitty." << endl;
    }
    void greeting(string saying)
    {
        cout << "The cat ";
        Pet::greeting(saying);
    }
};

int main()
{
    Cat garfield(35, "Garfield");
    Cat garfieldSon(12, "Fargield", true);
    garfield.greeting("Hi");
    return 0;
}