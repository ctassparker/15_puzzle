//  Chris Tass-Parker 2015  
// IDA functions
// includes control loop & recursive function
// plus game - move functions 

#include "main.h" 

// global variables are the neatest way i could decifer to deal with 
// the counters through the recursive functions. 
long long int generated = INITIALISE; 
long long int expanded = INITIALISE; 

// IDA control loop 

node_t idaControlLoop(node_t ni, long long int OUTD[OUTDATA_SIZE]){
	// calculate initial threshold 
	double thresh = heuristic(ni.state);

	node_t r = blank_node(); 

	// expected output 
	print_init_est(thresh); 
	printf(YELLOW"Threshold: "); 


	while(r.f == 0.0){
		// set the B' to INT_MAX (infinity) 
		double threshp = INT_MAX-1;

		// print the threshold of the current loop 
     	printf("%.0f ", thresh); 

     	// call recursive idaStar function
    	r = idaStar(ni, &thresh, &threshp);

    	// if idaStar returns f(n)=0, threshold is increased and
    	// the while loop continues 
    	if (r.f == 0.0){
    		thresh = threshp;
    	}

	}

	// OUTD is my way of returning output data to main to call output function
	OUTD[NGENERATED] = generated; 
	OUTD[NEXPANDED] = expanded; 
	return r; 
}

node_t idaStar(node_t node, double *thresh, double *threshp){
	
	// creates an actions array for the current state and 
	// works out what possible moves can be made, returns
	// a, number of actions for the for loop guard. 
	int ACTIONS[GAME_SIZE],
		a = actions(node, ACTIONS), 
		i; 
	node_t r = blank_node();
	// increment generated node
	generated ++; 

	for(i=0; i<a; i++){
		// all four if statements use identical logic, commenting 
		// will only be in the first 'up' action as it applies 
		// to all other statements 

		// if guard protects against doing exactly what the 
		// last move was, which could make the algorithm circle 
		if((ACTIONS[i] == UP)&&(node.prev != DOWN)){
			// generate a new node
			node_t upnode; 
			// increment expanded count
			expanded++; 
			int g, k;
			// copy the old state. Could abstract this, 
			// as i got segmentation faults. 
			for(g = 0; g<GAME_SIZE; g++){
    			for(k=0; k<GAME_SIZE; k++){
    			upnode.state[g][k] = node.state[g][k]; 
    			}
     		}
     		// do the move so the state is updated 
			moveUp(upnode.state);

			// update cost, new heuristic, f(n) and the 'previous' move
			upnode.cost = node.cost+1; 
			upnode.heuristic = heuristic(upnode.state);
			upnode.f = upnode.cost + upnode.heuristic; 
			upnode.prev = UP; 

			// temporarily a dead end if f(n) is greater than 
			// current threshold, reassign thresh for a new iteration
			// on the surface 
			if(upnode.f>*thresh){
				*threshp = findMin(upnode.f, *threshp); 
			}
			else{
				// if the heuristic of this node = 0 return (this) upnode
				//  (this is the answer!)
				if ((upnode.heuristic) == 0.0){
					return upnode; 
				}

				// otherwise, go deeper. 
				r = idaStar(upnode, thresh, threshp); 
				
				// if the returned node is not empty return it, 
				// because an answer has been found deeper in the
				// recursion and is being 'sent' back up to the surface 
				if (r.f != 0.0){
					return r; 
				}
			}
		} 

		else if((ACTIONS[i] == DOWN)&&(node.prev != UP)){

			node_t downnode; 
			expanded++; 
			int g, k;

			for(g = 0; g<GAME_SIZE; g++){
    			for(k=0; k<GAME_SIZE; k++){
    			downnode.state[g][k] = node.state[g][k]; 
    			} 
     		}
			
			moveDown(downnode.state);

			downnode.cost = node.cost+1; 
			downnode.heuristic = heuristic(downnode.state);
			downnode.f = downnode.cost + downnode.heuristic; 
			downnode.prev = DOWN; 
			
			if(downnode.f>*thresh){
				*threshp = findMin(downnode.f, *threshp); 
			}
			else{
				if ((downnode.heuristic) == 0.0){
					return downnode; 
				}

				r = idaStar(downnode, thresh, threshp); 

				if (r.f != 0.0){
					return r; 
				}
			}
		}

		else if((ACTIONS[i] == LEFT)&&(node.prev != RIGHT)){

			node_t leftnode; 
			expanded++; 

			int g, k;

			for(g = 0; g<GAME_SIZE; g++){
    			for(k=0; k<GAME_SIZE; k++){
    			leftnode.state[g][k] = node.state[g][k]; 
    			} 
     		}
			
			moveLeft(leftnode.state);
			
			leftnode.cost = node.cost+1; 
			leftnode.heuristic = heuristic(leftnode.state);
			leftnode.f = leftnode.cost + leftnode.heuristic; 
			leftnode.prev = LEFT; 

			if(leftnode.f>*thresh){
				*threshp = findMin(leftnode.f, *threshp); 
			}
			else{
				// if the heuristic of leftnode = 0 return leftnode (this is the answer!)

				if (leftnode.heuristic == 0.0){
					return leftnode; 
				}
				
				r = idaStar(leftnode, thresh, threshp); 

				if (r.f != 0.0){
					return r; 
				}
			}
		}

		else if((ACTIONS[i] == RIGHT)&&(node.prev != LEFT)){
			
			node_t rightnode; 
			expanded++; 
			int g, k;

			for(g = 0; g<GAME_SIZE; g++){
    			for(k=0; k<GAME_SIZE; k++){
    			rightnode.state[g][k] = node.state[g][k]; 
    			} 
     		}
			
			moveRight(rightnode.state);

			rightnode.cost = node.cost+COST; 
			rightnode.heuristic = heuristic(rightnode.state); 
			rightnode.f = rightnode.cost + rightnode.heuristic; 
			rightnode.prev = RIGHT; 


			if(rightnode.f>*thresh){
				*threshp = findMin(rightnode.f, *threshp); 
			}
			else{

				if ((rightnode.heuristic) == 0.0){
					return rightnode; 
				}
				
				r = idaStar(rightnode, thresh, threshp); 

				if (r.f != 0.0){
					return r; 
				}
			}
		}
	}
	// if no answer is found, returns a blank node to tell 
	// control loop to increase the threshold 
	return blank_node();
}

