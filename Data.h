#include <iostream>
#include <string>
#include <list>
using namespace std;

/* PROTOTYPES */
class Element
{
private:
    enum Type {R, E, J};

    Type _type = R;
    int _id = -1;
    double _value = 0;

    void _SetType(const char &c);
    void _SetValue(const int &num);
    void _SetId(const int &id);

public:
    Element(const char &type, const int &id, const double &value);
	~Element();

    char GetType();
    void ChangeType(const char &c);
    int GetId();
    void ChangeId(const int &num);
    double GetValue();
    void ChangeValue(const int &num);
};

class Node 
{
private:
    const int _id;
    double _volt = 0;
    int _numElements = 0;

public:
	Node(const int &id);
	~Node();
	
    int GetId();
    void ChangeVolt(const double &v);
    double GetVolt();
    int GetNumOfElem();
    bool IsEssential();
    void Add(Element* e);
    void Remove(Element* e);
};

class Circuit 
{
private:
    Node* _firstNode = nullptr;
    Node* _lastNode = nullptr;

public:
	Circuit();
	~Circuit();

    bool Add(Node* n);
    bool Remove(Node* n);
	int GetNumOfNodes();
    void Read();
	void Push_back(Node* n);
	void Push_front(Node* n);
	bool Pop_back();
	bool Pop_front();
};