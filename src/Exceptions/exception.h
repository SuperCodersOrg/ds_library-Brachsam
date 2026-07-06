#pragma once
#include <stdexcept>
#include <string>

// custom exceptions for the library. all of them inherit from a standard
// exception type so callers can either catch the specific one or just
// catch std::exception and be done with it.

// bad index passed into DynamicArray
class DynamicArrayException : public std::out_of_range {
public:
    explicit DynamicArrayException(const std::string& msg)
        : std::out_of_range("DynamicArray Error: " + msg) {}
};

// bad index passed into SinglyLinkedList / DoublyLinkedList
class LinkedListException : public std::out_of_range {
public:
    explicit LinkedListException(const std::string& msg)
        : std::out_of_range("LinkedList Error: " + msg) {}
};

// deleteFront/deleteBack called on an empty list
class EmptyListException : public std::underflow_error {
public:
    explicit EmptyListException(const std::string& msg)
        : std::underflow_error("LinkedList Error: " + msg) {}
};

// get/remove called with a key that isn't in the map
class KeyNotFoundException : public std::out_of_range {
public:
    explicit KeyNotFoundException(const std::string& msg)
        : std::out_of_range("HashMap Error: " + msg) {}
};

// malloc came back null. inherits bad_alloc but we override what()
// so we can say which container ran out of memory instead of just
// getting the generic "std::bad_alloc" message.
class OutOfMemoryException : public std::bad_alloc {
    std::string msg;
public:
    explicit OutOfMemoryException(const std::string& m)
        : msg("Out of Memory Error: " + m) {}
    const char* what() const noexcept override { return msg.c_str(); }
};