#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../DynamicArray/Dynamicarray.h"
#include "../LinkedList/Linkedlist.h"
#include "../Exceptions/exception.h"
using namespace std;

// Hash — compiler picks the right specialization based on K
// for user-defined types: write your own specialization (see Point below)
template<typename K>
struct Hash {
    int operator()(const K& key, int buckets) const;
};

template<>
struct Hash<int> {
    int operator()(const int& key, int buckets) const {
        unsigned bits = (unsigned) key;
        bits = bits * 2654435761u;
        return (int)(bits % (unsigned) buckets);
    }
};

template<>
struct Hash<char> {
    int operator()(const char& key, int buckets) const {
        return Hash<int>()((int)(unsigned char) key, buckets);
    }
};

template<>
struct Hash<float> {
    int operator()(const float& key, int buckets) const {
        unsigned bits;
        memcpy(&bits, &key, sizeof(float));
        return (int)(bits % (unsigned) buckets);
    }
};

template<>
struct Hash<double> {
    int operator()(const double& key, int buckets) const {
        unsigned long long bits;
        memcpy(&bits, &key, sizeof(double));
        bits ^= bits >> 33;
        bits *= 0xff51afd7ed558ccdULL; //produces good mixing of bits, chosen by the designers of the MurmurHash3 algorithm
        bits ^= bits >> 33;
        return (int)(bits % (unsigned long long) buckets);
    }
};

template<>
struct Hash<string> {
    int operator()(const string& key, int buckets) const {
        unsigned long h = 5381; //DJB2 algorithm (multiplies by 33 and adds the ASCII value)
        for (char c : key)
            h = ((h << 5) + h) + (unsigned char) c;
        return (int)(h % (unsigned long) buckets);
    }
};

template<>
struct Hash<const char*> {
    int operator()(const char* const& key, int buckets) const {
        unsigned long h = 5381;
        const char* p = key;
        while (*p) h = ((h << 5) + h) + (unsigned char)(*p++);
        return (int)(h % (unsigned long) buckets);
    }
};

// Pair<K,V> — one key-value entry stored inside a bucket chain
template<typename K, typename V>
struct Pair {
    K key;
    V val;
    Pair() {}
    Pair(const K& k, const V& v) : key(k), val(v) {}
    bool operator==(const Pair& other) const { return key == other.key; }
};


template<typename K, typename V>
ostream& operator<<(ostream& os, const Pair<K,V>& p) {
    return os << p.key << ":" << p.val;
}

// HashMap<K, V>
template<typename K, typename V>
class HashMap {

public:
    int bucketCount;

private:
    DynamicArray< SinglyLinkedList< Pair<K,V> > > buckets;
    int count;
    Hash<K> hasher;

    static const int PROBE_LIMIT = 3;

    int homeIndex(const K& key) const {
        return hasher(key, bucketCount);
    }

    void rehash(int newCount) {
        DynamicArray< SinglyLinkedList< Pair<K,V> > > newBuckets;
        for (int i = 0; i < newCount; i++)
            newBuckets.append(SinglyLinkedList< Pair<K,V> >());

        for (int i = 0; i < bucketCount; i++) {
            typename SinglyLinkedList< Pair<K,V> >::Node* cur = buckets.get(i).getHead();
            while (cur) {
                int home = hasher(cur->data.key, newCount);
                bool placed = false;
                for (int p = 0; p < PROBE_LIMIT; p++) {
                    int idx = (home + p) % newCount;
                    if (newBuckets.get(idx).size() == 0) {
                        newBuckets.get(idx).insertBack(cur->data);
                        placed = true;
                        break;
                    }
                }
                if (!placed) newBuckets.get(home).insertBack(cur->data);
                cur = cur->next;
            }
        }
        buckets = newBuckets;
        bucketCount = newCount;
    }

public:

    HashMap() : bucketCount(8), count(0) {
        for (int i = 0; i < bucketCount; i++)
            buckets.append(SinglyLinkedList< Pair<K,V> >());
    }

    ~HashMap() {}

    int   size() const { return count; }
    float loadFactor() const { return (float) count / (float) bucketCount; }

