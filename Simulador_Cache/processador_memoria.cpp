//
// Created by root on 10/8/16.
//

#include "processador_memoria.h"

int processador_memoria::barramento_endereco = 0;

string processador_memoria::barramento_dados = "0";

int processador_memoria::getBarramento_endereco(){
    return barramento_endereco;
}

string processador_memoria::getBarramento_dados(){
    return barramento_dados;
}

void processador_memoria::set_barramento_endereco(int barramento_endereco_) {
    barramento_endereco = barramento_endereco_;
}

void processador_memoria::setBarramento_dados(string barramento_dados_) {
    barramento_dados = barramento_dados_;
}
