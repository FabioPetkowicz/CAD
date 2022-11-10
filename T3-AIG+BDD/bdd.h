#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

//CHAVE UNICA____________________________________________________________________
class ChaveUnica {
    int indice_;
    map<string, int> chaves_;
      
    public:
        ChaveUnica (); //Construtor da Classe ChaveUnica. Apenas instancia em memória.
        int createKey(int var, int  f0, int f1); //define o valor da chave para o nodo
};

//NODO DO BDD____________________________________________________________________
class nodobdd{
    int variavel_;
    int f0_;
    int f1_;
public:
    nodobdd(); 								 //Construtor da Classe nodobdd
    int inicializa(int var, int f0, int f1); //inicializa os atributos da classe.
    void imprime(ostream& saida); 			//NAO DEFINIDO...?
    //getters:    
    int variavel(); //getter para variavel
    int f0();       //getter para f0
    int f1();       //getter para f1

};

// GERENTE BDD____________________________________________________________________
class gerentebdd {
    ChaveUnica tabelaunica_;        //tabela unica das chaves
    map<string, int> var_indices_;  //me diz o numero da variavel a partir do nome (string)
    vector <string> variaveis_;     // me diz o nome (string) da variavel a partir do número
    vector <nodobdd> nodos_;        // armazena os nodos do BDD, indexados por um indice inteiro
    int proximoIdNodo_;             // armazena o proximo ID que vamos usar para o nodo (quase um contador)
    int proximoIndiceVar_;          // armazena o proximo ID que vamos usar para a variavel (quase um contador)
public:
    gerentebdd();
    int cadastravariavel(string s);
    int ite(int, int, int);
    int and2(int, int);
    int or2(int, int);
    int inv(int);
};

//ChaveUnica Definições dos Métodos______________________________________________
ChaveUnica::ChaveUnica() {
    indice_=2;  //indice acima do máximo a ser indexado
}

int ChaveUnica::createKey(int var, int  f0, int f1) {
    if (f0 == f1) return f0; //regra da redundancia do BDD, nao pode apontar duas vezes pro mesmo lugar
    if (f0 >= indice_) exit(0); //aponta para nodo que ainda não existe: erro; Sai do programa
    if (f1 >= indice_) exit(0); //aponta para nodo que ainda não existe: erro; Sai do programa

    int retorno=-1;
    
    ostringstream saida; 
    saida<< var <<"/"<< f0 << "/" << f1;
    string chave = saida.str(); 
    map<string, int>::iterator it;
    it = chaves_.find(chave);
    
    //Se nodo nao existe, deve ser criado
    if (it == chaves_.end()) {
        retorno = indice_;
        chaves_[chave]=indice_;
        indice_++;
    } 
    else { //nodo existe, eh o segundo elemento do iterador do mapa
        retorno = it->second;
    }

    cout<<"cadastra("<<var<<","<<f0<<","<<f1<<")  ";
    cout<<"chave ="<<chave;
    cout<<"  indice ="<<retorno<<endl;

    return retorno;
}
//_______________________________________________________________________________

//Definições classe NodoBDD______________________________________________________
nodobdd::nodobdd(){}

int nodobdd::inicializa(int var, int f0, int f1) {
    variavel_=var;   
    f0_=f0;   
    f1_=f1; 
    return 0;
}
//********************GETTERS CLASSE nodobdd****************************
int nodobdd::variavel()
{return variavel_;}

int nodobdd::f0()
{return f0_;}

int nodobdd::f1()
{return f1_;}

//---------------------------------------------------------------------------

gerentebdd::gerentebdd( ) {
    proximoIdNodo_=2;
    proximoIndiceVar_=0;
    variaveis_.resize(1000);
    nodos_.resize(1000);
}
//***************************************************************************
int gerentebdd::cadastravariavel(string v) {
	
	int index_var_temp;
	map<string, int>::iterator it;
	it=var_indices_.find(v);

	if (it == var_indices_.end()) {
	    index_var_temp = proximoIndiceVar_;
	}
	else {
	    index_var_temp = var_indices_[v];
	}

	int nodoretorno = tabelaunica_.createKey(index_var_temp, 0, 1);

	if ( nodoretorno == proximoIdNodo_) {//nodo nao existe, deve ser criado
	    var_indices_[v] = proximoIndiceVar_;
	    variaveis_[proximoIndiceVar_] = v;
	    nodos_[nodoretorno].inicializa(index_var_temp, 0, 1);
	    proximoIdNodo_++;
	    proximoIndiceVar_++;
	}
	else {//nodo existe, eh o segundo elemento do iterador do mapa
	    nodoretorno = it->second;
	}
	return nodoretorno;
}
//***************************************************************************
int gerentebdd::ite(int condicao, int entao, int senao) {
    int indiceTmp;
    int nodoretorno = 0;
    
    if (condicao == 1) {
        return entao;
    }
    else if (condicao == 0) {
        return senao;
    }
    else if ((entao == 1) && (senao == 0)) {
        return condicao;
    }
    else {   //nivelar o topo assumindo variavel 0 na raiz do BDD (menor o valor, variavel mais alta) 
            indiceTmp = nodos_[condicao].variavel();

            if (entao !=0 && entao !=1 && nodos_[entao].variavel()<indiceTmp) {
                indiceTmp= nodos_[entao].variavel();
            }

            if (senao !=0 && senao !=1 && nodos_[senao].variavel()<indiceTmp) {
                indiceTmp= nodos_[senao].variavel();
            }

            int condicao_cf0, condicao_cf1, entao_cf0, entao_cf1,
                    senao_cf0, senao_cf1, n0, n1;  
            
            if (indiceTmp < (nodos_[condicao].variavel()) ) {
                condicao_cf0 = condicao; condicao_cf1 = condicao;
            }
            else {
                condicao_cf0 = nodos_[condicao].f0(); condicao_cf1 = nodos_[condicao].f1();
            }

            if (indiceTmp < (nodos_[entao].variavel()) || entao==0 || entao==1) {
                entao_cf0 = entao; entao_cf1 = entao;
            }
            else {
                entao_cf0 = nodos_[entao].f0(); entao_cf1 = nodos_[entao].f1();
            }

            if (indiceTmp < (nodos_[senao].variavel()) || senao==0 || senao==1) {
                senao_cf0 = senao; senao_cf1 = senao;}
            else {
                senao_cf0 = nodos_[senao].f0(); senao_cf1 = nodos_[senao].f1();
            }
        
            n0=ite(condicao_cf0, entao_cf0, senao_cf0);
            n1=ite(condicao_cf1, entao_cf1, senao_cf1);

            nodoretorno=tabelaunica_.createKey(indiceTmp, n0, n1);
            if (nodoretorno==proximoIdNodo_) {
                //nodo nao existe, deve ser criado
                //var_indices_[v]=proximoIndiceVar_;
                //variaveis_[proximoIndiceVar_] = v;
                nodos_[nodoretorno].inicializa(indiceTmp, n0, n1);
                proximoIdNodo_++;
                //proximoIndiceVar_++;
            }
    }
    return nodoretorno;
}
//***************************************************************************
int gerentebdd::and2(int bdd1, int bdd2) {
    return ite(bdd1, bdd2, 0);
}
//***************************************************************************
int gerentebdd::or2(int bdd1, int bdd2) {
    return ite(bdd1, 1, bdd2);
}
//***************************************************************************
int gerentebdd::inv(int bdd1) {
    return ite(bdd1, 0, 1);
}
//***************************************************************************

