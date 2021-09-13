#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

// using std::cout; using std::cerr;
// using std::endl; using std::string;
// using std::ifstream; using std::ostringstream;
map<string,string> mymap;
//map<string,char>::iterator it = mymap.begin();

string readFileIntoString(const string& path) {
    ifstream input_file(path);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '" << path << "'" << endl;
        exit(EXIT_FAILURE);
    }
    return string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

void ejercicio_2(string &text){
    string acents    = "áéíóú";
    string notAcents = "aeiou";
    
    // mymap.insert(pair<string,string>("á","a"));
    // mymap.insert(pair<string,string>("é","e"));
    // mymap.insert(pair<string,string>("í","i"));
    // mymap.insert(pair<string,string>("ó","o"));
    // mymap.insert(pair<string,string>("ú","u"));

    for (size_t i = 0; i < text.size(); i++)
    {
        //cout << text[i]<<endl;
        // if(text[i] == '\n') cout << "salto de linea" <<endl;
        // for (map<string,string>::iterator it=mymap.begin(); it!=mymap.end(); ++it){
        //     if(text[i] == it->first){

        //     }
        // }
        for (size_t j = 0; j < acents.size(); j++)
        {
            if(text[i] == acents[j]){
                text[i] = notAcents[j];
            
            }
        }
    }
    
}

int main()
{
    //read text
    ifstream fileText("text.txt");
    string file_contents;
    //write text
    string fileResult("result.txt");
    fstream file_out;

    //file_contents = readFileIntoString(fileText);
    
    while (!fileText.eof()) 
    {
        getline(fileText,file_contents);
        //if (!fileText.eof()) 
          //  cout << file_contents << endl;
    }

    fileText.close();
    cout << file_contents << endl;

    ejercicio_2(file_contents);
    
    
    file_out.open(fileResult, ios_base::out);
    if (!file_out.is_open()) {
        cout << "failed to open " << fileResult << '\n';
    } else {
        file_out << file_contents << endl;//write file_contents
        cout << "Done Writing!" << endl;
    }
    file_out.close();

    return 0;
}
