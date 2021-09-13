#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;
 
int main()
{
    string nombre;
    string linea;
 
    cout << "Dime el nombre del fichero: ";    
    getline(cin, nombre);
    cout << nombre<<endl;

    ifstream fichero(nombre.c_str());
    if( fichero.fail() )
    {
        cout << "No existe el fichero!" << endl;
        exit(1);
    }
 
    while (!fichero.eof()) 
    {
        getline(fichero,linea);
        if (!fichero.eof()) 
            cout << linea << endl;
    }

    cout << linea<<endl;
    fichero.close();
 
    return 0;
}