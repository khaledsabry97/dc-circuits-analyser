#include "Data.h"

/*      Node        */

//  private:
void Node::_SetFirstElem(Element* n)
{
    _firstElement = n;
}
//  public:
// constructor
Node::Node(const int &id) :_id(id)
{}

// next node:
void Node::SetNext(Node* n)
{
    _next = n;
}

Node* Node::GetNext()
{
    return (_next);
}

// elements:
void Node::Add(Element* e)
{
    
    /* pseudo:
        ;let e be the added element and e+ the firstElement
        ;e is new and e+ is the prev

        1- e+.prev points at e 
        2- e.next points at e+
        3- node.firstelement points at e
    */
    Element* e_plus = _firstElement;

    if (e_plus)
        e_plus->SetPrev(e);
    
    e->SetNext(e_plus);

    _firstElement = e;

    _numElements++;
}

void Node::Remove(Element* e)
{
    /*pseudo:
        ;general case
        ;let e is the element, e- the previous one and e+ the next one

        e+.prev = e-;
        e-.next = e+;
        delete e;
    */

    Element* e_minus = e->GetPrev();
    Element* e_plus = e->GetNext();

    if (e_minus)    // has prev element
        e_minus->SetNext(e_plus);
    else    // first elemen 
        _firstElement = e_plus;

    if (e_plus) // has next element
        e_plus->SetPrev(e_minus);

    _numElements--;
    delete e;
}

Element* Node::GetFirstElem()
{
    return (_firstElement);
}

// node:
bool Node::IsEssential()
{
    return (_numElements > 2);
}

int Node::GetNumOfElem()
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
Node::~Node()
{
    // delete all elements before deleting the node
    while (_numElements)
        Remove(_firstElement);
}
