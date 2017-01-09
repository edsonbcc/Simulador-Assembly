//
// Created by lucp2 on 17/09/16.
//

#include "instrucoes.h"
 instrucoes::instrucoes(string caminho_comandos, string caminho_registradores) {
     pega_info(caminho_comandos, caminho_registradores);
 }
bool instrucoes::pega_info(string caminho_comandos, string caminho_registradores) {
    ifstream arq_comandos(caminho_comandos.c_str());
    ifstream arq_registradores(caminho_registradores.c_str());
    unsigned int i, delimitador_1 = 0, delimitador_2 = 0;
    bool delimit1, delimit2;
    string linha;

    if (arq_comandos || arq_registradores){
        while(getline(arq_comandos, linha)){
            delimit1 = false;
            delimit2 = false;
            if (linha != "") {
                for (i = 0; i < linha.size(); i++) {
                    if (linha[i] == ' ' && !delimit1) {
                        delimitador_1 = i;
                        delimit1 = true;
                    } else if (linha[i] == ' ' && !delimit2) {
                        delimitador_2 = i;
                        delimit2 = true;
                    }
                }
                comandos.push_back(make_pair(linha.substr(0, delimitador_1),
                                             linha.substr(delimitador_1 + 1, delimitador_2 - delimitador_1)));
            }
        }
        while(getline(arq_registradores, linha)){
            delimit1 = false;
            delimit2 = false;
            if (linha != "") {
                for (i = 0; i < linha.size(); i++) {
                    if (linha[i] == ' ' && !delimit1) {
                        delimitador_1 = i;
                        delimit1 = true;
                    } else if (linha[i] == ' ' && !delimit2) {
                        delimitador_2 = i;
                        delimit2 = true;
                    }
                }
                registradores.push_back(make_pair(linha.substr(0, delimitador_1),
                                                  linha.substr(delimitador_1 + 1, delimitador_2 - delimitador_1)));
            }
        }
    }
    for(i = 0; i < comandos.size(); i++) {
        cout << comandos[i].first << ", " << comandos[i].second << endl;
    }

    for(i = 0; i < registradores.size(); i++) {
        cout << registradores[i].first << ", " << registradores[i].second << endl;
    }

    return true;
}