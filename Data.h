#pragma once
#include <iostream>
#include <string>
using namespace std;

#ifndef NULL
#define NULL nullptr
#endif

/* PROTOTYPES */
class Element
{
private:
    enum Type {R, E, J};

    Element* _next;
    Element* _prev;
    Type _type;
    int _id;
    double _value;

    void _SetType(const char &c);
    void _SetValue(const double &num);
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
    Node* _next;
    Element* _firstElement;
    const int _id;
    double _volt;
    int _numElements;

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

// used in circuit methods
enum SEARCH_BY {ID, VOLT};

class Circuit 
{
private:
    Node* _firstNode;
    Node* _lastNode;
	int _numNodes;

    bool _IsIt(Node* ptr, const double &val, SEARCH_BY type);

public:
    void Add(Node* n);
    bool Remove(Node* n);
    Node* GetLastNode();
    Node* GetFirstNode();
	int GetNumOfNodes();
    void Read();
	~Circuit();
	Circuit();
	void Push_back(Node* n);
	void Push_front(Node* n);
	bool Pop_back();
	bool Pop_front();

    bool Remove(const double &val, SEARCH_BY type = ID);
    Node* GetNode(const double &val, SEARCH_BY type = ID);
    bool HasNode(const double &val, SEARCH_BY type = ID);
    void RemoveDuplicates();
    bool IsEmpty();
};