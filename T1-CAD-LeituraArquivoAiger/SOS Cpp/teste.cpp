#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
//#include <cstdlib>
//#include <iomanip>

using namespace std;

int main()
{
    int nro_linha;
    string linha;
    ifstream in_file; 

    in_file.open("sat"); // abre o arquivo para leitura
    if(!in_file) {  
        cout <<"Arquivo sat nao pode ser aberto"<< endl;
        abort();
    }
    else {
        getline(in_file, linha);
//        linha.
        while(getline(in_file, linha)) {
            cout << linha << endl;       
        }
    }
} 



/*
int nro_linha;
    string linha;
    ifstream in_file; 

    in_file.open("sat", ios::in); // abre o arquivo para leitura
    if(!in_file) {  
        cout <<"Arquivo sat nao pode ser aberto"<< endl;
        abort();
    }
    else {
        while(getline(in_file, linha)) {
            cout << linha << endl;       
        }
    }
*/
