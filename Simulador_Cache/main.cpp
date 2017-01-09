//
// Created by Edson Monteiro and Lucca Portes on 17/09/16.
//

#include "arquivo.h"
#include "instrucoes.h"
#include "processador.h"
#include "analisador.h"
#include "interface.h"
#include "executor.h"
#include "console.h"
#include <stdlib.h>



int main(){
	analisador::imprime_assembler();
	system("Montador");
	system("CLS");
	analisador::imprime_assembler();
	cout << "Voce quer o modo indireto\n1-sim\n2-nao\n";
	int escolha;
	cin >> escolha;
	if (escolha == 1)
		_interface::modo_indireto = true; //true
	else
		_interface::modo_indireto = false; // false
    arquivo *arq;
    arq = new arquivo("codigo_binario.txt");
    //instrucoes *inst;
    //inst = new instrucoes("instrucoes_att.txt", "registradores_att.txt");
    _interface *inter;
    inter = new _interface();
    Memoria *memoria;
    memoria = new Memoria();
    processador *proc;
    proc = new processador(inter, memoria);
    analisador::poe_na_memoria(memoria,arq->get_linhas());
//    proc->fetch_processador();
//    memoria->fetch_memoria();
//    proc->decodifica();
//    proc->fetch_processador();
//    memoria->fetch_memoria();
//    proc->decodifica();
	
    proc->faz_ciclos();
    console *cons;
    cons = new console();
//    _interface *inter;
//    inter = new _interface();
//    inter->escreve_console(cons, "oii");
//    inter->display_direto(cons, proc->zipa_dados());

	cin.ignore();
	getchar();

    return 0;
}