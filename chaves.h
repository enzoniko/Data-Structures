// Copyright [2022] Enzo Nicolás Spotorno Bieger
#include <string>
#include "./array_stack.h"
bool verificaChaves(std::string trecho_programa) {
    bool resposta = true;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);
    for (int i = 0; i < tamanho; i++) {
        // condições de parada do 'for' podem ser adicionadas...
        if ((trecho_programa[i] == '{') && (!pilha.full())) {
            pilha.push(trecho_programa[i]);
        } else if ((trecho_programa[i] == '}') && (!pilha.empty())) {
            pilha.pop();
        } else if (((trecho_programa[i] == '{') && (pilha.full())) || ((trecho_programa[i] == '}') && (pilha.empty()))) {
            resposta = false;
        }
    }
    if (!pilha.empty()) resposta = false;
    return resposta;
}
