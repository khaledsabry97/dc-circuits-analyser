/*
        Data structure definitions 
*/
#pragma once
#include <iostream>
#include <string>
#include <list>
#include <tuple>
#include <cmath>
#include "Errors.h"
#include "Format.h"
using namespace std;

#ifndef NULL
#define NULL nullptr
#endif

// see Circuit::GetNode and Circuit::HasNode
enum 
SEARCH_BY { ID, VOLT };

// element's type
enum 
Type { R, E, J };

// commands available to user
enum 
Command {
    CMD_PRINT_HELP,
    CMD_PRINT_CREDITS,
    CMD_PRINT_CIRC, 
    CMD_END_NODE, 
    CMD_END_ALL,
    CMD_INVALID,
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

        static bool IsSame(Element*, Element*);
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
        bool Remove(char type, const int &id);

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

        // operator overloading to copy given circuit to this
        Circuit& operator= (Circuit &c);

        // return a deep copy of this circuit
        Circuit* Copy();  

        // returns array of two terminals of given element
        Node** GetTerminals(Element* e);  

        // overloading of above, returns terminals in two ways
        Node** GetTerminals(Element* e, Node* &n1, Node* &n2);

        void Print();
        
    private:
        // aliases for tuples
        typedef tuple<Element*, Node*, Node*> ElementTuple;
        typedef list<ElementTuple>::iterator tpl_itr;

        // temp list for elements 
        // store them while reading for error checking
        class _List
        {
            private:
                list<ElementTuple> list;

                void _Check_then_add(Element* e, Node* node);
                void _Check_errors_between_two_nodes(Element* e, Element* e_in_list, Node* foundNode1, Node* foundNode2);

                bool _Remove_invalid_voltage_source(tpl_itr &itr, tpl_itr &itr2);
                bool _Remove_invalid_current_source(tpl_itr &itr, tpl_itr &itr2);

                void _Parse_ElementTuple_pointers(ElementTuple& tpl, Element*& e, Node*& term1, Node*& term2);

                void _Print_Tuple_list();

                bool _Is_Parallel(const ElementTuple& first, const ElementTuple& second);
                bool _Is_Series(const ElementTuple& first, const ElementTuple& second);
            public:
                void Add(Element* e, Node* node);
                void Pop_back();
                void Clear();
                void Remove_lonely_elements();
                void Remove_invalid_sources();
        };

        // handle user input in reading
        // accepts command and elements
        // NO error handling inside, expects to handle them externally using its functions
        class _Input
        {   
            private:
                enum 
                InputType {
                    CMD, 
                    ELMNT,
                    INVALID,
                    UNKNOWN
                };

                string _line;

                // is it command? element? or invalid?
                InputType input_type;
                Command _cmd;

                void _Command_Parse();
                void _Element_Parse();
                

            public:
                char type;
                int id;
                double val;

                // constructor
                _Input();

            // use this first
                // parse the line 
                // and detect whether it has a command or not
                void Get();

            // use those after parsing
 
                bool IsElement();

                bool IsCommand();
                Command GetCommand();

                // not valid command nor element
                bool IsInvalid();

            // reset variables in this class for next use
                // when NOT used, results in unexpected behaviour 
                // because variables still hold prev data
                void Reset();
                
        };

        Node* _firstNode;
        Node* _lastNode;
        int _numNodes;


        // is this given val (ID or VOLT) is in ptr? 
        // used to increase readability
        bool _IsIt(Node* ptr, const double &val, SEARCH_BY type);

        void _RemoveDuplicates();

        // take circuit and make me a deep copy of it 
        // after: this circuit is the same as the given
        void _Copy_this_to_me(Circuit*);

        // invalid node : has one element or empty
        void _Remove_invalid_nodes();

        //      invalid elements are:-
        // lonely elements: connected to one node
        // curr sources in series
        // volt srcs in parallel
        void _Remove_invalid_elements(_List &list);

        void _Push_back(Node* n);
        void _Push_front(Node* n);
        bool _Pop_back();
        bool _Pop_front();

        

        // re-read this circuit if Circuit::Read ended with empty circuit
        void _Reread_if_empty();

        void _Read_nodes(_List &list);
        void _Read_elements(_List& list, Node* newNode, bool& still_reading_nodes, const int& nodeI);

        // called after filling the node in Circuit::Read
        // decides whether to add node or not depending on its size
        void _Check_and_add_node(Node* newNode, _List& list ,int& nodeI, const bool& continueReading);

        // is this given character a valid type?
        // valid types: r, e, j
        // why static? -to be called without making object of the circuit, it's nicer :)
        static bool _Is_valid_type(char& readenChar);

        // make response according to given command from user input
        // see Circuit::_Input and command enumerator
        void _RespondToCommand(const Command &cmd, bool &still_reading_nodes, bool &still_reading_elements);
};