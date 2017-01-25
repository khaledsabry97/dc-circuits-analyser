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
        case INVALID_INPUT:
        {
            cerr << HANDLE_INVALID_INPUT;
            break;
        }
        case PARALLEL_DIFF_VOLTAGES:
        {
            cerr << HANDLE_PARALLEL_DIFF_VOLTAGES;
            break;
        }
        case SERIES_DIFF_CURRENTS:
        {
            cerr << HANDLE_SERIES_DIFF_CURRENTS;
            break;
        }
        case INVALID_STORED_TYPE:
            assert(FOR_DEBUGGING && "INVALID_STORED_TYPE Exception has been thrown, you seem to be accessing invalid memory");
        default:
            assert(FOR_DEBUGGING && "unhandled exeption, please debug this point");
    }
}