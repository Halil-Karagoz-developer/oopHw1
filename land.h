
#include <iostream>
#include <string.h>

using namespace std;

class Land{
    private : 
    string name;
    string holding;
    public : 
    string getName(){return name;}
    string getHolding(){return holding;}
    Land(string inname, string inholding) : name(inname), holding(inholding) {}
    Land(Land& in) {name = in.name ; holding = in.holding; }
    Land* next;
};



