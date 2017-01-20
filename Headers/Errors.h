#pragma once
#include "Colors.h"
#include <cassert>
#include <iostream>
using namespace std;
#define FOR_DEBUGGING 0

/*
    Different errors that may occur
    and their handling messages and functions.

        used in exception handling.
*/

// identify different errors that might happen
enum error 
{
    SAME_POLARITY, 
    DUPLICATE_WITH_DIFF_VALUES, 
    DUPLICATE_ELEMENT, 
    BAD_TYPE_NAME, 
    NEGATIVE_RESISTANCE, 
    INVALID_STORED_TYPE, 
    LONELY_ELEMENT,
    DEREF_NULL_PTR,
    DEL_ELEMENT_FROM_WRONG_NODE,
    NODE_ID_IN_ELEM_UNASSIGNED,
    INVALID_NODE_ID
};

// strings to handle errors
#define HANDLE_SAME_POLARITY RED "\tERROR, found source element with the same polarity, deleting the last one\n" WHITE
#define HANDLE_DUPLICATE_ELEMENT RED "\tERROR, found duplicate element, deleting it\n" WHITE
#define HANDLE_DUPLICATE_WITH_DIFF_VALUES RED "\tERROR, found two elements having same ID and differnt values, deleting the last one\n" WHITE
#define HANDLE_BAD_TYPE_NAME RED "\tERROR, type entered is not valid, please re-enter it\n" WHITE
#define HANDLE_NEGATIVE_RESISTANCE RED "\tERROR, found a negative resistance, deleted it\n" WHITE
#define HANDLE_EMPTY_NODE RED "\tERROR, found empty node, deleting it\n" WHITE
#define HANDLE_NODE_WITH_ONE_ELEM RED "\tERROR, found node with one element, deleting the node and the element\n" WHITE

// print the appropriate message for the error 
// with color RED if colors are enabled
// if exception is not listed, it asserts for debugging printing that error is not handled
void HandleError(const error& err);