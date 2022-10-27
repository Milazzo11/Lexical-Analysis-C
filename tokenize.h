// Tokenizer FMS program header file.
//
// FILE: tokenize.h
//
// @author - Max Milazzo
// @email - mam9563@rit.edu
///////////////////////////////////////////////////////////



#ifndef TOKENIZE
#define TOKENIZE


#include "classes.h"


// defines global variables used by program
#define TOK_SIZE    80
#define ERR_STATE   -1
#define SAVE        's'
#define DISCARD     'd'



// defines a new type "State" as a stuct holding transition/operation arrays
// a State type will hold all data for a finite state machine
typedef struct {

    int transition[NUM_CLASSES];
    char operation[NUM_CLASSES];

} State;



/// Uses data from file to construct a single state in the FSM.
///
/// @param buf - the biffer containing the current line from file
/// @param FSM - the finite state machine
/// @param built_states - holds information about which states have been built

void build_state_FSM(char * buf, State * FSM, int * built_states);



/// Builds states not defined in file (fills in "empty" states).
/// All transitions go to the ERR_STATE and all operations are DISCARD.
///
/// @param FSM - the finite state machine
/// @param built_states - holds information about which states have been built
/// @param size - contains the number of states

void build_empties_FSM(State * FSM, int * built_states, int size);



/// Displays a visual representation of the finite state machine.
///
/// @param FSM - the finite state machine
/// @param size - contains the number of states

void print_FSM(State * FSM, int size);



/// Reads text from standard input and feeds it to the finite state machine.
/// The state transitions made and the tokens found in input will be displayed.
///
/// @param FSM - the finite state machine
/// @param start - the starting state index
/// @param accept - the accepting state index

void read_stdin(State * FSM, int start, int accept);



#endif
