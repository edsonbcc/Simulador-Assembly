//
// Created by lucp2 on 18/09/16.
//
/*
#include "executor.h"

void executor::le_memo() {

}

void executor::executa(arquivo *arqui) {
    for(int i = 0; i < arqui->operador.size(); i++){
    if (arqui->operador[i] == "001101")
        MOV1(arqui->op1[i], arqui->op2[i]);

    }
}
//AX 000
//BX 001
//CX 010
//DX 011
//SP 100

void executor::ADD(string opcode){

}

void executor::SUB(string opcode){

}

void executor::MUL(string opcode){

}
void executor::DIV(string opcode){

}
void executor::INC(string opcode){

}
void executor::DEC(string opcode){

}
void executor::CMP(string opcode){

}
void executor::AND(string opcode){

}
void executor::OR(string opcode){

}
void executor::XOR(string opcode){

}
void executor::NOT(string opcode){

}
void executor::NEG(string opcode){

}
//AX 000
//BX 001
//CX 010
//DX 011
void executor::MOV1(string op1, string op2){
    if(op1 == "000"){

        if(op2 == "001"){

        }
        else if(op2 == "010"){

        }
        else if(op2 == "011"){

        }
    }
    else if(op1 == "001"){

    }
    else if(op1 == "010"){

    }
    if(op1 == "011"){

    }
}
void executor::MOV2(string opcode){

}
void executor::MOV3(string opcode){

}
void executor::MOV4(string opcode){

}
void executor::MOV5(string opcode){

}
void executor::PUSH(string opcode){

}
void executor::POP(string opcode){

}
void executor::JMP(string opcode){

}
void executor::JE(string opcode){

}
void executor::JNE(string opcode){

}
void executor::JZ(string opcode){

}
void executor::JNZ(string opcode){

}
void executor::JG(string opcode){

}
void executor::JGE(string opcode){

}
void executor::JL(string opcode){

}
void executor::JLE(string opcode){

}
void executor::INICIO(string opcode){

}
void executor::FIM(string opcode){

}
void executor::INT(string opcode){

}
void executor::CALL(string opcode){

}
void executor::RET(string opcode){

}
void executor::LABEL(string opcode){

}

bool executor::checa_tres_ultimos(string opcode) {
    if(opcode.substr(opcode.size()-3, 3) == "000") {
        cout << "sim";
        return true;
    } else
        return false;
}

int executor::binaryToBase10(int n) {

    int output = 0;

    for(int i=0; n > 0; i++) {

        if(n % 10 == 1) {
            output += pow(2, i);
        }
        n /= 10;
    }

    return output;
}
 */