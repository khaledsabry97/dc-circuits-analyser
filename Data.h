#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "errors.h"
using namespace std;

#ifndef NULL
#define NULL nullptr
#endif

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

    void _SetType(const char &c);
    void _SetValue(const double &num);
    void _SetId(const int &id);

public:
    Element(const char &type, const int &id, const double &val);
    char GetType();
    void ChangeType(const char &c);
    Element* GetNext();
    Element* GetPrev();
    int GetId();
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

    class _List
    {
    private:
        vector<Element*> v;

        // check the list from errors
        // throw error when found
        void _Check(Element* e, int &occ)
        {
            // iterate through all elements in list befor adding it 
            for (int i = v.size(); i--;)
            {
                // if both elements are equal in id and type
                if (*e == *v[i])
                {
                    // now we have found the duplicate element in list
                    occ++;

                    // check the duplicate type:
                    //
                    // if it is source
                    if (e->GetType() != 'R')
                        // error if the source is duplicate with the same polarity in both nodes
                        if (e->GetValue() == v[i]->GetValue())
                            throw SAME_POLARITY;

                    // resistance element
                    else
                        // resistance cant be duplicate with different values
                        if (e->GetValue() != v[i]->GetValue())
                            throw DUPLICATE_WITH_DIFF_VALUES;
                }

                if (occ > 2)
                    throw DUPLICATE_ELEMENT;
            }
        }

    public:
        enum check {CHECK, NO_CHECK};

        // adds address of element in list
        // returns number of occurrences of that element
        int Add(Element* e, check c = NO_CHECK)
        {
            // number of times that this element hadd occurred in vector
            int occ = 0;

            if (c == CHECK)
                _Check(e, occ);

            // add it 
            v.push_back(e);

            return occ;
        }

        // clears the vector from data
        void Clear()
        {
            v.clear();
        }
    };
    bool _Repair(_List &l);

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
    bool IsEmpty();
    Circuit& operator= (Circuit &c);
    Circuit* Copy();
    bool Repair();
};