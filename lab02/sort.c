#include "sort.h"

 
void swap(int* a, int* b) { 
    int temp = *a;
    *a = *b;
    *b = temp;
    return; 
}

void copyArray(int a[], int b[], int len) {
    for(int i = 0; i < len; i++) {
        b[i] = a[i];
    }

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
        
        if(min != low) swap(&a[low], &a[min]); 
        low++; 
    }
}



void shellSort(int a[], int len) {
    int compared;

    for(int gap = len/2; gap > 0; gap /= 2) {
        for(int i = gap; i < len; i++) {
            compared = a[i];
            int j;
            for(j = i; j >= gap && a[j - gap] > compared; j -= gap) {
                a[j] = a[j-gap];
            }
            a[j] = compared;   
        } 
    }
}

void mergeSort(int a[], int len) {
    
}
