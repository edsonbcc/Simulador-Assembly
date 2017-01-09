//
// Created by root on 10/8/16.
//

#include "Memoria.h"

Memoria::Memoria() {

}

void Memoria::set_mem(string valor, int posicao){
    mem[posicao] = valor;
}

string Memoria::get_mem(int posicao) {
    return mem[posicao];
}

string* Memoria::retorna_memoria(){
	return mem;
}

void Memoria::fetch_memoria() {
    int indice = processador_memoria::getBarramento_endereco();
    processador_memoria::setBarramento_dados(mem[indice]);
}

void Memoria::set_mem_part_1() {
    indice_temp = processador_memoria::getBarramento_endereco();
}

void Memoria::set_mem_part_2() {
     mem[indice_temp] = processador_memoria::getBarramento_dados();
}

