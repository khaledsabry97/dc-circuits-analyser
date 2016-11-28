#include <iostream>
#include <string>
using namespace std;

/* PROTOTYPES */
class Element
{
private:
    enum Type {R, E, J};

    Element* _next = nullptr;
    Element* _prev = nullptr;
    Type _type = R;
    int _id = -1;
    double _value = 0;

    void _SetType(const char c);
    void _SetValue(const int &num);
    void _SetId(const int &id);

public:
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
};

class Node 
{
private:
    Node* _next = nullptr;
    Element* _firstElement = nullptr;
    const int _id;
    double _volt = 0;
    int _numElements = 0;

    void _SetFirstElem(Element* n);

public:
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
};

class Circuit 
{
public:
    Node* firstNode = nullptr;
    Node* lastNode = nullptr;
};