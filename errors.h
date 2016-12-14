#pragma once
#include <cassert>
#define FOR_DEBUGGING 0
#define WITH_CHECK 1
#define NO_CHECK 0

// identify different errors that might happen
enum error {SAME_POLARITY, 
            DUPLICATE_WITH_DIFF_VALUES, 
            DUPLICATE_ELEMENT, BAD_TYPE_NAME, 
            NEGATIVE_RESISTANCE, INVALID_STORED_TYPE, 
            LONELY_ELEMENT};

// strings to handle errors
#define HANDLE_SAME_POLARITY "===> ERROR, found source element with the same polarity, deleting the last one found\n"
#define HANDLE_DUPLICATE_ELEMENT "===> ERROR, found duplicate element, deleting it\n"
#define HANDLE_DUPLICATE_WITH_DIFF_VALUES "===> ERROR, found two elements having same ID and differnt values, deleting the last one\n"
#define HANDLE_BAD_TYPE_NAME "====> ERROR, type entered is not valid, please re-enter it\n"
#define HANDLE_NEGATIVE_RESISTANCE "===> ERROR, found a negative resistance, deleted it\n"
#define HANDLE_EMPTY_NODE "===> ERROR, found empty node, deleting it\n"
#define HANDLE_NODE_WITH_ONE_ELEM "===> ERROR, found node with one element, deleting the node and the element\n"