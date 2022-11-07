
using namespace std;

#include "t2.h"


//*************************************************************************
int main()
{
	//define o nome do arquivo fonte para o objeto aig em memória
    string filename("sat");

    cout <<"Cria instância de objeto aig em memória: "<<endl;
    aig aig_local(filename);

    cout <<"----------------------"<<endl;
    //imprime objeto aig local
    aig_local.print();

	cout <<"----------------------"<<endl;
	//percorre o aig topologicamente
   	run_aig_topologic(aig_local);

    cout <<"----------------------"<<endl;
    //exporta o aig instânciado em memória para um arquivo texto
    recreate_aiger_ascii(aig_local);

    return 0;
}


int aig::trata_linha_entrada_(string & linha)
{
    istringstream in(linha);
    int entrada;
    in >> entrada;
    cout <<"in = "<< entrada << endl;
    entradas_.insert(entrada);		//entradas_ é um: set<int>
    return 0;
}

int aig::trata_linha_saida_(string & linha)
{
    istringstream in(linha);
    int saida;
    in >> saida;
    cout <<"out = "<< saida << endl;
    saidas_.insert(saida);		//saidas_ é um: set<int>

    return 0;	//para indicar que deu tudo certo!
}

/*
* nas linhas "AND" pega os filhos{filho0 e filho1}
*
*/
int aig::trata_linha_and_(string & linha)
{
	//https://cplusplus.com/reference/sstream/istringstream/
    istringstream in(linha);
    
    int saida, entrada0, entrada1;
    
    in >> saida;
    cout <<"conecta pino = "<< saida << endl;

    in >> entrada0;
    cout <<"conecta pino = "<< entrada0 << endl;
    
    in >> entrada1;
    cout <<"conecta pino = "<< entrada1 << endl;
    
    saida = saida/2;	//+/- o número das "ANDs" corresponde ao dobro do número da linha???
    
    filho0_[saida] = entrada0; //indexa vinculada ao valor de saida???
    filho1_[saida] = entrada1;

    return 0;	//se deu tudo certo!
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

    return 0; //para indicar que deu tudo certo!
}
//Contrutor do aig; Recebe o nome do arquivo. Bufferiza e a partir di buffer vai setando nos atributos do objeto aig.
// Aloca memória para os filhos.
aig::aig(string& filename)
{
    int i=0;
    ifstream aiger_in(filename);
    char buffer[200];
    aiger_in.getline(buffer, 200, '\n');
    string cabecalho(buffer);
    int maxvar, ni, nl, no, na;
    trata_linha_cabecalho_(cabecalho, maxvar, ni, nl, no, na); //Antes da declaração de filho0_ e filho1_

    filho0_ = new int[maxvar+1]; //PQ maxvar+1 ???
    filho1_ = new int[maxvar+1];

    while (aiger_in.getline(buffer, 200, '\n'))
    {
        i++;
        string s(buffer);

        if (i<=ni){ //estaLendoEntradas
          cout<<"adiciona entrada"<<endl;
          trata_linha_entrada_(s);
        }
        else if (i<=(ni+no)){ //estaLendoSaidas
          cout<<"adiciona saida"<<endl;
          trata_linha_saida_(s);
        }
        else if (i<=(ni+no+na)){ //estaLendoAnds
          cout<<"adiciona and"<<endl;
          trata_linha_and_(s);
        }
    }
}

//*************************************************************************
int aig::print(){

    cout<<"Agora vou imprimir"<<endl;
    set<int>::iterator itr;
    for (itr = entradas_.begin(); itr != entradas_.end(); itr++) {
        cout <<"entrada =" << *itr << endl;
    }

    for (itr = saidas_.begin(); itr != saidas_.end(); itr++) 
    {
        cout <<"saida =" << *itr << endl;
    }

    for (int i=ni_+1; i<(ni_+1+na_); i++)
    {
        cout << "AND   "<<i*2<<"="<<filho0_[i]<<"*"<<filho1_[i]<<endl;
    }
    return 0;
}