    void set(const K& key, const V& val) {
        if ((count + 1.0f) / bucketCount >= 0.7f)
            rehash(bucketCount * 2);

        int home = homeIndex(key);

        // update if key already exists, search all probe slots for the key
        // bounded linear probing
        for (int p = 0; p < PROBE_LIMIT; p++) {
            int idx = (home + p) % bucketCount;
            typename SinglyLinkedList< Pair<K,V> >::Node* cur = buckets.get(idx).getHead();
            while (cur) {
                if (cur->data.key == key) { cur->data.val = val; return; }
                cur = cur->next;
            }
        }

        // insert into first empty probe slot
        for (int p = 0; p < PROBE_LIMIT; p++) {
            int idx = (home + p) % bucketCount;
            if (buckets.get(idx).size() == 0) {
                buckets.get(idx).insertBack(Pair<K,V>(key, val));
                count++;
                return;
            }
        }

        // all probe slots full — chain at home bucket
        buckets.get(home).insertBack(Pair<K,V>(key, val));
        count++;
    }

    V& get(const K& key) const {
        int home = homeIndex(key);
        for (int p = 0; p < PROBE_LIMIT; p++) {
            int idx = (home + p) % bucketCount;
            typename SinglyLinkedList< Pair<K,V> >::Node* cur = buckets.get(idx).getHead();
            while (cur) {
                if (cur->data.key == key) return cur->data.val;
                cur = cur->next;
            }
        }
        throw KeyNotFoundException("get: key not found");
    }

    bool exists(const K& key) const {
        int home = homeIndex(key);
        for (int p = 0; p < PROBE_LIMIT; p++) {
            int idx = (home + p) % bucketCount;
            typename SinglyLinkedList< Pair<K,V> >::Node* cur = buckets.get(idx).getHead();
            while (cur) {
                if (cur->data.key == key) return true;
                cur = cur->next;
            }
        }
        return false;
    }

    void remove(const K& key) {
        int home = homeIndex(key);
        for (int p = 0; p < PROBE_LIMIT; p++) {
            int idx = (home + p) % bucketCount;
            typename SinglyLinkedList< Pair<K,V> >::Node* cur = buckets.get(idx).getHead();
            while (cur) {
                if (cur->data.key == key) {
                    buckets.get(idx).removeVal(cur->data);
                    count--;
                    return;
                }
                cur = cur->next;
            }
        }
        throw KeyNotFoundException("remove: key not found");
    }

    void clear() {
        buckets = DynamicArray< SinglyLinkedList< Pair<K,V> > >();
        bucketCount = 8;
        for (int i = 0; i < bucketCount; i++)
            buckets.append(SinglyLinkedList< Pair<K,V> >());
        count = 0;
    }

    DynamicArray<K> keys() const {
        DynamicArray<K> result;
        for (int i = 0; i < bucketCount; i++) {
            typename SinglyLinkedList< Pair<K,V> >::Node* cur = buckets.get(i).getHead();
            while (cur) { result.append(cur->data.key); cur = cur->next; }
        }
        return result;
    }

    DynamicArray<V> values() const {
        DynamicArray<V> result;
        for (int i = 0; i < bucketCount; i++) {
            typename SinglyLinkedList< Pair<K,V> >::Node* cur = buckets.get(i).getHead();
            while (cur) { result.append(cur->data.val); cur = cur->next; }
        }
        return result;
    }

    void merge(const HashMap<K,V>& other) {
        DynamicArray<K> otherKeys = other.keys();
        for (int i = 0; i < otherKeys.size(); i++) {
            const K& key = otherKeys.get(i);
            if (!exists(key))
                set(key, other.get(key));
        }
    }

    void print() const {
        cout << "HashMap  size=" << count << "  buckets=" << bucketCount
             << "  load=" << loadFactor() << "\n";
        for (int i = 0; i < bucketCount; i++) {
            if (buckets.get(i).size() == 0) continue;
            cout << "  [" << i << "] ";
            typename SinglyLinkedList< Pair<K,V> >::Node* cur = buckets.get(i).getHead();
            while (cur) {
                cout << "{" << cur->data.key << " : " << cur->data.val << "}";
                if (cur->next) cout << " -> ";
                cur = cur->next;
            }
            cout << "\n";
        }
    }
};

// ─────────────────────────────────────────────────────────────────────────────
// user-defined type example
// ─────────────────────────────────────────────────────────────────────────────
struct Point {
    int x, y;
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    friend ostream& operator<<(ostream& os, const Point& p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};

template<>
struct Hash<Point> {
    int operator()(const Point& p, int buckets) const {
        unsigned h = (unsigned)(p.x * 73856093 ^ p.y * 19349663);
        return (int)(h % (unsigned) buckets);
    }
};