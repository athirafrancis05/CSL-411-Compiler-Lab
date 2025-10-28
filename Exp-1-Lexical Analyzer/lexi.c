#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *w){
    char *kw[]={"int","float","char","if","else","while","for","return","void","double"};
    for(int i=0;i<10;i++) if(!strcmp(kw[i],w)) return 1;
    return 0;
}

int main(){
    char tok[100]; int j=0; char c;
    printf("Enter code (end with $):\n");
    while((c=getchar())!='$' && c!=EOF){
        if(isalnum(c)) tok[j++]=c;
        else{
            if(j){
                tok[j]='\0'; j=0;
                if(isKeyword(tok)) printf("%s : keyword\n",tok);
                else if(isalpha(tok[0])) printf("%s : identifier\n",tok);
                else if(isdigit(tok[0])){
                    // ensure all chars are digits
                    int valid=1;
                    for(int k=1; tok[k]; k++) if(!isdigit(tok[k])) valid=0;
                    printf("%s : %s\n", tok, valid?"number":"identifier");
                }
                else printf("%s : identifier\n",tok);
            }
            if(strchr("=+-*/",c)) printf("%c : operator\n",c);
            else if(strchr(";,(){}",c)) printf("%c : special symbol\n",c);
        }
    }
    return 0;
}

