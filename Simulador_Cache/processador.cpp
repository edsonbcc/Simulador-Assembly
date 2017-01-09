//
// Created by lucp2 on 17/09/16.
//

#include "processador.h"
#include "arquivo.h"

processador::processador(_interface *inter_, Memoria *mem_){
    ula = new ULA();
    ax = 0; bx = 0; cx = 0; dx = 0; cs_ip = 100; bi = 0; sp = 0; ir = " ";
    cache_miss = 0; cache_hit = 0;
	ax_in = false; ax_out = false;
    bx_in = false; bx_out = false;
    cx_in = false; cx_out = false;
    dx_in = false; dx_out = false;
    inter = inter_;
    mem = mem_;
    //inicializa cache
    for(int i = 0; i < CACHE_TAM; i++)
         cache.push_back(make_pair(-1, ""));
}

void processador::executa() {
//    for(int i = 0; i < arqui->operador.size(); i++){
//        if (arqui->operador[i] == "001101")
//            MOV1(arqui->op1[i], arqui->op2[i]);
//
//    }
}

void processador::decodifica(){
    string opcode = processador_memoria::getBarramento_dados();AT
    cout << "fim do fetch\n";
    if(opcode.substr(0, 6) == "001101") {
        MOV1();
    }
}
void processador::set_ax(int valor){
    ax = valor;
}
void processador::set_bx(int valor){
    bx = valor;
}
void processador::set_cx(int valor){
    cx = valor;
}
void processador::set_dx(int valor){
    dx = valor;
}
void processador::set_csip(int valor){
    cs_ip = valor;
}
//void processador::set_mem(int valor, int posicao){
//    memoria[posicao] = valor;
//}

int processador::getax(){
    return ax;
}

int processador::getbx(){
    return bx;
}

int processador::getcx(){
    return cx;
}

int processador::getdx(){
    return dx;
}

int processador::getcs_ip(){
    return cs_ip;
}

vector<int> processador::zipa_dados() {
    vector<int> dados;
    dados.push_back(ax);
    dados.push_back(bx);
    dados.push_back(cx);
    dados.push_back(dx); //stoi(a)
    dados.push_back(cs_ip);
    dados.push_back(bi);
//    cout << processador_memoria::getBarramento_dados();
//    int temp = stoi(processador_memoria::getBarramento_dados());
//    dados.push_back(temp);
    dados.push_back(processador_memoria::getBarramento_endereco());
    if (ax_in)
        dados.push_back(1);
    else
        dados.push_back(0);
    if (ax_out)
        dados.push_back(1);
    else
        dados.push_back(0);
    if (bx_in)
        dados.push_back(1);
    else
        dados.push_back(0);
    if (bx_out)
        dados.push_back(1);
    else
        dados.push_back(0);
    if (cx_in)
        dados.push_back(1);
    else
        dados.push_back(0);
    if (cx_out)
        dados.push_back(1);
    else
        dados.push_back(0);
    if (dx_in)
        dados.push_back(1);
    else
        dados.push_back(0);
    if (dx_out)
        dados.push_back(1);
    else
        dados.push_back(0);
    dados.push_back(ula->getUla_in_1());
    dados.push_back(ula->getUla_in_2());
    dados.push_back(ula->getUla_out());
    dados.push_back(sp);
	if (ula->overflow)
		dados.push_back(1);
	else
		dados.push_back(0);
	if (ula->signal)
		dados.push_back(1);
	else
		dados.push_back(0);
	dados.push_back(cs_ip - fila.size() * 2);
    dados.push_back(cache_hit);
    dados.push_back(cache_miss);
    if(cache_hit + cache_miss != 0)
        dados.push_back(100 * cache_hit/(cache_hit + cache_miss));
    else
        dados.push_back(0);

    return dados;
}

int processador::binario_pra_decimal(int n) {
    int decimal = 0, i = 0, resto;
    while (n!=0) {
        resto = n % 10;
        n /= 10;
        decimal += resto * pow(2,i);
        ++i;
    }
    return decimal;
}


void processador::fetch_processador() {
    // cout << "\n\nInicio do fetch (Busca instrucao atraves do B_E) \n";
	if(mem->get_mem(cs_ip - fila.size() * 2).substr(0, 6) != "011101")
    cs_ip += 2;
    processador_memoria::set_barramento_endereco(cs_ip); 
}

void processador::prefetch() {
    if(!fila.empty()){
        if (fila.front().substr(0, 6) != "011101")
            cout << "preenchendo a fila\n";
    }
    else{
        cout << "preenchendo a fila\n";
    }

//    int i = cs_ip;
    while(fila.size() != 5){
        if(!fila.empty())
            if(fila.front().substr(0, 6) == "011101")
                break;
//        fetch_processador(); AT
//		mem->fetch_memoria();
        //cout << processador_memoria::getBarramento_dados();
		//if (processador_memoria::getBarramento_dados().size() != 16) {
		//	cout << "Fetch cancelado, n�o h� mais instrucoes";
		//	break;
		//}
		//cout << endl << "BUS_DADOS retorna instrucao solicitada atraves do B_E" << endl;
       // cout << "Fim do fetch (Instrucao foi colocada na fila(Prefetch input queue))  \n";
        pede_ip(cs_ip);
        fila.push_front(bi_str);
        if(mem->get_mem(cs_ip - fila.size() * 2).substr(0, 6) != "011101")
            cs_ip += 2;
    }

}

