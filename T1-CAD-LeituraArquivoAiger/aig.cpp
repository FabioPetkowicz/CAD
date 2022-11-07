#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>

using namespace std;


class aig{
    //atributos
    int *filho0_; //ponteiro para os filho0
    int *filho1_; //ponteiro para os filho1
    int maxvar_, ni_, no_, na_;
    set<int> entradas_;
    set<int> saidas_;
    
    //métodos privados
    int trata_linha_entrada_(string & linha);
    int trata_linha_saida_(string & linha);
    int trata_linha_and_(string & linha);
    int trata_linha_cabecalho_(string & linha, int &maxvar, int &ni, int &no, int &na);
    
    //interface publica da classe
    public: 
    aig(string& filename); //construtor da classe
    int print();

};

void create_aiger(string &);

int main()
{
    string s("sat");
    create_aiger(s);
    
    aig meu_aig(s);
    meu_aig.print();
    return 0;
}

//cria arquivo aiger no formato ASCII
void create_aiger(string & filename)
{
    ofstream aiger_out(filename);
    aiger_out<<"aag 11 5 0 2 6"<<endl;
    aiger_out<<"2"<<endl;
    aiger_out<<"4"<<endl;
    aiger_out<<"6"<<endl;
    aiger_out<<"8"<<endl;
    aiger_out<<"10"<<endl;
    aiger_out<<"19"<<endl;
    aiger_out<<"23"<<endl;
    aiger_out<<"12 6 2"<<endl;
    aiger_out<<"14 8 6"<<endl;
    aiger_out<<"16 15 4"<<endl;
    aiger_out<<"18 17 13"<<endl;
    aiger_out<<"20 15 10"<<endl;
    aiger_out<<"22 21 17"<<endl;
    aiger_out.close();

}

int aig::trata_linha_entrada_(string & linha)
{//coloca entrada na estrutura do AIG
    istringstream in(linha);
    int entrada;
    in >> entrada;
    cout <<"in="<< entrada << endl;
    entradas_.insert(entrada);
    return 0;
}

int aig::trata_linha_saida_(string & linha)
{//coloca saida na estrutura do AIG
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

int aig::trata_linha_cabecalho_(string & linha, int &maxvar, int &ni, int &no, int &na)
{
    istringstream in(linha);
    int l;
    string word;
    in >> word; cout<<"string discarded ="<<word<<endl;
    in >> maxvar; cout<<"number of variables is ="<<maxvar<<endl;
    in >> ni; cout<<"number of inputs is ="<<ni<<endl;  
    in >> l; cout<<"number of latches is ="<<l<<endl;  
    in >> no; cout<<"number of outputs is ="<<no<<endl;  
    in >> na; cout<<"number of ands is ="<<na<<endl;  
    maxvar_=maxvar; 
    ni_=ni; 
    no_=no; 
    na_=na;
    return 0;
}

aig::aig(string& filename)
{
    int i=0;
    ifstream aiger_in(filename);                            //ifstream: classe para a leitura do arquivo
    char buffer[200];                                       // buffer de linha
    aiger_in.getline(buffer, 200, '\n');                    //lê a linha header para colocar no buffer
    string cabecalho(buffer);                               //cria objeto string cabecalho, com o conteúdo do buffer
    int maxvar, ni, no, na;                                 //define as variáveis da tupla M I L O A={maximum, inputs, latches, outputs, ands}
    trata_linha_cabecalho_(cabecalho, maxvar, ni, no, na);  //"setter" das variáveis do aig a partir dos valores do cabeçalho
    filho0_=new int[maxvar+1];                              //aloca array para os filhos0_ com um elemento a mais que o número máximo de variáveis 
    filho1_=new int[maxvar+1];                              //aloca array para os filhos1_ com um elemento a mais que o número máximo de variáveis 
    
    //lê as próximas linhas do aig e vai bufferizando
    while (aiger_in.getline(buffer, 200, '\n'))
    {
        i++;                            //indexador de linha
        string s(buffer);               //pega o valor do bufferizado e constroi s.
        
        if (i<=ni){                     //=>Se i está indexando uma entrada
        cout<<"adiciona entrada"<<endl;
        trata_linha_entrada_(s);
        }
        
        else if (i<=(ni+no)){           //=>Se i está indexando uma saída
        cout<<"adiciona saida"<<endl;
        trata_linha_saida_(s);
        }
        else if (i<=(ni+no+na)){
        cout<<"adiciona and"<<endl;
        trata_linha_and_(s);
        }
    }
}


//método de impressão das Entradas, Saídas e ANDs
int aig::print(){
 
    cout<<"Agora vou imprimir"<<endl;
    set<int>::iterator itr;
    for (itr = entradas_.begin(); itr != entradas_.end(); itr++) {
        cout <<"entrada =" << *itr << endl;
    }  
    
    for (itr = saidas_.begin(); itr != saidas_.end(); itr++) {
        cout <<"saida =" << *itr << endl;
    }   
    for (int i=ni_+1; i<(ni_+1+na_); i++)
    {
        cout << "AND   "<<i*2<<"="<<filho0_[i]<<"*"<<filho1_[i]<<endl;
    }
    return 0;
}

