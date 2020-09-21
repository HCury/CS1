#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
	int i;
	if(num_fragments <= 0 || fragment_length <= 0)
		return NULL;
	struct LonelyPartyArray *myLPA = malloc(sizeof(LonelyPartyArray));
	if(myLPA == NULL)
		return NULL;
	myLPA->num_fragments = num_fragments;
	myLPA->fragment_length = fragment_length;
	myLPA->num_active_fragments = 0;
	myLPA->size = 0;
	myLPA->fragments = malloc(sizeof(int*) * num_fragments);
		if( myLPA->fragments == NULL)
			free (myLPA);
	myLPA->fragment_sizes = malloc(sizeof(int) * num_fragments);
	if(myLPA->fragment_sizes == NULL)
	{
		free (myLPA->fragments);
		free (myLPA);
		return NULL;
	}
	for (i = 0; i < num_fragments; i++)
	{
		myLPA->fragments[i] = NULL;
		myLPA->fragment_sizes[i] = 0;
	}
	printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", num_fragments * fragment_length, num_fragments);
return myLPA;
}




LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
	//Freeing inside out
	int i;
	free (party->fragment_sizes);
	for(i = 0; i < party->num_fragments; i++)
	{
		if(party->fragments[i] != NULL){
			free(party->fragments[i]);
			party->fragments[i] = NULL;
		}
	}

	//Can free the pointer once every fragment is freed
	free(party->fragments);
	free(party);
	if( !party )
		return NULL;
	else
		printf("-> The LonelyPartyArray has returned to the void.\n");
  return NULL;
}



int set(LonelyPartyArray *party, int index, int key)
{

	int i, cell,fragmentArray;
	// First we check for a null pointer
	if(party == NULL){
		printf("-> Bloop! NULL pointer detected in set().\n");
		return LPA_FAILURE;
	}

	//Arithmetic for finding [1][2] as in the example
	cell = index % party->fragment_length;
	fragmentArray = index / party->fragment_length;

	// Then we test if it goes out of bounds or not
	if(index > party->num_fragments * party->fragment_length -1 || index<0){
		printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, fragmentArray, cell);
		return LPA_FAILURE;
	}

	// Then we can check if fragmentArray is null, if it is we can malloc
	if(party->fragments[fragmentArray] == NULL){
		party->fragments[fragmentArray] = malloc(sizeof(int) * party->fragment_length);
		printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n",fragmentArray, party->fragment_length, (fragmentArray) * party->fragment_length, (fragmentArray + 1) * party->fragment_length - 1);
		if(party->fragments[fragmentArray] == NULL)
			return LPA_FAILURE;
		for(i = 0; i < party->fragment_length; i++)
			party->fragments[fragmentArray][i] = UNUSED;
		party->num_active_fragments++;
	}
	if(party->fragments[fragmentArray][cell] == UNUSED){
		party->fragment_sizes[fragmentArray]++;
		party->size++;
	}
	party->fragments[fragmentArray][cell] = key;
return LPA_SUCCESS;
}



int get(LonelyPartyArray *party, int index)
{
	int fragmentArray, cell;
	// First checks for a null pointer
	if(party == NULL){
		printf("-> Bloop! NULL pointer detected in get().\n");
		return LPA_FAILURE;
	}

	//Arithmetic for finding [1][2] as in the example
	fragmentArray = index / party->fragment_length;
	cell = index % party->fragment_length;

	// Then we test if it goes out of bounds or not
	if(index > party->num_fragments * party->fragment_length - 1 || index < 0){
		printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, fragmentArray, cell );
		return LPA_FAILURE;
	}

	// Then we can check if fragmentArray is null
	if (party->fragments[fragmentArray] == NULL)
		return UNUSED;
  return party->fragments[fragmentArray][cell];
}



