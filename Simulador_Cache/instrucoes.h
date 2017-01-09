//
// Created by lucp2 on 17/09/16.
//

#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

class instrucoes{
private:
    vector<pair<string,string> > comandos;
    vector<pair<string,string> > registradores;
public:
    instrucoes(string caminho_comandos, string caminho_registradores);
    bool pega_info(string caminho_comandos, string caminho_registradores);

};
