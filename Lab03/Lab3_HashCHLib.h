#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "string.h"

//Macros
#define MAX_ARRAY 50
#define MAX_STRING 30
#define MAX_LINE 100


typedef struct sElementCH {
	struct sElementCH* next;
	int key;
	char value[MAX_STRING];
} sElementCH;

/**********************************************************************************************************************
Hashing functions
**********************************************************************************************************************/
/*
/*
Function calculates the hash value for the passed key.
Function return the calculated hash value.
*/
int hashing(int key);
int hash_midsquare(int key);
int hash_mult(int key); 
int hash_XOR(int key);

/**********************************************************************************************************************
Prototypes for address hashing
**********************************************************************************************************************/
/*
Function creates a new entry in the hash table or if the key already exists overwrites the value with the passed value.
Function receives the hash table and the key-value-pair to be inserted.
Function returns the number of collisions.
*/
int putCH(sElementCH hashtableCH[MAX_ARRAY], int (*hashMethod) (int),  int key, char value[MAX_STRING]);

/*
Function searches for the entry in the hash table having the passed key.
Function returns the value of entry or NULL if the key does not exist in the hash table.
*/
char* getCH(sElementCH hashtableCH[MAX_ARRAY], int (*hashMethod) (int),  int key);

/*
Function searches for the entry in the hash table having the passed key.
If it finds an entry the function deletes it from the hash table.
*/
void deleteCH(sElementCH hashtableCH[MAX_ARRAY], int (*hashMethod) (int),  int key);

/*
Function prints the hash table.
*/
void printHashTableCH(sElementCH hashtableCH[MAX_ARRAY]);

/*
Function gets a file pointer to a csv-file which contains some key-value-pairs.
Additionally, the function gets a hash table in which the function inserts the key-value-pairs in the csv-file.
*/
void readCSVCH(FILE* fP, sElementCH hashtableCH[MAX_ARRAY], int (*hashMethod) (int));


/*
Free the memory allocated for the table
*/
void freeTableCH(sElementCH hashtableCH[MAX_ARRAY]);


