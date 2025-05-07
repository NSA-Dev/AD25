#include <stdio.h>
#include "array.h"
#include "sort.h"

int main(void) {
        
        int array[MAX_SIZE];

        initArray(array, MAX_SIZE); // init array of MAX_SIZE, from 1 to MAX_SIZE

        printArray(array);
        shuffleK(array, 5);
        printArray(array);
         
        selectionSort(array, MAX_SIZE);
        printArray(array);


        return 0;
    } 
