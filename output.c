//  Chris Tass-Parker 2015  
//  output.c

#include "main.h"

// iterates through state and prints out current node in game format
void print_state(node_t current_node){
    int i, j;
    
    for(i = 0; i<4; i++){
        for(j=0; j<4; j++){
            
            if (current_node.state[i][j] >9){
                printf(" %d", current_node.state[i][j]);
            }
            else {
                printf(" %d ", current_node.state[i][j]);
            }
        }
        printf("\n");
    }
    
}

void test_output(node_t node, long long int OUTD[OUTDATA_SIZE], double time_spent){
    long long int generated = OUTD[NGENERATED]; 
    long long int expanded = OUTD[NEXPANDED];

    printf("\n"); 
    printf(CYAN"Solution = %.0f \n", node.f); 
    
    // setlocale used from local.h used for formatting output
    setlocale(LC_NUMERIC, "");
    printf(MAGENTA"Generated = %'lli\n", generated); 
    printf("Expanded = %'lli\n", expanded); 

    // time in seconds
    printf(CYAN"Time = %.2f\n", time_spent);

    // calculate average node expantion per second & protect from int division 
    long double expps = (1.0*expanded)/time_spent; 
    printf("Expanded/second = %'.2Lf\n"C_RESET, expps); 
}


void print_init_est(double est){
    printf(GREEN"Initial Estimate = %.0f \n"C_RESET, est); 
}
