#include "sort.h"



 
void swap(int* a, int* b) { 
    int temp = *a;
    *a = *b;
    *b = temp;
    return; 
}

int minimum(int x, int y) { 
	return (x < y) ? x : y; 
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
            compareCount++;
            exchangeCount++;   
        }
        a[j] = compared;
        exchangeCount++;
    }   
}

void selectionSort(int a[], int len) { 

    int min = 0;
    int low = 0; 

    while(low != len - 1) { 
        min = low;
        for(int i = low; i < len; i++) {
            if(a[i] < a[min]) min = i; // update min index
            compareCount++; 
        }
        
        if(min != low) {
            swap(&a[low], &a[min]);
            exchangeCount++; 
        }    
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
                compareCount++;
                exchangeCount++; 
            }
            a[j] = compared;
            exchangeCount++;    
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

/* Iterative mergesort function to sort arr[0...n-1] */
void mergesortBU(int array[], int arraySize){
	// For current size of subarrays to be merged
	// curr_size varies from 1 to n/2
	int currSize = 0;
	// For picking starting index of left subarray
	// to be merged
	int leftStart = 0;

	// Merge subarrays in bottom up manner. First merge subarrays of
	// size 1 to create sorted subarrays of size 2, then merge subarrays
	// of size 2 to create sorted subarrays of size 4, and so on.
	for (currSize = 1; currSize <= arraySize - 1; currSize = 2 * currSize){
		// Pick starting point of different subarrays of current size
		for (leftStart = 0; leftStart < arraySize - 1; leftStart += 2 * currSize){
			// Find ending point of left subarray. mid+1 is starting
			// point of right
			int mid = minimum(leftStart + currSize - 1, arraySize - 1);

			int right_end = minimum(leftStart + 2 * currSize - 1, arraySize - 1);

			// Merge Subarrays arr[left_start...mid] & arr[mid+1...right_end]
			mergeBU(array, leftStart, mid, right_end);
		}
	}
}

/* Function to merge the two haves arr[l..m] and arr[m+1..r] of array arr[] */
void mergeBU(int array[], int l, int m, int r){
	int i = 0, j = 0, k = 0;
	int leftSize = m - l + 1;
	int rightSize = r - m;

	/* create temp arrays */
	int leftPart[TEMP_SIZE] = { 0 }, rightPart[TEMP_SIZE] = { 0 };

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < leftSize; i++)
		leftPart[i] = array[l + i];
	for (j = 0; j < rightSize; j++)
		rightPart[j] = array[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0;
	j = 0;
	k = l;
	while (i < leftSize && j < rightSize){
		if (leftPart[i] <= rightPart[j]){
			array[k] = leftPart[i];
			i++;
		}
		else{
			array[k] = rightPart[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there are any */
	while (i < leftSize){
		array[k] = leftPart[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there are any */
	while (j < rightSize){
		array[k] = rightPart[j];
		j++;
		k++;
	}
}



int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low;


    for(int j = low; j < high; j++) {
        if(array[j] <= pivot) {
            swap(&array[i], &array[j]);
            exchangeCount++;
            compareCount++; 
            i++;
        }
    }

    swap(&array[i], &array[high]);
    exchangeCount++; 

    return i; 
} 
 
void quickSort(int* array, int low, int high) {
    if (low < high) {
        int pivot = partition(array, low, high); 
        quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    } 
}
