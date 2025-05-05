/**
 * Lab1_QueueList_Lib_Semeniuk.h
 * Submission by Nikita Semeniuk ID: 2722726
 * Singly linked list queue implementation for student records
 * 
 * Date 2025-05-01

 */
#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 25


typedef struct sStudent {
	char firstName[MAXNAME];
	char lastName[MAXNAME];
	unsigned long matNo;
} sStudent;

typedef struct sElement {
	sStudent student;
	struct sElement* next;
} sElement;

int countElements(sElement* head);
sElement* enqueue(sElement* head);
sElement* dequeue(sElement* head);
int isEmpty(sElement* head);
void printQueue(sElement* head);

/* ***** HELPER FUNCTIONS ***** */
int getInt();
void getString(char string[MAXNAME]);
