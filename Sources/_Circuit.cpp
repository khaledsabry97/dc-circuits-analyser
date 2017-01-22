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
        Read();
    }
}

void Circuit::_Read_nodes(_List& list)
{
    bool continueReading = true;

    for (int nodeI = 1; continueReading; nodeI++)
    {
        cout << WHITE 
            << "Node #" << nodeI << ":" 
            << "\n";
        
        Node* newNode = new Node(nodeI);
        
        _Read_elements(list, newNode, continueReading, nodeI);

        _Check_and_add_node(newNode, list ,nodeI, continueReading);
    }
}

void Circuit::_Read_elements(_List& list, Node* newNode, bool& continueReading, const int& nodeI)
{
    // variables to store the element
    char type;
    int id = 0;
    double val = 0;

    Element* e = nullptr;

    int temp = 0;

    // loop through all elements
    // TODO: use scanf instead of cin to parse arguments
    // TODO: bug when entering more than one r or j it goes to Element
    while (true)
    {
        cout << PROMPT;

        // get first character, escape spaces
        do cin >> type; 
        while (type == ' ');

        if (_Is_valid_type(type)) 
        {
            cin >> id >> val;
            
            try
            {
                e = new Element(type, id, val, nodeI);
                list.Add(e);
            }
            catch(const error &err)
            {
                HandleError(err);
                cout << err;
                if (err == BAD_TYPE_NAME || err == DUPLICATE_ELEMENT)
                    temp++;
                cout << temp << '\n';
                if (temp > 10)
                    assert(FOR_DEBUGGING);

                // escape this when element constructor is the thrower of problem
                // TODO: their is a better way to approach this solution
                if (err != NEGATIVE_RESISTANCE and err != BAD_TYPE_NAME)
                    delete e;       

                continue;
            }

            newNode->Add(e);
        }

        // TODO: enhance commands
        else if (toupper(type) == 'X')   
        {
            // if user typed another x, end all circuit
            type = cin.get();
            if (toupper(type) == 'X') 
                continueReading = false;
            
            break;
        }
        else if (toupper(type) == 'H')
            cout << HELP;
        else if (toupper(type) == 'P')
            Print();
        else
            HandleError(BAD_TYPE_NAME);
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