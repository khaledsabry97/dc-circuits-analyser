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
            throw INVALID_STORED_TYPE;
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
void Element::ChangeValue(const double &num)
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

// operator overloading 
// returns true if id and type are equall
bool Element::operator== (Element& e)
{
    return (_id == e.GetId() && GetType() == e.GetType());
}