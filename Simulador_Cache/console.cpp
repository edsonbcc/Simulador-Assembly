//
// Created by lucp2 on 17/09/16.
//

#include "console.h"


console::console(){
    prenche_bordas();
    //pula_linha();
//    imprime_console();
}
void console::prenche_bordas(){
    int i, j;
    for(i = 0; i < TAM; i++)
        for(j = 0; j < TAM; j++)
            if(i == 0 || i == TAM - 1 || j ==0 || j == TAM -1)
                consol[i][j] = '#';
            else
                consol[i][j] = ' ';



}
void console::insert_string(string str){
    int i, j=1, cont = 0;
    bool primeira_vez = true;
    for(j=1; j < TAM; j++)
        if((consol[TAM-2][j] == ' ' && consol[TAM-2][j + 1] == ' ') || (consol[TAM-2][j] == ' ' && consol[TAM-2][j + 1] == '#') || consol[TAM-2][j] == '#'){
            break;
        }
    for (cont = 0 ; cont<str.size(); cont){
        if (j != TAM - 1)
            consol[TAM-2][j] = str[cont++];
        else {
            pula_linha();
            j = 0;
        }
        j++;
//        i++;
    }
}
void console::pula_linha(){
    int i, j, cont;
    string linha;
    for(i = 2; i < TAM-1; i++){
        cont = 0;
        for (j = 1; j < TAM - 1; j++){
            linha.push_back(consol[i][j]);
            consol[i][j] = ' ';
        }
        for (j = 1; j < TAM - 1; j++){
            consol[i-1][j] = linha[cont++];
        }
        linha.clear();
    }
}

void console::imprime_console(){
    int i;
    for (i = 0; i<TAM; i++) {
        for(int columns=0; columns < TAM; columns++)
            cout << " " << consol[i][columns];
        cout << endl;
    }
}


