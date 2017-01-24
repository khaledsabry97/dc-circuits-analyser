/*     
        Circuit::_List
     list to store elements while reading
     used for issue tracking (error handling during reading)
*/
#include "Data.h"

//      private:

// check the list from errors
// throw error when found
void Circuit::_List::_Check(Element* e)
{
    // number of times that this element had occurred in vector
    int duplicates = 0;

    // iterate through all elements in list 
    for (int i = 0; i < v.size(); i++)
    {
        // aliases, for convenience
        Element*&     e_in_list   =    v[i];
        Element*&     e_given     =    e;

        // if both elements are equal in id and type
        if (    e_given->GetId()     ==   e_in_list->GetId() 
                                     && 
                e_given->GetType()   ==   e_in_list->GetType()     )
        {
            // now we have found a duplicate element in list
            duplicates++;

            // duplicates cant be in same node
            if (e_given->GetNodeId()     ==   e_in_list->GetNodeId())
                throw DUPLICATE_ELEMENT;

            // check duplicate type:

            // resistance element
            if (e_given->GetType() == 'R')
            {
                // assert r_given == r_in_list
                if (e_given->GetValue() != e_in_list->GetValue())
                    throw DUPLICATE_WITH_DIFF_VALUES;
            }

            // current/voltage source
            else
            {
                // assert   source1   !=   source2
                if (e_given->GetValue()      ==       e_in_list->GetValue())
                    throw SAME_POLARITY;

                // assert   source1    == - source2
                if (e_given->GetValue()      !=       - e_in_list->GetValue())
                    throw DUPLICATE_WITH_DIFF_VALUES;
            }
        }

        // we allow element to have one duplicate, no more
        if (duplicates > 1)
            throw DUPLICATE_ELEMENT;
    }
}

//      public:

// adds address of element in list
void Circuit::_List::Add(Element* e)
{
    try
    {
        _Check(e);
    }
    catch (const error &err)
    {
        HandleError(err);
        delete e;
        throw err;
    }

    // add it 
    v.push_back(e);
}

// detects lonely elements
// returns the address of the first lonely element found, or nullptr otherwise
Element* Circuit::_List::Get_lonely_elements()
{
    for (int i = 0; i < v.size(); i++)
    {
        bool is_lonely = true;

        // now we pick v[i] and check if lonely
        for (int j = 0; j < v.size(); j++)
        {
            if (j == i)
                continue;

            if (v[i]->GetId() == v[j]->GetId() && v[i]->GetType() == v[j]->GetType())   // found duplicate, v[i] is not lonely
            {
                // remove both of them from vector v
                // no need of them in the temp vector
                v.erase(v.begin() + j--);
                v.erase(v.begin() + i--);

                is_lonely = false;
                break;
            }
        }

        if (is_lonely)
            return v[i];
    }

    return nullptr;
} 

// removes element from list, it doesn't delete it from memory
// if found, it removes it and retunrs true
// otherwise returns false
bool Circuit::_List::Remove(Element* e)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == e)
        {
            v.erase(v.begin() + i);
            return true;    // success
        }
    }

    return false;   // failure
}

// clears the vector from data
void Circuit::_List::Clear()
{
    v.clear();
}

// for debugging
void Circuit::_List::Print()
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i]->GetId() << ' ' << v[i]->GetType() << ' ' << v[i]->GetValue() << '\n';
}