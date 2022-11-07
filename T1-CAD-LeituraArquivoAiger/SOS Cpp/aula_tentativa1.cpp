#include <iostream> //input-output
#include <fstream> //biblioteca para arquivos
#include <cstring> //evolução da <string.h>
#include <string> //definição da classe string
#include <string.h>

using namespace std;

int main() {    
    string txt("aag 11 5 0 2 6");
    string aux("");
//    cout << txt << endl;

    string::iterator itr;

//    for (itr = txt.begin(); itr != txt.end(); itr++ ){
//        cout << *itr << endl;
//    }

//    for (int i=0; i<txt.size(); i++ ){
//        if (txt[i] != ' ' && txt[i] >= 48 && txt[i] <= 57){            
//            cout << txt[i] << endl;
//        }
//    }
    
    for (itr = txt.begin(); itr != txt.end(); itr++ ){
         if (*itr != ' ' && *itr >= 48 && *itr <= 57)
            while (*itr != ' ' && *itr >= 48 && *itr <= 57 && *itr != '\0') {
                aux += *itr;
            }
            cout << aux << endl;
            aux.clear();
    }
    
        
    return 0;
}
