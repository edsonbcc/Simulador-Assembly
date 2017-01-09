//
// Created by lucp2 on 17/09/16.
//
#pragma once

#include <iostream>
#include <string>
#define TAM 30

using namespace std;

class console {
private:
    char consol[TAM][TAM];
public:
    console();
    void prenche_bordas();
    void insert_string(string str);
    void pula_linha();
    void imprime_console();
};

