//////////////////////////////////
/*          <Halil Faruk Karagöz>         */
/*          <150180014>           */
//////////////////////////////////

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include "GreatWarrior.h"
#include "GreatWarrior.cpp"



void listCharacters(CharacterList &);
void listLands(CharacterList &);
void readData(string, CharacterList &);
void printGameMenu();
bool endOfTurn(Character &, int);

int main()
{
    cout << "Welcome to the Great Warriors. Create your character and attack other lands to be a great warrior.\n"
         << endl;

    CharacterList charList; // list object to store the characters

    string fileName = "characters.txt"; // read characters.txt file
    readData(fileName, charList);

   
    string name, land, general;
    cout << "Enter your name: ";
    cin >> name;

    cout << "Enter name of your capital: ";
    cin >> land;

    cout << "Enter name of your general: ";
    cin >> general;

   
    Character const General(general);


    Character mycharacter(name, 3, 20);
    Land *capital = new Land(land, "village"); // village can change
    mycharacter.addLand(capital);
    charList.addCharacter(mycharacter);

    int choice = 0, round = 0;
    while (choice != 6)
    {
        printGameMenu();

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "You have rested in your palace." << endl;
            cout << "You've talked with your general " << General.getName() << "." << endl;

            round++;
            break;
        }
        case 2:
        {
            listLands(charList);
            cout << "Enter name of the land to attack." << endl;

            string land;
            cin >> land;
            Character *p, *oppenent;
            if (charList.getLandOwner(land))
            {
                oppenent = charList.getLandOwner(land);
                p = charList.getPlayer(name);
                if (p->getManPower() > oppenent->getManPower())
                {
                    cout << "You've won the battle and conquered " << land << "." << endl;
                    p->killManpower(oppenent->getManPower());
                    Land *newL;
                    newL = new Land(land, oppenent->getHoldingOfLand(land));
                    p->addLand(newL);
                    if (oppenent->removeLand(land))
                    {
                        charList.delCharacter(oppenent->getName());
                    }
                }
                else
                {
                    cout << "You've lost the battle and " << p->getManPower() << " manpower." << endl;

                    p->killManpower(p->getManPower());
                }
            }

            round++;
            break;
        }
        case 3:
            cout << "How much manpower do you need? (1 manpower=5 gold)" << endl;

            int order;
            cin >> order;
            Character *p;
            p = charList.getPlayer(name);
            if (p->getGold() > order * 5)
            {
                p->buyManpower(order);
                cout << "Order successful. You have " << p->getManPower() << " manpower." << endl;
            }
            else
                cout << "You do not have enough money." << endl;


            round++;
            break;
        case 4:
            listCharacters(charList);
            break;
        case 5:
            listLands(charList);
            break;
        case 6:
            return 0;
        default:
            cout << "You entered an invalid value. Try again." << endl;
        }
        if (!endOfTurn(*charList.getPlayer(name), round))
            break;
        if(charList.getSize() == 1){
            cout <<mycharacter.getName() << " is the only great warrior now." << endl;
            break;
        }
       
    }
    getchar();
    return 0;
}

void readData(string fileName, CharacterList &charList)
{

    fstream dataFile(fileName.c_str());

    if (dataFile.is_open())
    {

        string word;
        while (dataFile >> word)
        {

            string name, title;
            int money, manpower, numOfLands;

            name = word;
            dataFile >> manpower;
            dataFile >> money;
            dataFile >> numOfLands;

            Character newC(name, manpower, money, numOfLands);

            string landName, holding;

            for (int i = 0; i < numOfLands; i++)
            {
                dataFile >> landName;
                dataFile >> holding;

                Land *newLand = new Land(landName, holding);
                newC.addLand(newLand);
            }

            charList.addCharacter(newC);
        }

        dataFile.close();
    }
    else
    {
        cout << "Unable to open the file" << endl;
        exit(1);
    }

    return;
}

void printGameMenu()
{
    cout << endl;
    cout << "1. Stay in your palace" << endl;
    cout << "2. Attack to a land" << endl;
    cout << "3. Buy manpower" << endl;
    cout << "4. List characters" << endl;
    cout << "5. List lands" << endl;
    cout << "6. Exit" << endl;
    cout << endl;
}

void listCharacters(CharacterList &charList)
{
    for (int i = 0; i < charList.size; i++)
    {
        cout << charList.arr[i].getName() << endl;
    }
}

void listLands(CharacterList &charList)
{
    for (int i = 0; i < charList.size; i++)
    {
        charList.arr[i].writeLands();
    }
}

bool endOfTurn(Character &player, int round)
{ //return a bool value that indicates if the game is over or not.

    player.getTaxes();
    player.feedSoldier();
    if (player.getNumberOfLand() == 0)
    {
        cout << "You are no longer a great warrior. You survived " << round << " turns." << endl;
        cout << endl;
        cout << "GAME OVER." << endl;
        return false;
    }
    if (player.getManPower() == 0)
    {
        cout << "You lost one of your lands to rebellions since you don't have enough army." << endl;
        player.removeLand("dont care", true); // lost last one 
    }

    cout << "Turn " << round << ": "
         << " " << player.getName() << " has " << player.getNumberOfLand() << " land(s), " << player.getManPower() << " manpower and " << player.getGold() << " golds." << endl;
    
    
    
    return true;


}
