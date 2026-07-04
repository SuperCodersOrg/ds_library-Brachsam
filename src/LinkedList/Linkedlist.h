#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include "../Exceptions/exception.h"
using namespace std;

// base class — just the contract, no implementation
// every derived class must implement all of these
template<typename T>
class LinkedList {
public:
    // pure virtual functions, these force every derived class to implement them
    virtual void insertFront(const T& val)       = 0;
    virtual void insertBack(const T& val)        = 0;
    virtual void deleteFront()                   = 0;
    virtual void deleteBack()                    = 0;
    virtual void insert(int index, const T& val) = 0;
    virtual void remove(int index)               = 0;
    virtual bool search(const T& val)    const   = 0;
    virtual T    get(int index)          const   = 0;
    virtual int  size()                  const   = 0;
    virtual void print()                 const   = 0;

    // without this, deleting via base pointer won't call derived destructor
    virtual ~LinkedList() {}
};


// one pointer per node — less memory, but deleteBack is O(N)
template<typename T>
class SinglyLinkedList : public LinkedList<T> {

public:
    struct Node {
        T     data;
        Node* next;
    };

private:
    Node* head;
    Node* tail;
    int   count;

    Node* makeNode(const T& val) {
        Node* node = (Node*) malloc(sizeof(Node));
        if (!node) throw OutOfMemoryException("could not allocate a node");
        new (&node->data) T(val);
        node->next = nullptr;
        return node;
    }

    void freeNode(Node* node) {
        node->data.~T();
        free(node);
    }

    // walks to the node just before index
    // used by insert and remove to avoid repeating the same loop
    Node* nodeBefore(int index) const {
        Node* cur = head;
        for (int i = 0; i < index - 1; i++)
            cur = cur->next;
        return cur;
    }

public:

    SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~SinglyLinkedList() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;   // save next before freeing
            freeNode(cur);
            cur = next;
        }
    }

    SinglyLinkedList(const SinglyLinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        Node* cur = other.head;
        while (cur != nullptr) {
            insertBack(cur->data);
            cur = cur->next;
        }
    }

    SinglyLinkedList& operator=(const SinglyLinkedList& other) {
        if (this == &other) return *this;
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            freeNode(cur);
            cur = next;
        }
        head = nullptr; tail = nullptr; count = 0;
        cur = other.head;
        while (cur != nullptr) {
            insertBack(cur->data);
            cur = cur->next;
        }
        return *this;
    }

    int   size()    const override { return count; }
    Node* getHead() const           { return head;  }

    void insertFront(const T& val) override {
        Node* node = makeNode(val);
        node->next = head;
        head       = node;
        if (count == 0) tail = node;
        count++;
    }

    // O(1) only because we keep a tail pointer
    void insertBack(const T& val) override {
        Node* node = makeNode(val);
        if (count == 0) { head = node; tail = node; }
        else            { tail->next = node; tail = node; }
        count++;
    }

    // save the link before rewiring — do it the other way and the rest is lost
    void insert(int index, const T& val) override {
        if (index < 0 || index > count) throw LinkedListException("insert: index " + to_string(index) + " out of range, size is " + to_string(count));
        if (index == 0)     { insertFront(val); return; }
        if (index == count) { insertBack(val);  return; }
        Node* prev = nodeBefore(index);
        Node* node = makeNode(val);
        node->next = prev->next;
        prev->next = node;
        count++;
    }

    void deleteFront() override {
        if (count == 0) throw EmptyListException("deleteFront: list is empty");
        Node* toFree = head;
        head         = head->next;
        freeNode(toFree);
        if (count == 1) tail = nullptr;
        count--;
    }

    // no prev pointer so we walk from head — this is the O(N) cost of singly
    void deleteBack() override {
        if (count == 0) throw EmptyListException("deleteBack: list is empty");
        if (count == 1) {
            freeNode(head);
            head = nullptr; tail = nullptr;
            count--; return;
        }
        Node* cur = head;
        while (cur->next != tail)
            cur = cur->next;
        freeNode(tail);
        tail       = cur;
        tail->next = nullptr;
        count--;
    }

    void remove(int index) override {
        if (index < 0 || index >= count) throw LinkedListException("remove: index " + to_string(index) + " out of range, size is " + to_string(count));
        if (index == 0)         { deleteFront(); return; }
        if (index == count - 1) { deleteBack();  return; }
        Node* prev   = nodeBefore(index);
        Node* toFree = prev->next;
        prev->next   = toFree->next;
        freeNode(toFree);
        count--;
    }

    bool search(const T& val) const override {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == val) return true;
            cur = cur->next;
        }
        return false;
    }

    // no random access — must walk from head every time
    T get(int index) const override {
        if (index < 0 || index >= count) throw LinkedListException("get: index " + to_string(index) + " out of range, size is " + to_string(count));
        Node* cur = head;
        for (int i = 0; i < index; i++)
            cur = cur->next;
        return cur->data;
    }

    // used by HashMap to remove a specific key from a chain
    bool removeVal(const T& val) {
        Node* cur = head;
        Node* prev = nullptr;
        while (cur != nullptr) {
            if (cur->data == val) {
                if (prev) prev->next = cur->next;
                else      head       = cur->next;
                if (cur == tail) tail = prev;
                freeNode(cur);
                count--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    void clear() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            freeNode(cur);
            cur = next;
        }
        head = nullptr; tail = nullptr; count = 0;
    }

    void print() const override {
        Node* cur = head;
        cout << "[ ";
        while (cur != nullptr) {
            cout << cur->data;
            if (cur->next != nullptr) cout << " -> ";
            cur = cur->next;
        }
        cout << " ]  size=" << count << "  singly\n";
    }
};


