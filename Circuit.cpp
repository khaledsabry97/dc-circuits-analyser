#include "Data.h"

/*      Circuit     */

//  public:

// Deconstructor
Circuit::~Circuit()
{
    /* pseudo:
        call Remove on all nodes
    */

    while (_numNodes)
        Remove(_firstNode);
}

// void Circuit::Read()
// {
//     /* pseudo:
//         loop:
//             addd node with number
//             loop:
//                 add elements
//             stop on x
//         stop on xx
//     */

//     cout << "Enter circuit's nodes\nWhen node is entered, type x \nWhen finished the circuit, type xx\n\n";

//     for (int i = 1;; i++)
//     {
//         new node with num = i
//         Node* n = new Node(1);

//         cout << "Node " << i << ":\n";

//         while (true)
//         {
//             read line
//             string line; 
//             getline(cin, line);
//             end node if x, return if xx
//             if (line[0] == 'x')
//             {
//                 if (line[1] == 'x')
//                     return;
//                 else 
//                     break;
//             }

//             parse line into variables 
//             check if line is valid

//             new element with variables
//         }
//     }
// }


bool Circuit::Add(Node* n)
{
    /* pseudo:
        if essential:
            put at front of list
        else
            put at end of list

        put:
            ;let the pointer be ptr
            ptr.next points at n
            or -----> n.next points at ptr & ptr 
    */

    // handle Special case, when last and first are nullptrs
    if (!_lastNode && !_firstNode)
    {
        _lastNode = _firstNode = n;
        _numNodes++;
        return;
    }

    // general case
    if (n->IsEssential())
    {
        // put at front
        n->SetNext(_firstNode);
        _firstNode = n;
    }
    else 
    {
        // put at end
        if (_lastNode)
            _lastNode->SetNext(n);

        _lastNode = n;
    }

    _numNodes++;
}

bool Circuit::Remove(Node* n)
{
    /*  pseudo:
        get previous node:
            start from beginning
            iterate until this.next = n
            if finsished without finding it, throw exception
        ;let prev = n-, this = n
        n-.next = n.next
        delete n

        ;check if n- exists

        ;special cases:
        ;n = firstnode ----> +
        ;n = lastnode -----> +
        ;n is not in list ---->  +
    */
    if (!n)
        throw -1;       // cant delete null

    if (n == _firstNode)
    {
        _firstNode = _firstNode->GetNext();
        delete n;
        _numNodes--;

        return;
    }

    // get previous node
    Node* n_minus = _firstNode;
    while(n_minus)
    {
        if (n_minus->GetNext() == n)
            break;

        n_minus = _firstNode->GetNext();
    }

    if (!n_minus)       // not found in list
        return false;

    if (n == _lastNode)
        _lastNode = n_minus;

    n_minus->SetNext(n->GetNext());
    delete n;
    _numNodes--;

    return true;
}

Node* Circuit::GetLastNode()
{
    return (_lastNode);
}

Node* Circuit::GetFirstNode()
{
    return (_firstNode);
}

int Circuit::GetNumOfNodes()
{
    return(_numNodes);
}


void Push_back(Node* n)
{
    if (!n)
        throw -1;       // cant handle empty pointer

    n->SetNext(nullptr);
    _lastNode->SetNext(n);
    _lastNode = n;

    // special cases
    // _lastNode = _firstNode = nullptr
    if (!_firstNode) 
        _firstNode = _lastNode;

}
void Push_front(Node* n)
{
    if (!n)
        throw -1;       // cant handle empty pointer

    n->SetNext(_firstNode);
    _firstNode = n;

    // special cases
    // _lastNode = _firstNode = nullptr
    if (!_lastNode) 
        _lastNode = _firstNode;

}
bool Pop_back()
{
    if (!_lastNode)
        return false;
    Remove(_lastNode);
    return true;
}
bool Pop_front()
{
    if (!_frontNode)
        return false;

    Remove(_frontNode);
    return true;
}