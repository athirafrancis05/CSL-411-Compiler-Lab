#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

char stack[MAX];
int top = -1;

void printState(const char *input, int i, const char *action) {
    for (int k = 0; k <= top; k++) printf("%c", stack[k]); // Print Stack
    int spaces = 15 - (top + 1);
    while (spaces-- > 0) printf(" ");
    printf("%-15s", &input[i]);// Print Input
    printf("%s\n", action);// Print Action
}

void push(char c){ stack[++top]=c; }
char pop(){ return (top>=0)?stack[top--]:'\0'; }

int reduce(){
    if(top>=0 && stack[top]=='i'){ 
        pop(); push('E'); 
        return 1; 
    }
    if(top>=2 && stack[top]=='E' && (stack[top-1]=='+' || stack[top-1]=='*') && stack[top-2]=='E'){
        top-=3; push('E'); 
        return 1;
    }
    return 0;
}

int main(){
    char in[MAX], buf[MAX];
    fgets(in,sizeof(in),stdin);

    int j=0;
    for(int k=0; in[k]; k++)
        if(!isspace(in[k]))
            buf[j++] = isalpha(in[k]) ? 'i' : in[k];
    buf[j++]='$';
    buf[j]=0;

    push('$');
    printf("\n%-15s%-15s%s\n", "Stack", "Input", "Action");
    printf("---------------------------------------------\n");
    printState(buf, 0, "Initialize");

    int i=0;
    while(1){
        if(buf[i]!='$'){ 
            push(buf[i++]); 
            printState(buf, i, "Shift");
        }

        while(reduce()){
            if(stack[top]=='E' && stack[top-1]=='$')
                printState(buf, i, "Reduce: id -> E");
            else
                printState(buf, i, "Reduce: E op E -> E");
        }

        if(buf[i]=='$'){
            if(stack[top]=='E' && stack[top-1]=='$'){ 
                printState(buf, i, "Accept");
                printf("---------------------------------------------\n");
                printf("Result: Accepted\n");
                return 0; 
            } else { 
                printState(buf, i, "Reject");
                printf("---------------------------------------------\n");
                printf("Result: Not Accepted\n");
                return 0; 
            }
        }
    }
}
