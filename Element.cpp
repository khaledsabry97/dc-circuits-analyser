#include "Data.h"


/*      Element     */

//  private:
    void Element::_SetType(const char c)
    {
        switch(c):
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

    void Element::_SetValue(const int &num)
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
    Element::Element(char t, const int &id, const double &v)
    {
        _SetType(toupper(t));
        _SetId(id);
        _SetValue(v);
    }

    // Type:
    // when source transformation only
    void Element::ChangeType(char c)
    {
        c = toupper(c);
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

    void Element::SetNext(Element* n)
    {
        _next = n;
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