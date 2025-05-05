/**
 * Lab1_QueueArray_Lib_Semeniuk.c
 * Submission by Nikita Semeniuk ID: 2722726
 * Array queue implementation for student records
 * 
 * Date 2025-05-01

 */
#include "Lab1_QueueArray_Lib_Semeniuk.h"


/*
This function inserts a new student in the waiting line.
If the queue is already full, the function prints a message to the console
that informs the user that no more students can be inserted in the queue.
If the queue is not full, the function asks the user for the first name, the last name, and the matriculation number. 
Then, it adds this student as last element to the queue.

Parameters: 
   waitingLine -> Array storing the students

Returns: None
*/
void enqueue(sStudent waitingLine[]) {

    int lineSize = countElements(waitingLine); // get last available position in the array
    
    if(lineSize == MAXARRAY) printf("The line is full, no more students can be queued up.\n");
    else {
        sStudent element; // Create a new student for insertion into the array

        /*Prompt the user to enter student data & assign it to the struct fields */
        printf("Enter student's first name (%d char limit): ", MAXNAME);
        getString(element.firstName);
        printf("Enter student's last name (%d char limit): ", MAXNAME);
        getString(element.lastName);
        printf("Enter student ID: ");
        element.matNo = getInt();


        waitingLine[lineSize] = element; // Assign the struct to the current last index in the queue  
    }


	return;
}


/*
This function removes the first student from the waiting line.
If the queue is empty, the function prints a message to the console
that informs the user that the waiting list does not contain any students.
If the queue is not full, the function first prints the full name and matriculation number of the first student of the waiting line to the console.
Second, it removes the student from the queue by moving all students forward one place in the array.

Parameters:
   waitingLine -> Array storing the students

Returns: None
*/
void dequeue(sStudent waitingLine[]) {
    /* If the que is not empty perform remove and shift otherwise notify the user. */
    if(isEmpty(waitingLine) != 0) {
        int count = countElements(waitingLine); // returns the free index
        
        /* Printing the data of the student to be removed */
        printf("Student: %s %s ID:%lu dequeued.\n", waitingLine[0].firstName,
                                                    waitingLine[0].lastName,
                                                    waitingLine[0].matNo
                                                    );        

        /* Go through all elements-1 (because count returns free index) */
        for(int i = 0; i < count-1; i++) {
            waitingLine[i] = waitingLine[i+1]; // Assign next elem to the current position
        }
        /* Zero out all of the entries in the last element making it available */
        waitingLine[count-1].firstName[0] = '\0';
        waitingLine[count-1].lastName[0] = '\0';
        waitingLine[count-1].matNo = 0; 
    } else {
        printf("Cannot dequeue. The queue is empty. \n");
    }
    return;
}


/*
This function checks if the waiting line is empty.

Parameters:
   waitingLine -> Array storing the students

Returns: 
 - If the waiting line is empty, the function returns 0.
 - If there are students in the waiting line, the function returns 1.

*/
int isEmpty(sStudent waitingLine[]) {
    // If the starting element contains no valid id, then the queue is empty,
    // this is fast but can be potentially unsafe, since it relies on outside logic.
    // As alternative I could scan the entire array using countElements[], but this 
    // is slow.  
    if(waitingLine[0].matNo == 0 && waitingLine[0].firstName[0] == '\0'
                                 && waitingLine[0].lastName[0] == '\0') return 0; 
    
    return 1;
}


/*
This function counts the number of students in the waiting line and returns this number.

Parameters:
   waitingLine -> Array storing the students

Returns: 
 - Number of students in the waiting line. 
 - If the waiting line is empty the function returns 0.
*/
int countElements(sStudent waitingLine[]) {
	int counter = 0;
	for (counter = 0; counter < MAXARRAY; counter++) {
		if (waitingLine[counter].matNo == 0)
			break;
	}
	return counter;
}


/*
This function prints the full names and matriculation number of all students in the waiting list to the console. 
The printing starts with the first student in the waiting line and prints the other students in the order of insertion.

Parameters:
   waitingLine -> Array storing the students

Returns: None
*/
void printQueue(sStudent waitingLine[]) {
	int numberStudents = countElements(waitingLine);
    if(numberStudents == 0) printf("The line is empty.\n");
	for (int i = 0; i < numberStudents; i++) {
		printf("Student %3d:\t%s\t%s\t%ld\n", i + 1, waitingLine[i].firstName, waitingLine[i].lastName, waitingLine[i].matNo);
	}
	return;
}


/* ***** HELPER FUNCTIONS ***** */

/*
* Function reads a positive integer safely from the keyboard.
*
* Parameters: None.
*
* Returns: A positive integer read from the keyboard.
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


/*
* Function reads a string safely from the keyboard.
*
* Parameters: A string in which the string read from the keyboard is stored.
*
* Returns: None
*/
void getString(char string[MAXNAME]) {
	int val = 0;
	while (1) {
		if (scanf("%s", string) != 1) {
			while (getchar() != '\n');
			printf("Not a valid string.\n");
		}
		else {
			while (getchar() != '\n');
			break;
		}
	}
	return;
}
