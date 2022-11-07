#include <iostream> //input-output
#include <fstream> //biblioteca para arquivos

using namespace std;

int main() {
    //ofstream --> saida do programa para o arquivos
    //ifstream --> entrada do arquivo para o programa == leitura
    //fstream  --> ambos casos I/O
    
    ofstream arquivo;

    arquivo.open("cfbcursos.txt");
    
    arquivo << "CFB Cursos\n";
    arquivo << "Curso C++\n";
    arquivo << "youtube.com/cfbcursos\t JabAH";
    
    arquivo.close();
    
    return 0;
}
