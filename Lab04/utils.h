#ifndef UTILS_H
#define UTILS_H

#define MAX_STRING 100 
// Struct to store letter and its count 
typedef struct {
	char letter;
	int count;
} record_t; 


void getString(char string[]);
char* countChar(char* string);
void printBin(char c); 

#endif 
