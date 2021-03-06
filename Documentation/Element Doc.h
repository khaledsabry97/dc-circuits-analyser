#ifdef _DO_NOT_INCLUDE_ME_
// do not include this header file in project
Documentation of the Classes:
listing public functionality only

<EXAMPLE>

<END>
#####   Element   #####

## SUMMARRY

Element(const char &type, const int &id, const double &val);
Element* Copy();

Element* GetNext();
Element* GetPrev();

char GetType();
void ChangeType(const char &c);
int GetId();

void ChangeId(const int &num);
double GetValue();
void ChangeValue(const int &num);

static bool IsSame(Element*, Element*);

/* Constructors and copy */

// takes element type, id and value when initializing it
// type can be upper or lower
// id cant be negative
// val cant be negative if type is resistance
Element(const char &type, const int &id, const double &val);

<EXAMPLE>
    Element* e = new Element('r', 2, 8);        // resistance id= 2 val = 8 ohm, good
    Element* e1 = new Element('r', -2, 8);       // ERROR
    Element* e2 = new Element('r', 2, -8);      // ERROR  

    Element* e3 = new Element('J', 3, -9);      // Ok
<END>

// copy this element and return the new copy address
Element* Copy();

<EXAMPLE>
     Element* e = new Element('r', 2, 8); 
     Element* otherOne = e->Copy();     // it is a duplicate of this node
<END>

/* Other Elements */

// return address of next element
Element* GetNext();

<EXAMPLE>
    Node* n = new Node(4);
    Element* e1 = new Element('j', 9, 18);     
    Element* e2 = new Element('r', 2, +38); 
    n->Add(e2);
    n->Add(e1);

    // now e1 points.next points at e2 
    Element* temp = e1->GetNext();
    if (temp == e2)
        cout << "Im correct\n";
<END>

// return address of previous node 
Element* GetPrev();

/* Element Data */

// retuns type of node
char GetType();

<EXAMPLE>
    Element* e1 = new Element('r', 2, 8);       
    char t = e1->GetType();
    // t now equals 'R'
<END>

// change type of element, use only on source transformation
void ChangeType(const char &c);

// returns the id of element
int GetId();

// changes the id of element
void ChangeId(const int &num);

// returns the vlaue of the element
double GetValue();

// changes the value of the element
void ChangeValue(const int &num);

// two elements are same, if both have same id and type
// use when having two elements at two different nodes and want to check if they are the same element
// returns true if both are the same
static bool IsSame(Element*, Element*);

NOTE: static here means you call it just if it is inside a namespace, see example below

<EXAMPLE>
    // we have e1 and e2
    if (Element::IsSame(e1, e2))
        cout << "they are the same element\n";
    else
        cout << "they are different elements\n";
<END>

// get id of the connected node 
void GetNodeId();

NOTE: if not connected to a node it returns -1

<EXAMPLE>
    Node* n = new Node(5);
    Element* e = new Element('R', 6, 4);
    cout << n->GetNodeId(); // prints 5
<END>

#endif