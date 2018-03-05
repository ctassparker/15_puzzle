/*
//  main.c
//  15_puzzle - IDA* and WIDA* implementation 
//
//  Created by Christopher Tass-Parker on 21/10/2015.
//  Student no: 541236
//  Username: tass
//  Tutor: Grady, Wed 10am 
//*/

#include "main.h"


int main(int argc, char *argv[]) {
    // count data needs to be long long ints to ensure support of ints >10^12
	long long int OUTD[OUTDATA_SIZE];

    // declare and input the initial game state into node 'initial'
    node_t initial;
    initial = initial_node(argc, argv);
    
    // print the initial state on screen. 
    printf(GREEN "Initial State:\n" C_RESET); 
    print_state(initial);

    // start the clock 
    clock_t tbegin = clock(); 

    // initiate IDA Control Loop 
	node_t r = idaControlLoop(initial, OUTD); 

    // stop the clock 
	clock_t tend = clock(); 

    // calculate time spent in seconds using the CLOCKS_PER_SEC macro from time.h
	double time_spent = (double)(tend - tbegin)/CLOCKS_PER_SEC; 

    // send data to the formatted output function 
	test_output(r, OUTD, time_spent); 

    return 0;   
}