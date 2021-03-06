// Name: Deen Aariff
// Student ID: W1103023
// Assignment: #3 Sets, Arrays, and Hash Tables
// Class: COEN 12L T 2:15-5:00
// Date: 10/25/15

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"set.h"
#include<string.h>
#include<assert.h>

// define set data structure
struct set {
	int count;
	int len;
	char **words;
	char *status;
		// E: empty
		// F: filled
		// P: previously filled
};

// create set with paramter of maximum elements
SET *createSet(int maxELTS) {
	SET *sp;
	// allocate size for a set
	sp = malloc(sizeof(SET));
	// allocate memory for sp->words 
	sp -> words = malloc(maxELTS*sizeof(char *));
	sp -> status = malloc(maxELTS*sizeof(char));
	sp -> len = maxELTS;
	// Set all elements in status to Empty
	for (int i = 0; i < sp->len; i++)
		sp->status[i] = 'E';
	// initialize lenght and count	
	sp -> count = 0;
	return sp;
}

// destructor for set
void destroySet (SET *sp) {
	// check if sp is null
	assert(sp != NULL);
	// count through each index of sp->words and set to null
	for (int i = 0; i < sp -> count; i++) {
		free(sp->words[i]);
	}
	// free sp->words 
	assert(sp->words != NULL);
	free(sp->words);
	// free sp 
	free(sp);
}

// Return number of elements in string
int numElements(SET *sp) {
	return sp->count;
};

unsigned hashString(char *s) {
	// set hash to 0 
	unsigned hash = 0;
	// While not end of string 
 	while (*s != '\0')
 		// unique hash value from string
 		hash = 31 * hash + *s ++;
 	return hash;
}

// Find element passed in paramater
// If found return true
// If not found return false
static int findElement (SET *sp, char *elt, bool *found) {
	int hash = hashString(elt) % sp->len;
	// Holds value of first previously filled
	int store;
	// Whether previously filled value encountered
	bool foundStore = false; 
	while(hash <= sp->len) {
		// If value is empty then return index
		if (sp->status[hash] == 'E') {
			// If previously dleted is true then
			if (foundStore == true)
				// return first perviously dleted value
				return store;
			*found = false;
			return hash;
		}
		// If value is continue probe
		else if(sp->status[hash] == 'F') {
			// If filled value is value searching for return
			if(strcmp(elt,sp->words[hash]) == 0) {
				// set found to true
				*found = true;
				return hash;
			}
			// increment hash by linear probing
			hash++;
		}
		// If value is previously filled then continue probe
		else if(sp->status[hash] == 'P') {
			// if first previously delted value
			if (foundStore == false) {
				// Store index of first previously delted value
				store = hash;
				// set found to true
				foundStore = true;
			}
			hash++;
		}
	}
	// set found to false
	*found = false;
	return 0;
};

// Checks if element is present
// Returns boolean
bool hasElement(SET *sp, char *elt) {
	bool found;
	// Call find element 
	findElement(sp, elt, &found);
	return found;
};

// If element is not found, add element
bool addElement(SET *sp, char *elt){
	bool found; 
	// find index by calling findElement
	assert(sp != NULL || sp->words != 0);
	int index = findElement(sp, elt, &found);
	// if element exists return false
	if (found == true) 
		return false;
	else {
		// assign value for elt
        	elt = strdup(elt);
        	// set index to elt
		sp->words[index] = elt;
        	// Set value to filled 
		sp->status[index] = 'F';
		// increment count
		sp->count++;
		return true;
	}
};

// Remove element in Data Set
bool removeElement(SET *sp, char *elt) {
	bool found; 
	// find index by calling findElement
	int index = findElement(sp, elt, &found);
	// if element does not exist return false
	if (found == false) 
		return false;
	else {
        // Set value to previously filled 
		sp->status[index] = 'P';
		// decrement count
		sp->count--;
		return true;
	}
};
