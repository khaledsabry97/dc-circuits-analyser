#include "Data.h"


/*      Element     */

//  private:
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
            throw -1;
    }
}

void Element::_SetValue(const double &num)
{
    if (_type == R && num < 0)
        throw -1;

    _value = num;
}

void Element::_SetId(const int &id)
{
    if (id < 0)
        throw -1;

    _id = id;
}

//  public:
/* implementation: */

// constructor
Element::Element(const char &type, const int &id, const double &val) 
	:_next(nullptr), _prev(nullptr), _type(R), _id(-1), _value(0)
{
    _SetType(type);
    _SetId(id);
    _SetValue(val);
}

// Type:
// when source transformation only
void Element::ChangeType(const char &c)
{
    _SetType(c);
}

char Element::GetType()
{
    switch (_type)
    {
        case R:
            return 'R';
        case E:
            return 'E';
        case J:
            return 'J';
        default:
            throw -1;
    }
}  

// Ptr:
Element* Element::GetNext()
{
    return (_next);
}  

Element* Element::GetPrev()
{
    return (_prev);
}

// ID:
int Element::GetId()
{
    return (_id);
}

// needed for transforamtions
void Element::ChangeId(const int &num)
{
    _SetId(num);
}

// Value:
double Element::GetValue()
{
    return (_value);
}

// for transformations
void Element::ChangeValue(const int &num)
{
    _SetValue(num);
}

// retunrs address of new element wiht the same variables as this
// Note: next and prev with the returned one are NULL
Element* Element::Copy()
{
    // make new one
    Element* newElement = new Element(GetType(), _id, _value);

    return newElement;
}