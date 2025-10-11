/****************************************************************************
 * File: Hw6_JosephNeubert.cpp
 * Author: Joseph Neubert
 * Purpose: To create a fraction class that creates, multiplies, and displays fractions
 * Version: 1.0 Oct 3, 2024
 * Resources: N/A
 *******************************************************************************/

#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

class Monster
{
private:
    int strength;

public:
    static int count;

    Monster()
    {
        srand(time(0));
        strength = (rand() % 30) + 1;
    }

    int getStrength() const
    {
        return strength;
    }

    virtual void speak()
    {
        cout << "Boo!" << endl;
    }
};
int Monster::count = 0;

class Zombie : public Monster
{
public:
    Zombie() : Monster()
    {
        cout << "It's a zombie." << endl;
        count++;
    }

    void speak()
    {
        cout << "Undead groan!" << endl;
    }
};

class Werewolf : public Monster
{
public:
    Werewolf() : Monster()
    {
        cout << "It's a werewolf." << endl;
        count++;
    }

    void speak()
    {
        cout << "Wolf growl!" << endl;
    }
};

class Vampire : public Monster
{
public:
    Vampire() : Monster()
    {
        cout << "It's a vampire." << endl;
        count++;
    }

    void speak()
    {
        cout << "Bleh bleh bleh" << endl;
    }
};

int main()
{
    Monster* monsterList[5];
    int totalStrength = 0;

    while (Monster::count < 5)
    {
        string response;
        cout << "Select the monster type (Zombie, Werewolf, Vampire): ";
        cin >> response;
        if (!cin) {
            cout << "Invalid response. Please try again." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }

        if (response == "Zombie")
        {
            Zombie* zombie = new Zombie();
            totalStrength += zombie->getStrength();
            monsterList[Monster::count - 1] = zombie;
            cout << "Monster #" << Monster::count<< " with strength " << zombie->getStrength() << " appears." << endl;
        }
        else if (response == "Werewolf")
        {
            Werewolf* werewolf = new Werewolf();
            totalStrength += werewolf->getStrength();
            monsterList[Monster::count - 1] = werewolf;
            cout << "Monster #" << Monster::count << " with strength " << werewolf->getStrength() << " appears." << endl;
        }
        else if (response == "Vampire")
        {
            Vampire* vampire = new Vampire();
            totalStrength += vampire->getStrength();
            monsterList[Monster::count - 1] = vampire;
            cout << "Monster #" << Monster::count<< " with strength " << vampire->getStrength() << " appears." << endl;
        }
        else
        {
            cout << "Invalid response. Please try again." << endl;
        }
    }

    cout << "Each monsters' greetings: " << endl;
    for (int i = 0; i < 5; i++)
    {
        monsterList[i]->speak();
        delete(monsterList[i]);
    }

    cout << "Total strength of monsters is " << totalStrength << "." << endl;

    return 0;
}