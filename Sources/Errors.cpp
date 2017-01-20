#include "Errors.h"

void HandleError(const error& err)
{
    switch (err)
    {
        case SAME_POLARITY:
        {
            cerr << HANDLE_SAME_POLARITY;
            break;
        }
        case DUPLICATE_WITH_DIFF_VALUES:
        {
            cerr << HANDLE_DUPLICATE_WITH_DIFF_VALUES;
            break;
        }
        case DUPLICATE_ELEMENT:
        {   
            cerr << HANDLE_DUPLICATE_ELEMENT;
            break;
        }
        case BAD_TYPE_NAME:
        {
            cerr << HANDLE_BAD_TYPE_NAME;
            break;
        }
        case NEGATIVE_RESISTANCE:
        {
            cerr << HANDLE_NEGATIVE_RESISTANCE;
            break;
        }
        case INVALID_STORED_TYPE:
            assert(FOR_DEBUGGING && "INVALID_STORED_TYPE");
        default:
            assert(FOR_DEBUGGING && "unhandled exeption");
    }
}