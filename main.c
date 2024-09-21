#include <stdio.h>
#include "./array.h"

int main() {
    Array obj;
    __construct(&obj);
    __push(&obj, 5, 1,2,3,4,5);   
    
    return 0;
}