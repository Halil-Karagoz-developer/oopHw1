
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
    string getName(){return name;}
    int getManPower(){return manpower;}
    int getGold(){return gold;}
    string getHoldingOfLand(string);
    int getNumberOfLand(){return numOfLands;}

    void killManpower(int);
    void buyManpower(int);
    bool feedSoldier();
    void writeLands();
    bool isOwnLand(string);
    Character(string,int,int,int);
    Character();
    ~Character();
    void getTaxes();
    void addLand(Land* node);
    bool removeLand(string ,bool); // RETURN TRUE WHEN NO LAND LEFT

};


class CharacterList{
    Character* arr;
    int size;
    int maxsize;
    public:
    friend void listCharacters(CharacterList&);
    friend void listLands(CharacterList&);
    CharacterList();
    ~CharacterList();
    void addCharacter(Character&);
    void makeBiggerArr();
    void delCharacter(string);
    Character getPlayer(string ); // both work for a land name or character name
    Character getLandOwner(string);

};
