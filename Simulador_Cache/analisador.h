//
// Created by lucp2 on 17/09/16.
//

#pragma once

#include "processador.h"
#include "Memoria.h"
#include <iostream>
#include <vector>

using namespace std;

class analisador {
private:
    static unsigned long int tamanho;
	static unsigned long int fim;

public:
    static int num_const;
    static unsigned long getTamanho();
//    static vector<pair<string, int> > constantes;

public:
    static void poe_na_memoria(class Memoria *m, vector<string> linhas);
	static void imprime_assembler();
    static int binario_pra_decimal(int n);
};

