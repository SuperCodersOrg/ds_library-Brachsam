Date: June 23

Duration:
2 Hours 30 minutes (2:00 p.m.- 4:30 p.m.)

Goal:
Implement DynamicArray using STL-style memory management with malloc(), placement new, manual destructor calls, and free().

Problem Encountered:
- While implementing allocator-style storage, I found it difficult to understand when an object actually exists in memory and when memory is only raw storage. I initially thought allocated memory could be used immediately, but later realized objects must be constructed before they can be used.

- Also instead of resizing array when full, it resizes on every append. Instead of 4->8 it goes directly to 4->64. Also after removing 3 times the array does not shrink. The element was removed but the capacity remained the same.
![alt text](image.png)

What I Tried:
Implemented:
* To debug the resizing issue, I added print statements to track the values of size (n) and capacity after each append operation. This helped identify that the resize condition was incorrect and causing the array to resize repeatedly instead of only when full.
* To debug the remove() issue, I traced the value of n after each removal and compared the logical size of the array with the printed output. This revealed that objects were being destroyed correctly, but the size counter was not being updated, causing removed elements to still appear in the output. 
* Raw memory allocation using malloc()
* Placement new for object construction
* Manual destructor calls
* free() for memory deallocation

Implemented and tested:

* Constructor
* Destructor
* append()
* insert()
* remove()
* get()
* size()
* capacity()
* Copy Constructor
* Copy Assignment Operator

Used print statements and small test cases to trace object creation, destruction, and resizing behavior.

Outcome:
Successfully completed a working allocator-style DynamicArray implementation.

Verified that:

* Capacity doubles correctly when full.
* Elements are copy-constructed during resize.
* Old objects are destroyed before freeing memory.
* Deep copy works correctly.
* Copy Constructor creates independent arrays.
* Assignment Operator works correctly.
* Invalid indexes trigger error messages and terminate the program.
* Modifying a copied array does not affect the original array.

The DynamicArray now uses malloc() instead of new[] and delete[].