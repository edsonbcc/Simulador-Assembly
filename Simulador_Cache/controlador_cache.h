//
// Created by Lucca Portes on 19/11/16.
//

#ifndef SIMULADOR_CACHE_CONTROLADOR_CACHE_H
#define SIMULADOR_CACHE_CONTROLADOR_CACHE_H

#include <iostream>
#include <vector>
#include <string>
#include "processador.h"

using namespace std;

class controlador_cache {
    friend class processador;
private:
    static vector<pair<int, string> > cache;
    static int cache_hit;
    static int cache_miss;
    void pede_ip(int ip);
};



#endif //SIMULADOR_CACHE_CONTROLADOR_CACHE_H
