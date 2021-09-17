#include<iostream>
#include <string>
#include<map>
using namespace std;


FILE * f;
FILE * fw;
char lexema[798];

int main ()
{
    map<string,string> mymap;
    //map<string,char>::iterator it = mymap.begin();
    mymap.insert(pair<string,string>("á","a"));
    mymap.insert(pair<string,string>("é","e"));
    mymap.insert(pair<string,string>("í","i"));
    mymap.insert(pair<string,string>("ó","o"));
    mymap.insert(pair<string,string>("ú","u"));
    
    string cg;
    int c,i;
    int n = 0;
    f=fopen ("text.txt","r");
    fw=fopen ("result.txt", "w");
    
    if (f==NULL) perror ("Error opening file");
    else
    {
        i = 0;
        do {
        c = fgetc (f);
        //cout<<c <<" ";
        //if (c == 195 || c == 169) c = 101;
        lexema[i++]=c;
        
        cout<<c<<" ";
        // cg = c;//entra con 2digitos
        // for (map<string,string>::iterator it=mymap.begin(); it!=mymap.end(); ++it){
            
        //     if( cg == it->first){
        //         cout<<it->second << '\n';
        //     }
        //     //cout <<  << " => " << 
        // }
        
        if (c == '\n') n++;

        } while (c != EOF);

        lexema[i]=0;
        //fwrite (lexema , sizeof(char), sizeof(lexema), fw);
        //fclose (f);        
        //printf ("The file contains %d salto de linea($) y total de caracteres %d.\n",n,i);
  }
  return 0;
}


