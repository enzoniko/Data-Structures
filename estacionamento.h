// Copyright [2023] Enzo Nicolás Spotorno Bieger

/*
    *** Importante ***

    O código de fila em vetor está disponível internamente (não precisa de implementação aqui)

*/



void retira_veiculo(structures::ArrayQueue<int> &f, int k) {
    for (int i = 0; i < k - 1; i++) {
        f.enqueue(f.dequeue());
    }
    f.dequeue();
}


void mantenha_veiculo(structures::ArrayQueue<int> &f, int k) {
    for (int i = 0; i < k - 1; i++) {
        f.enqueue(f.dequeue());
    }
    int t = f.dequeue();
    f.clear();
    f.enqueue(t);
}



/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
