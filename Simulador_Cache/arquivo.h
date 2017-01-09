//
// Created by lucp2 on 17/09/16.
//

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

class arquivo {
    friend class processador;
private:
    string caminho;
    vector<string> linhas;
    vector<string> operador;
    vector<string> op1;
    vector<string> op2;
public:
    arquivo(string _caminho);
    //abre();
    vector<string> get_linhas();

    void operator=(const arquivo &rhs);

};