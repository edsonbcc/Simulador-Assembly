//
// Created by root on 10/8/16.
//

#ifndef SIMULADOR_PROCESSADOR_MEMORIA_H
#define SIMULADOR_PROCESSADOR_MEMORIA_H

#include <iostream>
#include <string>

using namespace std;


class processador_memoria {
private:
    static int barramento_endereco;
    static string barramento_dados;
public:
    static int getBarramento_endereco();

    static string getBarramento_dados();

    static void set_barramento_endereco(int barramento_endereco_);

    static void setBarramento_dados(string barramento_dados_);




};


#endif //SIMULADOR_PROCESSADOR_MEMORIA_H
