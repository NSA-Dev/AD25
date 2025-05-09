#ifndef SORT_H
#define SORT_H

#include <stdlib.h>
#include <stdio.h>

extern unsigned long int exchangeCount;
extern unsigned long int compareCount;

/* ascending sorts */
void insertionSort(int a[], int len);  
void selectionSort(int a[], int len);
void shellSort(int a[], int len);
void mergeSort(int a[], int len);
void mergeSort_recursion(int a[], int l, int r);
void mergeSortedArrays(int a[], int l, int m, int r);
int partition(int* array, int low, int high);
void quickSort(int* array, int low, int high);
void mergesortBU(int array[], int arraySize);
void mergeBU(int array[], int l, int m, int r);
void bubbleSort(int arr[], int len);
void combSort(int arr[], int len);  
/* helper functions */
void swap(int* a, int* b);
int minimum(int x, int y);  
void copyArray(int a[], int b[], int len); // array length must match 

#endif
