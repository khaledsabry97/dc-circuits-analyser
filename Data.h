#include <iostream>
#include <string>
using namespace std;

class Node;
class Elemnt
class Circuit;

class Element
{
public:
    string id = "None-Initialized";
    double value = 0;

    // ptrs
    Element* next = nullptr;

    bool CheckType()
    {
        char type = toupper(id[0]);

        if (type == 'R' || type == 'I' || type == 'J')
            return true;

        return false;
    }

    Element(string name, int num) :id(toupper(name)), value(num)
    {
        // id is invalid
        if (!CheckID())
            throw -1;
    }

    // parse
    Element(string line)
    {
        
    }
    void Add(Element* n)
    {
        next = n;
        n->prev = n;
    }

    char GetType()
    {
        return (id[0]);
    }
};

class Node 
{
public:
    Node* next = nullptr;
    Node* prev = nullptr;

    Element* firstElement = nullptr;

    
};

class Circuit 
{
public:
    Node* firstNode = nullptr;
    Node* lastNode = nullptr;

    void Read()
    {
        // loop:
        //      addd node with number
        //      loop:
        //          add elements
        //      stop on x
        //  stop on xx

        cout << "Enter circuit's nodes\nWhen node is entered, type x \nWhen finished the circuit, type xx\n\n";

        for (int i = 1;; i++)
        {
            // new node with num = i
            Node* n = new Node;

            cout << "Node " << i << ":\n";

            while (true)
            {
                // read line
                string line; 
                cin.getline(line);
                // end node if x, return if xx
                if (line[0] == 'x')
                {
                    if (line[1] == 'x')
                        return;
                    else 
                        break;
                }

                // parse line into variables 
                // check if line is valid

                // new element with variables
            }
        }
    }
};