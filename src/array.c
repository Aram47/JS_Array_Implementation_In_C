#include <string.h>
#include "../header/array.h"

// Constructor function
void __construct(Array* const this) {
    if (!this) {
        return;
    }
    this->head = NULL;
    this->tail = NULL;
    this->length = 0;
}
// Destructor function
void __destruct(Array* const this) {
    if (!this) {
        return;
    }
    while (this->head) {
        Node* temp = this->head->next;
        free(this->head);
        this->head = temp;
    }
    this->tail = NULL;
}
// Reverse string
void __reverse_str(char* str, int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
// Itoa (integer to ASCII)
char* __itoa(int value, char* str, int base) {
    int i = 0;
    int isNegative = 0;
    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if (value < 0 && base == 10) {
        isNegative = 1;
        value = -value;
    }
    while (value != 0) {
        int remainder = value % base;
        str[i++] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
        value = value / base;
    }
    if (isNegative) {
        str[i++] = '-';
    }
    str[i] = '\0';
    __reverse_str(str, i);

    return str;
}
// Pivot geter
unsigned __get_pivot(int* arr, unsigned length) {
    unsigned i = 0, j = 0;

    while (i < length - 1) {
        if (arr[i] <= arr[length - 1]) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            ++i;
            ++j;
        } else {
            ++i;
        }
    }
    int temp = arr[j];
    arr[j] = arr[length - 1];
    arr[length - 1] = temp;

    return j;
}
// QuickSort function
void __quickSort(int* arr, unsigned start, unsigned end) {
    if (start >= end) {
        return;
    }
    unsigned pivot = __get_pivot(arr, end);
    __quickSort(arr, start, pivot);
    __quickSort(arr, pivot + 1, end);
}
// Adds an element to the end of the array
void __push(Array* const this, unsigned n, ...) {
    if (!this) {
        return;
    }
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
    this->length += n;
}
// Removes the last element from the array
int __pop(Array* const this) {
    if (!this) {
        return 0;
    }
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
    --(this->length);
    return 0;
}
// Removes the first element from the array
int __shift(Array* const this) {
    if ((!this) || (!this->head)) {
        return 0;
    }
    if (!this->head->next) {
        int val = this->head->val;
        free(this->head);
        this->head = NULL;
        this->tail = NULL;
        this->length = 0;
        return val;
    }
    int val = this->head->val;
    this->head = this->head->next;
    free(this->head->prev);
    this->head->prev = NULL;
    --(this->length);
    return val;
}
// Adds one or more elements to the array
void __unshift(Array* const this, unsigned n, ...) {
    if ((!n) || (!this)) {
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
    this->length += n;
}
// Merges two or more arrays
void __concat(Array* const this, Array* const other) {
    if ((!this) || (!other) || (!other->head)) {
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
    this->length += other->length;
}
// Returns a shallow copy of a portion of array
Array __slice(Array* const this, unsigned f, unsigned l) {
    if ((!this) || (f >= l) || (f > this->length) || (l > this->length)) {
        Array emptyArray;
        __construct(&emptyArray);
        return emptyArray;
    }
    unsigned index = 0;
    Node* tempHead = (Node*)malloc(sizeof(Node));
    Node* tempTail = tempHead;
    Node* tempThisHead = this->head;
    while (index < l) {
        if (index >= f) {
            tempTail->val = tempThisHead->val;
            tempTail->next = (Node*)malloc(sizeof(Node));
            tempTail->next->prev = tempTail;
            tempTail->next->next = NULL;
            tempTail = tempTail->next;
        }
        ++index;
        tempThisHead = tempThisHead->next;
    }
    Array result;
    result.length = l - f;
    result.head = tempHead;
    result.tail = tempTail;
    return result;
}
// Changes the contents of an array by removing or adding elements
void __splice(Array* const this,  unsigned i, unsigned n, ...) {

}
// Returns the first index of a value in the array, or -1 if not found
int __indexOf(Array* const this, int target) {
    if ((!this) || (!this->head)) {
        return -1;
    }
    Node* iterator = this->head;
    for (int i = 0; i < this->length; ++i) {
        if (iterator->val == target) {
            return i;
        }
        iterator = iterator->next;
    }
    return - 1;
}
// Checks if an array contains a specific element
bool __includes(Array* const this, int target) {
    return __indexOf(this, target) == -1 ? false : true;
}
// Reverses the order of elements in an array
void __reverse(Array* const this) {
    if ((!this) || (!this->head)) {
        return;
    }
    Node* tempHead = this->head;
    Node* tempTail = this->tail;
    for (unsigned i = 0; i < this->length / 2; ++i) {
        tempHead->val ^= tempTail->val;
        tempTail->val ^= tempHead->val;
        tempHead->val ^= tempTail->val;
        tempHead = tempHead->next;
        tempTail = tempTail->prev;
    }
}
// Joins all elements of an array into a string
char* __join(Array* const this, const char* const symb) {
    if ((!this) || (!this->head)) {
        return NULL;
    }
    char* res = (char*)malloc(sizeof(char));
    res[0] = '\0';
    Node* temp = this->head;
    for (unsigned i = 0; i < this->length; ++i) {
        char str[19];
        res = strcat(res, __itoa(temp->val, str, 10));
        res = strcat(res, symb);
        temp = temp->next;
    }
    return res;
}
// Sorts the elements of an array
void __sort(Array* const this) {
    if ((!this) || (!this->head)) {
        return;
    }
    Node* temp = this->head;
    int* arr = (int*)malloc(sizeof(int) * this->length);
    for (unsigned i = 0; i < this->length; ++i) {
        arr[i] = temp->val;
        temp = temp->next;
    }
    __quickSort(arr, 0, this->length);
    temp = this->head;
    for (unsigned i = 0; i < this->length; ++i) {
        temp->val = arr[i];
        temp = temp->next;
    }
    free(arr);
}
// Executes a provided function once for each array element
void __forEach(Array* const this, void(*cb)(int)) {
    if ((!this) || (!this->head)) {
        return;
    }
    Node* temp = this->head;
    while (temp) {
        cb(temp->val);
        temp = temp->next;
    }
}
// Creates a new array populated with the results of calling a
// function on every element
Array __map(Array* const this, void(*cb)(int*)) {
    if ((!this) || (!this->head)) {
        Array emptyArr;
        __construct(&emptyArr);
        return emptyArr;
    }
    Node* tempHead = (Node*)malloc(sizeof(Node));
    tempHead->prev = NULL;
    Node* tempTail = tempHead;
    Node* tempThisHead = this->head;
    for (unsigned i = 0; i < this->length; ++i) {
        tempTail->val = tempThisHead->val;
        tempTail->next = (Node*)malloc(sizeof(Node));
        tempTail->next->prev = tempTail;
        tempTail->next->next = NULL;
        tempTail = tempTail->next;
        tempThisHead = tempThisHead->next;
    }
    tempTail = tempHead;
    for (unsigned i = 0; i < this->length; ++i) {
        cb(&(tempTail->val));
        tempTail = tempTail->next;
    }
    Array res;
    __construct(&res);
    res.head = tempHead;
    res.tail = tempTail;
    res.length = this->length;
    return res;
}
// Creates a new array with elements that pass a test
Array __filter(Array* const this, bool(*cb)(int)){
    if ((!this) || (!this->head)) {
        Array emptyArr;
        __construct(&emptyArr);
        return emptyArr;
    }
    Node* tempHead = (Node*)malloc(sizeof(Node));
    tempHead->prev = NULL;
    Node* tempTail = tempHead;
    Node* tempThisHead = this->head;
    unsigned length = 0;
    for (unsigned i = 0; i < this->length; ++i) {
        if (cb(tempThisHead->val)) {
            tempTail->val = tempThisHead->val;
            tempTail->next = (Node*)malloc(sizeof(Node));
            tempTail->next->prev = tempTail;
            tempTail->next->next = NULL;
            tempTail = tempTail->next;
            ++length;
        }
        tempThisHead = tempThisHead->next;
    }
    Array res;
    __construct(&res);
    res.head = tempHead;
    res.tail = tempTail;
    res.length = length;
}
// Reduces the array to a single value by applying a function
// to each element
Array __reduce(Array* const this, void(*cb)(int)) {
    
}
// Returns the first element that passes a test
int __find(Array* const this, void(*cb)(int)) {

}
// Returns the index of the first element that passes o test
int __findIndex(Array* const this, void(*cb)(int)) {

}
// Tests if at least one element in the array passes the test
bool __some(Array* const this, void(*cb)(int)) {

}
// Tests if all elements in the array pases the test
bool __every(Array* const this, void(*cb)(int)) {

}
// Fills all the elements in an array with a static value
void __fill(Array* const this, int) {

}