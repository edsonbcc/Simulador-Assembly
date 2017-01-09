//
// Created by lucp2 on 17/09/16.
//

#include "analisador.h"

#include "cor.h"

void analisador::imprime_assembler() {
	text_color cor;


	CLBLUE printf("	   _____ _____ ______ __  __ ____  _      ______ _____  \n");
	CLBLUE printf("    /\\    / ____/ ____|  ____|  \\/  |  _ \\| |    |  ____|  __ \\ \n");
	CYELLOW printf("   /  \\  | (___| (___ | |__  | \\  / | |_) | |    | |__  | |__) |\n");
	CYELLOW printf("  / /\\ \\  \\___ \\\\___ \\|  __| | |\\/| |  _ <| |    |  __| |  _  / \n");
	CGREEN printf(" / ____ \\ ____) |___) | |____| |  | | |_) | |____| |____| | \\ \\ \n");
	CGREEN printf("/_/    \\_\\_____/_____/|______|_|  |_|____/|______|______|_|  \\_\\\n\n");

	CGRAY

}


int analisador::binario_pra_decimal(int n) {
    int decimal = 0, i = 0, resto;
    while (n!=0) {
        resto = n % 10;
        n /= 10;
        decimal += resto*pow(2,i);
        ++i;
    }
    return decimal;
}

void analisador::poe_na_memoria (Memoria *m, vector<string> linhas) {
    bool primeiro;
    int cont = 50, i = 0;
    string temp;
	m->set_mem("answer", 42);
    while(linhas[i].substr(0,6) != "011100"){
        temp = to_string(binario_pra_decimal(stoi(linhas[i].substr(9,7))));
        m->set_mem(temp, cont);
        i++;
        cont += 2;
    }
    num_const = i * 2;
    cont = 100;
    for(i; i < linhas.size(); i++){
        m->set_mem(linhas[i], cont);
        m->set_mem("ins", cont + 1);
		if (linhas[i].substr(0, 6) == "011101")
			fim = cont;
        cont += 2;
    }
     tamanho = linhas.size();

	 /*system("CLS");
	 text_color cor;
	 

	 CLBLUE printf("	   _____ _____ ______ __  __ ____  _      ______ _____  \n");
	 CLBLUE printf("    /\\    / ____/ ____|  ____|  \\/  |  _ \\| |    |  ____|  __ \\ \n");
	 CYELLOW printf("   /  \\  | (___| (___ | |__  | \\  / | |_) | |    | |__  | |__) |\n");
	 CYELLOW printf("  / /\\ \\  \\___ \\\\___ \\|  __| | |\\/| |  _ <| |    |  __| |  _  / \n");
	 CGREEN printf(" / ____ \\ ____) |___) | |____| |  | | |_) | |____| |____| | \\ \\ \n");
	 CGREEN printf("/_/    \\_\\_____/_____/|______|_|  |_|____/|______|______|_|  \\_\\\n\n");

	 CGRAY
*/


		



}
int analisador::num_const = 0;
unsigned long int analisador::tamanho = 0;
unsigned long int analisador::fim = 0;

//vector analisador::constantes = ;

unsigned long analisador::getTamanho() {
    return tamanho;
}


