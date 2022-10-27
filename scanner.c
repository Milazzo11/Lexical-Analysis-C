// Uses transition matrix to scan and classify input.
//
// FILE: scanner.c
// 
// @author - Max Milazzo
// @email - mam9563@rit.edu
///////////////////////////////////////////////////////////



#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tokenize.h"



/// Runs through the FMS for a single input.
///
/// @param FSM - the finite state machine
/// @param cur - pointer to the current state index of FSM
/// @param w_index - pointer to index of next character in the text token
/// @param token - holds the text in the token
/// @param ch - the current character being read

void run_FSM(State * FSM, int * cur, int * w_index, char token[TOK_SIZE], int ch) {

    int cc_index;
    char operation;
    // temporary values to hold FSM data

    if (ch == ' ' || ch == '\t') {
    // checks if whitespace

        cc_index = CC_WS;

    } else if (ch == '\n') {
    // checks if newline

        cc_index = CC_NL;
        
    } else if (isalpha(ch) || ch == '_') {
    // checks if alphabet character or '_'

        cc_index = CC_ALPHA;

    } else if (ch == '0') {
    // checks if 0

        cc_index = CC_ZERO;

    } else if (ch >= '1' && ch <= '7') {
    // checks if value is 1-7

        cc_index = CC_OCTAL;

    } else if (ch == '8' || ch == '9') {
    // checks if value is 8 or 9

        cc_index = CC_DECIMAL; 

    } else if (ch == '/') {
    // checks if '/'

        cc_index = CC_SLASH;

    } else if (ch == '*') {
    // checks if '*'

        cc_index = CC_STAR;

    } else if (ch == '+' || ch == '-' || ch == '%') {
    // checks if character is an arithmetic operator

        cc_index = CC_ARITH;

    } else if (isascii(ch)) {
    // checks if character is any other ASCII-representable value

        cc_index = CC_OTHER;

    } else if (ch == EOF) {
    // checks for EOF

        cc_index = CC_EOF;

    } else {
    // if anything else, set to "ERROR class"

        cc_index = CC_ERROR;

    }
    
    operation = FSM[*cur].operation[cc_index];
    *cur = FSM[*cur].transition[cc_index];
    // updates current state and operation using FSM

    printf("%d ", *cur);
    
    if (operation == SAVE) {
    // saves character in token for "SAVE" operation

        token[*w_index] = ch;
        ++(*w_index);

    }

}



/// Reads text from standard input and feeds it to the finite state machine.
/// The state transitions made and the tokens found in input will be displayed.
///
/// @param FSM - the finite state machine
/// @param start - the starting state index
/// @param accept - the accepting state index

void read_stdin(State * FSM, int start, int accept) {
    
    int ch;
    int cur = start;
    int next_index = 0;
    char token[TOK_SIZE];
    // holds input data

    int err = 0;
    // holds error state (0 means no error, 1 means error)

    printf("%d ", start);


    while ((ch = getchar()) != EOF) {

        if (!err)
            run_FSM(FSM, &cur, &next_index, token, ch);

        if (cur == accept && err == 0) {
        // displays data when token is recognized

            token[next_index] = '\0';

            printf("recognized '%s'\n", token);
            printf("%d ", start);
            
            cur = start;
            next_index = 0;

        } else if (cur == ERR_STATE) {

            err = 1;
            // error set to 1 (true) when ERR_STATE encountered

        }

        if (err == 1 && (ch == ' ' || ch == '\t' || ch == '\n')) {
        // displays rejected state info when error is true and WS or NL found
        // WS = whitespace, NL = newline
        
            token[next_index] = '\0';

            printf("rejected\n");
            printf("%d ", start);

            cur = start;
            next_index = 0;
            err = 0;

        }

    }


    run_FSM(FSM, &cur, &next_index, token, ch);
    printf("EOF\n");
    // runs FMS one last time and displays "EOF" on end of input

}
