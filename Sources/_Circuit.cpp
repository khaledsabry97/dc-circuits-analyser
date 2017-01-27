/*      
    Circuit private methods source
*/
#include "Data.h"

bool Circuit::_IsIt(Node* ptr, const double &val, SEARCH_BY type)
{
    switch (type)
    {
        case ID:
            return (val == ptr->GetId());
        case VOLT:
            return (val == ptr->GetVolt());
        default:
            assert(FOR_DEBUGGING && "passed SEARCH_BY is not valid, maybe function tried to access invalid memory");
    }
}

void Circuit::_Copy_this_to_me(Circuit* c)
{
     // copy nodes
    Node* originalNode = c->GetFirstNode();

    // traverse through them all till null
    while (originalNode)
    {
        Node* copiedNode = originalNode->Copy();
        Add(copiedNode);

        // go to the next
        originalNode = originalNode->GetNext();
    }
}

// invalid nodes: that have one/zero elements
void Circuit::_Remove_invalid_nodes()
{
    Node* n = GetFirstNode();
    for (int count = 0; n; count++)
    {
        if (n->IsEmpty())
        {
            cerr << HANDLE_EMPTY_NODE << " Node #" << n->GetId() << '\n';
            Node* temp = n;
            n = n->GetNext();
            Remove(temp);
        }
        else if (n->GetNumOfElements() == 1) // one element
        {
            cerr << HANDLE_NODE_WITH_ONE_ELEM << " Node #" << n->GetId() << '\n';
            Node* temp = n;
            n = n->GetNext();
            Remove(temp);
        }
        else
            n = n->GetNext();

    }
}

//      invalid elements are:-
// lonely elements: connected to one node
// curr sources in series
// volt srcs in parallel
void Circuit::_Remove_invalid_elements(_List &list)
{
    list.Remove_lonely_elements();
    list.Remove_invalid_sources();
}

void Circuit::_Reread_if_empty()
{
    if (IsEmpty())
    {
        cerr << RED << "\tCircuit is Empty \n" << "\tEnter the circuit again\n" << WHITE;
        Read();
    }
}

void Circuit::_Read_nodes(_List &list)
{
    bool still_reading_nodes = true;

    for (int nodeI = 1; still_reading_nodes; nodeI++)
    {
        cout << WHITE 
            << "Node #" << nodeI << ":" 
            << "\n";
        
        Node* newNode = new Node(nodeI);
        
        _Read_elements(list, newNode, still_reading_nodes, nodeI);

        _Check_and_add_node(newNode, list, nodeI, still_reading_nodes);
    }
}

void Circuit::_Read_elements(_List& list, Node* newNode, bool& still_reading_nodes, const int& nodeI)
{
    Element* e = nullptr;
    bool still_reading_elements = true;
    _Input input;

    // loop through all elements
    while (still_reading_elements)
    {
        // get/parse input 
        input.Get();
        
        // react
        if (input.IsElement()) 
        {
            try
            {
                e = new Element(input.type, input.id, input.val, nodeI);
                list.Add(e, newNode);
            }
            catch (const error &err)
            {
                continue;
            }
            // else
            {
                newNode->Add(e);
            }
        }
        else if (input.IsCommand())
        {
            _RespondToCommand(input.GetCommand(), still_reading_nodes, still_reading_elements);
        }
        else if (input.IsInvalid())
        {
            HandleError(INVALID_INPUT);
        }

        // reset variables
        input.Reset();
    }
}

bool Circuit::_Is_valid_type(char& readenChar)
{
    readenChar = toupper(readenChar);
    switch(readenChar)
    {
        case 'R': break;
        case 'J': break;
        case 'E': break;

        default: return false;
    }
    return true;
}

// called after filling the node in Circuit::Read
// decides whether to add node or not depending on its size
void Circuit::_Check_and_add_node(Node* newNode, _List& list ,int& nodeI, const bool& continueReading)
{
    if (newNode->IsEmpty())
    {
        // delete it and tell user that it's not added

        // only tell user if he didn't type xx
        if (continueReading)
        {
            cout << HANDLE_EMPTY_NODE;
            delete newNode;
            nodeI--;
        }
    }
    else if (newNode->GetNumOfElements() == 1)  
    {
        cout << HANDLE_NODE_WITH_ONE_ELEM;
        
        // remove the element from the list before removing the node
        list.Remove(newNode->GetFirstElement());

        delete newNode;
        nodeI--;
    }
    // valid node
    else         
        Add(newNode);
}

void Circuit::_RespondToCommand(const Command &cmd, bool &still_reading_nodes, bool &still_reading_elements)
{
    switch (cmd)
    {
        case CMD_PRINT_HELP:
        {
            Print_Help(); 
            break;
        } 
        case CMD_PRINT_CREDITS:
        {
            Print_Credits();
            break;
        }
        case CMD_PRINT_CIRC:
        {
            Print();
            break;
        }
        case CMD_END_ALL:
        {
            still_reading_nodes = false;
        }
        case CMD_END_NODE:
        {
            still_reading_elements = false;
            break;
        }
        case CMD_INVALID: 
            HandleError(INVALID_INPUT);
            break;
        default:
            assert(FOR_DEBUGGING && "passed command is unknown and not-invalid either, check cases in Circuit::_RespondToCommand");
    }
}

void Circuit::_Push_back(Node* n)
{
    if (!n)
        throw -1;       // cant handle empty pointer

    n->_next = nullptr;

    // handle special case, when first time pushing
    if (!_lastNode && !_firstNode)
    {
        _lastNode = _firstNode = n;
        n->_prev = nullptr;
        _numNodes++;
        return;
    }

    _lastNode->_next = n;
    n->_prev = _lastNode;
    _lastNode = n;
    _numNodes++;
}

void Circuit::_Push_front(Node* n)
{
    if (!n)
        throw -1;       // cant handle empty pointer

    n->_prev = nullptr;

    if (!_lastNode && !_firstNode)
    {
        _lastNode = _firstNode = n;
        n->_next = nullptr;
        _numNodes++;
        return;
    }   

    n->_next = _firstNode;
    _firstNode->_prev = n; 
    _firstNode = n;
    _numNodes++;
}

bool Circuit::_Pop_back()
{
    if (!_lastNode)
        return false;

    Node* temp = _lastNode;

    // if there is only one node, move both to null after removing it
    if (_lastNode == _firstNode)
        _lastNode = nullptr; 
        
    _lastNode = _lastNode->_prev;
    _lastNode->_next = nullptr;
    delete temp;
    _numNodes--;

    return true;
}

bool Circuit::_Pop_front()
{
    if (!_firstNode)
        return false;

    Node* temp = _firstNode;

    // if there is only one node, move both to null after removing it
    if (_lastNode == _firstNode)
        _lastNode = nullptr;     

    _firstNode = _firstNode->_next;
    if (_firstNode)     // TODO: chekc if this helped avoid seg. fault
        _firstNode->_prev = nullptr;
    delete temp;
    _numNodes--;

    return true;
}