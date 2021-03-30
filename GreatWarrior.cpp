#include <iostream>
#include "GreatWarrior.h"
using namespace std;


Character :: Character(){
    head = NULL;
}
void Character :: writeLands(){
    Land* traverse = head;
    while(traverse){
        cout << traverse->getName() << " " << traverse->getHolding()  << " owned by " << name << endl;
        traverse= traverse->next;
    }
}


Character :: Character(string inname,int inmanpower = 0, int ingold = 0,int innumoflands = 0) : name(inname),manpower(inmanpower),gold(ingold),numOfLands(innumoflands){
    head = NULL;
}

void Character :: addLand(Land* node){
    if(head == NULL){
        head = node;
        return;
    }

    else{
        Land* traverse = head;
        while(traverse->next){
            traverse = traverse->next;
        }
        traverse->next = node;
    }
    node->next = NULL;

}

void Character :: getTaxes(){
    Land* traverse = head;
    while(traverse->next){
        if(traverse->getHolding() == "city")
            gold+=10;
        else if(traverse->getHolding() == "castle ")
            gold+=7;
        else 
            gold+=5;
    }

}

bool Character :: removeLand(string name){ // return true if there are no land left and delete character from list
    Land* traverse = head;
    Land* traverseTail;
    if(head->next == NULL){
        delete head;
        return true;    
    }
    else {    
        while(traverse->next && traverse->getName() != name){
            traverseTail = traverse;
            traverse  =traverse->next;
        }

        if(traverse->getName() == name){
            Land* temp = traverse;
            traverseTail->next = traverse->next;
            delete temp;
        }
    }
    return false;
}

Character :: ~Character(){
    Land* traverse= head;
    while(traverse){
        traverse = traverse->next;
        delete head;
        head = traverse;
    }
}
bool Character ::isOwnLand(string name){
    Land* traverse = head;
    while(traverse){
        if(traverse->getName() == name){
            return true;
        }
        traverse = traverse->next;
    }
    return false;
}

CharacterList:: CharacterList(){
    arr = new Character[10];
    size =0;
    maxsize = 10;
}

CharacterList:: ~CharacterList(){
    delete [] arr;
}

void CharacterList ::  addCharacter(Character& c){
    if(size == maxsize){
        Character* newarray = new  Character[maxsize*2];
        memcpy(newarray,arr,sizeof(Character)*maxsize);
        delete [] arr;
        arr = newarray;
        maxsize = 2*maxsize;
    }

        arr[size++] = c;

}
    void CharacterList :: delCharacter(string name){
        for(int i = 0; i< size; i++){
            if(name.compare(arr[i].getName()) == 0){
                for(int k = i ; k < size-1;k++){
                    Character temp = arr[i];
                    arr[i] = arr[i+1];
                    arr[i+1] = temp;
                }
                size--;
                break;
            }
        }
     
    }

    //void delCharacter();
    Character CharacterList :: getPlayer(string name){
        for(int i = 0; i< size;i++){
            if(name.compare(arr[i].getName()) == 0){
                return arr[i];
                
            }
        }
        
    }

    
    Character CharacterList :: getLandOwner(string name){
        for(int i = 0; i< size;i++){
            if(arr[i].isOwnLand(name))
                return arr[i];
        }
    }