// two pointers per node — more memory, but deleteBack is O(1)
template<typename T>
class DoublyLinkedList : public LinkedList<T> {

public:
    struct Node {
        T     data;
        Node* next;
        Node* prev;
    };

private:
    Node* head;
    Node* tail;
    int   count;

    Node* makeNode(const T& val) {
        Node* node = (Node*) malloc(sizeof(Node));
        if (!node) throw OutOfMemoryException("could not allocate a node");
        new (&node->data) T(val);
        node->next = nullptr;
        node->prev = nullptr;
        return node;
    }

    void freeNode(Node* node) {
        node->data.~T();
        free(node);
    }

    Node* nodeBefore(int index) const {
        Node* cur = head;
        for (int i = 0; i < index - 1; i++)
            cur = cur->next;
        return cur;
    }

public:

    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoublyLinkedList() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            freeNode(cur);
            cur = next;
        }
    }

    DoublyLinkedList(const DoublyLinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        Node* cur = other.head;
        while (cur != nullptr) {
            insertBack(cur->data);
            cur = cur->next;
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList& other) {
        if (this == &other) return *this;
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            freeNode(cur);
            cur = next;
        }
        head = nullptr; tail = nullptr; count = 0;
        cur = other.head;
        while (cur != nullptr) {
            insertBack(cur->data);
            cur = cur->next;
        }
        return *this;
    }

    int   size()    const override { return count; }
    Node* getHead() const           { return head;  }

    void insertFront(const T& val) override {
        Node* node = makeNode(val);
        node->next = head;
        if (head != nullptr) head->prev = node;
        head = node;
        if (count == 0) tail = node;
        count++;
    }

    void insertBack(const T& val) override {
        Node* node = makeNode(val);
        if (count == 0) { head = node; tail = node; }
        else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        count++;
    }

    void insert(int index, const T& val) override {
        if (index < 0 || index > count) throw LinkedListException("insert: index " + to_string(index) + " out of range, size is " + to_string(count));
        if (index == 0)     { insertFront(val); return; }
        if (index == count) { insertBack(val);  return; }
        Node* prev = nodeBefore(index);
        Node* next = prev->next;
        Node* node = makeNode(val);
        node->next = next;
        node->prev = prev;
        prev->next = node;
        if (next != nullptr) next->prev = node;
        count++;
    }

    void deleteFront() override {
        if (count == 0) throw EmptyListException("deleteFront: list is empty");
        Node* toFree = head;
        head         = head->next;
        if (head != nullptr) head->prev = nullptr;
        freeNode(toFree);
        if (count == 1) tail = nullptr;
        count--;
    }

    // O(1) — just jump to tail->prev, no walking needed
    // this is exactly why doubly linked exists
    void deleteBack() override {
        if (count == 0) throw EmptyListException("deleteBack: list is empty");
        if (count == 1) {
            freeNode(head);
            head = nullptr; tail = nullptr;
            count--; return;
        }
        Node* toFree = tail;
        tail         = tail->prev;
        tail->next   = nullptr;
        freeNode(toFree);
        count--;
    }

    void remove(int index) override {
        if (index < 0 || index >= count) throw LinkedListException("remove: index " + to_string(index) + " out of range, size is " + to_string(count));
        if (index == 0)         { deleteFront(); return; }
        if (index == count - 1) { deleteBack();  return; }
        Node* prev   = nodeBefore(index);
        Node* toFree = prev->next;
        Node* next   = toFree->next;
        prev->next = next;
        if (next != nullptr) next->prev = prev;
        freeNode(toFree);
        count--;
    }

    bool search(const T& val) const override {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == val) return true;
            cur = cur->next;
        }
        return false;
    }

    T get(int index) const override {
        if (index < 0 || index >= count) throw LinkedListException("get: index " + to_string(index) + " out of range, size is " + to_string(count));
        Node* cur = head;
        for (int i = 0; i < index; i++)
            cur = cur->next;
        return cur->data;
    }

    bool removeVal(const T& val) {
        Node* cur = head;
        while (cur != nullptr) {
            if (cur->data == val) {
                if (cur->prev) cur->prev->next = cur->next;
                else           head            = cur->next;
                if (cur->next) cur->next->prev = cur->prev;
                else           tail            = cur->prev;
                freeNode(cur);
                count--;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    void clear() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* next = cur->next;
            freeNode(cur);
            cur = next;
        }
        head = nullptr; tail = nullptr; count = 0;
    }

    void print() const override {
        Node* cur = head;
        cout << "[ ";
        while (cur != nullptr) {
            cout << cur->data;
            if (cur->next != nullptr) cout << " -> ";
            cur = cur->next;
        }
        cout << " ]  size=" << count << "  doubly\n";
    }
};