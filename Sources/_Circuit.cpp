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

void Circuit::_Remove_lonely_elements()
{
    // create list again from this circuit
    _List list;
    Node* n = GetFirstNode();
    while (n)
    {
        Element* e = n->GetFirstElement();
        while (e)
        {
            list.Add_without_check(e);
            e = e->GetNext();
        }

        n = n->GetNext();
    }

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

        // tell the user the details and delete it 
        cerr << RED << "\tFound lonely element " << lonely->GetType() << lonely->GetId() << " in Node #" << n->GetId() 
            << " ,Removing it\n" << WHITE ;

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
        cerr << RED << "\tCircuit is Empty \n" << "\tEnter the circuit again\n" << WHITE;
        Read(false);
    }
}

void Circuit::_Read_nodes()
{
    _List list;

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
        case Print_Credits:
        {
            cout << CREDITS;
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

void Circuit::_Remove_invalid_sources()
{
    /*pseudo-code:
        get data
            make list for current
            --    --  for voltage
            file them with tuples

        track issues
            v: terminals cant be duplic with different voltage value
            c: one terminal cant be duplic in any with different curr value

        O(n^2)
    */

    list<ElementTuple> volt_list;
    list<ElementTuple> curr_list;

    _Get_Sources(volt_list, curr_list);

    _Print_Tuple_list(volt_list);
    _Print_Tuple_list(curr_list);

    _Remove_invalid_voltage_sources(volt_list);

    Print();

    _Remove_invalid_current_sources(curr_list);

    Print();
}

// fill lists with sources from this circuit
void Circuit::_Get_Sources(list<ElementTuple>& volt_list, list<ElementTuple>& curr_list)
{
    Node* n = GetFirstNode();
    while (n)
    {
        Element* e = n->GetFirstElement();
        while (e)
        {
            // is current source
            if (e->GetType() == 'J')
                _Add_to_tuple_list(e, n, curr_list);
            // is voltage source
            else if (e->GetType() == 'E')
                _Add_to_tuple_list(e, n, volt_list);

            e = e->GetNext();
        }

        n = n->GetNext();
    }
}

// adds given element with its terminal(node) to the list
void Circuit::_Add_to_tuple_list(Element* e, Node* terminal, list<ElementTuple>& some_list)
{
    /*pseudo-code:
        // search in the list
        // found it?   
            // add terminal as second one
        // no!
            // make tuple
            // add tuple
    */

    cout << "Element is " << e->GetType() << e->GetId() << " Terminal " << terminal->GetId() << '\n';//FOR_DEBUGGING

    // search in reverse; to find a match quickly
    for (auto itr = some_list.rbegin(); itr != some_list.rend(); ++itr)
    {
        // aliases
        Element*& e2 = get<0>(*itr);
        Node*& new_terminal = get<2>(*itr);

        // found
        if (e->GetId() == e2->GetId())
        {
            // add terminal as second one
            new_terminal = terminal;
            return;
        }
    }

    // not found
    // add one
    ElementTuple tpl(e, terminal, nullptr);
    some_list.push_back(tpl);

}

// TODO: make one function for both curr/volt 
void Circuit::_Remove_invalid_voltage_sources(list<ElementTuple>& volt_list)
{
    Element *e, *e2;
    Node *e_term_1, *e_term_2, *e2_term_1, *e2_term_2;

    // iterate volt sources
    for (auto itr = volt_list.begin(); itr != volt_list.end(); ++itr)
    {
        _Parse_ElementTuple_pointers(*itr, e, e_term_1, e_term_2);

        for (auto itr2 = next(itr); itr2 != volt_list.end(); ++itr2)
        {
            _Parse_ElementTuple_pointers(*itr2, e2, e2_term_1, e2_term_2);

            if (_Is_Parallel(*itr, *itr2))
            {
                // if they are not equall
                // remove both 
                if (e->GetValue()   !=   e2->GetValue())
                {
                    int id1 = e->GetId(), id2 = e2->GetId();

                    // tell user
                    HandleError(PARALLEL_DIFF_VOLTAGES);

                    // remove both of them
                    //
                    // remove from term_1
                    e_term_1->Remove('E', id1);
                    e_term_1->Remove('E', id2);
                    // remove from term_2
                    e_term_2->Remove('E', id1);
                    e_term_2->Remove('E', id2);

                    // remove tuples from list
                    auto temp_itr = itr; itr++;
                    volt_list.erase(temp_itr);
                    volt_list.erase(itr2);

                }
                // if they are equall
                else
                {
                    int id2 = e2->GetId();

                    // just remove last one 
                    //
                    // from list
                    volt_list.erase(itr2);
                    // from terminal 1
                    e2_term_1->Remove('E', id2);
                    // from terminal 2
                    e2_term_2->Remove('E', id2);
                }

                // stop the inner loop
                break;
            }
        }
    }
}

void Circuit::_Remove_invalid_current_sources(list<ElementTuple>& curr_list)
{
    Element *e, *e2;
    Node *e_term_1, *e_term_2, *e2_term_1, *e2_term_2;

    // iterate current sources
    for (auto itr = curr_list.begin(); itr != curr_list.end(); ++itr)
    {
        _Parse_ElementTuple_pointers(*itr, e, e_term_1, e_term_2);

        for (auto itr2 = next(itr); itr2 != curr_list.end(); ++itr2)
        {
            _Parse_ElementTuple_pointers(*itr2, e2, e2_term_1, e2_term_2);

            if (_Is_Series(*itr, *itr2))
            {
                // not equall
                // remove both
                if (e->GetValue()  !=  e2->GetValue())
                {
                    int id1 = e->GetId(), id2 = e2->GetId();

                    // tell user
                    HandleError(SERIES_DIFF_CURRENTS);

                    // remove both of them
                    //
                    // remove e
                    e_term_1->Remove('J', id1);
                    e_term_2->Remove('J', id1);
                    // remove e2
                    e2_term_1->Remove('J', id2);
                    e2_term_2->Remove('J', id2);
                    

                    // remove tuples from list
                    auto temp_itr = itr; itr++;
                    curr_list.erase(temp_itr);
                    curr_list.erase(itr2);
                }
                // they are equall
                // remove last one
                else 
                {
                    int id2 = e2->GetId();

                    // just remove last one 
                    //
                    // from list
                    curr_list.erase(itr2);
                    // from terminal 1
                    e2_term_1->Remove('J', id2);
                    // from terminal 2
                    e2_term_2->Remove('J', id2);
                }

                // stop the inner loop
                break;
            }
        }
    }
}

void Circuit::_Parse_ElementTuple_pointers(ElementTuple& tpl ,Element*& e, Node*& term1, Node*& term2)
{
    ElementTuple& e_tuple = tpl;

    // element
    e = get<0>(e_tuple);

    // terminals in order
    term1 = get<1>(e_tuple);
    term2 = get<2>(e_tuple);
}

void Circuit::_Print_Tuple_list(list<ElementTuple>& some_list)
{
    Element *e, *e2;
    Node *e_term_1, *e_term_2;

    for (auto itr = some_list.begin(); itr != some_list.end(); ++itr)
    {
        _Parse_ElementTuple_pointers(*itr, e, e_term_1, e_term_2);

        cout << "Element " << e->GetType() << e->GetId()
            << " terminals ";
            
        if (e_term_1)
            cout << e_term_1->GetId();

        if (e_term_2)
            cout << " and " << e_term_2->GetId() << '\n';
    }
}

bool Circuit::_Is_Parallel(const ElementTuple& first, const ElementTuple& second)
{
    // get terminals from the tuple
    Node *e_term_1 = get<1>(first), 
    *e_term_2 = get<2>(first), 

    *e2_term_1 = get<1>(second), 
    *e2_term_2 = get<2>(second);

    return ((e_term_1 == e2_term_1       &&       e_term_2 == e2_term_2) || 
            (e_term_1 == e2_term_2       &&       e_term_2 == e2_term_1));
}

bool Circuit::_Is_Series(const ElementTuple& first, const ElementTuple& second)
{
    // get terminals from the tuple
    Node *e_term_1 = get<1>(first), 
    *e_term_2 = get<2>(first), 

    *e2_term_1 = get<1>(second), 
    *e2_term_2 = get<2>(second);

    // i know it is bad :( 
    return !_Is_Parallel(first, second) && 
        (e_term_1 == e2_term_1 || e_term_1 == e2_term_2 || 
        e_term_2 == e2_term_1 || e_term_2 == e2_term_2);
}