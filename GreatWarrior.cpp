#include <iostream>
#include "GreatWarrior.h"
using namespace std;

void Character :: assign(const Character &src)
{
    head = NULL;
    name.assign(src.name);
    manpower = src.manpower;
    gold = src.gold;
    numOfLands = src.numOfLands;
    Land *traverse = src.head;
    while (traverse)
    {
        Land *node = new Land(*traverse);
        node->next = NULL;
        traverse = traverse->next;
        if (head == NULL)
        {
            head = node;
        }
        else
        {
            Land *traverse2 = head;
            while (traverse2->next)
            {
                traverse2 = traverse2->next;
            }
            traverse2->next = node;
        }
    }
}
Character ::Character(const Character &c)
{
    name.assign(c.name);
}

string Character ::getHoldingOfLand(string name)
{
    Land *traverse = head;
    while (traverse)
    {
        if (name.compare(traverse->getName()) == 0)
        {
            return traverse->getHolding();
            break;
        }
        traverse = traverse->next;
    }
    return " ";
}



void Character ::feedSoldier()
{

    if (gold > manpower)
    {
        gold -= manpower;
    }
    else
    { // if dont have enough gold but not zero
        manpower = gold;
        cout << gold - manpower << " soldiers run away from your army because you don't have enough gold to feed them." << endl;
        gold = 0;
    }
}

void Character ::killManpower(int how_many)
{
    manpower = manpower - how_many;
}

void Character ::buyManpower(int how_many)
{
    manpower += how_many;
    gold -= how_many * 5;
}

Character ::Character()
{
    head = NULL;
}
void Character ::writeLands()
{
    Land *traverse = head;
    while (traverse)
    {
        cout << traverse->getName() << " " << traverse->getHolding() << " owned by " << name << endl;
        traverse = traverse->next;
    }
}

Character ::Character(string inname, int inmanpower, int ingold, int innumoflands) : manpower(inmanpower), gold(ingold), numOfLands(innumoflands)
{
    name.assign(inname);
    head = NULL;
}

void Character ::addLand(Land *node)
{
    if (head == NULL)
    {
        head = node;
        head->next = NULL;
        numOfLands = 1;
        return;
    }

    else
    {
        Land *traverse = head;
        while (traverse->next)
        {
            traverse = traverse->next;
        }
        traverse->next = node;
    }
    node->next = NULL;
    numOfLands++;
}

void Character ::getTaxes()
{
    Land *traverse = head;
    while (traverse)
    {
        if (strcmp(traverse->getHolding(), "city") == 0)
            gold += 10;
        else if (strcmp(traverse->getHolding(), "castle") == 0)
            gold += 7;
        else
            gold += 5;
        traverse = traverse->next;
    }
}

bool Character ::removeLand(string name, bool remove_last_one)
{ // return true if there are no land left and delete character from list
    if (head == NULL)
        return true;
    Land *traverse = head;
    Land *traverseTail = head;
    if (remove_last_one)
    {

        while (traverse->next)
        {
            traverseTail = traverse;
            traverse = traverse->next;
        }
        if (traverse == head)
        {
            head = NULL;
        }
        else
            traverseTail->next = NULL;
        delete traverse;
        numOfLands--;
    }
    else
    {
        if (name.compare(head->getName()) == 0)
        {
            head = head->next;
            delete traverse;
            numOfLands--;
        }
        else
        {
            while (traverse->next && traverse->getName() != name)
            {
                traverseTail = traverse;
                traverse = traverse->next;
            }

            if (traverse->getName() == name)
            {
                Land *temp = traverse;
                traverseTail->next = traverse->next;
                delete temp;
                numOfLands--;
            }
        }
    }
    if (head == NULL)
        return true;

    return false;
}

Character ::~Character()
{
    Land *traverse = head;
    while (traverse)
    {
        traverse = traverse->next;
        delete head;
        head = traverse;
    }
}
bool Character ::isOwnLand(string name)
{
    Land *traverse = head;
    while (traverse)
    {
        if (traverse->getName() == name)
        {
            return true;
        }
        traverse = traverse->next;
    }
    return false;
}

CharacterList::CharacterList()
{
    arr = NULL;
    size = 0;
}

CharacterList::~CharacterList()
{
    delete[] arr;
}

void CharacterList ::addCharacter(Character &c)
{
        Character *newarray = new Character[size+1];
        for (int i = 0; i < size; i++)
        {
            newarray[i].assign(arr[i]);
        }
        delete[] arr;
        arr = newarray;
    
    arr[size++].assign(c);
}
void CharacterList ::delCharacter(string name)
{
    for (int i = 0; i < size; i++)
    {
        if (name.compare(arr[i].getName()) == 0)
        {
            for (int k = i; k < size - 1; k++)
            {
                Character temp;
                temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
            }
            size--;
            break;
        }
    }
}

//void delCharacter();
Character *CharacterList ::getPlayer(string name)
{
    for (int i = 0; i < size; i++)
    {
        if (name.compare(arr[i].getName()) == 0)
        {
            return &(arr[i]);
        }
    }
    return NULL;
}

Character *CharacterList ::getLandOwner(string name)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].isOwnLand(name))
            return &(arr[i]);
    }
    cout << "Could not find " << name << " place" << endl;
    return NULL;
}
