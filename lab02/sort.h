#ifndef SORT_H
#define SORT_H

/* ascending sorts */
void insertionSort(int a[], int len);  
void selectionSort(int a[], int len);
void shellSort(int a[], int len);
void mergeSort(int a[], int len); 

/* helper functions */
void swap(int* a, int* b); 
void copyArray(int a[], int b[], len) // array length must match
#endif
