#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
char input[100];
int i = 0;
int f=0;
void E();
void Eprime();
void T();
void Tprime();
void F();
void error() {
    printf("Not Accepted\n");
    exit(0);
}
void ps()
{int j;
for(j=i;j<=strlen(input);j++)
{
printf("%c",input[j]);
}


}
void match(char c) {
    if (input[i] == c)
     {  ps(); 
     i++;
        f=1;
        }
    
}
void F() {
    if (input[i] == 'i')
        match('i');
        if(f==1)
        {printf("     F=i");
        printf("\n");
        }
        f=0;
    
}
void T() {
    F();
    Tprime();
}
void Tprime() {
    if (input[i] == '*') {
        match('*');
        if(f==1)
        {printf("     T=*FT'");
        printf("\n");
        }
        f=0;
        F();
        Tprime();
    }
}
void E() {
    T();
    Eprime();
}
void Eprime() {
    if (input[i] == '+') {
        match('+');
        if(f==1)
        {printf("     E'=+TE'");
        printf("\n");
        }
        f=0;
        T();
        Eprime();
    }
}
int main() {
    printf("Enter the input expression: ");    
    fgets(input, sizeof(input), stdin);
    int len = strlen(input);
    if (input[len - 1] == '\n') input[len - 1] = '\0';   
    strcat(input, "$");     
    E();
    if (input[i] == '$')
        printf("Accepted\n");
    else
        printf("Not Accepted\n");

    return 0;
}
