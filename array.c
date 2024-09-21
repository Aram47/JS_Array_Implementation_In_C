#include "./array.h"

// typedef struct {
//     int val;
//     Node* next;
//     Node* prev;
// } Node;

// typedef struct {
//     Node* head;
//     Node* tail;
// } Array;

// Constructor function
void __construct(Array* const this) {
    this->head = NULL;
    this->tail = NULL;
}
// Destructor function
void __destruct(Array* const this) {
    while (this->head) {
        Node* temp = this->head->next;
        free(this->head);
        this->head = temp;
    }
    this->tail = NULL;
}
// Adds an element to the end of the array
void __push(Array* const this, unsigned n, ...) {
    if (!this->head && n) {
        this->head = (Node*)malloc(sizeof(Node));
        this->tail = this->head;
    }

    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; ++i) {
        this->tail->val = va_arg(args, int);
        this->tail->next = (Node*)malloc(sizeof(Node));
        this->tail->next->prev = this->tail;
        this->tail = this->tail->next;
        this->tail->next = NULL;
    }
    va_end(args);

}
// Removes the last element from the array
int __pop(Array* const this) {
    if (this->tail) {
        int val = this->tail->val;
        if (!this->tail->prev) {
            free(this->tail);
            this->tail = NULL;
            this->head = NULL;
            return val;
        }
        this->tail = this->tail->prev;
        free(this->tail->next);
        this->tail->next = NULL;
        return val;
    }
    return 0;
}
// Removes the first element from the array
int __shift(Array* const this) {
    if (!this->head) {
        return 0;
    }
    if (!this->head->next) {
        int val = this->head->val;
        free(this->head);
        this->head = NULL;
        this->tail = NULL;
        return val;
    }
    int val = this->head->val;
    this->head = this->head->next;
    free(this->head->prev);
    this->head->prev = NULL;
    return val;
}
// Adds one or more elements to the array
void __unshift(Array* const this, unsigned n, ...) {
    if (!n) {
        return;
    }
    Node* tempHead = (Node*)malloc(sizeof(Node));
    tempHead->next = NULL;
    tempHead->prev = NULL;
    Node* tempTail = tempHead;

    va_list args;
    va_start(args, n);
    for (int i = 0; i < n; ++i) {
        tempTail->val = va_arg(args, int);
        tempTail->next = (Node*)malloc(sizeof(Node));
        tempTail->next->prev = tempTail;
        tempTail->next->next = NULL;
        tempTail = tempTail->next;
    }
    va_end(args);
    tempTail->next = this->head;
    this->head = tempHead;
}
// Merges two or more arrays
void __concat(Array* const this, Array* const other) {
    if (!other->head) {
        return;
    }
    if (!this->head) {
        this->head = (Node*)malloc(sizeof(Node));
        this->tail = this->head;
        this->head->next = NULL;
        this->head->prev = NULL;
    }
    Node* otherIterator = other->head;
    while (otherIterator) {
        this->tail->val = otherIterator->val;
        this->tail->next = (Node*)malloc(sizeof(Node));
        this->tail->next->prev = this->tail;
        this->tail->next->next = NULL;
        this->tail = this->tail->next;
        otherIterator = otherIterator->next;
    } 
}
// Returns a shallow copy of a portion of array
void __slice(Array* const this, ...) {
    
}
// Changes the contents of an array by removing or adding elements
void __splice(Array* const, ...);
// Returns the first index of a value in the array, or -1 if not found
int __indexOf(Array* const, int);
// Checks if an array contains a specific element
bool __includes(Array* const, int);
// Reverses the order of elements in an array
void __reverce(Array* const);
// Joins all elements of an array into a string
char* __join(Array* const);
// Sorts the elements of an array
void __sort(Array* const);
// Executes a provided function once for each array element
void __forEach(Array* const, void(*cb)(int));
// Creates a new array populated with the results of calling a
// function on every element
Array __map(Array* const, void(*cb)(int));
// Creates a new array with elements that pass a test
Array __filter(Array* const, void(*cb)(int));
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
// Flattnes nested arrays into a single array
Array __flat(Array* const);
// Fills all the elements in an array with a static value
void __fill(Array* const, int);