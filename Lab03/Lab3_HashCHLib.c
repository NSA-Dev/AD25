#pragma once

#include "Lab3_HashCHLib.h"
#include "HashAHLib.h"



/**********************************************************************************************************************
Prototypes for address hashing
**********************************************************************************************************************/
/*
Function creates a new entry in the hash table or if the key already exists overwrites the value with the passed value.
Function receives the hash table and the key-value-pair to be inserted.
Function returns the number of collisions or -1 in case the table is full 
*/
int putCH(sElementCH hashtableCH[MAX_ARRAY], int (*hashMethod) (int), int key, char value[MAX_STRING]) {
	// Get table index to look for
	int i = hashMethod(key);
	int colCount = 0; 
 		  
 	// Collision number == MAX ARRAY? Table is full return -1 
 	while(colCount < MAX_ARRAY) {
		/* Three possible scenarios to handle:
			1. We encounter empty space -> record k-v pair
			2. We encounter same key -> overwrite the record
			3. None of the above -> adjust index, 
									check if the table is full
									count collisions
		*/
		
		// Found an empty bucket, record KV pair into the table 
		if(hashtableCH[i].key == -1) {
			hashtableCH[i].key = key;
			strcpy(hashtableCH[i].value, value);
			return colCount;  
		}
		// Found the same key 
		else if(hashtableCH[i].key == key) {
			strcpy(hashtableCH[i].value, value);
			return colCount;  
			}
		// No space, no key found -> collision 
		else {
		// Find next available slot	
		sElementCH* current = &hashtableCH[i];
		while(current->next != NULL) {
			current = current->next;
			colCount++; 
		}	
				
		// malloc() newElement, populate its fields 
		sElementCH* newElement  = (sElementCH*)malloc(sizeof(sElementCH)); 
		if(!newElement) return -1;
		newElement->next = NULL;
		newElement->key = key;
		strcpy(newElement->value, value);
		  
		// add to the chain by assigning a pointer  
		current->next = newElement; 
		return colCount; // return collisions on exit 
		} 		 
	}	  
 	return -1; 
}

/*
Function searches for the entry in the hash table having the passed key.
Function returns the value of entry or NULL if the key does not exist in the hash table.
*/
char* getCH(sElementCH hashtableCH[MAX_ARRAY], int (*hashMethod) (int),  int key) {
	int i = hashMethod(key);
	int startIndex = i; 
	
	// check the main bucket if found the key return its value 
	if(hashtableCH[i].key == key) {
		return hashtableCH[i].value; 
	} else {
		return NULL; // TODO
	}
	 
}

/*
Function searches for the entry in the hash table having the passed key.
If it finds an entry the function deletes it from the hash table.
*/
void deleteCH(sElementCH hashtableCH[MAX_ARRAY], int (*hashMethod) (int), int key) {
	int i = hashMethod(key);
	
	// check the main bucket 
	if(hashtableCH[i].key == key) {
		if(hashtableCH[i].next == NULL) {
			hashtableCH[i].key = -1;
			hashtableCH[i].value[0] = '\0';
		} 
		// else promote next element to the starting position
		else {
			sElementCH* temp = hashtableCH[i].next;
			hashtableCH[i].key = temp->key;
			strcpy(hashtableCH[i].value, temp->value);
			hashtableCH[i].next = temp->next;
			free(temp); // discard the duplicate
		}
		return; 
	}
	
	// Check if the chain has the key 
	sElementCH* current = &hashtableCH[i];
	sElementCH* prev = NULL; // needed for iteration down the line 
	while(current->next != NULL) {
		prev = current;
		current = current->next;
		
		// if current->key matches, then adjust prev pointer to its val, free current
		if(current->key == key) {
			prev->next = current->next;
			free(current);
			return; 
		}
	} 
	return; // nothing found, return 
}

/*
Function prints the hash table.
If a field in the array is empty, it prints “empty”.
*/
void printHashTableCH(sElementCH hashtableCH[MAX_ARRAY]) {
	// print the heading
	printf("| %-4s | %-30s |\n", "KEY", "VALUE");  
    printf("|------|--------------------------------|\n"); 
	// print the table elements
	for(int i = 0; i < MAX_ARRAY; i++) {
		if(hashtableCH[i].key == -1) printf("NULL		%s\n", "<EMPTY>"); 
		else {
			printf("%d		%s\n", hashtableCH[i].key, hashtableCH[i].value);
		}
		
		// print chained
		sElementCH* current = hashtableCH[i].next;
		while(current != NULL) {
			printf("%d		%s\n", current->key, current->value);
			current = current->next; 
		}
	}
}

/*
Function gets a file pointer to a csv-file which contains some key-value-pairs.
Additionally, the function gets a hash table in which the function inserts the key-value-pairs in the csv-file.
*/
void readCSVCH(FILE* fP, sElementCH hashtableCH[MAX_ARRAY], int (*hashMethod) (int)) {
	int number = 0;
	char buffer[MAX_LINE];
	char* field;
	int key;
	char string[MAX_STRING];

	if (fP == NULL) {
		printf("File does not exist.");
		exit(0);
	}
	else
		// Get number of lines
		while (!feof(fP)) {
			char ch = fgetc(fP);
			if (ch == '\n')
				number++;
		}

	if (fP != NULL)
		rewind(fP);

	for (int i = 0; i < number; i++) {
		fgets(buffer, MAX_LINE, fP);


		field = strtok(buffer, ";");
		key = atoi(field);

		field = strtok(NULL, ";");
		strcpy(string, field);
		//replace \n in name
		string[strlen(string) - 1] = '\0';

		putCH(hashtableCH, hashMethod, key, string);
	}

	return;
}

/*
Free the memory allocated for the table
*/
void freeTableCH(sElementCH hashtableCH[MAX_ARRAY]) {
	for(int i = 0; i < MAX_ARRAY; i++) {
		sElementCH* current = hashtableCH[i].next;
		while(current != NULL) {
			sElementCH* temp = current;
			current = current->next;
			free(temp); 
		}
	}
}

