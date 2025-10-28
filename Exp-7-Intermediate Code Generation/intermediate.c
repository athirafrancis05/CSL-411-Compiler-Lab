#include <stdio.h>
#include <ctype.h>

char st[100]; int top=-1;

// stack ops
void push(char c){ st[++top]=c; }
char pop(){ return st[top--]; }

// precedence
int prec(char c){ return (c=='+'||c=='-')?1:(c=='*'||c=='/')?2:0; }

// ---- infix to postfix ----
void infixToPostfix(char in[], char post[]) {
    int k=0; char c;
    for(int i=0; in[i]; i++){
        c=in[i];
        if(isalnum(c)) post[k++]=c;
        else if(c=='(') push(c);
        else if(c==')'){ while(st[top]!='(') post[k++]=pop(); pop(); }
        else{ while(top!=-1 && prec(st[top])>=prec(c)) post[k++]=pop(); push(c); }
    }
    while(top!=-1) post[k++]=pop();
    post[k]='\0';
}

// ---- postfix to intermediate code ----
void genCode(char post[]) {
    top=-1; int t=1;
    for(int i=0; post[i]; i++){
        char c=post[i];
        if(isalnum(c)) push(c);
        else{
            char b=pop(), a=pop();
            printf("t%d = %c %c %c\n", t, a, c, b);
            push('A'+t-1);
            t++;
        }
    }
}

// ---- main ----
int main(){
    char infix[100], postfix[100];
    printf("Enter infix: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);
    printf("Intermediate Code:\n");
    genCode(postfix);
}

