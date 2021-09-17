#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include <map>

using namespace std;

// remove accents
void ejercicio_2(string &text){
    string accents = "áéíóú";
    string notAccents = "aeiou";
    for (int i = 0; i < text.size(); i++)
    {
        for (int j = 0; j < accents.size(); j++)
        {
            if(text[i] == accents[j]){
                text[i] = notAccents[j];        
            }
        }
    }
    return;
}

int main(){
    //read text
    ifstream fileInput;
    ofstream fileOut("result.txt");
    string file_contents;
    
    fileInput.open("text.txt",ios::in);
    while (!fileInput.eof())
    {
        getline(fileInput,file_contents);
        ejercicio_2(file_contents);
        cout<<file_contents<<endl;
    }
    fileInput.close();
    return 0;
}