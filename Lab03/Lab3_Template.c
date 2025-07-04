#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "HashAHLib.h"
#include "Lab3_HashCHLib.h"
#define MAX_OPTIONS 4 // max currently available options for hashing 

int main() {
	//Variables
	int choice = 0;
	int key = -1;
	char value[MAX_STRING] = { 0 };
	char* valuePointer = NULL;
	int counter=0;
	int (*hashMethod) (int) = NULL; // pointer to the currently used hashing method
	int hashMethod_choice = 1;  // user choice for hashing method (default 0 - mod)
	int freeMem = 0; // flag to indicate if cleanup is needed (see outer case 2) 

	//Open csv-file
	FILE* fP = NULL;
	fP = fopen("students.csv", "r");
	if (fP == NULL) {
		printf("CSV file could not be opend.\n");
		exit(1);
	}

	//Welcome and choice of collision strategy
	printf("Welcome to our Hashing program!\n");
	// Select hashing algorithm before proceeding
	printf("Please, select Hashing method:\n");
	printf("Available options:\n1: mod (default)\n2: mid square\n3: multiplication\n4: XOR shift\n");
	hashMethod_choice = getInt();
	// adjust function pointer to user choice  
	if(hashMethod_choice > MAX_OPTIONS || hashMethod_choice == 0) {
		printf("Selected option is unavailable. Reseting to default: mod\n");
		hashMethod_choice = 1;
		hashMethod = hashing;
	} else if (hashMethod_choice == 1) {
		hashMethod = hashing;
	} else if (hashMethod_choice == 2) {
		hashMethod = hash_midsquare;
	} else if (hashMethod_choice == 3) {
		hashMethod = hash_mult;
	} else if (hashMethod_choice == 4) {
		hashMethod = hash_XOR;
	} else {
		hashMethod = hashing; // set to default for unrecognized input
	} 
			
	printf("What kind of collision strategy do you prefer?\n1: Address Hashing\n2: Chained Hashing\nAny other choice: exit program\n");
	choice = getInt();
	// set default hashing method
	hashMethod = hashing; 

	switch (choice) {
	case 1:
		// ;
		//Create a hash table and initialize it
		sElementAH hashtableAH[MAX_ARRAY];
		for (int i = 0; i < MAX_ARRAY; i++) {
			hashtableAH[i].key = -1;
			strcpy(hashtableAH[i].value, "");
		}

		//Read in the key-value-pairs from the csv-file and print the hash table
		readCSVAH(fP, hashtableAH, hashMethod);
		printHashTableAH(hashtableAH);

		//User can choose what to do next
		printf("OK, lets do Hashing using Address Hashing strategy:-)\n");
		do {
			// Print currently selected method used for Hash calculations
			switch(hashMethod_choice) {
			case 1:
				printf("Hashing method -> mod \n");
				break;
			case 2:
				printf("Hashing method -> mid square\n");
				break;
			case 3:
				printf("Hashing method -> multiplication\n");
				break;
			case 4:
				printf("Hashing method -> XOR shift\n");
				break;
			}
			printf("What do you like to do?\n1: Adding new element\n2: Searching for an element\n3: Delete key\nAny other choice: exit program\n");
			choice = getInt();
			switch (choice) {
				//Adding a new element to the hash table
			case 1:
				printf("Type in the key: \n");
				key = getInt();
				printf("\nType in the value: \n");
				getString(value);
				counter = putAH(hashtableAH, hashMethod, key, value);
				printHashTableAH(hashtableAH);
				printf("There were %d collision(s).\n", counter);
				break;
				//Searching for an element
			case 2:
				printf("Type in the key: \n");
				key = getInt();
				valuePointer = getAH(hashtableAH, hashMethod, key);
				if (valuePointer == NULL)
					printf("Key not found in hashtable\n");
				else
					printf("Value is %s\n", valuePointer);
				valuePointer = NULL;
				break;
				//Delete a key-value pair if it exists
			case 3:
				printf("Type in the key: \n");
				key = getInt();
				deleteAH(hashtableAH, hashMethod, key);
				printHashTableAH(hashtableAH);
				break;

			default:
				return 0;
			}
		} while (1);
		break;
	case 2:
		//Create a hash table and initialize it
		sElementCH hashtableCH[MAX_ARRAY];
		for (int i = 0; i < MAX_ARRAY; i++) {
			hashtableCH[i].next = NULL;
			hashtableCH[i].key = -1;
			strcpy(hashtableCH[i].value, "");
		}
		//Read in the key-value-pairs from the csv-file and print the hash table
		readCSVCH(fP, hashtableCH, hashMethod); // TODO
		printHashTableCH(hashtableCH); // TODO 
		do {
			// Print currently selected method used for Hash calculations
			switch(hashMethod_choice) {
			case 1:
				printf("Hashing method -> mod \n");
				break;
			case 2:
				printf("Hashing method -> mid square\n");
				break;
			case 3:
				printf("Hashing method -> multiplication\n");
				break;
			case 4:
				printf("Hashing method -> XOR shift\n");
				break;
			}
			printf("What do you like to do?\n1: Adding new element\n2: Searching for an element\n3: Delete key\nAny other choice: exit program\n");
			choice = getInt();
			switch (choice) {
				//Adding a new element to the hash table
			case 1:
				printf("Type in the key: \n");
				key = getInt();
				printf("\nType in the value: \n");
				getString(value);
				counter = putCH(hashtableCH, hashMethod, key, value);
				printHashTableCH(hashtableCH);
				printf("There were %d collision(s).\n", counter);
				break;
				//Searching for an element
			case 2:
				printf("Type in the key: \n");
				key = getInt();
				valuePointer = getCH(hashtableCH, hashMethod, key);
				if (valuePointer == NULL)
					printf("Key not found in hashtable\n");
				else
					printf("Value is %s\n", valuePointer);
				valuePointer = NULL;
				break;
				//Delete a key-value pair if it exists
			case 3:
				printf("Type in the key: \n");
				key = getInt();
				deleteCH(hashtableCH, hashMethod, key);
				printHashTableCH(hashtableCH);
				break;

			default:
				return 0;
		}
		} while (1);
		break;
	default:
		// free resources in Case chained addressing was used
		if(freeMem) freeTableCH; 
		//Close file
		if (fP != NULL)
			fclose(fP);
		return 0;
	}
}
