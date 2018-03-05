//  Chris Tass-Parker 2015  
// heauristic.c 

#include "main.h"

// heuristic is the sum of the manhattan distances of the current state to the final state
double heuristic(int state[GAME_SIZE][GAME_SIZE]){
    
    double heuristic = INITIALISE;
    int i,
    j;
    
    for(i = 0; i<4; i++){
        for(j=0; j<4; j++){
            
            if(state[i][j] != 0) {
                heuristic += manhattan_dist(state[i][j], i, j);
            }
        }
    }
    return heuristic;
}

double manhattan_dist(int num, int x, int y){
    // we have the current value - num
    // we have the current value's position - x, y
    double dist;
    // find the final position (where it needs to be)
    int finX = finalX(num);
    int finY = finalY(num, finX);
    
    // calculate how many x and how many y steps away it is
    // = manhattan dist
    dist = abs(x - finX) + abs(y - finY);
    
    return dist;
}

// returns the x coordinate of a given number's final position
int finalX(int num){
    return num/GAME_SIZE;
}

// returns the y coordinate of a given number's final position
int finalY(int num, int row){
    return (num- row * GAME_SIZE);
}