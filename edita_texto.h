// Copyright [2022] Enzo Nicolás Spotorno Bieger
#include <string>
#include "./array_queue.h"

structures::ArrayQueue<char> editaTexto(std::string texto) {
    structures::ArrayQueue<char> fila(500);
    for (char c : texto) {
        if (c == '<') {
            fila.dequeue();
        } else if (c == '>') {
            fila.enqueue(fila.back());
        } else {
            fila.enqueue(c);
        }
    }
    return fila;
}