void processador::faz_ciclos() {
    while (ir.substr(0,6) != "011101"){
        prefetch();
        ir = fila.back();
        fila.pop_back();
		cout << "\nInstrucao a ser executada: ";
		if (ir.substr(0, 6) == "001101")
			MOV1();
		else if (ir.substr(0, 6) == "001100")
			MOV2();
		else if (ir.substr(0, 6) == "011100")
			INICIO();
		else if (ir.substr(0, 6) == "000000")
			ADD();
		else if (ir.substr(0, 6) == "000001")
			SUB();
		else if (ir.substr(0, 6) == "000010")
			MUL();
		else if (ir.substr(0, 6) == "000011")
			DIV();
		else if (ir.substr(0, 6) == "010001")
			PUSH();
		else if (ir.substr(0, 6) == "010010")
			POP();
		else if (ir.substr(0, 6) == "010011")
			JMP();
		else if (ir.substr(0, 6) == "010100")
			JE();
		else if (ir.substr(0, 6) == "010101")
			JNE();
		else if (ir.substr(0, 6) == "010110")
			JZ();
		else if (ir.substr(0, 6) == "010111")
			JNZ();
		else if (ir.substr(0, 6) == "011000")
			JG();
		else if (ir.substr(0, 6) == "011001")
			JGE();
		else if (ir.substr(0, 6) == "011010")
			JL();
		else if (ir.substr(0, 6) == "011011")
			JLE();
		else if (ir.substr(0, 6) == "000110")
			CMP();
		else if (ir.substr(0, 6) == "000100")
			INC();
		else if (ir.substr(0, 6) == "000101")
			DEC();
		else if (ir.substr(0, 6) == "000111")
			AND();
		else if (ir.substr(0, 6) == "001000")
			OR();
		else if (ir.substr(0, 6) == "001001")
			XOR();
		else if (ir.substr(0, 6) == "001010")
			NOT();
		else if (ir.substr(0, 6) == "001011")
			NEG();
		else if (ir.substr(0, 6) == "001110")
			MOV3();
		else if (ir.substr(0, 6) == "001111")
			MOV4();
		else if (ir.substr(0, 6) == "100011")
			STORE1();
		else if (ir.substr(0, 6) == "100010")
			STORE2();
		else if (ir.substr(0, 6) == "011111")
			CALL();
		else if (ir.substr(0, 6) == "100000")
			RET();
    }



	system("cls");

	_interface::modo_indireto = true;
	//analisador::imprime_assembler();
	AT

}

void processador::CALL() {
	cout << "CALL PROC\n";
	int convertido = binario_pra_decimal(stoi(ir.substr(9, 7))); AT
	convertido += 100; AT
	convertido -= analisador::num_const; AT
	pilha_cs_ip.push(cs_ip - fila.size() * 2);  AT
	fila.clear();
	bi = convertido; 
	cs_ip = bi; AT
	cout << "Fim\n";
}

void processador::RET() {
	cout << "RET\n";
	cs_ip = pilha_cs_ip.top(); AT
		cout << "cs:ip " << cs_ip << endl;
		//cs_ip += 2;
	fila.clear();
	pilha_cs_ip.pop();
	cout << "FIM\n";
}



