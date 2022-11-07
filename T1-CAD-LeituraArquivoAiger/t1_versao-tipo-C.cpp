/*
Lê linha a linha e concatena num único stringão.
Lê os 5 primeiros números do stringão, calcula o tamanho necessário ao vatorzão e aloca o aag_vetor.
Lê o stringão pegando apenas os números. Vai colocando-os num grande array.
*/

#include <iostream> //para IO Cpp
#include <string>   //para strings Cpp
#include <cstdlib>  //para atoi
#include <fstream>  //para arquivos

#define SZ_VETOR_HEAD 5
#define SZ_VET_CHARINT 10

using namespace std;

//===================================================================
void imprime_header(int head[]){

    for(int i=0; i<SZ_VETOR_HEAD; i++){
        cout << head[i] << endl;
    }
}
//===================================================================
void imprime_agg_vetor(int agg[], int sz){

    for(int i=0; i<sz; i++){
        cout << agg[i] << endl;
    }
}
//===================================================================
int calcula_sz_aag_full(int head[]){
    int maior;
    int tamanho1 = head[1] + head[3] + 3*head[4];
    int soma = 0;

    for(int i=0; i<SZ_VETOR_HEAD; i++){
        soma += head[i];
    }
    tamanho1 > soma ? maior=tamanho1 : maior=soma;

    return maior;
}
//===================================================================
    int* cria_vetor_header(string linha, int aag_header[]) {
        int temp, i, j, k, sz;
        char a[SZ_VET_CHARINT];

        sz=linha.size();
        for(i=0, j=0, k=0; i < sz; i++){
            if(linha[i] != ' ' && linha[i] >= 48 && linha[i] <= 57) {
                while (linha[i] != ' ' && linha[i] != '\0') {
                    a[j] = linha[i];
                    j++;
                    i++;
                }
                a[j]='\0';
                temp = atoi(a);
                aag_header[k] = temp;
                k++;
                j=0;
            }
       }
    }
//===================================================================
void popula_aag_vetor(int aag_header[], int aag_vetor[]) {

    for(int i=0; i<SZ_VETOR_HEAD; ++i){
        aag_vetor[i] = aag_header[i];
    }
}
//===================================================================
int* string_to_array (string linha, int aag[]) {
    int temp, i, j, k, sz;
    char a[SZ_VET_CHARINT];

    sz=linha.size();
    for(i=0, j=0, k=0; i < sz; i++){
        if(linha[i] != ' ' && linha[i] >= 48 && linha[i] <= 57) {
            while (linha[i] != ' ' && linha[i] != '\0') {
                a[j] = linha[i];
                j++;
                i++;
            }
            a[j]='\0';
            temp = atoi(a);
            aag[k] = temp;
            k++;
            j=0;
        }
   }
}
//===================================================================
int main()
{
    ifstream  arquivo;
    string linha;
    string str_aag;

    int *aag_vetor;
    int aag_header[SZ_VETOR_HEAD];
    int size_aag;

    //Cria o vetor aag_header:
    arquivo.open("sat");
    if(arquivo.is_open()){
        getline(arquivo, linha);
        cria_vetor_header(linha, aag_header);
    } else {
        cout <<"Não foi possível abrir o arquivo" << endl;
    }
    arquivo.close();

    //Monta um stringão str_aag:
    arquivo.open("sat");
    if(arquivo.is_open()){
        while(getline(arquivo, linha)) {
            linha.append(" ");
            str_aag += linha;
        }
    } else {
        cout <<"Não foi possível abrir o arquivo" << endl;
    }
    arquivo.close(); //cout << str_aag << endl;

    //Calcula Tamanho do Array aag_vetor
    size_aag = calcula_sz_aag_full(aag_header) + SZ_VETOR_HEAD;

    //Aloca memória:
    aag_vetor = (int*)calloc(size_aag, sizeof(int));

    //Popula o Array:
    string_to_array (str_aag, aag_vetor);
    imprime_agg_vetor(aag_vetor, size_aag);

   return 0;
}
