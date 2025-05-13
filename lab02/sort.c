/**
 * Lab2 Tasks
 * Submission by Nikita Semeniuk ID: 2722726
 * 
 * Date 2025-05-09

 */
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
            compareCount++;
            compared = a[i];
            int j;
            for(j = i; j >= gap && a[j - gap] > compared; j -= gap) {
                a[j] = a[j-gap];
                compareCount++;
                exchangeCount++; 
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
    compareCount++; 
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
    int* tempLeft = (int*)malloc(leftLen * sizeof(int));
    int* tempRight = (int*)malloc(rightLen * sizeof(int));

    if (!tempLeft || !tempRight) {
        printf("malloc fail inside mergeSortedArrays, returning...\n");
        return; 
    }

    /* Copy subsections */
    for(int i = 0; i < leftLen; i++) {
        tempLeft[i] = a[l + i];
        compareCount++;
        exchangeCount++;
    }

    for(int i = 0; i < rightLen; i++) {
        tempRight[i] = a[m + 1 + i];
        compareCount++;
        exchangeCount++;
    }

    /* Compare and copy into the original check for bounds in the if */
    int i, j, k; // declare indices for a[], tempLeft, tempRight 
    i = j = 0; // a[] & j index to 0 for now
    
    for( k = l; k <= r; k++) {
        if((i < leftLen) && 
                (j >= rightLen || tempLeft[i] <= tempRight[j])) {
            a[k] = tempLeft[i];
            i++;
			compareCount++;
			exchangeCount++; 
        } else {
            a[k] = tempRight[j];
			exchangeCount++;
            j++; 
        }
    }
    free(tempLeft);
    free(tempRight); 
    return;
}

void mergeBU(int array[], int l, int m, int r) {
    int leftSize = m - l + 1;
    int rightSize = r - m;
    
    // Dynamic allocation for temp arrays
    int *leftPart = malloc(leftSize * sizeof(int));
    int *rightPart = malloc(rightSize * sizeof(int));
    
    if (!leftPart || !rightPart) {
        fprintf(stderr, "Memory allocation failed in mergeBU\n");
        exit(EXIT_FAILURE);
    }
    
    /* Copy data to temp arrays */
    for (int i = 0; i < leftSize; i++)
        leftPart[i] = array[l + i];
    for (int j = 0; j < rightSize; j++)
        rightPart[j] = array[m + 1 + j];
    
    /* Merge temp arrays back into array[l..r] */
    int i = 0, j = 0, k = l;
    while (i < leftSize && j < rightSize) {
        compareCount++; // Count comparison
        if (leftPart[i] <= rightPart[j]) {
            array[k] = leftPart[i++];
        } else {
            array[k] = rightPart[j++];
            exchangeCount++; // Count exchange
        }
        k++;
    }
    
    /* Copy remaining elements */
    while (i < leftSize) {
        array[k++] = leftPart[i++];
        exchangeCount++;
        compareCount++;
    }
    while (j < rightSize) {
        array[k++] = rightPart[j++];
        exchangeCount++;
        compareCount++;
    }
    
    free(leftPart);
    free(rightPart);
}

void mergesortBU(int array[], int arraySize) {
    // Allocate a single temp array once
    int *temp = malloc(arraySize * sizeof(int));
    if (!temp) {
        fprintf(stderr, "Memory allocation failed in mergesortBU\n");
        return;
    }
    
    for (int currSize = 1; currSize < arraySize; currSize *= 2) {
        for (int leftStart = 0; leftStart < arraySize - 1; leftStart += 2 * currSize) {
            int mid = minimum(leftStart + currSize - 1, arraySize - 1);
            int rightEnd = minimum(leftStart + 2 * currSize - 1, arraySize - 1);
            
            // Use the pre-allocated temp array
            int i = leftStart, j = mid + 1, k = 0;
            
            // Merge two subarrays into temp
            while (i <= mid && j <= rightEnd) {
                compareCount++;
                if (array[i] <= array[j]) {
                    temp[k++] = array[i++];
                } else {
                    temp[k++] = array[j++];
                    exchangeCount++;
                }
            }
            
            // Copy remaining elements
            while (i <= mid) {
                temp[k++] = array[i++];
                compareCount++;
                exchangeCount++;

            }
            while (j <= rightEnd) {
                temp[k++] = array[j++];
                compareCount++;
                exchangeCount++;
            }
            
            // Copy back from temp to original array
            for (i = leftStart, k = 0; i <= rightEnd; i++, k++) {
                array[i] = temp[k];
                exchangeCount++;
                compareCount++;
            }
        }
    }
    
    free(temp);
}




int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low;


    for(int j = low; j < high; j++) {
        compareCount++;
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

void bubbleSort(int arr[], int n) {
    int swapped;
    do {
        swapped = 0;
        for (int i = 0; i < n-1; i++) {
            compareCount++;
            if (arr[i] > arr[i+1]) {
                // Swap elements
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                exchangeCount++;
                swapped = 1;
            }
        }
       // n--; // Optimization - largest element bubbles to end
    } while (swapped);
}

void combSort(int arr[], int n) {
    int gap = n;
    float shrink = 1.3;
    int swapped;

    do {
        // Update gap size
        gap = (int)(gap / shrink);
        if (gap < 1) gap = 1;

        swapped = 0;
        for (int i = 0; i + gap < n; i++) {
            compareCount++;
            if (arr[i] > arr[i+gap]) {
                // Swap elements
                int temp = arr[i];
                arr[i] = arr[i+gap];
                arr[i+gap] = temp;
                exchangeCount++;
                swapped = 1;
            }
        }
    } while (gap > 1 || swapped);
}
