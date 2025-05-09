#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"

#define TIMEOUT_SEC 300 // if runtime > 5 min (300 s) stop the sort
// Contents of array.h << moved here due to submission reqs
#define OLD_MAX_SIZE 20 // inital size
#define MAX_SIZE 50000

void initArray(int a[], int k, int size); // init array a with k values  
void printArray(int a[], int size);
int pickRandomIndex(int size);
void shiftLeft(int a[], int start, int size);
void shuffleK(int a[], int k, int size); // pick k elements randomly, assign to the end while shifting left

typedef struct {
	double runTime;
	unsigned long int comparisons;
	unsigned long int exchanges;
	
} perfomance_t; 


// end of array.h

unsigned long int exchangeCount = 0; 
unsigned long int compareCount = 0;  

void resetCounters(void); 
void getSortsRuntime(void);     // measure runtime of selectionSort & mergeSort
void benchmarkAll(void);

int main(void) {
    // Declare arrays containing counter info for each algo
    unsigned long int exchanges[4], comparisons[4];
    // Create an array, init from 1 to MAX_SIZE, print result 
    int array[OLD_MAX_SIZE];
    initArray(array, OLD_MAX_SIZE, OLD_MAX_SIZE); 
    printf("Initialized array:\n");
    printArray(array, OLD_MAX_SIZE);

    // Randomly shuffle the array, print result
    shuffleK(array, OLD_MAX_SIZE, OLD_MAX_SIZE);
    printf("Shuffled array:\n"); 
    printArray(array, OLD_MAX_SIZE);
        

    // Test the following sorts(get count of exchanges & comparisons):
    // 1. Insertion sort
    // 2. Selection sort
    // 3. Shell sort
    // 4. Quick sort
    // Print results table
        
    // Insertion sort
    printf("Running insertion sort... \n");
    insertionSort(array, OLD_MAX_SIZE);
    exchanges[0] = exchangeCount;
    comparisons[0] = compareCount;
    resetCounters();
    printf("Selection sort result:\n");
    printArray(array, OLD_MAX_SIZE);
    shuffleK(array, OLD_MAX_SIZE, OLD_MAX_SIZE); // reshuffle the array again  

    // Selection sort
    printf("Running selection sort... \n");
    selectionSort(array, OLD_MAX_SIZE);
    exchanges[1] = exchangeCount;
    comparisons[1] = compareCount;
    resetCounters();
    printf("Selection sort result:\n");
    printArray(array, OLD_MAX_SIZE);
    shuffleK(array, OLD_MAX_SIZE, OLD_MAX_SIZE);

        
    // Shell sort
    printf("Running Shellsort... \n");
    shellSort(array, OLD_MAX_SIZE);
    exchanges[2] = exchangeCount;
    comparisons[2] = compareCount;
    resetCounters();
    printf("Shellsort result:\n");
    printArray(array, OLD_MAX_SIZE);
    shuffleK(array, OLD_MAX_SIZE, OLD_MAX_SIZE);


    // Quick sort
    printf("Running quicksort... \n");
    quickSort(array, 0, OLD_MAX_SIZE - 1);
    exchanges[3] = exchangeCount;
    comparisons[3] = compareCount;
    resetCounters();
    printf("Quicksort result:\n");
    printArray(array, OLD_MAX_SIZE);
    

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

    // Runtime test
    getSortsRuntime();
    benchmarkAll();
    return 0;
}


void resetCounters(void) {
    exchangeCount = 0;
    compareCount = 0; 
}

