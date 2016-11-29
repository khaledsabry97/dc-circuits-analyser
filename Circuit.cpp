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


void Circuit::Add(Node* n)
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
    if (n->IsEssential())
        Push_front(n);
    else 
        Push_back(n);
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
        // if there is only one node, move both to null after removing it
        if (_lastNode == _firstNode)
            _lastNode = nullptr;     

        _firstNode = _firstNode->GetNext();
        delete n;
        _numNodes--;

        return true;
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


void Circuit::Push_back(Node* n)
{
    if (!n)
        throw -1;       // cant handle empty pointer

    n->SetNext(nullptr);

    if (!_lastNode && !_firstNode)
    {
        _lastNode = _firstNode = n;
        return;
    }

    _lastNode->SetNext(n);
    _lastNode = n;
    _numNodes++;
}

void Circuit::Push_front(Node* n)
{
    if (!n)
        throw -1;       // cant handle empty pointer

    if (!_lastNode && !_firstNode)
    {
        _lastNode = _firstNode = n;
        return;
    }   

    n->SetNext(_firstNode);
    _firstNode = n;
    _numNodes++;
}

bool Circuit::Pop_back()
{
    if (!_lastNode)
        return false;

    Remove(_lastNode);
    return true;
}
bool Circuit::Pop_front()
{
    if (!_firstNode)
        return false;

    Remove(_firstNode);
    return true;
}