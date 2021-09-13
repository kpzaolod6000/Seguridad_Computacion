
#include <iostream>
#include <string>
#include<map>

using namespace std;
int main(){

     word1;
    getline (cin, word1);
    for (int i = 0 ; i< word1.size();i++){
        
        cout << word1[i];
    }

    //if(word1[0] == 'ñ')cout << "aqui";
    cout<<word1<<endl;

    map<string,string> mymap;
    //map<string,char>::iterator it = mymap.begin();
    mymap.insert(pair<string,string>("ñ","a"));
    mymap.insert(pair<string,string>("é","e"));
    mymap.insert(pair<string,string>("í","i"));
    mymap.insert(pair<string,string>("ó","o"));
    mymap.insert(pair<string,string>("ú","u"));
    string cg;

    for (int i = 0 ; i< word1.size();i++){
        
        cg = word1[0];
        for (map<string,string>::iterator it=mymap.begin(); it!=mymap.end(); ++it){
            
            if( cg == it->first){
                cout<<it->second << '\n';
            }
            cout<<cg;
            break;
            //cout <<  << " => " << 
        }
    }



    return 0;
}