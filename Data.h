#include <iostream>
using namespace std;

class Element
{
public:
    string id = "None-Initialized";
    double value = 0;

    // ptrs
    Element* next;
    Element* prev;

    enum DEL {ALL, ONE};

    Element(string name, int num) :id(name), value(num)
    {}

    ~Element(DEL operation= ONE)
    {
        if (operation == ALL)
            if (next)
                delete next(ALL); 
    }

    
};