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
    mergeSort_recursion(a, 0, len - 1); // have to offset (not inclusive interval) 
    return; 
}

void mergeSort_recursion(int a[], int l, int r) {
    /*Find middle return if we are out of bounds*/
    if(l >= r) return; 
    int m = l + (r - l) / 2;

    /* Recursively sort left and right side */
    mergeSort_recursion(a, l, m); // sort left side
    mergeSort_recursion(a, m + 1, r); // sort  right side
    
    /* select from two sorted parts and coppy to provided array */
    mergeSortedArrays(a, l, m, r); 

    return;
}

void mergeSortedArrays(int a[], int l, int m, int r) {
    /* Calculate indices */
    int leftLen = m - l + 1;
    int rightLen = r - m;

    /*Declare subsections and their indices */
    int tempLeft[leftLen];
    int tempRight[rightLen];
    

    /* Copy subsections */
    for(int i = 0; i < leftLen; i++) {
        tempLeft[i] = a[l + i];
    }

    for(int i = 0; i < rightLen; i++) {
        tempRight[i] = a[m + 1 + i];
    }

    /* Compare and copy into the original check for bounds in the if */
    int i, j, k; // declare indices for a[], tempLeft, tempRight 
    i = j = 0; // a[] & j index to 0 for now
    
    for( k = l; k <= r; k++) {
        if((i < leftLen) && 
                (j >= rightLen || tempLeft[i] <= tempRight[j])) {
            a[k] = tempLeft[i];
            i++; 
        } else {
            a[k] = tempRight[j];
            j++; 
        }
    }

    return;
}

int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low;


    for(int j = low; j < high; j++) {
        if(array[j] <= pivot) {
            swap(&array[i], &array[j]);
            i++;
        }
    }

    swap(&array[i], &array[high]);

    return i; 
} 


void quickSort(int* array, int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high); 
        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    } 
}
