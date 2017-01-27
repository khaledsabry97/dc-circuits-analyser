/*
    Different errors that may occur
    and their handling messages and functions.

        used in exception handling.
*/
#pragma once
#include "Format.h"
#include <cassert>
#include <iostream>
#include <csignal>
using namespace std;
#define FOR_DEBUGGING 0
#define SUCCESS 0

// for sleeping
#if !defined(_WIN32)
    #include <unistd.h>
    #define Sleep(milliseconds) usleep(milliseconds * 1000)
#else
    #include <windows.h>
#endif
#define SECOND 1000


// identify different errors that might happen
enum 
error {
    SAME_POLARITY, 
    DUPLICATE_WITH_DIFF_VALUES, 
    DUPLICATE_ELEMENT, 
    BAD_TYPE_NAME, 
    NEGATIVE_RESISTANCE, 
    INVALID_STORED_TYPE, // stored type is against rules, usually happens when accessing invalid memory
    LONELY_ELEMENT,
    DEREF_NULL_PTR,
    DEL_ELEMENT_FROM_WRONG_NODE,
    NODE_ID_IN_ELEM_UNASSIGNED,
    INVALID_NODE_ID,
    INVALID_INPUT,
    PARALLEL_DIFF_VOLTAGES,
    SERIES_DIFF_CURRENTS,
    UNAVAILABLE_ELEMENT,    // when trieng to search for an element not in circuit
};

// strings to handle errors
#define HANDLE_SAME_POLARITY RED << "\tTheir is two source elements with the same polarity, deleting the last one\n" << WHITE
#define HANDLE_DUPLICATE_ELEMENT RED << "\tDuplicate element, deleting it\n" << WHITE
#define HANDLE_DUPLICATE_WITH_DIFF_VALUES RED << "\tFound two elements having same ID and differnt values, deleting the last one\n" << WHITE
#define HANDLE_BAD_TYPE_NAME RED << "\tInvalid Type, please re-enter it\n" << WHITE
#define HANDLE_NEGATIVE_RESISTANCE RED << "\tResistance can't be negative, deleted it\n" << WHITE
#define HANDLE_EMPTY_NODE RED << "\tLast node is empty, deleting it\n" << WHITE
#define HANDLE_NODE_WITH_ONE_ELEM RED << "\tFound node with one element, deleting the node and the element\n" << WHITE
#define HANDLE_INVALID_INPUT RED << "\tInvalid input, type h to see valid commands\n" << WHITE 
#define HANDLE_PARALLEL_DIFF_VOLTAGES RED << "\tFound two parallel voltage sources with different values, deleteing both of them\n" << WHITE
#define HANDLE_SERIES_DIFF_CURRENTS RED <<  "\tFound two current sources with different values in series, deleteing both of them\n" << WHITE
#define HANDLE_LONELY_ELEMENT RED <<  "\tFound lonely element, deleting it\n" << WHITE
#define HANDLE_UNAVAILABLE_ELEMENT RED <<  "\tElement not found, please check the circuit\n" << WHITE


// print the appropriate message for the error 
// with color RED if colors are enabled
// if exception is not listed, it asserts for debugging printing that error is not handled
void HandleError(const error& err);

// DEPRECATED! results in undefined behaviour on windows
// run this to set functions in signal to specific system signals
// to be run at beginning
void HandleSignals();

namespace sgnl
{
    // accessing invalid memory
    void Seg_Fault(int signum);

    // stopping program
    void Terminate(int signum);

    // float point signal
    void Divide_by_zero(int signum);
}
