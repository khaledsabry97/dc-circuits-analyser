#ifdef _DO_NOT_INCLUDE_ME_
// do not include this header file in project
Documentation of the Classes:
listing public functionality only

#####   Node   #####

## SUMMARRY
Node(const int &id);
Node* Copy();

void Add(Element* e);
bool Remove(Element* e);
bool IsEmpty();
Element* GetFirstElement();

Node* GetNext();
Node* GetPrev();

Element* GetElement(char type, const int &id);
bool HasElement(char type, const int &id);

int GetId();
void ChangeVolt(const double &v);
double GetVolt();
int GetNumOfElements();
bool IsEssential();

/* Construcors and Copy */

// gives the created node its id that cant be changed 
Node(const int &id);

<EXAMPLE>
    Node* n = new Node(7);      // now its id is 7
<END>

// returns a copy of this node
Node* Copy();

<EXAMPLE>
    Node* n = new Node(7);
    Node* newOne = n->Copy()        // now newOne is a copy of n
<END>

/* Elements Handling */

// add element to list 
// adds in FIFO (First In First Out) way
void Add(Element* e);

<EXAMPLE>
    Node* n = new Node(7);
    Element* e = new Element('r', 8, 9);
    n->Add(e)       // element is added to list
<END>

// removes the given element 
// WARNING! DO NOT PASS AN ELEMENT FROM OTHER NODE, IT MAY RESULT IN FATAL ERRORS
bool Remove(Element* e);

<EXAMPLE>
    Node* n = new Node(7);
    Element* e = new Element('r', 8, 9);
    n->Add(e)       // element is added to list

    // remove it 
    n->Add(e);
    // removed now
<END>

// returns true if empty, false otherwise
bool IsEmpty();


// returns address of first element in the list, if empty: returns nullptr
Element* GetFirstElement();

<EXAMPLE>
    Node* n = new Node(7);
    Element* e = new Element('r', 8, 9);
    n->Add(e)       // element is added to list, and it is the first

    Element* temp = n->GetFirstElement();
    if (temp == e)
        cout << "e is the first element\n";
<END>

/* This Node Data */

// returns address of next node, nullptr is returned if not attached to next  
Node* GetNext();

<EXAMPLE>
    Circuit* c = new Circuit;
    Node* n = new Node(3);
    Node* n2 = new Node(5);
    // assume that n will be the first one and n2 is the second in nodes list 

    Node* temp = n->GetNext();
    if (temp == n2)
        cout << "this is means that n2 is the second node in the circuit and n is the first one\n";
<END>

// the same of GetNext but returns previous node address
Node* GetPrev();

// returns node's id
int GetId();

// changes the volt of this node, used after calculating node's voltage
void ChangeVolt(const double &v);

// returns node's volt, initiatlized to 0
double GetVolt();

// returns num of elements in this node
int GetNumOfElements();

// returns true if node is essential, false otherwise
// essential: has more than two elements
bool IsEssential();

#endif