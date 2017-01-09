//
// Created by root on 10/8/16.
//

#include "ULA.h"

ULA::ULA() {
    ula_in_1 = 0;
    ula_in_2 = 0;
    ula_out = 0;
	overflow = false;
	signal = false;
}

void ULA::completa_7_bits(string & entrada) {
    int i;

    while (entrada.size() < 7) {
        entrada = "0" + entrada;
    }
}

string ULA::to_binary(int n) {
    string saida;
    if (n == 0)
        return to_string(n); // só transforma zero pra string
    while (n != 0) {
        saida = (n % 2 == 0 ? "0" : "1") + saida;
        n /= 2;
    }
    return saida;
}


int ULA::getUla_in_1() const {
    return ula_in_1;
}

void ULA::setUla_in_1(int ula_in_1) {
    ULA::ula_in_1 = ula_in_1;
}

int ULA::getUla_in_2() const {
    return ula_in_2;
}

void ULA::setUla_in_2(int ula_in_2) {
    ULA::ula_in_2 = ula_in_2;
}

int ULA::getUla_out() const {
    return ula_out;
}

void ULA::setUla_out(int ula_out) {
    ULA::ula_out = ula_out;
}

void ULA::adiciona() {
    ula_out = ula_in_1 + ula_in_2;
	signal = checa_signal();
	overflow = checa_overflow();
}

void ULA::subtrai() {
    ula_out = ula_in_1 - ula_in_2;
	signal = checa_signal();
	overflow = checa_overflow();
}

void ULA::multiplica() {
    ula_out = ula_in_1 * ula_in_2;
	signal = checa_signal();
	overflow = checa_overflow();
}

void ULA::divide() {
    ula_out = ula_in_1 / ula_in_2;
	signal = checa_signal();
	overflow = checa_overflow();
}

void ULA::incrementa() {
    ula_out = ula_in_1 + 1;
	signal = checa_signal();
	overflow = checa_overflow();
}

void ULA::decrementa() {
    ula_out = ula_in_1 - 1;
	signal = checa_signal();
	overflow = checa_overflow();
}

void ULA::faz_and() {
    string reg1, reg2, result;
    reg1 = to_binary(ula_in_1);
    reg2 = to_binary(ula_in_2);
    completa_7_bits(reg1);
    completa_7_bits(reg2);
    for (int i = 0; i < reg1.size(); i++) {
        if (reg1[i] == '1' && reg2[i] == '1')
            result.push_back('1');
        else
            result.push_back('0');
    }
    ula_out = binario_pra_decimal(stoi(result));
}

void ULA::faz_or() {
    string reg1, reg2, result;
    reg1 = to_binary(ula_in_1);
    reg2 = to_binary(ula_in_2);
    completa_7_bits(reg1);
    completa_7_bits(reg2);
    for (int i = 0; i < reg1.size(); i++) {
        if (reg1[i] == '1' || reg2[i] == '1')
            result.push_back('1');
        else
            result.push_back('0');
    }
    ula_out = binario_pra_decimal(stoi(result));
}

int ULA::binario_pra_decimal(int n) {
    int decimal = 0, i = 0, resto;
    while (n!=0) {
        resto = n % 10;
        n /= 10;
        decimal += resto*pow(2,i);
        ++i;
    }
    return decimal;
}

void ULA::faz_xor() {
    string reg1, reg2, result;
    reg1 = to_binary(ula_in_1);
    reg2 = to_binary(ula_in_2);
    completa_7_bits(reg1);
    completa_7_bits(reg2);
    for (int i = 0; i < reg1.size(); i++) {
        if (reg1[i] == reg2[i])
            result.push_back('0');
        else
            result.push_back('1');
    }
    ula_out = binario_pra_decimal(stoi(result));
}

void ULA::faz_not() {
    string reg1, result;
    reg1 = to_binary(ula_in_1);
    completa_7_bits(reg1);
    for (int i = 0; i < reg1.size(); i++) {
        if (reg1[i] == '1')
            result.push_back('0');
        else
            result.push_back('1');
    }
    ula_out = binario_pra_decimal(stoi(result));
}

bool ULA::checa_overflow() {
	if (ula_out > 127) {
		string binario;
		binario = to_binary(ula_out);
		int tamanho = binario.size();
		string final = binario.substr(tamanho - 7, 7);
		ula_out = binario_pra_decimal(stoi(final));
		return true;
	}
	return false;
}

bool ULA::checa_signal(){
	if (ula_out < 0) {
		ula_out = ula_out * (-1);
		return true;
	}
	return false;
}

