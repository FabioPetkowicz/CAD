#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

class aig{
    int *filho0_; //ponteiro para todos os filhos Zero
    int *filho1_; //ponteiro para todos os filhos Um
    int maxvar_, ni_, nl_, no_, na_; //variáveis do header; atributo número de latches (nl_) acrescentado
    set<int> entradas_; //conjunto de entradas (set<>, "generics")
    set<int> saidas_;   //conjunto de saídas
    
    //métodos privados
    int trata_linha_entrada_(string & linha);   //em t2.cpp
    int trata_linha_saida_(string & linha);     //em t2.cpp
    int trata_linha_and_(string & linha);       //em t2.cpp
    int trata_linha_cabecalho_(string & linha, int &maxvar, int &ni, int &nl, int &no, int &na);       //em t2.cpp
    
    //interface publica da classe
    public: 
	    aig(string& filename); //construtor da classe
	    int print();
	    int get_maxvar();
	    int get_ni();
        int get_nl();
	    int get_no();
	    int get_na();
	    int get_filho0(int index);
	    int get_filho1(int index);
        bool entradas_contains(int n);
        bool saidas_contains(int n);
        set<int> get_set_entradas();
        set<int> get_set_saidas();

};

//**********************Definições dos Métodos**************************************************
int aig::get_maxvar(){
    return maxvar_;
}

int aig::get_ni(){
    return ni_;
}

int aig::get_nl() {
    return nl_;
}
int aig::get_no(){
    return no_;    
}

int aig::get_na(){
    return na_;    
}

int aig::get_filho0(int index){
    return filho0_[index];
}

int aig::get_filho1(int index){
    return  filho1_[index];
}

bool aig::entradas_contains(int n) {
    set<int>::iterator it = entradas_.begin();

    if (it != entradas_.end()) {
        return true;    
    } 
    else {
        return false;
    }
}

bool aig::saidas_contains(int n) {
    set<int>::iterator it = saidas_.begin();
    
    if (it != saidas_.end()) {
        return true;    
    } 
    else {
        return false;
    }
}

set<int> aig::get_set_entradas() {
    return entradas_;
}

set<int> aig::get_set_saidas() {
    return saidas_;
}
//*************************************************************************

void run_aig_topologic(aig &aig_) {
    int i;
    cout << "Impressão Topológica:" <<endl;
    
    //usa apenas o filho0 pq o filho0 vem primeiro; se estiver != Zero, o filho1 também deverá ser.
    //não há necessidade de verificar o filho1; 
    for (i=0; i<= aig_.get_maxvar(); i++) {
        if (aig_.get_filho0(i) != 0) {         
            cout << "O filho0 de "<< 2*i <<" vale: "<< aig_.get_filho0(i) <<endl;
            cout << "O filho1 de "<< 2*i <<" vale: "<< aig_.get_filho1(i) <<endl;
        }
    }
    cout <<endl;
}

void recreate_aiger_ascii(aig aig_) {

    cout <<"Criando arquivo \"aiger_ascii.txt\" a partir do objeto em memória."<<endl;
    ofstream aiger_out("aiger_ascii.txt");
    aiger_out<<"aag "<<aig_.get_maxvar()<<" "<<aig_.get_ni()<< " "<< aig_.get_nl() << aig_.get_no() <<" "<<aig_.get_na()<<endl;

    set<int> setEntradas = aig_.get_set_entradas();
    set<int>::iterator it = setEntradas.begin();
    while(it != setEntradas.end() ) {
        aiger_out<<*it<<endl;
        it++;
    }

    set<int> setSaidas = aig_.get_set_saidas();
    it = setSaidas.begin();
    while(it != setSaidas.end() ) {
        aiger_out<<*it<<endl;
        it++;
    }

    for (int i = 0; i<= aig_.get_maxvar(); i++) {
        if (aig_.get_filho0(i) != 0) {
            aiger_out<< 2*i <<" "<< aig_.get_filho0(i) <<" "<< aig_.get_filho1(i) <<endl;
        }
    }
    
    aiger_out.close();
    cout <<"Arquivo \"aiger_ascii.txt\" criado com sucesso."<<endl;

}