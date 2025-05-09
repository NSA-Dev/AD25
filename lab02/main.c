#include <stdio.h>
#include "array.h"
#include "sort.h"

unsigned long int exchangeCount = 0; 
unsigned long int compareCount = 0;  


void resetCounters(void);

int main(void) {
    // Declare arrays containing counter info for each algo
    unsigned long int exchanges[4], comparisons[4];
    // Create an array, init from 1 to MAX_SIZE, print result 
    int array[MAX_SIZE];
    initArray(array, MAX_SIZE); 
    printf("Initialized array:\n");
    printArray(array);

    // Randomly shuffle the array, print result
    shuffleK(array, MAX_SIZE);
    printf("Shuffled array:\n"); 
    printArray(array);
        

    // Test the following sorts(get count of exchanges & comparisons):
    // 1. Insertion sort
    // 2. Selection sort
    // 3. Shell sort
    // 4. Quick sort
    // Print results table
        
    // Insertion sort
    printf("Running insertion sort... \n");
    insertionSort(array, MAX_SIZE);
    exchanges[0] = exchangeCount;
    comparisons[0] = compareCount;
    resetCounters();
    printf("Selection sort result:\n");
    printArray(array);
    shuffleK(array, MAX_SIZE); // reshuffle the array again  

    // Selection sort
    printf("Running selection sort... \n");
    selectionSort(array, MAX_SIZE);
    exchanges[1] = exchangeCount;
    comparisons[1] = compareCount;
    resetCounters();
    printf("Selection sort result:\n");
    printArray(array);
    shuffleK(array, MAX_SIZE);

        
    // Shell sort
    printf("Running Shellsort... \n");
    shellSort(array, MAX_SIZE);
    exchanges[2] = exchangeCount;
    comparisons[2] = compareCount;
    resetCounters();
    printf("Shellsort result:\n");
    printArray(array);
    shuffleK(array, MAX_SIZE);


    // Quick sort
    printf("Running quicksort... \n");
    quickSort(array, 0, MAX_SIZE - 1);
    exchanges[3] = exchangeCount;
    comparisons[3] = compareCount;
    resetCounters();
    printf("Quicksort result:\n");
    printArray(array);
    

    // Print the table
    printf("\n");
	printf("          ===== SORTING ALGORITHM BENCHMARK =====\n");    
    printf("+----------------+------------------+------------------+\n");
	printf("| %-14s | %-16s | %-16s |\n", "Algorithm", "Comparisons", "Exchanges");
	printf("+----------------+------------------+------------------+\n");
	printf("| %-14s | %-16lu | %-16lu |\n", "Insertion sort", comparisons[0], exchanges[0]);
	printf("| %-14s | %-16lu | %-16lu |\n", "Selection sort", comparisons[1], exchanges[1]);
	printf("| %-14s | %-16lu | %-16lu |\n", "Shell sort", comparisons[2], exchanges[2]);
	printf("| %-14s | %-16lu | %-16lu |\n", "Quicksort", comparisons[3], exchanges[3]);
	printf("+----------------+------------------+------------------+\n");

            return 0;
}


void resetCounters(void) {
    exchangeCount = 0;
    compareCount = 0; 
}
