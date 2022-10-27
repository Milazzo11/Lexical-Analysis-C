// Functions to initialize and display transition matrix.
//
// FILE: matrix.c
// 
// @author - Max Milazzo
// @email - mam9563@rit.edu
///////////////////////////////////////////////////////////



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"



/// Displays a visual representation of the finite state machine.
///
/// @param FSM - the finite state machine
/// @param size - contains the number of states

void print_FSM(State * FSM, int size) {

    printf("Scanning using the following matrix:\n ");


    for (int i = 0; i < NUM_CLASSES; ++i) {
    // displays the number classes for different text characters
        
        if (i < 10)
            printf(" ");

        printf("   %d", i);

    }


    printf("\n");


    for (int j = 0; j < size; ++j) {

        if (j < 10)
            printf(" ");

        printf("%d", j);
        

        for (int k = 0; k < NUM_CLASSES; ++k) {
        // displays FSM data

            int transition = FSM[j].transition[k];
            char operation = FSM[j].operation[k];

            if (transition < 10 && transition != ERR_STATE)
                printf(" ");

            printf("  %d%c", transition, operation);

        }

        printf("\n");
            
    }

}



/// Builds states not defined in file (fills in "empty" states).
/// All transitions go to the ERR_STATE and all operations are DISCARD.
///
/// @param FSM - the finite state machine
/// @param built_states - holds information about which states have been built
/// @param size - contains the number of states

void build_empties_FSM(State * FSM, int * built_states, int size) {


    for (int i = 0; i < size; ++i) {

        if (built_states[i] == 0) {

            for (int j = 0; j < NUM_CLASSES; ++j) {

                FSM[i].transition[j] = ERR_STATE;
                FSM[i].operation[j] = DISCARD;
                // sets all "empty" state transitions to the ERR_STATE
                // sets all "empty" state operations as DISCARD

            }

        }

    }

}



/// Uses data from file to construct a single state in the FSM.
///
/// @param buf - the biffer containing the current line from file
/// @param FSM - the finite state machine
/// @param built_states - holds information about which states have been built

void build_state_FSM(char * buf, State * FSM, int * built_states) {

    char * res = strtok(buf, " \t");
    int index = atoi(res);
    // gets state index

    built_states[index] = 1;
    // marks state has built

    int cur_index, transition;
    char operation;
    // holds temporary state data

    int past_indicies[NUM_CLASSES] = {0};
    // holds information about which transitions have been built

    res = strtok(NULL, " \t");


    while (res != NULL) {
    // loops through line using strtok to get data split by whitespace

        sscanf(res, "%d/%d%c", &cur_index, &transition, &operation);
        // gets FSM data from specified format

        FSM[index].transition[cur_index] = transition;
        FSM[index].operation[cur_index] = operation;
        past_indicies[cur_index] = 1;
        // updates FSM state

        res = strtok(NULL, " \t");

    }


    for (int i = 0; i < NUM_CLASSES; ++i) {

        if (past_indicies[i] == 0) {

            FSM[index].transition[i] = ERR_STATE;
            FSM[index].operation[i] = DISCARD;
            // sets all non-defined transitions to go to ERR_STATE
            // sets all non-defined operations as DISCARD
            
        }

    }

}
