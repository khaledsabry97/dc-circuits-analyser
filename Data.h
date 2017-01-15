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

    // list to store elements while reading
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
                    {
                        // error if the source is duplicate with the same polarity in both nodes
                        if (e->GetValue() == v[i]->GetValue())
                            throw SAME_POLARITY;
                    }
                    // resistance element
                    else
                    {
                        // resistance cant be duplicate with different values
                        if (e->GetValue() != v[i]->GetValue())
                            throw DUPLICATE_WITH_DIFF_VALUES;
                    }
                }

                if (occ > 2)
                    throw DUPLICATE_ELEMENT;
            }
        }

    public:
        // adds address of element in list
        // returns number of occurrences of that element
        // set check to true to make it check errors during adding to list
        int Add(Element* e, bool check = false)
        {
            // number of times that this element hadd occurred in vector
            int occ = 0;

            if (check)
                _Check(e, occ);

            // TODO: what the hell is this?
            if (e->GetType() == 'J' && e->GetId() == 1)
                cout << "this shouldnt be printed\n";

            // add it 
            v.push_back(e);

            return occ;
        }


        // detects lonely elements
        // returns the address of the first lonely element found, or nullptr otherwise
        Element* Get_lonely_elements()
        {
            for (int i = 0; i < v.size(); i++)
            {
                bool is_lonely = true;

                // now we pick v[i] and check if lonely
                for (int j = i + 1; j < v.size(); j++)
                {
                    if (v[i]->GetId() == v[j]->GetId() && v[i]->GetType() == v[j]->GetType())   // found duplicate, v[i] is not lonely
                    {
                        //delete both of them 
                        v.erase(v.begin() + j);
                        v.erase(v.begin() + i);

                        is_lonely = false;
                        break;
                    }
                }

                if (is_lonely)
                    return v[i];
            }

            return nullptr;
        } 

        // removes element from list, it doesn't delete it from memory
        // if found, it removes it and retunrs true
        // otherwise returns false
        bool Remove(Element* e)
        {
            for (int i = 0; i < v.size(); i++)
            {
                if (v[i] == e)
                {
                    v.erase(v.begin() + i);
                    return true;    // success
                }
            }

            return false;   // failure
        }

        // clears the vector from data
        void Clear()
        {
            v.clear();
        }

        // for debugging
        void Print()
        {
            for (int i = 0; i < v.size(); i++)
                cout << v[i]->GetId() << ' ' << v[i]->GetType() << ' ' << v[i]->GetValue() << '\n';
        }
    };

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