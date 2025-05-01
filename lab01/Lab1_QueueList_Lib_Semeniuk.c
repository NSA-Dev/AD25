#include "Lab1_QueueList_Lib_Semeniuk.h"

/*
This function inserts a new student in the waiting line.
If the queue is already full, the function prints a message on the console
that informs the user that no more students can be inserted in the queue.
If the queue is not full, the function asks the user for the first name, the last name, and the matriculation number.
Then, it adds this student as the last element to the queue.

Parameters:
   head -> pointer to the first student of the waiting line

Returns: 
   The functions returns the first student of the waiting line.
*/
sElement* enqueue(sElement* head) {
    /*
    Since the number of elements to be supported is not given, I chose the memory limit.
    In case malloc fails, the user is notified that the queue is full and a NULL is returned.
    Otherwise a constant could be implemented to define a limit for people in our queue. But since
    it is not directly specified for this part, I made a choice to leave it out.  
    */

    sElement* element = (sElement*)malloc(sizeof(sElement)); // allocate struct memory
    if(element == NULL) {
        printf("Out of memory (the queue is full).\n");
        return NULL;  
    }
    /* Prompting user for data, same approach as in previous */
    printf("Enter student's first name (%d char limit): ", MAXNAME);
    getString(element->student.firstName);
    printf("Enter student's last name (%d char limit): ", MAXNAME);
    getString(element->student.lastName);
    printf("Enter student ID: ");
    element->student.matNo = getInt();
    element->next = NULL; // set the  pointer to the next element to NULL (since we always append to the end)
    
    /* Here the linking happens. If the head is not pointing anywhere, 
      then the element becomes the head. Otherwise, move to the end and assign there.
    */
    if(head == NULL) {
        head = element; 
    } else {
        sElement* current = head; // pointer which we iterate with
        while(current->next != NULL) {
            current = current->next; // In human: while we're not pointing nowhere, 
                                     // assign the address of the next one to the current
        }

        current->next = element; 
    }
	
    return head; 
}


/*
This function removes the first student from the waiting line.
If the queue is empty, the function prints a message to the console
that informs the user that the waiting list does not contain any students.
If the queue is not full, the function prints the full name and matriculation number of the first student of the waiting line to the console.
Second, it removes the student from the queue and frees the memory.

Parameters:
   head -> pointer to the first student of the waiting line

Returns: 
   The functions returns the first student of the waiting line.
*/
sElement* dequeue(sElement* head) {
    /* In case the head is not set the line is considered empty & NULL is returned. */
    if(head == NULL) {
        printf("The line is already empty.\n"); 
	    return NULL;
    }

    /* Print student's data */
    printf("Student: %s %s %lu dequeued.\n", head->student.firstName,
                                             head->student.lastName,
                                             head->student.matNo
                                             );

    /* Remove the student from the list */
    sElement* newHead = head->next; // otherwise, we copy address of the next and designate it as new head.
    free(head); // free the memory used by previous object.
    return newHead; // return ptr to the new head.  

}


/*
This function checks if the waiting line is empty.

Parameters:
   head -> pointer to the first student of the waiting line

Returns:
 - If the waiting line is empty, the function returns 0.
 - If there are students in the waiting line, the function returns 1.

*/
int isEmpty(sElement* head) {
	if(head == NULL) return 0;
    return 1; 
}


/*
This function counts the number of students in the waiting line and returns this number.

Parameters:
   head -> pointer to the first student of the waiting line

Returns:
 - Number of students in the waiting line.
 - If the waiting line is empty the function returns 0.
*/
int countElements(sElement* head) {
	int counter = 0;
	sElement* temp = head;
	while (temp != NULL) {
		counter++;
		temp = temp->next;
	}
	return counter;
}


/*
This function prints the full names and matriculation number of all students in the waiting line to the console.
The printing starts with the first student in the waiting line and prints the other students in the order of insertion.

Parameters:
   head -> pointer to the first student of the waiting line

Returns: None
*/
void printQueue(sElement* head) {
	if (head == NULL) {
		printf("Queue is empty.\n\n");
		return;
	}

	int numberStudent = countElements(head);
	sElement* temp = head;
	for (int i = 0; i < numberStudent; i++) {
		printf("Student %3d:\t%s\t%s\t%d\n", i + 1, temp->student.firstName, temp->student.lastName, temp->student.matNo);
		temp = temp->next;
	}
	printf("\n");
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
