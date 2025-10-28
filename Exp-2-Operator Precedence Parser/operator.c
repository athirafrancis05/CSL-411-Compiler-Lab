#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX 100

char stack[MAX]; 
int top = -1;

const char syms[] = "+*i$";
char prec[4][4] = {
// +    *    i    $
{ '>', '<', '<', '>' }, // +
{ '>', '>', '<', '>' }, // *
{ '>', '>', 'E', '>' }, // i
{ '<', '<', '<', 'A' }  // $
};

int idx(char c){ for(int i=0;i<4;i++) if(syms[i]==c) return i; return -1; }
void push(char c){ stack[++top]=c; }
char pop(){ return stack[top--]; }
char top_term(){ for(int i=top;i>=0;i--) if(strchr(syms,stack[i])) return stack[i]; return '$'; }

void printStack(){
    printf("Stack: ");
    for(int i=0;i<=top;i++) printf("%c", stack[i]);
    printf("\n");
}

void preprocess(char*in,char*out){
    int j=0; 
    for(int i=0;in[i];i++)
        if(!isspace(in[i])) 
            out[j++]=isalpha(in[i])?'i':in[i];
    out[j++]='$'; out[j]=0;
}

int reduce(){
    if(stack[top]=='i'){ pop(); push('E'); printf("Reduce: id -> E\n"); return 1; }
    if(top>=2 && stack[top]=='E' && strchr("+*",stack[top-1]) && stack[top-2]=='E'){
        top-=3; push('E'); printf("Reduce: E op E -> E\n"); return 1;
    }
    return 0;
}

void parse(char in[]){
    int i=0; push('$');
    printf("\n%-20s %-20s Action\n","Stack","Input");
    while(1){
        char a=top_term(), c=in[i], r=prec[idx(a)][idx(c)];
        stack[top+1]=0; 
        printf("%-20s %-20s ",stack,in+i);

        if(r=='<'||r=='='){ push(c); i++; printf("Shift\n"); }
        else if(r=='>'){ if(!reduce()){ printf("Error\n"); return; } }
        else if(r=='A'){ printf("Accept\n"); return; }
        else { printf("Error\n"); return; }
    }
}

int main(){
    char in[100], p[100];
    printf("Enter the input expression: ");
    fgets(in,sizeof(in),stdin);
    preprocess(in,p);
    parse(p);
    return 0;
}
