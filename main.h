/*
//  main.h
//  15_puzzle
//
//  Christopher Tass-Parker 
//	541236
/ */
// C libraries used: 
#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
#include <limits.h> 
#include <time.h> 
#include <locale.h>

// ANSI colours for making the output pretty
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define C_RESET  "\x1b[0m"

// general definitions
#define GAME_SIZE 4
#define INITIALISE 0 
#define INITIALISE_D 0.0
#define COST 1
#define VECTOR 2

// zero position vector array lookup
#define XPOS 0
#define YPOS 1

// movement lookup for actions array 
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

// output array lookup
#define OUTDATA_SIZE 2
#define NGENERATED 0
#define NEXPANDED 1

typedef struct {
    // values keep track of a given instance
    int state[GAME_SIZE][GAME_SIZE];
    int cost; // current cost = g(n)
    double heuristic;
    double f; // f(n) = g(n) +h(n)
    // OPTIMISATION: 
    // keeps track of what the last move was
   	// in order to prevent 'circling'
    int prev; 

} node_t;

// initialising & input functions
node_t initial_node(int argc, char *argv[]);
void init_actions_array(int ACTIONS[GAME_SIZE]);
node_t blank_node();
void input(int);

// output functions
void print_state(node_t current_node);
void print_init_est(double est); 
void test_output(node_t r, long long int OUTD[OUTDATA_SIZE], double time_spent); 

// ida functions 
node_t idaControlLoop(node_t r, long long int OUTD[OUTDATA_SIZE]);
node_t idaStar(node_t node, double *thresh, double *threshp);
int actions(node_t node, int ACTIONS[GAME_SIZE]);

//heuristic and related functions
double heuristic(int state[GAME_SIZE][GAME_SIZE]);
double manhattan_dist(int num, int x, int y);
int finalX(int num);
int finalY(int num, int row);

// moving tiles
void moveUp(int STATE[][GAME_SIZE]);
void moveDown(int STATE[][GAME_SIZE]);
void moveLeft(int STATE[][GAME_SIZE]);
void moveRight(int STATE[][GAME_SIZE]);


// helpers
double findMin(double a, double b);
void findZero(int ZERO[VECTOR], int STATE[][GAME_SIZE]);
void copyArray(int STATE[GAME_SIZE][GAME_SIZE], node_t target);