void getSortsRuntime(void) {
    // declare metrics
    unsigned long selComp, mergeComp;
    // declare clock times 
    clock_t start, end;  
    double mergeTime, selTime;
    // declare flags for enabling algorithm options
    int enable_selectionSort, enable_mergeSort;


    // init flags
    enable_selectionSort = 1;
    enable_mergeSort = 1; 
    
    // print the heading
    printf("\n+--------+----------------+----------------+----------------+----------------+\n");
    printf("| %-6s | %-14s | %-14s | %-14s | %-14s |\n", 
           "k", "SelSort Time", "SelSort Comp", "MergeSort Time", "MergeSort Comp");
    printf("+--------+----------------+----------------+----------------+----------------+\n");
    
    // Test loop
    for(int k = 500; k < MAX_SIZE; k *= 2) {
        // Allocate new array of k size
        int *array =(int *) malloc(k * sizeof(int));
        
        // Exit if out of memory 
        if(!array) {
            printf("Memory allocation failed for k=%d (getSortsRuntime()\n)");
            printf("Shutting down...\n");
            exit(EXIT_FAILURE); 
        }
        
        // init array 1 up to k
        initArray(array, k, k);
 
        
        // Test selectionSort()
        if(enable_selectionSort) {
            shuffleK(array, k, k); // shuffle before sorting
            start = clock();
            selectionSort(array, k);
            end = clock(); 
            selTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            selComp = compareCount;
            resetCounters(); 
        
            // stop the test run if computational time exceeds TIMEOUT_SEC 
            if(selTime > TIMEOUT_SEC) enable_selectionSort = 0;  

        } 

        // Test mergeSort
        if(enable_mergeSort) {
            shuffleK(array, k, k); // shuffle before sorting
            start = clock(); 
            mergeSort(array, k);
            end = clock(); 
            mergeTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            mergeComp = compareCount;
            resetCounters();

            if(mergeTime > TIMEOUT_SEC) enable_mergeSort = 0;  
        }
        
        // Print table entry
        printf("| %-6d | ", k);
        if(selTime >= 0) printf("%-14.3f | %-14lu | ", selTime, selComp);
        else printf("%-14s | %-14s | ", "TIMEOUT", "TIMEOUT");
        
        if(mergeTime >= 0) printf("%-14.3f | %-14lu |\n", mergeTime, mergeComp);
        else printf("%-14s | %-14s |\n", "TIMEOUT", "TIMEOUT");

        // never forget to free the memory
        free(array); 
    }
    printf("+--------+----------------+----------------+----------------+----------------+\n");
}

