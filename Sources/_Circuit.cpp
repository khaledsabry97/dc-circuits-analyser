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

    _Remove_invalid_voltage_sources(volt_list);

    _Remove_invalid_current_sources(curr_list);
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

    // search in reverse; to find a match quickly
    for (auto itr = some_list.rbegin(); itr != some_list.rend(); itr++)
    {
        // aliases
        Element*& e2 = get<0>(*itr);
        Node*& new_terminal = get<2>(*itr);

        // found
        if (e == e2)
        {
            // add terminal as second one
            new_terminal = terminal;
        }
    }

    // not found
    // add one
    ElementTuple tpl(e, terminal, nullptr);
    some_list.push_back(tpl);
}

// BUG: infinte loop, it seems it doesnt work
// TODO: group all those aliases in one function 
void Circuit::_Remove_invalid_voltage_sources(list<ElementTuple>& volt_list)
{
    // iterate volt sources
    for (auto itr = volt_list.begin(); itr != volt_list.end(); itr++)
    {
        /*  aliases: e_tuple, e, e_term_1, e_term_2  */
            ElementTuple& e_tuple = *itr;

            Element*& e = get<0>(e_tuple);//element

            // terminals in order
            Node*& e_term_1 = get<1>(e_tuple);
            Node*& e_term_2 = get<2>(e_tuple);

        for (auto itr2 = next(itr); itr != volt_list.end(); itr2++)
        {
            /*  aliases: e2_tuple, e2, e2_term_1, e2_term_2 */
                ElementTuple& e2_tuple = *itr2;

                Element*& e2 = get<0>(e2_tuple);//element

                // terminals in order
                Node*& e2_term_1 = get<1>(e2_tuple);
                Node*& e2_term_2 = get<2>(e2_tuple);


            // terminals cant be duplic with different voltage value
            if (e_term_1 == e2_term_1       &&       e_term_2 == e2_term_2)
                if (e->GetValue()   !=   e2->GetValue())
                {
                    // tell user
                    HandleError(PARALLEL_DIFF_VOLTAGES);

                    // remove both of them
                    //
                    // remove from term_1
                    e_term_1->Remove(e);
                    e_term_1->Remove(e2);
                    // remove from term_1
                    e_term_2->Remove(e);
                    e_term_2->Remove(e2);

                    // remove tuples from list
                    auto temp_itr = itr; itr++;
                    volt_list.erase(temp_itr);
                    volt_list.erase(itr2);

                    // stop the inner loop
                    break;
                }
        }
    }
}

void Circuit::_Remove_invalid_current_sources(list<ElementTuple>& curr_list)
{

    // iterate current sources
    for (auto itr = curr_list.begin(); itr != curr_list.end(); itr++)
    {
        /*  aliases: e_tuple, e, e_term_1, e_term_2  */
            ElementTuple& e_tuple = *itr;

            Element*& e = get<0>(e_tuple);//element

            // terminals in order
            Node*& e_term_1 = get<1>(e_tuple);
            Node*& e_term_2 = get<2>(e_tuple);

        for (auto itr2 = next(itr); itr != curr_list.end(); itr2++)
        {
            /*  aliases: e2_tuple, e2, e2_term_1, e2_term_2 */
                ElementTuple& e2_tuple = *itr2;

                Element*& e2 = get<0>(e2_tuple);//element

                // terminals in order
                Node*& e2_term_1 = get<1>(e2_tuple);
                Node*& e2_term_2 = get<2>(e2_tuple);

            // one terminal cant have a duplicate while curr valu is different
            if (e_term_2 == e2_term_1)
            {
                if (e->GetValue()  !=  e2->GetValue())
                {
                    // tell user
                    HandleError(PARALLEL_DIFF_VOLTAGES);

                    // remove both of them
                    //
                    // remove from term_1
                    e_term_1->Remove(e);
                    e_term_1->Remove(e2);
                    // remove from term_1
                    e_term_2->Remove(e);
                    e_term_2->Remove(e2);

                    // remove tuples from list
                    auto temp_itr = itr; itr++;
                    curr_list.erase(temp_itr);
                    curr_list.erase(itr2);
                }
                else // they are equall
                {
                    // just remove last one 
                    curr_list.erase(itr2);
                }

                // stop the inner loop
                break;
            }
        }
    }
}