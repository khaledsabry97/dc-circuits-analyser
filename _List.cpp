#include "Data.h"

/*     Node::_List     */

// list to store elements while reading
// used for issue tracking (error handling during reading)

//      private:

// check the list from errors
// throw error when found
void Node::_List::_Check(Element* e, int &occ)
{
    // iterate through all elements in list before adding it 
    for (int i = v.size(); i--;)
    {
        // if both elements are equal in id and type
        if (*e == *v[i])
        {
            // now we have found the duplicate element in list
            occ++;

            // if both are in same node, they are duplicate
            if (e->GetNodeId() == v[i]->GetNodeId())
                throw DUPLICATE_ELEMENT;

            // check the duplicate type:
            //
            // if it is source
            if (e->GetType() != 'R')
            {
                // error if the source is duplicate with the same polarity in both nodes
                if (e->GetValue() == v[i]->GetValue())
                    throw SAME_POLARITY;
            }
            // resistance element
            else
            {
                // resistance cant be duplicate with different values
                if (e->GetValue() != v[i]->GetValue())
                    throw DUPLICATE_WITH_DIFF_VALUES;
            }
        }

        if (occ > 2)
            throw DUPLICATE_ELEMENT;
    }
}

//      public:

// adds address of element in list
// returns number of occurrences of that element
// set check to true to make it check errors during adding to list
int Node::_List::Add(Element* e)
{
    // number of times that this element hadd occurred in vector
    int occ = 0;

    _Check(e, occ);

    // TODO: what the hell is this?
    // if (e->GetType() == 'J' && e->GetId() == 1)
    //     cout << "this shouldnt be printed\n";

    // add it 
    v.push_back(e);

    return occ;
}

// detects lonely elements
// returns the address of the first lonely element found, or nullptr otherwise
Element* Node::_List::Get_lonely_elements()
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
bool Node::_List::Remove(Element* e)
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
void Node::_List::Clear()
{
    v.clear();
}

// for debugging
void Node::_List::Print()
{
    for (int i = 0; i < v.size(); i++)
        cout << v[i]->GetId() << ' ' << v[i]->GetType() << ' ' << v[i]->GetValue() << '\n';
}