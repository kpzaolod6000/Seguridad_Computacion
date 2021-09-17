#include<iostream>
#include <string>
#include<map>
#include<vector>
using namespace std;

FILE * f;
FILE * fw;
int c;

vector<char> Pre_process;
map<char, int> frequentLetters;

// Substitution of following characters: j x i, h x i, ñ x n, k x l, u x v, w x v, y x z
void ejercicio_1(){
    //c
    if(c == 106 || c == 104) c = 105;
    else if (c == 107) c = 108;
    else if (c == 117 || c == 119) c = 118;
    else if (c == 121) c = 122;
    else if (c == 195){
        c = fgetc (f);
        if(c == 177 ) c = 110;
        else{
            //cout<<"hola"<<endl;
            ungetc(c,f);
            c=195;
        } 
    }
}

//remove accents
void ejercicio_2(){
    if(c == 195){
        c = fgetc (f);  
        switch(c)
        {
            case 161: c = 97; //a
            break;
            case 169: c = 101; //e
            break;
            case 173: c = 105; //i
            break;
            case 179: c = 111; //o
            break;
            case 186: c = 117; //u
            break;
            default: ungetc(c,f); c=195;
        }
    }
}

//convert to uppercase
void ejercicio_3(){
    if(c>= 97 && c <=122) c = c - 32;
}

//remove puntuation signs

void ejercicio_4(){

    if(ispunct(c)){
        while(ispunct(c)){
            c= fgetc(f);
        }
    }
    else if(c == 194){
        c = fgetc(f);
        if (c == 161){ 
            c = fgetc(f); //ignorar (¡)
        }
    }
    //error con spacio index
    // else if(c == 32){
    //     while(c == 32){
    //         c= fgetc(f);
    //     }
    // }
}

//frecuency
void ejercicio_5(){
    
    if(frequentLetters.count(c)>0){
        map<char,int>::iterator it;
        it = frequentLetters.find(c);
        it->second +=1; 
    }else{
        frequentLetters.insert(pair<char,int>(c,1));
    }
}
// KASISKI METHOD
void ejercicio_6(){

    vector<char> trigrams;
    map<vector<char>, int> trigramsFrecuency;
    map<vector<char>, vector<int>> positions;
    

    for(int i = 0; i < Pre_process.size()-2 ; i++) {
        int cont = i;
        while(cont < i+3){
            trigrams.push_back(Pre_process[cont]);
            cont++;
        }
        trigramsFrecuency.insert(pair<vector<char>,int>(trigrams,0));
        positions.insert(pair<vector<char>,vector<int>>(trigrams,0));
        trigrams.clear();
    }
    // trigrams.clear();
    for(int i = 0; i < Pre_process.size()-2 ; i++) {
        int cont = i;
        while(cont < i+3){
            trigrams.push_back(Pre_process[cont]);
            cont++;
        }
        map<vector<char>,vector<int>>::iterator it2=positions.begin();
        for (map<vector<char>,int>::iterator it=trigramsFrecuency.begin(); it!=trigramsFrecuency.end(); ++it){
            bool isEqual = true;
            map<vector<char>,int>::iterator index;

            for(int j = 0; j<it->first.size(); j++) {
                if(trigrams[j] != it->first[j]){
                    isEqual = false;
                    index = it;
                }
                // cout<<it->first[j];
            }
            // cout<<" => "<<it->second<<endl;
            if(isEqual){
                it->second += 1;
                it2->second.push_back(i);
            }
            ++it2;
        }
        trigrams.clear();
    }
    
    map<vector<char>,vector<int>>::iterator it2=positions.begin();
    for (map<vector<char>,int>::iterator it=trigramsFrecuency.begin(); it!=trigramsFrecuency.end(); ++it){
        if (it2->second.size()>1){
            for(int j = 0; j<it->first.size(); j++) {
                cout<<it->first[j];
            }
            cout<<" => "<<it->second<<" : [ ";
            for(int k = 0; k < it2->second.size() ; k++){
                cout<<it2->second[k]<<" ";
            }
            int first = it2->second[0];
            cout<<"] "<<endl;
            cout<<"Distancias: \n"; 
            for(int l = 1; l < it2->second.size() ; l++){
                cout<<it2->second[l]<< " - " <<first<<" = "<<it2->second[l] - first<<endl;
            }
            cout<<endl;   
        }
        ++it2;
    }
}

