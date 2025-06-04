#pragma once

#include "HashAHLib.h"

/**
* @brief Function reads an integer value safely from the keyboardand.
*
* @param Parameter
* None.
*
* @return Function returns the integer value.
*/
int getInt() {
	int val = 0;
	while (1) {
		if ((scanf("%d", &val) != 1) || (val < 0)) {
			while (getchar() != '\n');
			printf("Not a valid integer.\n");
		}
		else {
			while (getchar() != '\n');
			break;
		}
	}
	return val;
}

/**
* @brief Function reads a string value safely from the keyboardand.
*
* @param string The parameter string is transferred via CbR and contains the read string after it has been read in.
*
* @return
* None.
*/

void getString(char string[]) {
    while (1) {
        if (fgets(string, MAX_STRING, stdin) == NULL) {
            printf("Error reading input.\n");
            continue;
        }
        
        // Remove trailing newline if present
        size_t len = strlen(string);
        if (len > 0 && string[len-1] == '\n') {
            string[len-1] = '\0';
        }
        
        // Check if input was just whitespace
        if (string[0] != '\0') {
            break;
        }
        printf("Input cannot be empty. Try again.\n");
    }
}

/*
Function calculates the hash value for the passed key.
Function return the calculated hash value.
*/
int hashing(int key) {
	return key % MAX_ARRAY;
}



/**********************************************************************************************************************
Prototypes for address hashing
**********************************************************************************************************************/
/*
Function creates a new entry in the hash table or if the key already exists overwrites the value with the passed value.
Function receives the hash table and the key-value-pair to be inserted.
Function returns the number of collisions or -1 in case the table is full 
*/
int putAH(sElementAH hashtableAH[MAX_ARRAY], int key, char value[MAX_STRING]) {
	// Get table index to look for
	int i = hashing(key);
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
			if(hashtableAH[i].key == -1) {
				hashtableAH[i].key = key;
				strcpy(hashtableAH[i].value, value);
				return colCount;  
			}
		// Found the same key 
			else if(hashtableAH[i].key == key) {
				strcpy(hashtableAH[i].value, value);
				return colCount;  
			};
		// No space, no key found -> collision 
		i = (i + 1) % MAX_ARRAY; // wrap around array bounds 
		colCount++; 		 
	}	  
 	return -1; 
}

/*
Function searches for the entry in the hash table having the passed key.
Function returns the value of entry or NULL if the key does not exist in the hash table.
*/
char* getAH(sElementAH hashtableAH[MAX_ARRAY], int key) {
	int i = hashing(key);
	int startIndex = i; 
	
	// search the array, if arrived at the start return NULL
	do {
		// keys match, return value
		if(hashtableAH[i].key == key) return hashtableAH[i].value;  
	
		// empty key -> return null
		if(hashtableAH[i].key == -1) return NULL;
		
		// adjust index
		i = (i + 1) % MAX_ARRAY; 
	} while(i != startIndex);
	
	return NULL; 
}

/*
Function searches for the entry in the hash table having the passed key.
If it finds an entry the function deletes it from the hash table.
*/
void deleteAH(sElementAH hashtableAH[MAX_ARRAY], int key) {
	int i = hashing(key);
	int startIndex = i; 
	
	do {
		// key found, delete entry from the table
		if(hashtableAH[i].key == key) {
			hashtableAH[i].key = -1;
			hashtableAH[i].value[0] = '\0';
			return; 
		}	
		// adjust index
		i = (i + 1) % MAX_ARRAY; 
	
	} while (i != startIndex);
	 
}

/*
Function prints the hash table.
If a field in the array is empty, it prints “empty”.
*/
void printHashTableAH(sElementAH hashtableAH[MAX_ARRAY]) {
	// print the heading
	printf("| %-4s | %-30s |\n", "KEY", "VALUE");  
    printf("|------|--------------------------------|\n"); 
	// print the table elements
	for(int i = 0; i < MAX_ARRAY; i++) {
		if(hashtableAH[i].key == -1) printf("NULL		%s\n", "<EMPTY>"); 
		else {
			printf("%d		%s\n", hashtableAH[i].key, hashtableAH[i].value);
		}
	}
}

/*
Function gets a file pointer to a csv-file which contains some key-value-pairs.
Additionally, the function gets a hash table in which the function inserts the key-value-pairs in the csv-file.
*/
void readCSVAH(FILE* fP, sElementAH hashtableAH[MAX_ARRAY]) {
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

		putAH(hashtableAH, key, string);
	}

	return;
}

