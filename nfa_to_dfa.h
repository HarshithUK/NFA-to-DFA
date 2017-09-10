#include<stdio.h>
#include<string.h>
#include "set.h"
char* alphabets;
typedef struct node
{
    int n_no; //state or node number
    int is_final;//whether it is a final state or not
    struct node** t;//state transitions it can take
    struct node** l;//lambda state transitions
    int n_lt;//number of lambda state transitions
}Node;
Node** n_array = NULL;
Node** d_array = NULL;
int state_num = 0;
int alpha_num = 1;
int nfa = 1;
