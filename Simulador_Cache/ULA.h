//
// Created by root on 10/8/16.
//

#ifndef SIMULADOR_ULA_H
#define SIMULADOR_ULA_H

#include "processador.h"
#include <string>

using namespace std;


class ULA {
friend class processador;
private:
    int ula_in_1, ula_in_2, ula_out;
	bool overflow, signal;
public:

    ULA();

    int getUla_in_1() const;

    void setUla_in_1(int ula_in_1);

    int getUla_in_2() const;

    void setUla_in_2(int ula_in_2);

    int getUla_out() const;

    void setUla_out(int ula_out);

    int binario_pra_decimal(int n);

    void adiciona();
    void subtrai();
    void multiplica();
    void divide();
    void incrementa();
    void decrementa();
    void faz_and();
    void faz_xor();
    void faz_not();
    void completa_7_bits(string &entrada);

	bool checa_overflow();
	bool checa_signal();
    string to_binary(int n);

    void faz_or();
};


#endif //SIMULADOR_ULA_H
