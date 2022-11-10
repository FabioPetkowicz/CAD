#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

using namespace std;

//AIG____________________________________________________________________
class aig{
    int *filho0_;
    int *filho1_;
    int maxvar_, ni_, nl_, no_, na_; //atributo número de latches (nl_) acrescentado
    set<int> entradas_;
    set<int> saidas_;
    
    //métodos privados
    int trata_linha_entrada_(string & linha);
    int trata_linha_saida_(string & linha);
    int trata_linha_and_(string & linha);
    int trata_linha_cabecalho_(string & linha, int &maxvar, int &ni, int &nl, int &no, int &na);
    
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
        void run_aig_topologic();
        int* busca_nodos_saida();
        int* busca_filhos_nodo(int nro_id_nodo);
        void recreate_aiger_ascii();
};

//**********************Definições dos Métodos**************************************************
aig::aig(string& filename)
{
    int i=0;  
    ifstream aiger_in(filename);           
    char buffer[200];                 
    aiger_in.getline(buffer, 200, '\n');                    
    string cabecalho(buffer);                               
    int maxvar, ni, nl, no, na;                                 
    trata_linha_cabecalho_(cabecalho, maxvar, ni, nl, no, na);   

    filho0_=new int[maxvar+1];
    filho1_=new int[maxvar+1];
    
    while (aiger_in.getline(buffer, 200, '\n')){
        i++;
        string s(buffer);
        
        if (i<=ni){
          cout<<"adiciona entrada"<<endl;
          trata_linha_entrada_(s);
        }
        
        else if (i<=(ni+no)){
          cout<<"adiciona saida"<<endl;
          trata_linha_saida_(s);
        }
        else if (i<=(ni+no+na)){
          cout<<"adiciona and"<<endl;
          trata_linha_and_(s);
        }
    }
}
//************************************************************************
int aig::print(){
 
    cout<<"Imprimindo aig em tela: "<<endl;
    set<int>::iterator itr;
    for (itr = entradas_.begin(); itr != entradas_.end(); itr++) {
        cout <<"entrada =" << *itr << endl;
    }  
    
    for (itr = saidas_.begin(); itr != saidas_.end(); itr++) {
        cout <<"saida =" << *itr << endl;
    }

    for (int i=ni_+1; i<(ni_+1+na_); i++) {
        cout << "AND   "<<i*2<<"="<<filho0_[i]<<"*"<<filho1_[i]<<endl;
    }
    return 0;
}
//*************************************************************************
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
    
    return false;
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

int aig::trata_linha_entrada_(string & linha)
{   
    istringstream in(linha);
    int entrada;
    in >> entrada;
    cout <<"in="<< entrada << endl;
    entradas_.insert(entrada);
    return 0;
}

int aig::trata_linha_saida_(string & linha)
{
    istringstream in(linha);
    int saida;
    in >> saida;
    cout <<"out="<< saida << endl;
    saidas_.insert(saida);
    return 0;
}

//coloca AND na estrutura do AIG
int aig::trata_linha_and_(string & linha)
{       
    istringstream in(linha);
    int saida, entrada0, entrada1;
    in >> saida;
    cout <<"conecta pino ="<< saida << endl;
    in >> entrada0;
    cout <<"conecta pino ="<< entrada0 << endl;
    in >> entrada1;
    cout <<"conecta pino ="<< entrada1 << endl;
    saida=saida/2;
    filho0_[saida]=entrada0;
    filho1_[saida]=entrada1;
    return 0;
}

int aig::trata_linha_cabecalho_(string & linha, int &maxvar, int &ni, int &nl, int &no, int &na)
{
    istringstream in(linha);
    int l;
    string word;
    in >> word; cout<<"string discarded ="<<word<<endl;
    in >> maxvar; cout<<"number of variables is ="<<maxvar<<endl;
    in >> ni; cout<<"number of inputs is ="<<ni<<endl;  
    in >> nl; cout<<"number of latches is ="<<nl<<endl;  
    in >> no; cout<<"number of outputs is ="<<no<<endl;  
    in >> na; cout<<"number of ands is ="<<na<<endl;  
    maxvar_=maxvar; 
    ni_=ni;
    nl_=nl; 
    no_=no; 
    na_=na;
    return 0;
}
//*************************************************************************
void aig::run_aig_topologic() {
    int i;
    cout << "Impressão Topológica:" <<endl;
    
    for (i=0; i<= maxvar_; i++) {
        if (filho0_[i] != 0) {
            cout << "O filho0 de "<< 2*i <<" vale: "<< filho0_[i] <<endl;
            cout << "O filho1 de "<< 2*i <<" vale: "<< filho1_[i] <<endl;
        }
    }
    cout <<endl;
}


int* aig::busca_nodos_saida() {
    
    int *nros_nodos_saida = new int[no_];

    cout << "Buscando nodos de saída." <<endl;
    set<int>::iterator itr;
    int i;
    for (itr = saidas_.begin(), i=0; itr != saidas_.end(); itr++) {
        if ( *itr % 2 != 0){
            nros_nodos_saida[i] = *itr - 1;
            //cout << "nodo saida aig: "<< nros_nodos_saida[i] <<endl;
            i++;
        }
    }
    return nros_nodos_saida;
}

int* aig::busca_filhos_nodo(int nro_id_nodo) { 
    int *filho_do_nodo = new int[2];

    for (int i=0; i<= maxvar_; i++) {
        
        if (filho0_[i] != 0 and 2*i == nro_id_nodo) {
                cout << "and"<< 2*i <<" filho0: "<< filho0_[i] <<endl;
                filho_do_nodo[0] = filho0_[i];

                cout << "and"<< 2*i <<" filho1: "<< filho1_[i] <<endl;
                filho_do_nodo[1] = filho1_[i];
            }
    }
    
    return filho_do_nodo;
}
//constroi um aig_ascii a partir de qualquer aig em memória
void aig::recreate_aiger_ascii() {
    cout <<"Criando arquivo \"aiger_ascii.txt\" a partir do objeto em memória."<<endl;
    ofstream aiger_out("aiger_ascii.txt");
    aiger_out<<"aag "<<maxvar_<<" "<<ni_<< " "<< nl_ <<" "<< no_ <<" "<< na_ <<endl;

    set<int>::iterator it = entradas_.begin();
    while(it != entradas_.end()){
        aiger_out<<*it<<endl;
        it++;
    }

    it = saidas_.begin();
    while(it != saidas_.end() ){
        aiger_out<<*it<<endl;
        it++;
    }

    for (int i = 0; i <= maxvar_; i++) {
        if (filho0_[i] != 0) {
            aiger_out<< 2*i <<" "<< filho0_[i] <<" "<< filho1_[i] <<endl;
        }
    }
    
    aiger_out.close();
    cout <<"Arquivo \"aiger_ascii.txt\" criado com sucesso."<<endl;
}

//FIM-AIG____________________________________________________________________
