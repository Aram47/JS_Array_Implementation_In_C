#ifndef __Array
#define __Array

#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct Node {
    int val;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    unsigned length;
} Array;

// Constructor function
void __construct(Array* const);
// Destructor function
void __destruct(Array* const);
// Reverse string
void __reverse_str(char*, int);
// Itoa (integer to ASCII)
char* __itoa(int, char*, int);
// Pivot geter
unsigned __get_pivot(Node*, unsigned);
// QuickSort function
void __quickSort(Node*, unsigned, unsigned);
// Adds an element to the end of the array
void __push(Array* const, unsigned, ...);
// Removes the last element from the array
int __pop(Array* const);
// Removes the first element from the array
int __shift(Array* const);
// Adds one or more elements to the array
void __unshift(Array* const, unsigned, ...);
// Merges two or more arrays
void __concat(Array* const, Array* const);
// Returns a shallow copy of a portion of array
Array __slice(Array* const, unsigned, unsigned);
// Changes the contents of an array by removing or adding elements
void __splice(Array* const,  unsigned, unsigned, ...);
// Returns the first index of a value in the array, or -1 if not found
int __indexOf(Array* const, int);
// Checks if an array contains a specific element
bool __includes(Array* const, int);
// Reverses the order of elements in an array
void __reverse(Array* const);
// Joins all elements of an array into a string
char* __join(Array* const, const char* const);
// Sorts the elements of an array
void __sort(Array* const);
// Executes a provided function once for each array element
void __forEach(Array* const, void(*cb)(int));
// Creates a new array populated with the results of calling a
// function on every element
Array __map(Array* const, void(*cb)(int*));
// Creates a new array with elements that pass a test
Array __filter(Array* const, bool(*cb)(int));
// Reduces the array to a single value by applying a function
// to each element
Array __reduce(Array* const, void(*cb)(int));
// Returns the first element that passes a test
int __find(Array* const, void(*cb)(int));
// Returns the index of the first element that passes o test
int __findIndex(Array* const, void(*cb)(int));
// Tests if at least one element in the array passes the test
bool __some(Array* const, void(*cb)(int));
// Tests if all elements in the array pases the test
bool __every(Array* const, void(*cb)(int));
// Fills all the elements in an array with a static value
void __fill(Array* const, int);

#endif // __Array