// returns nmoves which tells us how many different moves we can 
// make and thus how many times to iterate through our control loop in IDA. 
// w might need to check a little down the line with looking up the array 
// entry and if that will point us down a certain way of recursion (possible left etc.)

int actions(node_t node, int ACTIONS[GAME_SIZE]){
	int nmoves = 0;
	int zero_x, // x coordinates of the zero tile
		zero_y, // y coordinates of the zero tile

		i, j; 
	init_actions_array(ACTIONS); 

	for(i = 0; i<GAME_SIZE; i++){
    	for(j=0; j<GAME_SIZE; j++){
    		if(node.state[i][j] == 0){
    			zero_x = j; 
    			zero_y = i; 
    		} 
     	}
    }

	// move up check
	if (zero_y != 0){
		// can move up, because it's not in the [0] row 
		ACTIONS[nmoves] = UP; 
		nmoves++; 
	}

	// move down check
	if (zero_y < 3){
		// can move down because it's not in the [3] final row 
		ACTIONS[nmoves] = DOWN; 
		nmoves++; 
	}
	
	// move left check 
	if (zero_x != 0){
		// can move left because it's not in the [0] first column
		ACTIONS[nmoves] = LEFT; 
		nmoves++;
	}

	// move right check 
	if (zero_x < 3){
		// can move right because it's not in the [3] final column
		ACTIONS[nmoves] = RIGHT; 
		nmoves++;
	}

	return nmoves; 
}

	// MOVE functions for making a move in a given instance of the 
	// 15 puzzle. 
	// Each one finds zero then does an intswap. 
	// I haven't abstracted the intswap due to the complexity
	// of the different swap locations in the given state array. 

void moveUp(int STATE[][GAME_SIZE]){
	int zero_x, zero_y, temp; 
	int ZERO[VECTOR];
	findZero(ZERO, STATE);  

    // eg. swap 0 with the tile above, so at zero_x and zero_y
    // with zero_x zero_y-1
	zero_x = ZERO[XPOS];
	zero_y = ZERO[YPOS];

    temp = STATE[zero_y][zero_x]; 
    STATE[zero_y][zero_x] = STATE[zero_y-1][zero_x]; 
    STATE[zero_y-1][zero_x] = temp; 
}

void moveDown(int STATE[][GAME_SIZE]){
	int zero_x, zero_y, temp; 

	int ZERO[VECTOR];
	findZero(ZERO, STATE);  

	zero_x = ZERO[XPOS];
	zero_y = ZERO[YPOS];

    temp = STATE[zero_y][zero_x]; 
    STATE[zero_y][zero_x] = STATE[zero_y+1][zero_x]; 
    STATE[zero_y+1][zero_x] = temp; 

}

void moveLeft(int STATE[][GAME_SIZE]){
	int zero_x, zero_y, temp; 

	int ZERO[VECTOR];
	findZero(ZERO, STATE);  

	zero_x = ZERO[XPOS];
	zero_y = ZERO[YPOS];

    temp = STATE[zero_y][zero_x]; 
    STATE[zero_y][zero_x] = STATE[zero_y][zero_x-1]; 
    STATE[zero_y][zero_x-1] = temp; 
}


void moveRight(int STATE[][GAME_SIZE]){
	int zero_x, zero_y, temp; 

	int ZERO[VECTOR];
	findZero(ZERO, STATE);  

	zero_x = ZERO[XPOS];
	zero_y = ZERO[YPOS];

    temp = STATE[zero_y][zero_x]; 
    STATE[zero_y][zero_x] = STATE[zero_y][zero_x+1]; 
    STATE[zero_y][zero_x+1] = temp; 
}


