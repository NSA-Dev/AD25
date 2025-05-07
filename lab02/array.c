#include "array.h"


void initArray(int a[],  int k) {
    /* First the array shall be initialized with 1 to MAX_SIZE (main.c) asc */
    for(int i = 0; i < MAX_SIZE; i++) {
        a[i] = i+1;
    }
}

void printArray(int a[]) {
    for(int i = 0; i < MAX_SIZE; i++) {
        printf("%d ", a[i]);
    }

   printf("\n"); 
}

int pickRandomIndex(void) { 
    int index = rand() % MAX_SIZE; 
    return index;
}


void shiftLeft(int a[], int start) {
    int temp = a[start]; // pluck the value of interest from the array 
    for(int i = start; i < MAX_SIZE - 1; i++) {
        a[i] = a[i + 1]; // shift everything to the value's position
    }
    a[MAX_SIZE - 1] = temp; // assign the value to the end of the array  
    
}

void shuffleK(int a[], int k) { 
    srand(time(NULL)); // Init seed for pickRandomIndex() calls 
    
    if(k > MAX_SIZE) k = MAX_SIZE; // if k exceeds the range assign the limit to it
    
    while(k--) {
        int random = pickRandomIndex();
        shiftLeft(a, random);  
    }
}

