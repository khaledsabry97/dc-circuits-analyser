/*
        Data structure definitions 
*/
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Errors.h"
#include "___.h"// TODO: find another name/use for this header
using namespace std;

#ifndef NULL
#define NULL nullptr
#endif

// TODO: solve problem of infinte loop when entering invalid key
// TODO: add functionality to enable/disable colors
// TODO: check why it terminates with segmentation fault when circuit is not full (has one element)
// TODO: bug when entering one node with this element r1 1

// see Circuit::GetNode and Circuit::HasNode
enum SEARCH_BY {ID, VOLT};

// element's type
enum Type {R, E, J};

// commands available to user
enum Command {
        Help,
        Print_Circuit, 
        EndNode, 
        EndAll,
        NotCommand,
    };

class Element
{
    public:
        // constructors
        Element(const char &type, const int &id, const double &val);

        // only used in Circuit::Read
        Element(const char &type, const int &id, const double &val, const int &node_id);

        char GetType();
        void ChangeType(const char &c);

        Element* GetNext();
        Element* GetPrev();

        int GetId();
        void ChangeId(const int &num);

        // return id of node which contains this element
        int GetNodeId();
        
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

        // true if node has nodes > 2
        bool IsEssential();

        bool IsEmpty();

        Element* GetFirstElement();

        Node* GetNext();
        Node* GetPrev();

        void Add(Element* e);
        bool Remove(Element* e);

        Element* GetElement(char type, const int &id);
        bool HasElement(char type, const int &id);

        // constructor, used only on reading the circuit 
        Node(const int &id);

        // destructor
        ~Node();

        // return address of a copy of the node
        Node* Copy();

    private:
        Node* _next;
        Node* _prev;
        Element* _firstElement;
        const int _id;
        double _volt;
        int _numElements;

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
        // temp list for elements while reading
        class _List
        {
            private:
                vector<Element*> v;// TODO: make it a list not vector (if you can)

                void _Check(Element* e, int &occ);

            public:
                int Add(Element*);
                Element* Get_lonely_elements();
                bool Remove(Element* e);
                void Clear();
                void Print();
        };

        // handle user input in reading
        class _Input
        {   
            private:

                string _line;
                bool _is_valid;
                Command _cmd;

                void Command_Parse();
                void _Element_Parse();
                

            public:
                char type;
                int id;
                double val;

                _Input();
    
                // parse the line and detect whether it has a command or not
                void Get();
                bool IsElement();
                bool IsCommand();
                bool IsInvalid();
                Command GetCommand();
                void Reset();
                
        };
        
        Node* _firstNode;
        Node* _lastNode;
        int _numNodes;

        bool _IsIt(Node* ptr, const double &val, SEARCH_BY type);
        void _RemoveDuplicates();
        void _Copy_this_to_me(Circuit*);
        void _Remove_invalid_nodes();
        void _Push_back(Node* n);
        void _Push_front(Node* n);
        bool _Pop_back();
        bool _Pop_front();
        void _Remove_lonely_elements(_List&);
        void _Reread_if_empty();
        void _Read_nodes(_List& list);
        void _Read_elements(_List& list, Node* newNode, bool& still_reading_nodes, const int& nodeI);
        void _Check_and_add_node(Node* newNode, _List& list ,int& nodeI, const bool& continueReading);
        static bool _Is_valid_type(char& readenChar);
        void _HadleCommand(const Command &cmd, bool &still_reading_nodes, bool &still_reading_elements);
};