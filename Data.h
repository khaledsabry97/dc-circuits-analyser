#include <iostream>
#include <string>
using namespace std;

class Node;
class Elemnt
class Circuit;

class Element
{
private:
    enum Type {R, E, J};

    Element* _next = nullptr;
    Element* _prev = nullptr;
    Type _type = R;
    int _id = -1;
    double _value = 0;

    /* prototypes: */

    void _SetType(const char c);
    void _SetValue(const int &num);
    void _SetId(const int &id);

    /* implementation */

    void _SetType(const char c)
    {
        switch(c):
        {
            case 'R':
                _type = R;
                break;
            case 'E':
                _type = E;
                break;
            case 'J':
                _type = J;
                break;
            default:
                throw -1;
        }
    }

    void _SetValue(const int &num)
    {
        if (_type == R && num < 0)
            throw -1;

        _value = num;
    }

    void _SetId(const int &id)
    {
        if (num < 0)
            throw -1;

        _id = num;
    }

public:
    /* prototypes: */

    Element();
    char GetType();
    void ChangeType(char c);
    Element* GetNext();
    Element* GetPrev();
    void SetNext(Element* n);
    void SetPrev(Element* n);
    int GetId();
    void ChangeId(const int &num);
    double GetValue();
    void ChangeValue(const int &num);
    

    /* implementation: */

    // constructor
    Element(char t, const int &id, const double &v)
    {
        _SetType(toupper(t));
        _SetId(id);
        _SetValue(v);
    }

    // Type:
    // when source transformation only
    void ChangeType(char c)
    {
        c = toupper(c);
        _SetType(c);
    }

    char GetType()
    {
        switch (_type):
        {
            case R:
                return 'R';
            case E:
                return 'E';
            case J:
                return 'J';
            default:
                throw -1;
        }
    }  

    // Ptr:
    Element* GetNext()
    {
        return (_next);
    }  

    void SetNext(Element* n)
    {
        _next = n;
    }

    // ID:
    int GetId()
    {
        return (_id);
    }

    // needed for transforamtions
    void ChangeId(const int &num)
    {
        _SetId(num);
    }

    // Value:
    double GetValue()
    {
        return (_value);
    }

    // for transformations
    void ChangeValue(const int &num)
    {
        _SetValue(num);
    }

};

class Node 
{
private:
    Node* _next = nullptr;
    Element* _firstElement = nullptr;
    const int _id;
    double _volt = 0;
    int _numElements = 0;

    /* prototypes */
    void _SetFirstElem(Element* n);

    /* implementation */
    void _SetFirstElem(Element* n)
    {
        _firstElement = n;
    }
public:
    /* prototypes */
    int GetId();
    void ChangeVolt(const double &v);
    double GetVolt();
    int GetNumOfElem();
    bool IsEssential();
    Element* GetFirstElem();
    Node* GetNext();
    void SetNext(Node* n);
    void Add(Element* e);
    void Remove(Element* e);


    /* implementation */

    // next node:
    void SetNext(Node* n)
    {
        _next = n;
    }

    Node* GetNext()
    {
        return (_next);
    }

    // elements:
    void Add(Element* e)
    {
        
        /* pseudo:
            ;we have e and e2, that e is new and e2 is the prev
            1- e2.prev points at e 
            2- e.next points at e1
            3- node.firstelement points at e
        */

        _firstElement->SetPrev(e);
        e->SetNext(_firstElement);

        _firstElement = e;

        _numElements++;
    }

    void Remove(Element* e)
    {
        /*pseudo:
            ;general case
            ;let e is the element, e- the previous one and e+ the next one
            e+.prev = e-;
            e-.next = e+;
            delete e;
        */

        Element* e_minus = e->GetPrev();
        Element* e_plus = e->GetNext();

        if (e_minus)    // has prev element
            e_minus->SetNext(e_plus);
        else    // first elemen 
            _firstElement = e_plus;

        if (e_plus) // has next element
            e_plus->SetPrev(e_minus);

        _numElements--;
        delete e;
    }

    Element* GetFirstElem()
    {
        return (_firstElement);
    }

    // node:
    bool IsEssential()
    {
        return (_numElements > 2);
    }

    int GetNumOfElem()
    {
        return (_numElements);
    }

    double GetVolt()
    {
        return (_volt);
    }

    void ChangeVolt(const double &v)
    {
        _volt = v;
    }
    
    int GetId()
    {
        return (_id);
    }
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