#include <iostream>
#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include "aig.h"
#include "bdd.h"

using namespace std;

int main(){
    string filename("sat"); //define o nome do arquivo fonte para o objeto aig em memória
    
    cout <<"Cria instância de objeto aig em memória: "<<endl;
    aig aig_(filename);

    cout <<"----------------------"<<endl;
    aig_.print();
	
	cout <<"----------------------"<<endl;
   	aig_.run_aig_topologic();

    cout <<"----------------------"<<endl;
    aig_.recreate_aiger_ascii();
    cout <<"----------------------"<<endl;
    

    cout<<"Trabalho 3 (T3)"<<endl;

    int* nodos_saida = aig_.busca_nodos_saida();
    int saida0 = nodos_saida[0];
    int saida1 = nodos_saida[1];
   
    int* entradas_s0 = aig_.busca_filhos_nodo(saida0); 
    int* entradas_s1 = aig_.busca_filhos_nodo(saida1);    
    /////string s0(to_string(nodos_saida[0]));
    
    cout <<"----------------------------"<<endl;   
    cout<<"Entrada s0: "<< entradas_s0[0]<<endl;
    cout<<"Entrada s0: "<< entradas_s0[1]<<endl;

    cout<<"Entrada s1: "<< entradas_s1[0]<<endl;
    cout<<"Entrada s1: "<< entradas_s1[1]<<endl;
    cout <<"----------------------------"<<endl; 
    int igual = 0;
    if(entradas_s0[0] == entradas_s1[1]){
        igual= entradas_s0[0];
    }

    gerentebdd g;
    if(igual!=0) {
        
        cout<<"Calling: g.cadastravariavel(\"c\")"<<endl;
        int vc = g.cadastravariavel(to_string(entradas_s1[1]));
        
        cout <<"----------------------------"<<endl;         
        cout<<"Calling: g.cadastravariavel(\"b\")"<<endl;
        int vb = g.cadastravariavel(to_string(igual));   
        
        cout <<"----------------------------"<<endl;     
        cout<<"Calling: g.cadastravariavel(\"a\")"<<endl;
        int va = g.cadastravariavel(to_string(entradas_s0[0]));
        
        cout <<"-----------------------------------------------"<<endl;
        //uso De Morgan para obter o resultado das Nand's: !(a*b) = !a + !b
        cout<<"Por equivalência lógica\nos Resultados das Saídas são:"<<endl;
        int n_va = g.inv(va);        
        int n_vb = g.inv(vb);
        int n_vc = g.inv(vc);

        int negAandB = g.or2(n_va, n_vb);       
        cout<<"!(a*b)= "<< negAandB << endl;

        int negBandC = g.or2(n_vb, n_vc);
        cout<<"!(b*c)= "<< negBandC << endl;

        cout <<"-----------------------------------------------"<<endl;
    }

    return 0;
}
