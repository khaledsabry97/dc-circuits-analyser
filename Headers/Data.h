#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include "errors.h"
#include "Interface.h"// TODO: find another name/use for this header
using namespace std;

#ifndef NULL
#define NULL nullptr
#endif

// TODO: solve problem of infinte loop when entering invalid key
// TODO: add functionality to enable/disable colors

// see Circuit::GetNode and Circuit::HasNode
enum SEARCH_BY {ID, VOLT};

// element's type
enum Type {R, E, J};

class Element
{
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

    private:
        Element* _next;
        Element* _prev;
        Type _type;
        int _id;
        double _value;
        int _node_id;

        void _SetType(const char &c);
        void _SetValue(const double &num);
        void _SetId(const int &id);
        void _SetNodeId(const int &node_id);

        friend class Node;
        friend class Circuit;

};

class Node 
{
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

                void _Check(Element* e, int &occ);

            public:
                int Add(Element*);
                Element* Get_lonely_elements();
                bool Remove(Element* e);
                void Clear();
                void Print();
        };

        friend class Circuit; 
};

class Circuit
{
    public:
        // add node
        void Add(Node* n);

        // remove node
        bool Remove(Node* n);

        // remove specific node, see doc.
        bool Remove(const double &val, SEARCH_BY type = ID);

        Node* GetLastNode();
        Node* GetFirstNode();

        int GetNumOfNodes();

        // read nodes from user
        void Read();

        // deconstructor, 
        // this is called automatically when circuit is deleted
        ~Circuit();

        // constructors:
        // usual one
        Circuit();
        // copies circuit using its address
        Circuit(Circuit* c);
        // copies circuit using its reference
        Circuit(Circuit& c);

        // return specific node, see doc.
        Node* GetNode(const double &val, SEARCH_BY type = ID);

        // check if circuit includes this node, same as Circuit::GetNode
        bool HasNode(const double &val, SEARCH_BY type = ID);

        Element* GetElement(char type, const int &id);

        bool HasElement(char type, const int &id);

        bool IsEmpty();

        // operator overloading to copy given circiut to this
        Circuit& operator= (Circuit &c);

        // return a deep copy of this circuit
        Circuit* Copy();  

        // returns array of two terminals of given element
        Node** GetTerminals(Element* e);  

        // overloading of above, returns terminals in two ways
        Node** GetTerminals(Element* e, Node* &n1, Node* &n2);

        void Print();
        
    private:
        Node* _firstNode;
        Node* _lastNode;
        int _numNodes;

        bool _IsIt(Node* ptr, const double &val, SEARCH_BY type);
        void _RemoveDuplicates();
        void _Copy_this_toMe(Circuit*);
        void _Check_invalid_nodes();
        void _Push_back(Node* n);
        void _Push_front(Node* n);
        bool _Pop_back();
        bool _Pop_front();
};
