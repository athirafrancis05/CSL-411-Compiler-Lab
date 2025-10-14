#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c){ stack[++top]=c; }
char pop(){ return (top>=0)?stack[top--]:'\0'; }

int reduce(){
    if(top>=0 && stack[top]=='i'){ pop(); push('E'); return 1; }
    if(top>=2 && stack[top]=='E' && (stack[top-1]=='+' || stack[top-1]=='*') && stack[top-2]=='E'){
        top-=3; push('E'); return 1;
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
    int i=0;
    while(1){
        if(buf[i]!='$') push(buf[i++]);
        while(reduce());
        if(buf[i]=='$'){
            if(stack[top]=='E' && stack[top-1]=='$'){ printf("Accepted\n"); return 0; }
            else { printf("Not Accepted\n"); return 0; }
        }
    }
}

