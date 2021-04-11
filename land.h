//////////////////////////////////
/*          <Halil Faruk Karagöz>         */
/*          <150180014>           */
//////////////////////////////////


#pragma once 
#include <iostream>
#include <string.h>

using namespace std;

class Land{
    private : 
    char* name;
    char* holding;
    public : 
    char* getName(){return name;}
    char* getHolding(){return holding;}
    Land(string inname, string inholding) {
        name = new char[20];
        holding = new char[20];
        strcpy(name,inname.c_str());
        strcpy(holding,inholding.c_str());
    }
    Land( const Land& in) {
        name = new char[20];
        holding = new char[20];
        strcpy(name,in.name);
        strcpy(holding,in.holding);
    }
    ~Land(){
        delete [] name;
        delete [] holding;
    }
    Land* next;
};



