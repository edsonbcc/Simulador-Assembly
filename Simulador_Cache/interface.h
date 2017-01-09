//
// Created by lucp2 on 18/09/16.
//
#pragma once

#include "console.h"
#include "processador.h"
#include <deque>
#include "processador_memoria.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <stack>
#include "cor.h"



using namespace std;

class _interface {
private:
    //processador *proc;
    console *cons;
	text_color cor;
public:
    string op;
	static bool modo_indireto;
    _interface();
    void display_direto(class console *consol, vector<int> dados);
    void display_atualiza(vector<int> dados, deque<string> fila, stack<int> pilha, string* mem, vector<pair<int, string> > cache);
    void display_memoria(string* mem);
    void display_debug(class console *consol, vector<int> dados);
    void imprime_dados(vector<int> dados);
    void display_cache(vector<pair<int, string> > cache);
    void imprime_op();
    void escreve_console(class console *consol, string texto);
    void estruturas_adicionais(deque<string> fila, stack<int> pilha);
};

