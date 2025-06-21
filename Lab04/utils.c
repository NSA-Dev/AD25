#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils.h"

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


char* countChar(char* string) {
		do {
			record_t current; 
			current.letter = *string;
			current.count += 1;  
		
		} while(*string != '\0');
		
}

void printBin(char c) {
	for(int i = 7; i >= 0; --i) {
			putchar((c & (1 << i)) ? '1' : '0'); 
	}

}
