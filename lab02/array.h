#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 20

void initArray(int a[], int k); // init array a with k values  
void printArray(int a[]);
int pickRandomIndex(void);
void shiftLeft(int a[], int start);
void shuffleK(int a[], int k); // pick k elements randomly, assign to the end while shifting left
#endif 
