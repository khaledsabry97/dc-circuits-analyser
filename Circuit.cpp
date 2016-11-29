#include "Data.h"

/*      Circuit     */

// public:
Circuit::Circuit()
{
    
}

// delete nodes form memory and clear list
Circuit::~Circuit()
{
    for (itr i = _nodes.begin(); i != _nodes.end(); i++)
    {
        delete *i;       // delete the node
        _nodes.pop_front();     // remove the ptr from list
    }
}

// add node to cicuit
// pushes it from back if essential, push from front otherwise
void Circuit::Add(Node* n)
{
    if (!n)
        throw -1;

    if (!n->IsValid())
        cerr << "ERROR: Node Isn't Valid, aboritng..\n";
    
    if(n->IsEssential())
        _nodes.Push_front(n);
    else 
        _nodes.push_back(n);
}

bool Circuit::Remove(Node* n);
int Circuit::GetNumOfNodes();
void Circuit::Read();

void Circuit::Push_back(Node* n)
{
    if (!n)
        throw -1;

    _nodes.push_back(n);
}

void Circuit::Push_front(Node* n)
{
    if (!n)
        throw -1;

    _nodes.push_front(n);
}

bool Circuit::Pop_back()
{
    if (_nodes.empty())
        return false;
    
    _nodes.pop_back();
    return true;
}

bool Circuit::Pop_front()
{
    if (_nodes.empty())
        return false;
    
    _nodes.pop_front();
    return true;
}

// private:
