#include <iostream> //input-output
#include <fstream> //biblioteca para arquivos
#include <cstring> //evolução da <string.h>
#include <string> //definição da classe string

using namespace std;

int main() {    
    string linha("Fábio 8 9 10");
    string::iterator it;

    it=linha.begin();
    cout << *it << endl;

    return 0;
}
