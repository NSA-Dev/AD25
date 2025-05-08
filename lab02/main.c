#include <stdio.h>
#include "array.h"
#include "sort.h"

int main(void) {
        
        int array[MAX_SIZE];

        initArray(array, MAX_SIZE); // init array of MAX_SIZE, from 1 to MAX_SIZE

        printArray(array);
        shuffleK(array, 5);
        printArray(array);
         
        quickSort(array, 0, MAX_SIZE - 1);
        printArray(array);


            return 0;
} 
