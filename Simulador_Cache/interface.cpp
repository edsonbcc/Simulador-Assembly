//
// Created by lucp2 on 18/09/16.
//

#include "interface.h"


bool _interface::modo_indireto = true;


_interface::_interface() {
    cons = new console;
}

void _interface::display_direto(class console *consol, vector<int> dados) {
    consol->imprime_console();
    imprime_dados(dados);

}

void _interface::display_debug(class console *consol, vector<int> dados) {
    consol->imprime_console();
    imprime_dados(dados);
}

void _interface::imprime_dados(vector<int> dados){
    cout << "AX: " << dados[0] << " BX: " << dados[1] << " CX: " << dados[2] << " DX: " << dados[3] << " CS:IP: " << dados[4];
}

void _interface::imprime_op() {
    cout << "digite a opção(h para ajuda): ";
    cin >> op;

}

void _interface::escreve_console(class console *consol, string texto) {
    consol->insert_string(texto);
}

void _interface::display_atualiza(vector<int> dados, deque<string> fila, stack<int> pilha, string* mem, vector<pair<int, string> > cache) {
    // system("clear");
//    cons->imprime_console();
	if (modo_indireto) {
		CYELLOW cout << "____________________________________________________________" << endl;
		CPINK cout << " AX: " << dados[0];
		CRED cout << "\t BX: " << dados[1];
		CGREEN cout << "\t CX: " << dados[2];
		CYELLOW cout << "\t DX: " << dados[3];
		CBLUE cout << "\t CS:IP: " << dados[4];
		CLBLUE cout << "\t CS:IP (original): " << dados[21];
		CPINK cout << "\t SP: " << dados[18] << endl;
		CLBLUE cout << " BI: " << dados[5];
		//            << " \nB_D: " << processador_memoria::getBarramento_dados()
		cout << "\t BE: " << dados[6];
		cout << "\t BD : " << processador_memoria::getBarramento_dados() << endl;
		CPINK cout << " AX IN : " << dados[7];
		cout << "\t AX OUT : " << dados[8] << endl;
		CRED cout << " BX IN : " << dados[9];
		cout << "\t BX OUT : " << dados[10] << endl;
		CGREEN cout << " CX IN : " << dados[11];
		cout << "\t CX OUT : " << dados[12] << endl;
		CYELLOW cout << " DX IN : " << dados[13];
		cout << "\t DX OUT : " << dados[14] << endl;
		CLBLUE cout << " ULA IN 1 : " << dados[15];
		cout << "\t ULA IN 2 : " << dados[16];
		cout << "\t ULA OUT : " << dados[17] << endl;
		CPINK cout << " OV : " << dados[19];
		cout << "\t SIGNAL: " << dados[20] << endl;
        cout << "CACHE_HIT: " << dados[22];
        cout << " CACHE_MISS: " << dados[23];
        cout << " CACHE_HIT: : " << dados[24] << "%" << endl;
		CYELLOW cout << "____________________________________________________________" << endl;
		CGRAY
			//    cout << "ax: " << proc->getax()
			//         << "\nbx: " << proc->getbx()
			//         << "\ncx: " << proc->getcx()
			//         << "\ndx: " << proc->getdx()
			//         << "\ncs:ip: " << proc->getcs_ip()
			//         << "\nbarramento de dados: " << processador_memoria::getBarramento_dados()
			//         << "\nbarramento de enderecos: " << processador_memoria::getBarramento_endereco();
			int a = getchar();
		if (a == 104)
			estruturas_adicionais(fila, pilha);
        else if (a == 109)
            display_memoria(mem);
        else if (a == 99)
            display_cache(cache);
	}
}



void _interface::display_memoria(string* mem){
    cout << "\n\nDigite a posicao da memoria de que deseja verificar: ";
    int pos;
    cin >> pos;
    for(int i = pos - 5; i < pos + 5; i++){
        cout << i << "\t";
    }
    cout << endl;
    for(int i = pos - 5; i < pos + 5; i++){
        cout << mem[i] << "\t";
    }
    cout << endl;
    getchar();

}

void _interface::estruturas_adicionais(deque<string> fila, stack<int> pilha) {
    cout << "\n\n" << "fila:\n";
    if(fila.empty())
        cout << "fila vazia\n";
    else {
        while (!fila.empty()) {
            string x = fila.front();
            fila.pop_front();
            cout << x << "\n";

        }
    }
    cout << "\npilha\n";
    if(pilha.empty())
        cout <<"pilha vazia\n";
    else
        while(!pilha.empty()){
            int aux = pilha.top();
            pilha.pop();
            cout << aux << "\n";
        }

    getchar();
}

void _interface::display_cache(vector<pair<int, string> > cache) {
    for(int i = 0; i < cache.size(); i++){
        cout << i << "\t" << cache[i].first << ", " << cache[i].second << endl;
    }

}
