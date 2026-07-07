#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../HashMap/hmap.h"
#include "../Exceptions/exception.h"

using namespace std;

class RedisLite {
public:
    void run();

private:
    HashMap<string, string> storage;

    void printCommands();
    void handleSet(stringstream& in);
    void handleGet(stringstream& in);
    void handleDel(stringstream& in);
    void handleExists(stringstream& in);
    void handleCount();
    void handlePrint();
    void handleStats();
    void handleClear();
};

// ---------------------------------------------------------
// run() — read, parse, dispatch. No HashMap calls live here.
// the try/catch below is the only place in the whole app that
// actually catches exceptions — everything under it just throws
// and lets it bubble up. one bad command shouldn't kill the CLI.
// ---------------------------------------------------------
void RedisLite::run() {
    string line;
    cout << "===== Welcome to Redis Lite CLI =====" << endl;
    printCommands();

    while (true) {
        cout << "-> ";
        if (!getline(cin, line)) break;   // EOF (e.g. Ctrl+D)
        if (line.empty()) continue;

        stringstream in(line);
        string command;
        in >> command;

        try {
            if (command == "SET")          handleSet(in);
            else if (command == "GET")     handleGet(in);
            else if (command == "DEL")     handleDel(in);
            else if (command == "EXISTS")  handleExists(in);
            else if (command == "COUNT")   handleCount();
            else if (command == "PRINT")   handlePrint();
            else if (command == "STATS")   handleStats();
            else if (command == "CLEAR")   handleClear();
            else if (command == "HELP")    printCommands();
            else if (command == "EXIT")    break;
            else cout << "Unknown command. Type HELP for the command list." << endl;
        }
        catch (const KeyNotFoundException& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const DynamicArrayException& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const LinkedListException& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const EmptyListException& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const OutOfMemoryException& e) {
            cout << "Error: " << e.what() << endl;
        }
        catch (const invalid_argument& e) {
            // bad usage, e.g. SET with no key/value
            cout << "Error: " << e.what() << endl;
        }
        catch (const exception& e) {
            // catch-all so nothing we forgot about takes the CLI down
            cout << "Unexpected error: " << e.what() << endl;
        }
    }
}

void RedisLite::printCommands() {
    cout << "Commands -" << endl;
    cout << "  SET <key> <value>" << endl;
    cout << "  GET <key>" << endl;
    cout << "  DEL <key>" << endl;
    cout << "  EXISTS <key>" << endl;
    cout << "  COUNT" << endl;
    cout << "  PRINT" << endl;
    cout << "  STATS" << endl;
    cout << "  CLEAR" << endl;
    cout << "  HELP" << endl;
    cout << "  EXIT" << endl << endl;
}

// ---------------------------------------------------------
// SET <key> <value>
// ---------------------------------------------------------
void RedisLite::handleSet(stringstream& in) {
    string key, value;
    in >> key;
    getline(in, value);                        // grabs the rest of the line
    if (!value.empty() && value[0] == ' ')     // strip the leading space
        value.erase(0, 1);

    if (key.empty() || value.empty())
        throw invalid_argument("Usage: SET <key> <value>");

    storage.set(key, value);   // overwrite-on-duplicate handled inside set()
    cout << "OK" << endl;
}

// ---------------------------------------------------------
// GET <key>
// exists() check first so we don't even need the exception in
// the normal case — get() only throws on a key that's actually
// missing, which shouldn't happen after the check, but wrapping
// it anyway means we never print a raw exception to the user.
// ---------------------------------------------------------
void RedisLite::handleGet(stringstream& in) {
    string key;
    in >> key;

    if (key.empty())
        throw invalid_argument("Usage: GET <key>");

    try {
        if (storage.exists(key))
            cout << storage.get(key) << endl;
        else
            cout << "Not Found" << endl;
    } catch (const KeyNotFoundException&) {
        cout << "Not Found" << endl;
    }
}

// ---------------------------------------------------------
// DEL <key>
// same exists()-first + catch pattern as handleGet()
// ---------------------------------------------------------
void RedisLite::handleDel(stringstream& in) {
    string key;
    in >> key;

    if (key.empty())
        throw invalid_argument("Usage: DEL <key>");

    try {
        if (storage.exists(key)) {
            storage.remove(key);
            cout << "Deleted" << endl;
        } else {
            cout << "Not Found" << endl;
        }
    } catch (const KeyNotFoundException&) {
        cout << "Not Found" << endl;
    }
}

// ---------------------------------------------------------
// EXISTS <key>
// ---------------------------------------------------------
void RedisLite::handleExists(stringstream& in) {
    string key;
    in >> key;

    if (key.empty())
        throw invalid_argument("Usage: EXISTS <key>");

    cout << (storage.exists(key) ? "True" : "False") << endl;
}

// ---------------------------------------------------------
// COUNT
// ---------------------------------------------------------
void RedisLite::handleCount() {
    cout << storage.size() << endl;
}

// ---------------------------------------------------------
// PRINT
// ---------------------------------------------------------
void RedisLite::handlePrint() {
    storage.print();
}

// ---------------------------------------------------------
// STATS
// bucketCount is a public field on HashMap, not a function —
// accessed directly, no parentheses.
// ---------------------------------------------------------
void RedisLite::handleStats() {
    cout << "Elements   : " << storage.size() << endl;
    cout << "Buckets    : " << storage.bucketCount << endl;
    cout << "LoadFactor : " << storage.loadFactor() << endl;
}

// ---------------------------------------------------------
// CLEAR
// Calls the HashMap's own clear() directly — resets the
// bucket array and count without hashing/removing each key
// individually.
// ---------------------------------------------------------
void RedisLite::handleClear() {
    storage.clear();
    cout << "Cleared" << endl;
}