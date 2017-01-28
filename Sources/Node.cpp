/*
      Node public methods source 
*/
#include "Data.h"


// constructor
Node::Node(const int &id)
	:_id(id), _next(nullptr), _prev(nullptr), 
    _firstElement(nullptr), _volt(0), 
    _numElements(0), _from_circuit(nullptr)
{}

// next node
Node* Node::GetNext()
{
    return (_next);
}

Node* Node::GetPrev()
{
    return (_prev);
}


// add element to this node
void Node::Add(Element* e)
{
    if (!e)
        throw DEREF_NULL_PTR;

    // assign node value to this node while inserting
    e->_node_id = GetId();

    /* pseudo:
        ;let e be the added element and e+ the firstElement
        ;e is new and e+ is the prev

        1- e+.prev points at e 
        2- e.next points at e+
        3- node.firstelement points at e
    */
    e->_next = _firstElement;
    e->_prev = nullptr;

    if (_firstElement)
        _firstElement->_prev = e;
        
    _firstElement = e;

    _numElements++;
}

// remove given element from this node
// throws DEL_ELEMENT_FROM_WRONG_NODE if element is not in this node
bool Node::Remove(Element* e)
{
    /*pseudo:
        ;general case
        ;let e is the element, e- the previous one and e+ the next one

        e+.prev = e-;
        e-.next = e+;
        delete e;
    */
    if (!e)
        return false;
    else if (e->GetNodeId() != GetId())
        throw DEL_ELEMENT_FROM_WRONG_NODE;

    Element* e_minus = e->_prev;
    Element* e_plus = e->_next;

    if (e_minus)    // has prev element
        e_minus->_next = e_plus; 
    else    // first element
        _firstElement = e_plus;

    if (e_plus) // has next element
        e_plus->_prev = e_minus;

    _numElements--;
    delete e;
    return true;
}

bool Node::Remove(char type, const int &id)
{
    Element* e = GetElement(type, id);
    return (Remove(e));
}

Element* Node::GetFirstElement()
{
    return (_firstElement);
}

// node:
bool Node::IsEssential()
{
    return (_numElements > 2);
}

int Node::GetNumOfElements()
{
    return (_numElements);
}

double Node::GetVolt()
{
    return (_volt);
}

void Node::ChangeVolt(const double &v)
{
    _volt = v;
}

int Node::GetId()
{
    return (_id);
}

// destructor
// delete all elements before deleting the node
Node::~Node()
{
    while (Remove(_firstElement));
}

// copies the node wiht its elements and return address for the copy
// NOTE: the returned node doesn't point at any other node; next and prev are null
Node* Node::Copy()
{
    // the new node
    Node* newNode = new Node(_id);
    newNode->_volt = _volt;

    // temp pointer while iterating through elements
    Element* originalElement = _firstElement;

    // traverse till null
    while (originalElement)
    {
        Element* copiedElement = originalElement->Copy();
        newNode->Add(copiedElement);

        // go to the next element
        originalElement = originalElement->_next;
    }

    // here your node
    return newNode;
}

bool Node::IsEmpty()
{
    return (!_numElements);
}

// look for the element in list
// returns the address of the element if found, otherwise nullptr
Element* Node::GetElement(char type, const int &id)
{
    type = toupper(type);

    Element* e = GetFirstElement();
    while (e)
    {
        if (e->GetType() == type && e->GetId() == id)
            return e;   // found it

        e = e->GetNext();
    }

    return nullptr;         // not found
}

bool Node::HasElement(char type, const int &id)
{
    type = toupper(type);

    Element* e = GetFirstElement();
    while (e)
    {
        if (e->GetType() == type && e->GetId() == id)
            return true;   // found it

        e = e->GetNext();
    }

    return false;         // not found
}