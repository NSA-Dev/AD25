#include <stdio.h>
#include <stdlib.h>
#include "utils.h"




void main(void) {
	char string[MAX_STRING];
	record_t charStats[MAX_STRING]; 
	
	getString(string); // read a string   
	//countChar(string); // count all chars and record them into charStats
	
	
	// Print ASCII and BIN
	for(int i = 0; string[i] != '\0'; i++) {
		printf("%c - %d - ", string[i], string[i]);
		printBin(string[i]);
		putchar('\n');
		
	} 
	
	// Print bin string
	for(int i = 0; string[i] != '\0'; i++) {
		printBin(string[i]);
	}
	  putchar('\n'); 
} 
