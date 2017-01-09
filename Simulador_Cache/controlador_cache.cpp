//
// Created by Lucca Portes on 19/11/16.
//

#include "controlador_cache.h"


vector<pair<int, string> > controlador_cache::cache = {};
int controlador_cache::cache_miss = 0;
int controlador_cache::cache_hit = 0;
//
//void controlador_cache::pede_ip(int ip) {
//    cout << "\n\nInicio do fetch (Busca instrucao atraves do B_E) \n";
//    if(mem->get_mem(cs_ip - fila.size() * 2).substr(0, 6) != "011101")
//        cs_ip += 2;
//    processador_memoria::set_barramento_endereco(cs_ip);
//
//}
