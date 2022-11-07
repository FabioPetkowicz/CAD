#include <iostream> //input-output
#include <fstream> //biblioteca para arquivos

using namespace std;

int main() {    
    ifstream  arquivo;
    string linha;

    arquivo.open("cbfcursos.txt");
    if(arquivo.is_open()){
        while(getline(arquivo, linha)) {
            cout << linha << endl;
        }
    } else {
        cout <<"Não foi possível abrir o arquivo" << endl;
    }

    arquivo.close();
    
    return 0;
}