int delete(LonelyPartyArray *party, int index)
{

	int fragmentArray, cell;
	// First we check for a null pointer
	if(party == NULL){
		printf("-> Bloop! NULL pointer detected in delete().\n");
		return LPA_FAILURE;
	}

	//Arithmetic for finding [1][2] as in the example
	fragmentArray = index / party->fragment_length;
	cell = index % party->fragment_length;

	// Then we test if it goes out of bounds or not
	if(index > party->num_fragments * party->fragment_length - 1 || index < 0){
		printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, fragmentArray, cell );
		return LPA_FAILURE;
	}

	// Then we can check if fragmentArray is null / UNUSED.
	if(party->fragments[fragmentArray] == NULL )
		return LPA_FAILURE;

	// If its not unused we set it equal to unused then decrement size and fragment_sizes
	if(party->fragments[fragmentArray][cell] != UNUSED){
		party->fragments[fragmentArray][cell] = UNUSED;
		party->size--;
		party->fragment_sizes[fragmentArray]--;

	// Checks if all the cells of fragmentArray is 0. If it is, deallocate and lower active fragments to keep accurate count.
		if(party->fragment_sizes[fragmentArray] == 0){
			free (party->fragments[fragmentArray]);
			party->fragments[fragmentArray] = NULL;
			party->num_active_fragments--;
			printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n",fragmentArray, party->fragment_length, (fragmentArray) * party->fragment_length, (fragmentArray + 1) * party->fragment_length - 1);
		}
		return LPA_SUCCESS;
	}
	// Checks if cell is UNUSED after deallocating
	 if(party->fragments[fragmentArray][cell] == UNUSED)
	 	return LPA_FAILURE;
	return LPA_SUCCESS;
}


int printIfValid(LonelyPartyArray *party, int index){
	int fragmentArray, cell;
	if(party == NULL)
		return LPA_FAILURE;
	if(index > party->num_fragments * party->fragment_length - 1 || index < 0)
		return LPA_FAILURE;
	fragmentArray = index / party->fragment_length;
	cell = index % party->fragment_length;
	if(party->fragments[fragmentArray] == NULL )
		return LPA_FAILURE;
	if(party->fragments[fragmentArray][cell] == UNUSED)
		return LPA_FAILURE;
	printf("%d\n", party->fragments[fragmentArray][cell]);
	return LPA_SUCCESS;
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party){
	int i;
	// Check for null party (testcase15)
	if(party == NULL)
		printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray()\n");

	//Using a for loop to set fragment_sizes/fragments back to original form.
	for(i = 0; i < party->num_fragments; i++){
		if(party != NULL){
			free(party->fragments[i]);
			party->fragments[i] = NULL;
		}
		party->fragment_sizes[i] = 0;
	}

	//Size and num_active_fragments started at 0. Putting it back to 0.
	party->size = 0;
	party->num_active_fragments = 0;
	printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", party->num_fragments * party->fragment_length, party->num_fragments);
	return party;
}


int getSize(LonelyPartyArray *party){
	if(party == NULL)
		return -1;

		return party->size;
}

int getCapacity(LonelyPartyArray *party){
	if(party == NULL)
		return -1;

		return party->fragment_length * party->num_fragments;
}

int getAllocatedCellCount(LonelyPartyArray *party){
	if(party == NULL)
		return -1;

		return party->fragment_length * party->num_active_fragments;
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party){
	return (long long unsigned int)(sizeof(int)) * party->fragment_length * party->num_fragments;
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party){
	long long unsigned int bytes = 0;
	if(party == NULL)
		return bytes;

	// Add all that the pdf asked
	bytes += (long long unsigned int)(sizeof(LPA*) + sizeof(LPA));
	bytes += (long long unsigned int)(sizeof(int*) * party->num_fragments);
	bytes += (long long unsigned int)(sizeof(int) * party->num_fragments);
	bytes += (long long unsigned int)(sizeof(int) * party->num_active_fragments * party->fragment_length);
	return bytes;
}

double difficultyRating(void){
	return 4.0;
}
double hoursSpent(void){
	return 32.0;
}
