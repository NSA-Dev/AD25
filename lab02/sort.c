#include "sort.h"

 
void swap(int* a, int* b) { 
    int temp = *a;
    *a = *b;
    *b = temp;
    return; 
}
void insertionSort(int a[], int len) {
    // start at 1
    // compare with elem to the left
    // shift
    int compared;

    for(int i = 1; i < len; i++){
        compared = a[i];
        int j = i;
        // while element to the left is larger shift it right
        while(j >  0 && a[j-1] > compared) {
            a[j] = a[j-1];
            j--;  
        }
        a[j] = compared;
    }   
}

void selectionSort(int a[], int len) {
   
    int min = 0;
    int low = 0; 

    while(low != len - 1) {
        min = low;
        for(int i = low; i < len; i++) {
            if(a[i] < a[min]) min = i; // update min index
        }
        
        if(min != low) swap(&a[low], &a[min]); // ideally I would add a check
        low++; 
    }
}
