#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include "../Exceptions/exception.h"
using namespace std;

template<typename T>
class DynamicArray {

private:
    T*  data;
    int count;
    int cap;

    // asks malloc for a raw block big enough to hold cap T's
    // no constructors run here — just bytes
    T* allocate(int cap) {
        T* block = (T*) malloc(cap * sizeof(T));
        if (!block) throw OutOfMemoryException("could not allocate memory");
        return block;
    }

    // builds a T object at this address using placement new, memory is raw before calling this
    void construct(T* ptr, const T& val) {
        new (ptr) T(val);
    }

    // calls T's destructor manually, doesn't free memory, just cleans up the object
    void destroy(T* ptr) {
        ptr->~T();
    }

    // double the capacity
    // copy all live objects into new block, destroy old ones, free old block
    void resize(int newCap) {
        T* newData = allocate(newCap);
        for (int i = 0; i < count; i++) {
            construct(newData + i, data[i]);
            destroy(data + i);
        }
        free(data);
        data = newData;
        cap  = newCap;
    }

public:

    // start with 4 raw slots, nothing live yet
    DynamicArray() : count(0), cap(4) {
        data = allocate(cap);
    }

    // destroy all live objects first, then free the block
    ~DynamicArray() {
        for (int i = 0; i < count; i++)
            destroy(data + i);
        free(data);
    }

    // fresh block, copy each element in properly
    DynamicArray(const DynamicArray& other) : count(other.count), cap(other.cap) {
        data = allocate(cap);
        for (int i = 0; i < count; i++)
            construct(data + i, other.data[i]);
    }

    // clean up what we have, then copy from other
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        for (int i = 0; i < count; i++)
            destroy(data + i);
        free(data);
        count = other.count;
        cap   = other.cap;
        data  = allocate(cap);
        for (int i = 0; i < count; i++)
            construct(data + i, other.data[i]);
        return *this;
    }

    int size()     const { return count; }
    int capacity() const { return cap;   }

    // if full, double first then construct the new value at data[count], which is raw storage
    void append(const T& val) {
        if (count == cap)
            resize(cap * 2);
        construct(data + count, val);
        count++;
    }

    // first create an extra slot at the end
    // shift elements right to open a gap
    // drop the new value into that gap
    void insert(int index, const T& val) {
        if (index < 0 || index > count)
            throw DynamicArrayException("insert: index " + to_string(index) + " out of range, size is " + to_string(count));
        if (count == cap)
            resize(cap * 2);
        construct(data + count, data[count - 1]);
        for (int i = count - 1; i > index; i--)
            data[i] = data[i - 1];
        data[index] = val;
        count++;
    }

    // shift everything left using assignment
    // destroy the last slot, which is now a duplicate
    void remove(int index) {
        if (index < 0 || index >= count)
            throw DynamicArrayException("remove: index " + to_string(index) + " out of range, size is " + to_string(count));
        for (int i = index; i < count - 1; i++)
            data[i] = data[i + 1];
        destroy(data + (count - 1));
        count--;
    }

    T& get(int index) {
        if (index < 0 || index >= count)
            throw DynamicArrayException("get: index " + to_string(index) + " out of range, size is " + to_string(count));
        return data[index];
    }
    const T& get(int index) const {
        if (index < 0 || index >= count)
            throw DynamicArrayException("get: index " + to_string(index) + " out of range, size is " + to_string(count));
        return data[index];
    }

    void print() const {
        cout << "[ ";
        for (int i = 0; i < count; i++)
            cout << data[i] << " ";
        cout << "]  size=" << count << "  cap=" << cap << "\n";
    }
};