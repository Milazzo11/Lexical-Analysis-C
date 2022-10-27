// Driver program to tokenize input and construct and use a FSM
//
// FILE: tokenize.c
// 
// @author - Max Milazzo
// @email - mam9563@rit.edu
///////////////////////////////////////////////////////////



#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenize.h"



/// Main function to read in FSM file and call FSM functions and tokenize text.
///
/// @param argc - number of command line arguments
/// @param argv - command line arguments
/// @return EXIT_SUCCESS if the program runs without error or EXIT_FAILURE

int main(int argc, char * argv[]) {
    
    if (argc != 2) {

        fprintf(stderr, "usage: ./tokenize tmfile\n");
        return EXIT_FAILURE;
        // prints usage message and exits program

    } else {

        FILE * fp;

        fp = fopen(argv[1], "r");

        if (fp == NULL) {

            perror(argv[1]);
            return EXIT_FAILURE;
            // file error

        }
        
        char * buf = NULL;
        size_t len = 0;
        // buffer and buffer length variables

        int line_iter = 0;
        // counter to get data on first three lines

        State * FSM;
        // finite state machine

        int * built_states;
        // holds data about which FMS states have been built

        int start, accept, size;
        // starting state, accepting state, number of states


        while (getline(&buf, &len, fp) > 0) {
        // loops through lines of file

            if (buf[0] != '#') {

                if (line_iter < 3) {

                    char * tok = strtok(buf, " \t");

                    if (strcmp(tok, "states") == 0) {
                    
                        char * spt = strtok(NULL, " \t");
                        size = atoi(spt);
                        // gets number of states

                        FSM = (State *) malloc(sizeof(State) * size);
                        built_states = (int *) calloc(size, sizeof(int));
                        // allocates memory using state size data

                    } else if (strcmp(tok, "start") == 0) {

                        start = atoi(strtok(NULL, " \t"));
                        // gets start state

                    } else if (strcmp(tok, "accept") == 0) {

                        accept = atoi(strtok(NULL, " \t"));
                        // gets accepting state

                    }

                    line_iter++;

                } else {

                    build_state_FSM(buf, FSM, built_states);

                }

            }

        }


        fclose(fp);

        build_empties_FSM(FSM, built_states, size);
        // builds states not defined in file

        print_FSM(FSM, size);
        read_stdin(FSM, start, accept);
        // displays FSM and gets input to tokenize

        free(FSM);
        free(built_states);
        // frees dynamically allocated memory

        if (buf != NULL)
            free(buf);
            // frees buffer if needed

    }

    return EXIT_SUCCESS;

}
