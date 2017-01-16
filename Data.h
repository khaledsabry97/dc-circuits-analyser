#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "errors.h"
#include "Interface.h"
using namespace std;

#ifndef NULL
#define NULL nullptr
#endif

// TODO: solve problem of infinte loop when entering invalid key

// used in circuit methods
enum SEARCH_BY {ID, VOLT};

// element's type
enum Type {R, E, J};

/* PROTOTYPES */
class Element
{
private:
    Element* _next;
    Element* _prev;
    Type _type;
    int _id;
    double _value;
    int _node_id;//TODO

    void _SetType(const char &c);
    void _SetValue(const double &num);
    void _SetId(const int &id);
    void _SetNodeId(const int &node_id);//TODO

public:
    Element(const char &type, const int &id, const double &val);
    Element(const char &type, const int &id, const double &val, const int &node_id);//TODO
    char GetType();
    void ChangeType(const char &c);
    Element* GetNext();
    Element* GetPrev();
    int GetId();
    int GetNodeId();//TODO
    void ChangeId(const int &num);
    double GetValue();
    void ChangeValue(const double &num);
    Element* Copy();
    bool operator== (Element&);

    // friends
    friend class Node;
    friend class Circuit;
};

class Node 
{
private:
    Node* _next;
    Node* _prev;
    Element* _firstElement;
    const int _id;
    double _volt;
    int _numElements;

    
    class _List;

public:
    int GetId();
    void ChangeVolt(const double &v);
    double GetVolt();
    int GetNumOfElements();
    bool IsEssential();
    bool IsEmpty();
    Element* GetFirstElement();
    Node* GetNext();
    Node* GetPrev();
    void Add(Element* e);
    bool Remove(Element* e);
    Element* GetElement(char type, const int &id);
    bool HasElement(char type, const int &id);
    Node(const int &id);
	~Node();
    Node* Copy();

    // friends 
    friend class Circuit; 
};

class Circuit 
{
private:
    Node* _firstNode;
    Node* _lastNode;
	int _numNodes;

    bool _IsIt(Node* ptr, const double &val, SEARCH_BY type);
    void _RemoveDuplicates();
    void _Copy_this_toMe(Circuit*);
    void _Check_invalid_nodes();
    void _Print();
public:
    void Add(Node* n);
    bool Remove(Node* n);
    Node* GetLastNode();
    Node* GetFirstNode();
	int GetNumOfNodes();
    void Read();
	~Circuit();
	Circuit();
    Circuit(Circuit* c);
    Circuit(Circuit& c);
	void Push_back(Node* n);
	void Push_front(Node* n);
	bool Pop_back();
	bool Pop_front();
    bool Remove(const double &val, SEARCH_BY type = ID);
    Node* GetNode(const double &val, SEARCH_BY type = ID);
    bool HasNode(const double &val, SEARCH_BY type = ID);
    Element* GetElement(char type, const int &id);
    bool HasElement(char type, const int &id);
    bool IsEmpty();
    Circuit& operator= (Circuit &c);
    Circuit* Copy();  
    Node** GetTerminals(Element* e);  
    Node** GetTerminals(Element* e, Node* &n1, Node* &n2);
};

class Node::_List
{
private:
    vector<Element*> v;

    void _Check(Element* e, int &occ);

public:
    int Add(Element*);
    Element* Get_lonely_elements();
    bool Remove(Element* e);
    void Clear();
    void Print();
};