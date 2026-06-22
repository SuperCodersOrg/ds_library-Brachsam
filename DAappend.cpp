#include <iostream>
using namespace std;

template<typename T>
class DynamicArray {
private:
    T* arr;
    int n;
    int capacity;

    void resize(int newCapacity) {
        T* temp = new T[newCapacity];

        for (int i = 0; i < n; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;

        arr = temp;
        capacity = newCapacity;
    }

public:
    // Constructor to initialize the dynamic array
    DynamicArray() {
        n = 0;
        capacity = 4;
        arr = new T[capacity];
    }

    // Destructor to free the allocated memory
    ~DynamicArray() {
        delete[] arr;
    }

    // Add element at end of the array
    void append(T value) {
        if (n == capacity) {
            resize(capacity * 2);
        }

        arr[n] = value;
        n++;
    }

    // Remove a specific value from the array
    void removeValue(T value) {
        int indexToRemove = -1;

        // Search for the value in the array
        for (int i = 0; i < n; i++) {
            if (arr[i] == value) {
                indexToRemove = i;
                break; // Stop at the first occurrence
            }
        }

        // If the value wasn't found
        if (indexToRemove == -1) {
            cout << "Error: Value " << value << " not found in the array." << endl;
            return;
        }

        // Shift elements to the left to fill the gap
        for (int i = indexToRemove; i < n - 1; i++) {
            arr[i] = arr[i + 1];
        }

        n--; // Reduce size
        cout << "Successfully removed " << value << endl;
    }

    // Display array
    void print() const {
        if (n == 0) {
            cout << "[ ] (Array is empty)" << endl;
            return;
        }

        cout << "[ ";
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << "]" << endl;
        cout << "Size = " << n << ", Capacity = " << capacity << endl;
    }
};

int main() {
    DynamicArray<int> arr;
    int choice;
    int element;

    do {
        cout << "\n--- Dynamic Array Menu ---" << endl;
        cout << "1. Append Element" << endl;
        cout << "2. Remove Element by Value" << endl;
        cout << "3. Display Array" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice between 1-4: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter integer value to append: ";
                cin >> element;
                arr.append(element);
                cout << element << " appended successfully." << endl;
                break;

            case 2:
                cout << "Enter integer value to remove: ";
                cin >> element;
                arr.removeValue(element);
                break;

            case 3:
                cout << "\nCurrent Array Status:" << endl;
                arr.print();
                break;

            case 4:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice! Please select an option between 1 and 4." << endl;
        }
    } while (choice != 4);

    return 0;
}