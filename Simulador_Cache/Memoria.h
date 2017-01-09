//
// Created by root on 10/8/16.
//

#ifndef SIMULADOR_MEMORIA_H
#define SIMULADOR_MEMORIA_H
#include<iostream>
#include<string>
#include "processador_memoria.h"
using namespace std;


class Memoria {
private:
    string mem[2000];
    int indice_temp;
public:
    Memoria();
    void set_mem(string valor, int posicao);
    string get_mem(int posicao);
    void fetch_memoria();
    void set_mem_part_1();
    void set_mem_part_2();
    string* retorna_memoria();

};


#endif //SIMULADOR_MEMORIA_H
