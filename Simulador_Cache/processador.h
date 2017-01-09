//
// Created by lucp2 on 17/09/16.
//
#pragma once
#define AT inter->display_atualiza(zipa_dados(), fila, pilha, mem->retorna_memoria(), cache);
#define CACHE_TAM 20

#include <iostream>
#include <deque>
#include <vector>
#include "analisador.h"
#include "ULA.h"
#include "Memoria.h"
#include "processador_memoria.h"
#include "interface.h"
#include "cor.h"
#include <stack>
#include <cmath>

using namespace std;

class processador {
//    friend class analisador;
    friend class executor;
private:
    class ULA *ula;
    string opcode_atual, ir;
    deque<string> fila;
    stack<int> pilha;
	stack<int> pilha_cs_ip;
    int ax, bx, cx, dx, cs_ip, sp;
    long int bi;
    string bi_str;
    bool ax_in, ax_out, bx_in, bx_out, cx_in, cx_out, dx_in, dx_out;
    bool equal, zero, greater, less;
    class _interface *inter;
    class Memoria *mem;
    vector<pair<int, string> > cache;
    int cache_hit;
    int cache_miss;
	text_color cor;
//    vector<pair<> >

public:
    //funcoes cache
    void pede_ip(int ip);

    processador(class _interface *inter, class Memoria *mem_);
    void executa();
    void set_ax(int valor);
    void set_bx(int valor);
    void set_cx(int valor);
    void set_dx(int valor);
    void set_csip(int valor);
    void faz_ciclos();
    void prefetch();
    static void chama_at();
//    void set_mem(int valor, int posicao);
    int getax();
    int getbx();
    int getcx();
    int getdx();
    int getcs_ip();
    int binario_pra_decimal(int n);
    vector<int> zipa_dados();

    void MOV1();
    void MOV2();
    void INICIO();
    void ADD();
    void SUB();
    void PUSH();
    void POP();
    void MUL();
    void DIV();
    void JMP();
    void CMP();
    void JE();
    void JNE();
    void JZ();
    void JNZ();
    void JG();
    void JGE();
    void JL();
    void JLE();
    void INC();
    void DEC();
    void STORE1();
    void STORE2();
    void AND();
    void OR();
    void XOR();
    void NOT();
    void NEG();
    void MOV3();
    void MOV4();
	void CALL();
	void RET();
    void fetch_processador();
    void decodifica();
    void preenche_cache(int ip);
    bool checa_cache(int pos);
	void escreve_cache_1(int ip, string dado);
	void escreve_cache_2(int ip, string dado);


    
};



