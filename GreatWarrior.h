#pragma once 
#include <iostream>
#include "land.h"

using namespace std;

class Character{
    string name;
    int manpower;
    int gold;
    int numOfLands;
    Land* head;
    public:
    // getters
    string getName () const {return name;}
    int getManPower() const {return manpower;}
    int getGold() const {return gold;}
    string getHoldingOfLand(string);
    int getNumberOfLand() const  {return numOfLands;}

    Character& operator=(const Character&); // overloading assign operator


    void killManpower(int);
    void buyManpower(int);
    void feedSoldier();
    void writeLands();
    bool isOwnLand(string);

    Character(string,int = 0,int= 0,int= 0);
    Character();
    ~Character();
    Character(const Character& c);

    void getTaxes();
    void addLand(Land* node);
    bool removeLand(string ,bool = false); // RETURN TRUE WHEN NO LAND LEFT

};


class CharacterList{
    Character* arr;
    int size;
    public:
    friend void listCharacters(CharacterList&);
    friend void listLands(CharacterList&);
    CharacterList();
    ~CharacterList();
    int getSize(){return size;}
    void addCharacter(Character&);
    void delCharacter(string);
    Character* getPlayer(string ); // both work for a land name or character name
    Character* getLandOwner(string);

};