void processador::AND() {
    if (ir.substr(6,3) == "000"){ //AND AX ___
        if(ir.substr(9,3) == "001"){
            cout << "AND AX BX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "AND AX CX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "AND AX DX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "001"){ //AND BX ___
        if(ir.substr(9,3) == "000"){
            cout << "AND BX AX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "AND BX CX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "AND BX DX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "010"){ //AND CX ___
        if(ir.substr(9,3) == "000"){
            cout << "AND CX AX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "AND CX BX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "AND CX DX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "011"){ //AND DX ___
        if(ir.substr(9,3) == "000"){
            cout << "AND DX AX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "AND DX CX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "AND DX BX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->faz_and(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }

    }
}

void processador::OR() {
    if (ir.substr(6,3) == "000"){ //OR AX ___
        if(ir.substr(9,3) == "001"){
            cout << "OR AX BX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "OR AX CX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "OR AX DX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "001"){ //OR BX ___
        if(ir.substr(9,3) == "000"){
            cout << "OR BX AX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "OR BX CX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "OR BX DX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "010"){ //OR CX ___
        if(ir.substr(9,3) == "000"){
            cout << "OR CX AX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "OR CX BX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "OR CX DX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "011"){ //OR DX ___
        if(ir.substr(9,3) == "000"){
            cout << "OR DX AX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "OR DX CX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "OR DX BX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->faz_or(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }

    }
}

void processador::NOT() {
    if (ir.substr(6,3) == "000"){ //NOT AX
        cout << "NOT AX\n";
        ax_out = true; AT
        bi = ax; AT
        ax_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->faz_not(); AT
        bi = ula->getUla_out();
        ax_in = true;
        ax = bi;
        ax_in = false;
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "001"){ //NOT BX
        cout << "NOT BX\n";
        bx_out = true; AT
        bi = bx; AT
        bx_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->faz_not(); AT
        bi = ula->getUla_out();
        bx_in = true;
        bx = bi;
        bx_in = false;
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "010"){ //NOT CX
        cout << "NOT CX\n";
        cx_out = true; AT
        bi = cx; AT
        cx_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->faz_not(); AT
        bi = ula->getUla_out();
        cx_in = true;
        cx = bi;
        cx_in = false;
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "011"){ //NOT DX
        cout << "NOT DX\n";
        dx_out = true; AT
        bi = dx; AT
        dx_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->faz_not(); AT
        bi = ula->getUla_out();
        dx_in = true;
        dx = bi;
        dx_in = false;
        cout << "Fim\n";
    }
}

void processador::NEG() {
    if (ir.substr(6,3) == "000"){ //NOT AX
        cout << "NOT AX\n";
        ax_out = true; AT
        bi = ax; AT
        ax_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->faz_not(); AT
        bi = ula->getUla_out();
        ax_in = true;
        ax = bi;
        ax_in = false;
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "001"){ //NOT BX
        cout << "NOT BX\n";
        bx_out = true; AT
        bi = bx; AT
        bx_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->faz_not(); AT
        bi = ula->getUla_out();
        bx_in = true;
        bx = bi;
        bx_in = false;
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "010"){ //NOT CX
        cout << "NOT CX\n";
        cx_out = true; AT
        bi = cx; AT
        cx_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->faz_not(); AT
        bi = ula->getUla_out();
        cx_in = true;
        cx = bi;
        cx_in = false;
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "011"){ //NOT DX
        cout << "NOT DX\n";
        dx_out = true; AT
        bi = dx; AT
        dx_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->faz_not(); AT
        bi = ula->getUla_out();
        dx_in = true;
        dx = bi;
        dx_in = false;
        cout << "Fim\n";
    }
}

void processador::XOR() {
    if (ir.substr(6,3) == "000"){ //XOR AX ___
        if(ir.substr(9,3) == "001"){
            cout << "XOR AX BX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "XOR AX CX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "XOR AX DX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
		else if (ir.substr(9, 3) == "000") {
				cout << "XOR AX AX\n";
				ax_out = true; AT
				bi = ax; AT
				ula->setUla_in_1(bi); AT
				ax_out = false; AT
				ax_out = true; AT
				bi = ax; AT
				ula->setUla_in_2(bi); AT
				ax_out = false; AT
				ula->faz_xor(); AT
				bi = ula->getUla_out(); AT
				ax_in = true; AT
				ax = bi; AT
				ax_in = false; AT
				cout << "Fim\n";
		}

    }
    else if (ir.substr(6,3) == "001"){ //XOR BX ___
        if(ir.substr(9,3) == "000"){
            cout << "XOR BX AX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "XOR BX CX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "XOR BX DX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
		else if (ir.substr(9, 3) == "001") {
			cout << "XOR BX BX\n";
			bx_out = true; AT
				bi = bx; AT
				ula->setUla_in_1(bi); AT
				bx_out = false; AT
				bx_out = true; AT
				bi = bx; AT
				ula->setUla_in_2(bi); AT
				bx_out = false; AT
				ula->faz_xor(); AT
				bi = ula->getUla_out(); AT
				bx_in = true; AT
				bx = bi; AT
				bx_in = false; AT
				cout << "Fim\n";
		}

    }
    else if (ir.substr(6,3) == "010"){ //XOR CX ___
        if(ir.substr(9,3) == "000"){
            cout << "XOR CX AX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
		else if (ir.substr(9, 3) == "010") {
			cout << "XOR cx cx\n";
			cx_out = true; AT
				bi = cx; AT
				ula->setUla_in_1(bi); AT
				cx_out = false; AT
				cx_out = true; AT
				bi = cx; AT
				ula->setUla_in_2(bi); AT
				cx_out = false; AT
				ula->faz_xor(); AT
				bi = ula->getUla_out(); AT
				cx_in = true; AT
				cx = bi; AT
				cx_in = false; AT
				cout << "Fim\n";
		}
        else if(ir.substr(9,3) == "001"){
            cout << "XOR CX BX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "XOR CX DX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "011"){ //XOR DX ___
        if(ir.substr(9,3) == "000"){
            cout << "XOR DX AX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
		else if (ir.substr(9, 3) == "011") {
			cout << "XOR dx dx\n";
			dx_out = true; AT
				bi = dx; AT
				ula->setUla_in_1(bi); AT
				dx_out = false; AT
				dx_out = true; AT
				bi = dx; AT
				ula->setUla_in_2(bi); AT
				dx_out = false; AT
				ula->faz_xor(); AT
				bi = ula->getUla_out(); AT
				dx_in = true; AT
				dx = bi; AT
				dx_in = false; AT
				cout << "Fim\n";
		}
        else if(ir.substr(9,3) == "010"){
            cout << "XOR DX CX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "XOR DX BX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->faz_xor(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }

    }
}

void processador::JL(){
    cout<<"JL\n";
    if(less){
        JMP();
        cout << "fim JL\n";
    }
}

void processador::JLE() {
    if (less || equal)
        JMP();
}
void processador::JG(){
    if(greater)
        JMP();
}

void processador::JGE(){
    if(greater || equal)
        JMP();
}

void processador::JE()	 {
    if (equal || zero)
        JMP();
}

void processador::JNE() {
    if (!equal || !zero)
        JMP();
}

void processador::JZ() {
    if (equal || zero)
        JMP();
}

void processador::JNZ() {
    if (!equal || !zero)
        JMP();
}

void processador::DEC(){
    if (ir.substr(6,3) == "000"){ //DEC AX
        cout << "DEC AX\n";
        ax_out = true; AT
        bi = ax; AT
        ax_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->decrementa();
        bi = ula->getUla_out(); AT
        ax_in = true; AT
        ax = bi; AT
        ax_in = false; AT
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "001"){ //DEC BX
        cout << "DEC BX\n";
        bx_out = true; AT
        bi = bx; AT
        bx_out = false; AT
        ula->setUla_in_1(bi);
        ula->decrementa(); AT
        bi = ula->getUla_out(); AT
        bx_in = true; AT
        bx = bi; AT
        bx_in = false; AT
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "010"){ //DEC CX
        cout << "DEC CX\n";
        cx_out = true; AT
        bi = cx; AT
        cx_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->decrementa(); AT
        bi = ula->getUla_out();
        cx_in = true; AT
        cx = bi; AT
        cx_in = false; AT
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "011"){ //DEC DX
        cout << "DEC DX\n";
        dx_out = true; AT
        bi = dx; AT
        dx_out = false; AT
        ula->setUla_in_1(bi); AT
        ula->decrementa(); AT
        bi = ula->getUla_out();
        dx_in = true; AT
        dx = bi; AT
        dx_in = false; AT
        cout << "Fim\n";
    }
}

void processador::INC(){
    if (ir.substr(6,3) == "000"){ //INC AX
        cout << "INC AX\n";
        ax_out = true;
        bi = ax;
        ax_out = false;
        ula->setUla_in_1(bi);
        ula->incrementa();
        bi = ula->getUla_out();
        ax_in = true;
        ax = bi;
        ax_in = false;
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "001"){ //INC BX
        cout << "INC BX\n";
        bx_out = true;
        bi = bx;
        bx_out = false;
        ula->setUla_in_1(bi);
        ula->incrementa();
        bi = ula->getUla_out();
        bx_in = true;
        bx = bi;
        bx_in = false;
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "010"){ //INC CX
        cout << "INC CX\n";
        cx_out = true;
        bi = cx;
        cx_out = false;
        ula->setUla_in_1(bi);
        ula->incrementa();
        bi = ula->getUla_out();
        cx_in = true;
        cx = bi;
        cx_in = false;
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "011"){ //INC DX
        cout << "INC DX\n";
        dx_out = true;
        bi = dx;
        dx_out = false;
        ula->setUla_in_1(bi);
        ula->incrementa();
        bi = ula->getUla_out();
        dx_in = true;
        dx = bi;
        dx_in = false;
        cout << "Fim\n";
    }
}

void processador::CMP(){
    if (ir.substr(6,3) == "000"){ //CMP AX ___
        if(ir.substr(9,3) == "001"){
            cout << "CMP AX BX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "FIM";

        }
        else if(ir.substr(9,3) == "010"){
            cout << "CMP AX CX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "CMP AX DX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "001"){ //CMP BX ___
        if(ir.substr(9,3) == "000"){
            cout << "CMP BX AX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "CMP BX CX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "CMP BX DX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "010"){ //CMP CX ___
        if(ir.substr(9,3) == "000"){
            cout << "CMP CX AX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "CMP CX BX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "CMP CX DX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "011"){ //CMP DX ___
        if(ir.substr(9,3) == "000"){
            cout << "CMP DX AX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "CMP DX CX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "CMP DX BX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->subtrai(); AT
            if(ula->getUla_out() == 0){
                greater = false;
                less = false;
                zero = true;
                equal = true;
            }
            else if(ula->getUla_out() < 0){
                greater = false;
                less = true;
                zero = false;
                equal = false;
            }
            else{
                greater = true;
                less = false;
                zero = false;
                equal = false;
            }
            cout << "Fim\n";
        }

    }
}

void processador::JMP(){
    cout << "JMP LABEL\n";
    int convertido = binario_pra_decimal(stoi(ir.substr(9, 7))); AT
    convertido += 100; AT
    convertido -= analisador::num_const; AT
    fila.clear(); AT
    bi = convertido; AT
    cs_ip = bi; AT
    cout << "Fim\n";
}

void processador::MOV1() {// REG - REG
    if (ir.substr(6,3) == "000"){ //MOV AX ___
        if(ir.substr(9,3) == "001"){
            cout << "MOV AX BX\n";
            bx_out = true; AT
            bi = bx; AT
            ax_in = true; AT
            ax = bi; AT
            bx_out = false; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "MOV AX CX\n";
            cx_out = true; AT
            bi = cx; AT
            ax_in = true; AT
            ax = bi; AT
            cx_out = false; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "MOV AX DX\n";
            dx_out = true; AT
            bi = dx; AT
            ax_in = true; AT
            ax = bi; AT
            dx_out = false; AT
            ax_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "001"){ //MOV BX ___
        if(ir.substr(9,3) == "000"){
            cout << "MOV BX AX\n";
            ax_out = true; AT
            bi = ax; AT
            bx_in = true; AT
            bx = bi; AT
            ax_out = false; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "MOV BX CX\n";
            cx_out = true; AT
            bi = cx; AT
            bx_in = true; AT
            bx = bi; AT
            cx_out = false; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "MOV BX DX\n";
            dx_out = true; AT
            bi = dx; AT
            bx_in = true; AT
            bx = bi; AT
            dx_out = false; AT
            bx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "010"){ //MOV CX ___
        if(ir.substr(9,3) == "000"){
            cout << "MOV CX AX\n";
            ax_out = true; AT
            bi = ax; AT
            cx_in = true; AT
            cx = bi; AT
            ax_out = false; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "MOV CX BX\n";
            bx_out = true; AT
            bi = bx; AT
            cx_in = true; AT
            cx = bi; AT
            bx_out = false; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "MOV CX DX\n";
            dx_out = true; AT
            bi = dx; AT
            cx_in = true; AT
            cx = bi; AT
            dx_out = false; AT
            cx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "011"){ //MOV DX ___
        if(ir.substr(9,3) == "000"){
            cout << "MOV DX AX\n";
            ax_out = true; AT
            bi = ax; AT
            dx_in = true; AT
            dx = bi; AT
            ax_out = false; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "MOV DX CX\n";
            cx_out = true; AT
            bi = cx; AT
            dx_in = true; AT
            dx = bi; AT
            cx_out = false; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "MOV DX BX\n";
            dx_out = true; AT
            bi = dx; AT
            bx_in = true; AT
            bx = bi; AT
            dx_out = false; AT
            bx_in = false; AT
            cout << "Fim\n";
        }

    }
}

//001100

void processador::MOV2() {// REG - IMEDIATO
    int convertido;
    if (ir.substr(6, 3) == "000") { //MOV AX ___
        convertido = binario_pra_decimal(stoi(ir.substr(9,7)));
        CGREEN cout << "MOV AX " << convertido << endl << endl;
		CGRAY cout << "BI(Barramento Interno) recebe Imediato" << endl;
        bi = convertido; AT
		CGRAY cout << "AX_in eh aberto" << endl;
        ax_in = true; AT
		CGRAY cout << "AX_in recebe BI (Barramento Interno)" << endl;
        ax = bi; AT
		CGRAY cout << "AX_in eh fechado" << endl;
		ax_in = false; AT
		CGRAY cout << "Fim da instrucao" << endl;
    }
    else if (ir.substr(6, 3) == "001") { //MOV BX ___
        convertido = binario_pra_decimal(stoi(ir.substr(9,7)));
        cout << "MOV BX " << convertido << endl;
        bi = convertido; AT
        bx_in = true; AT
        bx = bi; AT
        bx_in = false; AT
    }
    else if (ir.substr(6, 3) == "010") { //MOV CX ___
        convertido = binario_pra_decimal(stoi(ir.substr(9,7)));
        cout << "MOV CX " << convertido << endl;
        bi = convertido; AT
        cx_in = true; AT
        cx = bi; AT
        cx_in = false; AT
    }
    else if (ir.substr(6, 3) == "011") { //MOV DX ___
        convertido = binario_pra_decimal(stoi(ir.substr(9,7)));
        cout << "MOV DX " << convertido << endl;
        bi = convertido; AT
        dx_in = true; AT
        dx = bi; AT
        dx_in = false; AT
    }
}

void processador::MOV3() {// REG - MEMORIA
    int convertido;
    if (ir.substr(6, 3) == "000") { //MOV AX ___
        convertido = binario_pra_decimal(stoi(ir.substr(9,7)));
        cout << "MOV AX [" << convertido + 50 << "] (var)" << endl;
        //processador_memoria::set_barramento_endereco(convertido + 50); AT
        //mem->fetch_memoria(); AT
        //bi = stoi(processador_memoria::getBarramento_dados()); AT
		pede_ip(convertido + 50);
        ax_in = true; AT
        ax = stoi(bi_str); AT
        ax_in = false; AT
    }
    else if (ir.substr(6, 3) == "001") { //MOV BX ___
        convertido = binario_pra_decimal(stoi(ir.substr(9,7)));
        cout << "MOV BX [" << convertido + 50 << "] (var)" << endl;
        //processador_memoria::set_barramento_endereco(convertido + 50); AT
        //mem->fetch_memoria(); AT
        //bi = stoi(processador_memoria::getBarramento_dados()); AT
		pede_ip(convertido + 50);
        bx_in = true; AT
        bx = stoi(bi_str); AT
        bx_in = false; AT
    }
    else if (ir.substr(6, 3) == "010") { //MOV CX ___
        convertido = binario_pra_decimal(stoi(ir.substr(9,7)));
        cout << "MOV CX [" << convertido + 50 << "] (var)" << endl;
        //processador_memoria::set_barramento_endereco(convertido + 50); AT
        //mem->fetch_memoria(); AT
        //bi = stoi(processador_memoria::getBarramento_dados()); AT
		pede_ip(convertido + 50);
		cx_in = true; AT
        cx = stoi(bi_str); AT
        cx_in = false; AT
    }
    else if (ir.substr(6, 3) == "011") { //MOV DX ___
        convertido = binario_pra_decimal(stoi(ir.substr(9,7)));
        cout << "MOV DX [" << convertido + 50 << "] (var)" << endl;
        //processador_memoria::set_barramento_endereco(convertido + 50); AT
        //mem->fetch_memoria(); AT
        //bi = stoi(processador_memoria::getBarramento_dados()); AT
		pede_ip(convertido + 50);
		dx_in = true; AT
        dx = stoi(bi_str); AT
        dx_in = false; AT
    }
}

void processador::MOV4(){ // var - reg
    int convertido;
    if (ir.substr(13, 3) == "000") { //MOV ___ AX
        convertido = binario_pra_decimal(stoi(ir.substr(6,7)));
        cout << "MOV [" << convertido + 50 << "] AX (var)" << endl;
        //processador_memoria::set_barramento_endereco(convertido + 50); AT
        //mem->set_mem_part_1(); AT
		bi = convertido + 50; AT
		escreve_cache_1(bi, to_string(bi));
        ax_out = true; AT
        bi = ax; AT
        ax_out = false; AT
		escreve_cache_2(bi, to_string(bi));
    }
    else if (ir.substr(13, 3) == "001") { //MOV ___ BX
        convertido = binario_pra_decimal(stoi(ir.substr(6,7)));
        cout << "MOV [" << convertido + 50 << "] BX (var)" << endl;
        //processador_memoria::set_barramento_endereco(convertido + 50); AT
        //mem->set_mem_part_1(); AT
		bi = convertido + 50; AT
		escreve_cache_1(bi, to_string(bi));
        bx_out = true; AT
        bi = bx; AT
        bx_out = false; AT
		escreve_cache_2(bi, to_string(bi));
        //processador_memoria::setBarramento_dados(to_string(bi)); AT
        //mem->set_mem_part_2(); AT
    }
    else if (ir.substr(6, 3) == "010") { //MOV CX ___
        convertido = binario_pra_decimal(stoi(ir.substr(6,7)));
        cout << "MOV [" << convertido + 50 << "] CX (var)" << endl;
        //processador_memoria::set_barramento_endereco(convertido + 50); AT
        //mem->set_mem_part_1(); AT
		bi = convertido + 50; AT
		escreve_cache_1(bi, to_string(bi));
        cx_out = true; AT
        bi = cx; AT
        cx_out = false; AT
		escreve_cache_2(bi, to_string(bi));
        //processador_memoria::setBarramento_dados(to_string(bi)); AT
        //mem->set_mem_part_2(); AT
    }
    else if (ir.substr(6, 3) == "011") { //MOV DX ___
        convertido = binario_pra_decimal(stoi(ir.substr(6,7)));
        cout << "MOV [" << convertido + 50 << "] DX (var)" << endl;
        //processador_memoria::set_barramento_endereco(convertido + 50); AT
        //mem->set_mem_part_1(); AT
		bi = convertido + 50; AT
		escreve_cache_1(bi, to_string(bi));
        dx_out = true; AT
        bi = dx; AT
        dx_out = false; AT
		escreve_cache_2(bi, to_string(bi));
        //processador_memoria::setBarramento_dados(to_string(bi)); AT
        //mem->set_mem_part_2(); AT
    }
}


void processador::STORE1() {
	int convertido;
	if (ir.substr(6, 3) == "000") {
		convertido = binario_pra_decimal(stoi(ir.substr(9, 7)));
		cout << "STORE AX [" << convertido << "]\n";
//		processador_memoria::set_barramento_endereco(convertido);AT
//		// fetch_processador();
//		mem->fetch_memoria(); AT
//		bi = stoi(processador_memoria::getBarramento_dados()); AT

        pede_ip(convertido);
        ax_in = true; AT
        ax = stoi(bi_str); AT
        ax_in = false; AT
	}
	else if (ir.substr(6, 3) == "001") {
		convertido = binario_pra_decimal(stoi(ir.substr(9, 7)));
		cout << "STORE BX [" << convertido << "]\n";
//		processador_memoria::set_barramento_endereco(convertido);AT
        // fetch_processador();
//        mem->fetch_memoria(); AT
//        bi = stoi(processador_memoria::getBarramento_dados()); AT
        pede_ip(convertido);
        bx_in = true; AT
        bx = stoi(bi_str); AT
        bx_in = false; AT
	}
	else if (ir.substr(6, 3) == "010") {
		convertido = binario_pra_decimal(stoi(ir.substr(9, 7)));
		cout << "STORE CX [" << convertido << "]\n";
//		processador_memoria::set_barramento_endereco(convertido);AT
			// fetch_processador();
//			mem->fetch_memoria(); AT
//			bi = stoi(processador_memoria::getBarramento_dados()); AT
        pede_ip(convertido);
			cx_in = true; AT
			cx = stoi(bi_str); AT
			cx_in = false; AT

	}
	else if (ir.substr(6, 3) == "011") {
		convertido = binario_pra_decimal(stoi(ir.substr(9, 7)));
		cout << "STORE DX [" << convertido << "]\n";
//		processador_memoria::set_barramento_endereco(convertido);AT
			// fetch_processador();
//			mem->fetch_memoria(); AT
//			bi = stoi(processador_memoria::getBarramento_dados()); AT
        pede_ip(convertido);
			dx_in = true; AT
			dx = stoi(bi_str); AT
			dx_in = false; AT

	}
}

void processador::STORE2() {
	int convertido;
	if (ir.substr(13, 3) == "000") {
		convertido = binario_pra_decimal(stoi(ir.substr(6, 7)));
		cout << "STORE [" << convertido << "] AX\n";
		bi = convertido; AT
		escreve_cache_1(convertido, to_string(bi));
		ax_out = true; AT
		bi = ax; AT
		ax_out = false; AT
		escreve_cache_2(convertido, to_string(bi));
	}
	else if (ir.substr(13, 3) == "001") {
		convertido = binario_pra_decimal(stoi(ir.substr(6, 7)));
		cout << "STORE [" << convertido << "] BX\n";
		bi = convertido; AT
		escreve_cache_1(convertido, to_string(bi));
		bx_out = true; AT
		bi = bx; AT
		bx_out = false; AT
		escreve_cache_2(convertido, to_string(bi));

	}
	else if (ir.substr(13, 3) == "010") {
		convertido = binario_pra_decimal(stoi(ir.substr(6, 7)));
		cout << "STORE [" << convertido << "] CX\n";
		bi = convertido; AT
		escreve_cache_1(convertido, to_string(bi));
		cx_out = true; AT
		bi = cx; AT
		cx_out = false; AT
		escreve_cache_2(convertido, to_string(bi));
	}
	else if (ir.substr(13, 3) == "011") {
		convertido = binario_pra_decimal(stoi(ir.substr(6, 7)));
		cout << "STORE [" << convertido << "] DX\n";
		bi = convertido; AT
		escreve_cache_1(convertido, to_string(bi));
		dx_out = true; AT
		bi = dx; AT
		dx_out = false; AT
		escreve_cache_2(convertido, to_string(bi));
	}

}

void processador::INICIO() {
    cout << "INICIO \n";
}


void processador::ADD() {
    if (ir.substr(6,3) == "000"){ //ADD AX ___
        if(ir.substr(9,3) == "001"){
            cout << "ADD AX BX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "ADD AX CX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "ADD AX DX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "001"){ //ADD BX ___
        if(ir.substr(9,3) == "000"){
            cout << "ADD BX AX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "ADD BX CX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "ADD BX DX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "010"){ //ADD CX ___
        if(ir.substr(9,3) == "000"){
            cout << "ADD CX AX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "ADD CX BX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "ADD CX DX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "011"){ //ADD DX ___
        if(ir.substr(9,3) == "000"){
            cout << "ADD DX AX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "ADD DX CX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "ADD DX BX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->adiciona(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }

    }
}

void processador::SUB() {
    if (ir.substr(6,3) == "000"){ //SUB AX ___
        if(ir.substr(9,3) == "001"){
            cout << "SUB AX BX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "SUB AX CX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "SUB AX DX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "001"){ //ADD BX ___
        if(ir.substr(9,3) == "000"){
            cout << "SUB BX AX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "SUB BX CX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "SUB BX DX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "010"){ //ADD CX ___
        if(ir.substr(9,3) == "000"){
            cout << "SUB CX AX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "SUB CX BX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "SUB CX DX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "011"){ //ADD DX ___
        if(ir.substr(9,3) == "000"){
            cout << "SUB DX AX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "SUB DX CX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "SUB DX BX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->subtrai(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }

    }
}

void processador::PUSH() {
    if (ir.substr(6,3) == "000"){ //PUSH AX
        cout << "PUSH AX\n";
        ax_out = true; AT
        bi = ax; AT
        pilha.push(bi); AT
        sp = bi; AT
        ax_out = false; AT
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "001"){ //PUSH BX
        cout << "PUSH BX\n";
        bx_out = true; AT
        bi = bx; AT
        pilha.push(bi); AT
        sp = bi; AT
        bx_out = false; AT
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "010"){ //PUSH CX
        cout << "PUSH CX\n";
        cx_out = true; AT
        bi = cx; AT
        pilha.push(bi); AT
        sp = bi; AT
        cx_out = false; AT
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "011"){ //PUSH DX
        cout << "PUSH DX\n";
        dx_out = true; AT
        bi = dx; AT
        pilha.push(bi); AT
        sp = bi; AT
        dx_out = false; AT
        cout << "Fim\n";
    }
}

void processador::POP(){
    if (ir.substr(6,3) == "000"){ //POP AX
        cout << "POP AX\n";
        bi = pilha.top();
        pilha.pop(); AT
        if(!pilha.empty()) {
            sp = pilha.top();
            AT
        }
        else {
            sp = -1;
            AT
        }
        ax_in = true; AT
        ax = bi; AT
        ax_in = false; AT
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "001"){ //POP BX
        cout << "POP BX\n";
        bi = pilha.top();
        pilha.pop(); AT
        if(!pilha.empty()) {
            sp = pilha.top();
            AT
        }
        else {
            sp = -1;
            AT
        }
        bx_in = true; AT
        bx = bi; AT
        bx_in = false; AT
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "010"){ //POP CX
        cout << "POP CX\n";
        bi = pilha.top();
        pilha.pop(); AT
        if(!pilha.empty()) {
            sp = pilha.top();
            AT
        }
        else {
            sp = -1;
            AT
        }
        cx_in = true; AT
        cx = bi; AT
        cx_in = false; AT
        cout << "Fim\n";
    }
    else if (ir.substr(6,3) == "011"){ //POP DX
        cout << "POP DX\n";
        bi = pilha.top();
        pilha.pop(); AT
        if(!pilha.empty()) {
            sp = pilha.top();
            AT
        }
        else {
            sp = -1;
            AT
        }
        dx_in = true; AT
        dx = bi; AT
        dx_in = false; AT
        cout << "Fim\n";
    }
}

void processador::MUL() {
    if (ir.substr(6,3) == "000"){ //MUL AX ___
        if(ir.substr(9,3) == "001"){
            cout << "MUL AX BX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "MUL AX CX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "MUL AX DX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "001"){ //MUL BX ___
        if(ir.substr(9,3) == "000"){
            cout << "MUL BX AX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "MUL BX CX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "MUL BX DX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "010"){ //MUL CX ___
        if(ir.substr(9,3) == "000"){
            cout << "MUL CX AX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "MUL CX BX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "MUL CX DX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "011"){ //MUL DX ___
        if(ir.substr(9,3) == "000"){
            cout << "MUL DX AX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "MUL DX CX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "MUL DX BX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->multiplica(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }

    }
}

void processador::DIV() {
    if (ir.substr(6,3) == "000"){ //DIV AX ___
        if(ir.substr(9,3) == "001"){
            cout << "DIV AX BX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "DIV AX CX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "DIV AX DX\n";
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_1(bi); AT
            ax_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            ax_in = true; AT
            ax = bi; AT
            ax_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "001"){ //DIV BX ___
        if(ir.substr(9,3) == "000"){
            cout << "DIV BX AX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "DIV BX CX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "DIV BX DX\n";
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_1(bi); AT
            bx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            bx_in = true; AT
            bx = bi; AT
            bx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "010"){ //DIV CX ___
        if(ir.substr(9,3) == "000"){
            cout << "DIV CX AX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "DIV CX BX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "011"){
            cout << "DIV CX DX\n";
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_1(bi); AT
            cx_out = false; AT
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_2(bi); AT
            dx_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            cx_in = true; AT
            cx = bi; AT
            cx_in = false; AT
            cout << "Fim\n";
        }

    }
    else if (ir.substr(6,3) == "011"){ //DIV DX ___
        if(ir.substr(9,3) == "000"){
            cout << "DIV DX AX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            ax_out = true; AT
            bi = ax; AT
            ula->setUla_in_2(bi); AT
            ax_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "010"){
            cout << "DIV DX CX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            cx_out = true; AT
            bi = cx; AT
            ula->setUla_in_2(bi); AT
            cx_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }
        else if(ir.substr(9,3) == "001"){
            cout << "DIV DX BX\n";
            dx_out = true; AT
            bi = dx; AT
            ula->setUla_in_1(bi); AT
            dx_out = false; AT
            bx_out = true; AT
            bi = bx; AT
            ula->setUla_in_2(bi); AT
            bx_out = false; AT
            ula->divide(); AT
            bi = ula->getUla_out(); AT
            dx_in = true; AT
            dx = bi; AT
            dx_in = false; AT
            cout << "Fim\n";
        }

    }
}
//
//void processador::chama_at() {
////    AT
//}

bool processador::checa_cache(int pos){
    int pos_cache = pos % CACHE_TAM;
    return cache[pos_cache].first == pos;
}

void processador::pede_ip(int ip) {
    if(checa_cache(ip)){
        bi_str = cache[ip % CACHE_TAM].second;
        cache_hit++;
    }
    else {
        preenche_cache(ip);
        cache_miss++;
        bi_str = cache[ip % CACHE_TAM].second;
    }
}

void processador::preenche_cache(int ip) {
    int indice_inicial = ip % CACHE_TAM;
    for(int i = 0; i < CACHE_TAM; i++) {
        //cout << "\n\nInicio do fetch (Busca instrucao atraves do B_E) \n";
        processador_memoria::set_barramento_endereco(ip);
        mem->fetch_memoria();
        cache[ip % CACHE_TAM].first = ip;
        cache[ip % CACHE_TAM].second = processador_memoria::getBarramento_dados();
        //cout << "Fim do fetch (Instrucao foi colocada na fila(Prefetch input queue))  \n";

        ip += 1;



    }

}

void processador::escreve_cache_1(int ip, string dado) {
    int indice = ip % CACHE_TAM;
    cache[indice].first = ip;
    processador_memoria::set_barramento_endereco(ip); AT
    mem->set_mem_part_1();
    
}

void processador::escreve_cache_2(int ip, string dado) {
	int indice = ip % CACHE_TAM;
	cache[indice].second = dado;
	processador_memoria::setBarramento_dados(dado); AT
	mem->set_mem_part_2();
}



