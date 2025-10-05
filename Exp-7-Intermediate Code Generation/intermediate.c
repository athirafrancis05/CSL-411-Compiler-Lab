#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c){ stack[++top] = c; }
char pop(){ return top >= 0 ? stack[top--] : 0; }
int prec(char c){ return (c=='+'||c=='-')?1:(c=='*'||c=='/')?2:0; }

void infixToPostfix(char *infix, char *postfix){
    int k=0;
    for(int i=0; infix[i]; i++){
        char c = infix[i];
        if(isalnum(c)) postfix[k++] = c;
        else if(c=='(') push(c);
        else if(c==')'){ while(top>=0 && stack[top]!='(') postfix[k++]=pop(); pop(); }
        else{ while(top>=0 && prec(stack[top])>=prec(c)) postfix[k++]=pop(); push(c); }
    }
    while(top>=0) postfix[k++] = pop();
    postfix[k]='\0';
}

void generateIC(char *postfix){
    char tempStack[MAX][10];
    int tempTop=-1, t=1;
    for(int i=0; postfix[i]; i++){
        char c = postfix[i];
        if(isalnum(c)){
            char s[2]={c,'\0'};
            strcpy(tempStack[++tempTop], s);
        } else {
            char *b=tempStack[tempTop--], *a=tempStack[tempTop--], temp[10];
            sprintf(temp,"t%d",t++);
            printf("%s = %s %c %s\n", temp, a, c, b);
            strcpy(tempStack[++tempTop], temp);
        }
    }
}

int main(){
    char infix[MAX], postfix[MAX];
    printf("Enter infix expression: ");
    fgets(infix,sizeof(infix),stdin);
    infix[strcspn(infix,"\n")]=0;
    infixToPostfix(infix,postfix);
    printf("Postfix Expression: %s\n", postfix);
    generateIC(postfix);
    return 0;
}
