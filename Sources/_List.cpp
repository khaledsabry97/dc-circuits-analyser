/*     
        Circuit::_List
     list to store elements while reading
     used for issue tracking (error handling during reading)
*/
#include "Data.h"

//      private:

// checks for errors and adds element if valid
// throws DUPLICATE_ELEMENT, DUPLICATE_WITH_DIFF_VALUES, SAME_POLARITY
void Circuit::_List::_Check_then_add(Element* e, Node* node)
{
    /*pseudo-code:
        loop list in reverse:
            if found:
                if tuple has both nodes:
                    throw DUPLICATE_ELEMENT

                if thisNode is foundNode:
                    throw DUPLICATE_ELEMENT
                
                if (resistances) and (different in value):
                    throw DUPLICATE_WITH_DIFF_VALUES

                if e or j:
                    if same value:
                        throw SAME_POLARITY
                    
                    if given.value != - found.value:
                        throw DUPLICATE_WITH_DIFF_VALUES
            else:
                make new tuple
                add it
    */
    Element* e_in_list;
    Node* foundNode1, foundNode2;

    for (auto itr = l.rbegin(); itr != rend(); itr++)
    {
        auto tpl = _Parse_ElementTuple_pointers(*itr, e_in_list, foundNode1, foundNode2);

        if (Element::IsSame(e, e_in_list))
        {
        // check errors
        // TODO: move to a function
            // tuple is full -> duplicate
            if (foundNode1 && foundNode2)
                throw DUPLICATE_ELEMENT;

            // they are in same node -> duplicate
            if (node == foundNode1)
                throw DUPLICATE_ELEMENT;

            if (e->GetType() == 'R') 
            {
                // different in value
                if (e->GetValue()   !=   e_in_list->GetValue())
                    throw DUPLICATE_WITH_DIFF_VALUES;
            }
            else
            {
                // same value 
                if (e_given->GetValue()      ==       e_in_list->GetValue())
                    throw SAME_POLARITY;

                // not given == - found
                if (e_given->GetValue()      !=       - e_in_list->GetValue())
                    throw DUPLICATE_WITH_DIFF_VALUES;
            }
        //

               // element is valid, add its node to tuple
               get<2>(tpl) = node;
        }
    }

    // tuple is not found, lets make new tuple
    ElementTuple tpl(e, node, nullptr);
    l.push_back(tpl);
}

//      public:

// adds address of element in list
void Circuit::_List::Add(Element* e, Node* node)
{
    try
    {
        _Check_then_add(e, node);
    }
    catch (const error &err)
    {
        HandleError(err);
        delete e;
        throw err;
    }
}

// detects lonely elements
// returns the address of the first lonely element found, or nullptr otherwise
void Circuit::_List::Remove_lonely_elements()
{
    for (auto itr = l.begin(); itr != l.end(); itr++)
    {
        // parse tuple, *itr is an ElementTuple
        Node* node = get<2>(*itr);
        Element* e = get<0>(*itr);

        if (!node2)
        {
            // remove it 
            HandleError(LONELY_ELEMENT);
            delete e;

            l.erase(itr);
        }
    }
} 

// clears the list from data
void Circuit::_List::Clear()
{
    v.clear();
}

/*   immigrated   */

void Circuit::_List::Remove_invalid_sources()
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
    
    Element *e, *e2;
    char elementType = '\0';

    // traverse through list looking for sources
    for (auto itr = l.begin(); itr != l.end(); ++itr)
    {
        e = get<0>(*itr);
        // detect type of this src and store it here
        element_type = e->GetType();
        // ignore it if resistance
        if (element_type == 'R')
            continue;

        // traverse through rest of list
        for (auto itr2 = next(itr); itr2 != volt_list.end(); ++itr2)
        {
            e2 = get<0>(*itr2);

            // e must be same type as e2
            if (e2->GetType() != element_type)
                continue;

            // see what type is it, and call proper function
            switch (element_type)
            {
                case 'E':
                    _Remove_invalid_voltage_sources(*itr, *itr2);
                    break;
                case 'J':
                    _Remove_invalid_current_sources(*itr, *itr2);
                    break;
                default:
                    assert(FOR_DEBUGGING);
            }
        }
    }
}

// TODO: make one function for both curr/volt 
void Circuit::_List::_Remove_invalid_voltage_sources(ElementTuple &tpl, ElementTuple &tpl2)
{
    if (_Is_Parallel(tpl, tpl2))
    {
        // fill those
        Element *e, *e2;
        Node *e_term_1, *e_term_2, *e2_term_1, *e2_term_2;
        _Parse_ElementTuple_pointers(tpl, e, e_term_1, e_term_2);
        _Parse_ElementTuple_pointers(tpl2, e2, e2_term_1, e2_term_2);

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

void Circuit::_List::_Remove_invalid_current_sources(ElementTuple &tpl, ElementTuple &tpl2)
{
    if (_Is_Series(tpl, tpl2))
    {
        // fill those
        Element *e, *e2;
        Node *e_term_1, *e_term_2, *e2_term_1, *e2_term_2;
        _Parse_ElementTuple_pointers(tpl, e, e_term_1, e_term_2);
        _Parse_ElementTuple_pointers(tpl2, e2, e2_term_1, e2_term_2);

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

void Circuit::_List::_Parse_ElementTuple_pointers(ElementTuple& tpl, Element*& e, Node*& term1, Node*& term2)
{
    ElementTuple& e_tuple = tpl;

    // element
    e = get<0>(e_tuple);

    // terminals in order
    term1 = get<1>(e_tuple);
    term2 = get<2>(e_tuple);
}

void Circuit::_List::_Print_Tuple_list(list<ElementTuple>& some_list)
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

bool Circuit::_List::_Is_Parallel(const ElementTuple& first, const ElementTuple& second)
{
    // get terminals from the tuple
    Node *e_term_1 = get<1>(first), 
    *e_term_2 = get<2>(first), 

    *e2_term_1 = get<1>(second), 
    *e2_term_2 = get<2>(second);

    return ((e_term_1 == e2_term_1       &&       e_term_2 == e2_term_2) || 
            (e_term_1 == e2_term_2       &&       e_term_2 == e2_term_1));
}

bool Circuit::_List::_Is_Series(const ElementTuple& first, const ElementTuple& second)
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