void ejercicio_9(){
    vector<char> newPre_process;
    vector<char> aqui = {'A','Q','U','I'};
    for (int i = 0; i < Pre_process.size(); i++){
        if (i!=0){
            if(i % 20 == 0){
                for(int j = 0; j < aqui.size(); j++){
                    newPre_process.push_back(aqui[j]);
                }
                
            }
            // cout<<Pre_process[i]<<endl;
        }
        newPre_process.push_back(Pre_process[i]);
    }
    
    // cout<<newPre_process.size()<<endl;
    if (newPre_process.size() % 4 == 0) cout<<"La longitud : "<<newPre_process.size()<<" es multiplo de 4"<<endl;
    else{
        int module_ = newPre_process.size()%4;
        int rest = newPre_process.size() - module_;
        int value = rest + 4;
        int new_tam = value - newPre_process.size();

        for (int k = 0; k<new_tam; k++){
            newPre_process.push_back('X');
        }
        cout<<"La longitud : "<<newPre_process.size()<<" es multiplo de 4"<<endl;

    }
    for (int i = 0; i < Pre_process.size(); i++){
        cout<<newPre_process[i];
    }
}

void fiveMostFrequent(){
    map<char, int> aux(frequentLetters);
    int max = 0;
    int cont = 0;
    cout<<"\n5 caracteres mayores mas frecuentes \n";
    while(cont<5){
        map<char,int>::iterator index;
        for (map<char,int>::iterator it=frequentLetters.begin(); it!=frequentLetters.end(); ++it){
            if(it->second > max){
                max = it->second; 
                index = it;
            }
        }
        cout<<index->first<<" => "<<index->second<<endl;
        index->second = 0;
        max = 0;
        cont++;
    }
}

int main ()
{   
    f=fopen ("text.txt","r");
    fw=fopen ("HERALDOSNEGROS_pre.txt", "w");
    
    
    if (f==NULL) perror ("Error opening file");
    else
    {
        do {
        c = fgetc (f);
        ejercicio_2();
        ejercicio_1();
        ejercicio_4();
        ejercicio_3();// for uppercase
        // cout<<c<<" ";
        
        Pre_process.push_back(c);
        } while (c != EOF);

        
        fclose (f); 
    }
    for (vector<char>::iterator it = Pre_process.begin() ; it != Pre_process.end(); ++it){
        while(*it == 32 || *it == '\n') Pre_process.erase(it);
    }
    
    char Text[Pre_process.size()-1];
    int j;
    for(j=0;j<Pre_process.size();j++){
        
        Text[j]=Pre_process[j];
    }
    Text[j]=0;
    // cout<<Text<<endl;
    // lexema[i++]=c;
    
    fwrite (Text , sizeof(char), sizeof(Text), fw);
    fclose (fw);

    //Read
    Pre_process.clear();
    f=fopen("HERALDOSNEGROS_pre.txt","r");
    
    int t = 0;
    do {
        c = fgetc (f);
        // cout<<c<<" ";  
        ejercicio_5();
        Pre_process.push_back(c);
        // cout<<char(c)<<t<<" ";
        t++;

    } while (c != EOF);    
    fclose (f); 
    
     
    for (map<char,int>::iterator it=frequentLetters.begin(); it!=frequentLetters.end(); ++it)
        cout << it->first << " => " << it->second << '\n';


    fiveMostFrequent();
    cout<<"\nMETODO KASISKI\n\n";
    ejercicio_6();
    
    ejercicio_9();
    cout<<endl;

    return 0;
}

