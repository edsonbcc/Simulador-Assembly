//
// Created by lucp2 on 17/09/16.
//

#include "arquivo.h"

arquivo::arquivo(string _caminho){
    caminho = _caminho;
    ifstream arqui(caminho.c_str());
    string linha;
    if (arqui){
        while (getline( arqui, linha )){
            if(linha == "")
                break;
            linhas.push_back(linha);
            operador.push_back(linha.substr(0,6));
            op1.push_back(linha.substr(6,3));
            op2.push_back(linha.substr(9,7));
        }
        arqui.close();
    }
    else cout << "Unable to open file";
     for (int i =0; i < operador.size(); i++){
     	cout<< "operador " << operador[i] << endl;
     	cout<< "op1 " << op1[i] << endl;
     	cout<< "op2 " << op2[i] << endl;
     }
}

vector<string> arquivo::get_linhas() {
    return linhas;
}

void arquivo::operator=(const arquivo &rhs) {
    caminho = rhs.caminho;
    linhas = rhs.linhas;
    operador = rhs.operador;
    op1 = rhs.op1;
    op2 = rhs.op2;
}