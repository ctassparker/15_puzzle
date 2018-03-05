// C Tass-Parker 541236
// helpers

#include "main.h"

// find the minimum of two values 
double findMin(double a, double b){
if (a<b){
		return a; 
	}
	else{
		return b; 
	}
}

// locates the x and y coordinates of the zero 
// tile in a given state and saves positions
// in a small int array. 
void findZero(int ZERO[VECTOR], int STATE[][GAME_SIZE]){
	int i, j; 
		for(i = 0; i<4; i++){
			for(j=0; j<4; j++){

			if(STATE[i][j] == 0){
			ZERO[XPOS] = j; 
			ZERO[YPOS] = i; 
    		// printf(RED "j %d i %d\n" C_RESET, ZERO[X], ZERO[Y]);
			break; 
			}	 
		}
	}
}

// copies a state array into a target node's state array
void copyArray(int STATE[GAME_SIZE][GAME_SIZE], node_t target){
	int i, j; 
	for(i = 0; i<4; i++){
    	for(j=0; j<4; j++){
    		target.state[i][j] = STATE[i][j]; 
    	} 
    }

}

