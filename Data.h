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

    void _SetType(const char &c);
    void _SetValue(const int &num);
    void _SetId(const int &id);

public:
    Element(const char &t, const int &id, const double &v);
    char GetType();
    void ChangeType(const char &c);
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
    Node(const int &id);
	~Node();
};

class Circuit 
{
private:
    Node* _firstNode = nullptr;
    Node* _lastNode = nullptr;
	int _numNodes = 0;

public:
    void Add(Node* n);
    bool Remove(Node* n);
    Node* GetLastNode();
    Node* GetFirstNode();
	int GetNumOfNodes();
    //void Read();
	~Circuit();
	void Push_back(Node* n);
	void Push_front(Node* n);
	bool Pop_back();
	bool Pop_front();
};