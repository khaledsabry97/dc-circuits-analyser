/*      
    Element private methods source
*/
#include "Data.h"


void Element::_SetType(const char &c)
{
    switch (toupper(c))
    {
        case 'R':
            _type = R;
            break;
        case 'E':
            _type = E;
            break;
        case 'J':
            _type = J;
            break;
        default:
            throw BAD_TYPE_NAME;
    }
}

void Element::_SetValue(const double &num)
{
    if (_type == R && num < 0)
        throw NEGATIVE_RESISTANCE;

    _value = num;
}

void Element::_SetId(const int &id)
{
    _id = id;
}

void Element::_SetNodeId(const int &node_id)
{
    _node_id = node_id;
}