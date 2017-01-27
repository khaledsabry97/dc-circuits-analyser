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
        case LONELY_ELEMENT:
        {
            cerr << HANDLE_LONELY_ELEMENT;
            break;
        }
        case UNAVAILABLE_ELEMENT:
        {
            cerr << HANDLE_UNAVAILABLE_ELEMENT;
            break;
        }
        case INVALID_STORED_TYPE:
            assert(FOR_DEBUGGING && "INVALID_STORED_TYPE Exception has been thrown, you seem to be accessing invalid memory");
        default:
            assert(FOR_DEBUGGING && "unhandled exeption, please debug this point");
    }
}

void HandleSignals()
{
    // exit
    signal(SIGABRT, sgnl::Terminate);
    signal(SIGINT, sgnl::Terminate);
    signal(SIGTERM, sgnl::Terminate);

    // segmentation fault
    signal(SIGSEGV, sgnl::Seg_Fault);

    // float point
    signal(SIGFPE, sgnl::Divide_by_zero);
}

namespace sgnl
{
    void Seg_Fault(int signum)
    {
        cerr << RED << "\t\tProgram Tried to access invalid memory\n";
        cerr << "\t\tTerminating...\n" << WHITE;
        Sleep(2 * SECOND);
        exit(SIGSEGV);
    }
        
    // stopping program
    void Terminate(int signum)
    {
        cout << YELLOW << "\t\tProgram is terminating..\n" << WHITE;
        Sleep(2 * SECOND);
        exit(SUCCESS);
    }

    // float point signal
    void Divide_by_zero(int signum)
    {
        cerr << RED << "\t\tProgram tried to divide by zero\n\t\tTerminating...\n" << WHITE;
        Sleep(2 * SECOND);
        exit(SIGFPE);
    }
}
