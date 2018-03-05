//  Chris Tass-Parker 2015  
// initialise.c

#include "main.h"


// initialises the first node, reads in the file. 
// please note this doesn't guard against bad data. 
node_t initial_node(int argc, char *argv[]){

    FILE *fr = fopen(argv[1], "r");
    node_t initial; 

    // protects against no input file in cmd line argument 
    if(argc<2){
        printf(RED"No input file \n"C_RESET); 
        exit(EXIT_FAILURE);
    }
    
    // protect against empty file 
    if(fr == NULL){
        printf(RED"File read error: file empty\n"C_RESET);
        exit(EXIT_FAILURE);
    }

    int i, j, c;
    // initialise initial.state int array 
    for(i = 0; i < GAME_SIZE; i++)
    {
        for(j = 0; j < GAME_SIZE; j++)
        {
            fscanf(fr, "%d", &c);
            initial.state[i][j] = c;
        }
    }
    
    // initialise the core data of the initial node 
    initial.cost = INITIALISE;
    initial.heuristic = heuristic(initial.state);
    initial.f= INITIALISE_D;
    initial.prev = INITIALISE; 
    
    return initial;
}

// returns a node with all values set to 0; 
node_t blank_node(){
    node_t r; 
    
    r.cost = INITIALISE; 
    r. heuristic = INITIALISE_D; 
    r.f = INITIALISE_D; 
    r.prev = INITIALISE; 

    int i, j; 
    for (i=0; i<GAME_SIZE; i++){
        for(j=0; j<GAME_SIZE; j++){
            r.state[i][j] = 0; 
        }
    }
    return r; 
}

// initialises single dimentional array of size GAME_SIZE 
// - used for ACTIONS array
void init_actions_array(int ACTIONS[GAME_SIZE]){
    int i; 
    for(i = 0; i<4; i++){
        ACTIONS[i] = 0; 
    }
}

