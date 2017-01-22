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
            throw -1;
    }
}

// i don't know why i wrote it, but maybe Hadi asks for it , who knows :D
void Circuit::_RemoveDuplicates()
{
    Node* first = _firstNode;

    // iterate through list, let every one of them be 'first' in its own sublist
    while (first)    
    {
        // to point at others 
        Node* other = first->_next;

        // iterate through all list to check duplicates of first
        while (other)
        {
            // there is a duplicate, remove it
            if (other->GetId() == first->GetId())
            {
                Node* temp = other;
                other = other->_next;

                Remove(temp);

                continue;
            }

            other = other->_next;
        }

        first = first->GetNext();
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

void Circuit::_Remove_lonely_elements(_List& list)
{
    // remove lonely elements that occurred in list one time 
    while (true)
    {
        Element* lonely = list.Get_lonely_elements();
        if (!lonely)    // no lonely elements
            break;

        char type = lonely->GetType();
        int id = lonely->GetId();

        // look for it in nodes
        Node* n = GetFirstNode();
        Element* e = nullptr;
        while (n)
        {
            e = n->GetElement(type, id);
            if (e)  // found it 
                break;
            else    // not yet
                n = n->GetNext();
        }
        if (!e) // not found after searching, there is a problem
            assert(FOR_DEBUGGING && "cant find the lonely element");

        // tell the user the details and delete it TODO: add colors to this 
        cerr << "===> ERROR, found lonely element " << lonely->GetType() << lonely->GetId() << " in Node #" << n->GetId() 
            << " ,Removing it\n" ;

        // remove from list
        list.Remove(e);  

        // remove from node and memory  
        n->Remove(e);   

    }
}

void Circuit::_Reread_if_empty()
{
    if (IsEmpty())
    {
        // TODO: add colors
        cerr << "====> ERROR! Circuit is Empty \n" << "Enter the circuit again\n";
        Read(false);
    }
}

void Circuit::_Read_nodes(_List& list)
{
    bool still_reading_nodes = true;

    for (int nodeI = 1; still_reading_nodes; nodeI++)
    {
        cout << WHITE 
            << "Node #" << nodeI << ":" 
            << "\n";
        
        Node* newNode = new Node(nodeI);
        
        _Read_elements(list, newNode, still_reading_nodes, nodeI);

        _Check_and_add_node(newNode, list ,nodeI, still_reading_nodes);
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
                list.Add(e);
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
            _HadleCommand(input.GetCommand(), still_reading_nodes, still_reading_elements);
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

void Circuit::_HadleCommand(const Command &cmd, bool &still_reading_nodes, bool &still_reading_elements)
{
    switch (cmd)
    {
        case Help:
        {
            cout << HELP; 
            break;
        } 
        case Print_Circuit:
        {
            Print();
            break;
        }
        case EndAll:
        {
            still_reading_nodes = false;
        }
        case EndNode:
        {
            still_reading_elements = false;
            break;
        }
        default: 
            HandleError(INVALID_INPUT);
    }
}