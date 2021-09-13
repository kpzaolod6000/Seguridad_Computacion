#include<iostream>

using namespace std;


#define NUM 256


FILE *f;
int tok;
char lexema[80];

int scanner(){
    int c,i;
    do{
        c=fgetc(f); 
    }while(isspace(c));

    if(c == EOF) return EOF;
    

    if(isdigit(c))
    {
        i=0;
        do {
            lexema[i++]=c;
            c=fgetc(f);
        }while(isdigit(c));
        
        lexema[i]=0;

        //tam = i-1;

        ungetc(c,f);
        return NUM;
    }
}
void mostrar(int token){
    switch (token)
    {
    case NUM: printf("token = ID [%s\n",lexema);break;    
    default:
        break;
    }
}

int main(){

    f=fopen("text.txt","r");
    while(1){
        tok=scanner();
        if(tok==EOF) break;
        mostrar(tok);

    }
}