void benchmarkAll(void) {
	clock_t start, end; // declare clock start times
	
	// declare structs to hold statistics on each run
	perfomance_t insStats, selStats, shellStats, mergeStats, mergeStats_bu, qsStats;
	
	 // declare flags for enabling algorithm options (quick and dirty)
    int enable_insertionSort, enable_selectionSort,
		enable_shellSort, enable_mergeSort, enable_mergeSortBU, enable_quickSort; 
	
	// init flags
	enable_insertionSort = 1;
	enable_selectionSort = 1;
	enable_mergeSort = 1;
	enable_shellSort = 1;
	enable_mergeSortBU = 0; // debug
	enable_quickSort = 1; 
	
	
	

	// set up array parameters  	
	int k[] = {100, 200, 500, 1000}; // size for each array to test
	int arrayCount = 4; // size of the k[] corresponds to how many arrays we construct
	
	
	for(int i = 0; i < arrayCount; i++) {
		int *array =(int *) malloc(k[i] * sizeof(int)); // allocate array of size k
        
        // Exit if out of memory 
        if(!array) {
            printf("Memory allocation failed for k=%d (getSortsRuntime()\n)");
            printf("Shutting down...\n");
            exit(EXIT_FAILURE); 
        }
        initArray(array, k[i], k[i]); // k[i] contains size
        
        // Test each algorithm
                
        if(enable_insertionSort) {
            shuffleK(array, k[i], k[i]); // shuffle before sorting
            start = clock();
            insertionSort(array, k[i]);
            end = clock(); 
            insStats.runTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            insStats.comparisons = compareCount;
            insStats.exchanges = exchangeCount;
            resetCounters(); 
        
            // stop the test run if computational time exceeds TIMEOUT_SEC 
            if(insStats.runTime > TIMEOUT_SEC) enable_insertionSort = 0;  

        }
                
        if(enable_selectionSort) {
            shuffleK(array, k[i], k[i]); // shuffle before sorting
            start = clock();
            selectionSort(array, k[i]);
            end = clock(); 
            selStats.runTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            selStats.comparisons = compareCount;
            selStats.exchanges = exchangeCount;
            resetCounters(); 
        
            // stop the test run if computational time exceeds TIMEOUT_SEC 
            if(selStats.runTime > TIMEOUT_SEC) enable_selectionSort = 0;  

        }
        
                
        if(enable_shellSort) {
            shuffleK(array, k[i], k[i]); // shuffle before sorting
            start = clock();
            shellSort(array, k[i]);
            end = clock(); 
            shellStats.runTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            shellStats.comparisons = compareCount;
            shellStats.exchanges = exchangeCount;
            resetCounters(); 
        
            // stop the test run if computational time exceeds TIMEOUT_SEC 
            if(shellStats.runTime > TIMEOUT_SEC) enable_shellSort = 0;  

        }
                
        if(enable_mergeSort) {
            shuffleK(array, k[i], k[i]); // shuffle before sorting
            start = clock();
            mergeSort(array, k[i]);
            end = clock(); 
            mergeStats.runTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            mergeStats.comparisons = compareCount;
            mergeStats.exchanges = exchangeCount;
            resetCounters(); 
        
            // stop the test run if computational time exceeds TIMEOUT_SEC 
            if(mergeStats.runTime > TIMEOUT_SEC) enable_mergeSort = 0;  

        }
        
                
        if(enable_mergeSortBU) {
            shuffleK(array, k[i], k[i]); // shuffle before sorting
            start = clock();
            mergesortBU(array, k[i]);
            end = clock(); 
            mergeStats_bu.runTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            mergeStats_bu.comparisons = compareCount;
            mergeStats_bu.exchanges = exchangeCount;
            resetCounters(); 
        
            // stop the test run if computational time exceeds TIMEOUT_SEC 
            if(mergeStats_bu.runTime > TIMEOUT_SEC) enable_mergeSortBU = 0;  

        }
        
        
        if(enable_quickSort) {
            shuffleK(array, k[i], k[i]); // shuffle before sorting
            start = clock();
            quickSort(array, 0, k[i] - 1);
            end = clock(); 
            qsStats.runTime = ((double)(end - start)) / CLOCKS_PER_SEC;
            qsStats.comparisons = compareCount;
            qsStats.exchanges = exchangeCount;
            resetCounters(); 
        
            // stop the test run if computational time exceeds TIMEOUT_SEC 
            if(qsStats.runTime > TIMEOUT_SEC) enable_quickSort = 0;  

        }
        
        // free the memory
        free(array); 
		// print all stats for current k 
		// Print benchmark header
		printf("\n          ===== ALL SORTS BENCHMARK =====\n");
		printf("          ===== k = %-4d =====\n\n", k[i]);

		// Print table header
		printf("+----------------+----------------+----------------+----------------+\n");
		printf("| %-14s | %-14s | %-14s | %-14s |\n", 
       "Algorithm", "Time (s)", "Comparisons", "Exchanges");
		printf("+----------------+----------------+----------------+----------------+\n");

		// Insertion Sort
		printf("| %-14s | %-14.6f | %-14lu | %-14lu |\n",
       "Insertion", insStats.runTime, insStats.comparisons, insStats.exchanges);

		// Selection Sort
		printf("| %-14s | %-14.6f | %-14lu | %-14lu |\n",
       "Selection", selStats.runTime, selStats.comparisons, selStats.exchanges);

		// Shell Sort
		printf("| %-14s | %-14.6f | %-14lu | %-14lu |\n",
       "Shell", shellStats.runTime, shellStats.comparisons, shellStats.exchanges);

		// Merge Sort (Top-Down)
		printf("| %-14s | %-14.6f | %-14lu | %-14lu |\n",
       "Merge TD", mergeStats.runTime, mergeStats.comparisons, mergeStats.exchanges);

		// Merge Sort (Bottom-Up)
		//printf("| %-14s | %-14.6f | %-14lu | %-14lu |\n",
       //"Merge BU", mergeStats_bu.runTime, mergeStats_bu.comparisons, mergeStats_bu.exchanges);

		// Quick Sort
		printf("| %-14s | %-14.6f | %-14lu | %-14lu |\n",
       "Quick", qsStats.runTime, qsStats.comparisons, qsStats.exchanges);

		// Footer
		
		
		  
	}
	printf("+----------------+----------------+----------------+----------------+\n");
	return;
}

// Contents of array.c << moved here due to submission reqs

void initArray(int a[],  int k, int size) {
    /* First the array shall be initialized with 1 to MAX_SIZE (main.c) asc */
    for(int i = 0; i < size; i++) {
        a[i] = i+1;
    }
}

void printArray(int a[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", a[i]);
    }

   printf("\n"); 
}

int pickRandomIndex(int size) { 
    int index = rand() % size; 
    return index;
}


void shiftLeft(int a[], int start, int size) {
    int temp = a[start]; // pluck the value of interest from the array 
    for(int i = start; i < size - 1; i++) {
        a[i] = a[i + 1]; // shift everything to the value's position
    }
    a[size - 1] = temp; // assign the value to the end of the array  
    
}

void shuffleK(int a[], int k, int size) { 
    srand(time(NULL)); // Init seed for pickRandomIndex() calls 
    
    if(k > size) k = size; // if k exceeds the range assign the limit to it
    
    while(k--) {
        int random = pickRandomIndex(size);
        shiftLeft(a, random, size);  
    }
}
// end of array.c
