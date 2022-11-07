#include <iostream> //input-output
#include <fstream> //biblioteca para arquivos
#include <cstring> //evolução da <string.h>
#include <string> //definição da classe string

using namespace std;

int main() {    
    string txt("CFB Cursos - Curso de C++");
    cout << txt << endl;

    string::iterator it;
    it = txt.begin();
    cout << *it << endl;
    
    cout << txt.size() << endl;
    txt.resize(10);
    cout << txt << endl;

    cout << txt.max_size() << endl;
    int c = txt.capacity();

    txt.clear(); //esvazia a string
    txt.empty(); //retorna um boleano

    return 0;
}
