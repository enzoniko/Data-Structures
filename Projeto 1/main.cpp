// Copyright [2023] Enzo Nicolás Spotorno Bieger
#include <iostream>
#include <fstream>
#include <string>
#include "array_stack.h"
#include "array_queue.h"
using namespace std;

// Função que valida arquivos XML
int xmlvalidator(char * xmlfilename) {
    // Aloca a pilha
    structures::ArrayStack<string> stack{500u};
    // Tenta abrir o arquivo
    fstream file (xmlfilename);
    // Se o arquivo foi aberto
    if (file.is_open()) {
        // String pra guardar cada linha
        string line;
        // Loop por todas as linhas
        while (getline(file, line)) {
            // Loop por cada caracter de cada linha
            for (int i = 0; i < line.length(); i++) {
                // Se for uma marcação
                if (line[i] == '<') {
                    // Se for uma marcação de abertura
                    if (line[i + 1] != '/') {
                        // Descobre o identificador
                        i++;
                        int j = 0;
                        while (line[i + j] != '>') {
                            j++;
                        }
                        // Empilha o identificador
                        stack.push(line.substr(i, j));
                        
                        // Incrementa i com o tamanho do identificador lido pra não precisar passar por ele atoa
                        i += j;
                        
                    // Se for uma marcação de fechamento
                    } else {
                        // Descobre o identificador
                        i += 2;
                        int j = 0;
                        while (line[i + j] != '>') {
                            j++;
                        }
                        string identificador = line.substr(i, j);
                        
                        // Incrementa i com o tamanho do identificador lido pra não precisar passar por ele atoa
                        i += j;
                        // Verifica as situações de ERRO:
                        // Ao consultar o topo da pilha, se a pilha está vazia: ERRO
                        // Ao consultar o topo da pilha, se o identificador for diferente: ERRO
                        if (stack.empty() || (identificador != stack.top())) {
                            cout << "erro" << endl;
                            return 1;
                        // Se não houver erro, ou seja, o topo da pilha tem o mesmo identificador, desempilha
                        } else {
                            stack.pop();
                        }
                    }
                }
            }
        }
        // Ao finalizar a análise do arquivo, se a pilha não estiver vazia: ERRO
        if (!stack.empty()) {
            cout << "erro" << endl;
            return 1;
        }
        // Fecha o arquivo
        file.close();
    // Se não conseguiu abrir o arquivo, grita.
    } else {
        cout << "NAO ABRIU" << endl;
        return 1;
    }
    return 0;
}

// Estrutura que guarda as informações de um cenário
struct Info {
    string nome;
    int largura, altura, x, y;
    int ** matrix;
};

// Função que guarda as informações de cada cenário em uma fila circular
structures::ArrayQueue<Info> get_scenaries_infos(char * xmlfilename) {
    // Cria uma fila circular que guarda as informações de cada cenário.
    structures::ArrayQueue<Info> fila{110u};
    
    // Lê o arquivo e armazena as informações de cada cenário na fila.
    
    // Tenta abrir o arquivo
    fstream file (xmlfilename);
    // Se o arquivo foi aberto
    if (file.is_open()) {
        // String pra guardar cada linha
        string line;
        // Cria uma estrutura auxiliar para aguardas as informações do cenário
        Info scenary_info;
        
        // Flag que simboliza quando encontramos uma matriz
        bool is_matrix = false;
        
        // Declara a matriz, pra ser preenchida depois
        int ** matrix;
        
        // Guarda a linha que tem que ser preenchida
        int linha = 0;
        
        // Loop por todas as linhas
        while (getline(file, line)) {
        
            // Se a flag is_matrix estiver ativada
            if (is_matrix == true) {
                
                // Se achou a tag de fechamento de matriz
                if (line.find("</matriz>") != string::npos) {
                    // Guarda a matriz na estrutura
                    scenary_info.matrix = matrix;
                    
                    // Desativa a tag is_matrix
                    is_matrix = false;
                    
                    // Zera a linha que precisa ser preenchida
                    linha = 0;
                } else {
                    // Significa que as próximas linhas são 0's e 1's e correspondem às linhas da matriz
                
                    // Preenche a linha da matriz
                    for (int j = 0; j < scenary_info.largura; j++) {
                        matrix[linha][j] = int(line[j]) - 48;
                    }
                    linha ++;
                }
    
            } else {
                // Procurar outros identificadores, pra cada tipo, preencher a info na estrutura
                
                // Se achou a tag de abertura de matriz
                if (line.find("<matriz>") != string::npos) {
                    
                    // Aloca a matriz de inteiros com altura linhas e largura colunas
                    matrix = new int*[scenary_info.altura];
                    for (int i = 0; i < scenary_info.altura; ++i) matrix[i] = new int[scenary_info.largura];
                    
                    // Ativa a flag is_matrix
                    is_matrix = true;
                    
                    // Zera a linha que precisa ser preenchida
                    linha = 0;
                }
                if (line.find("<nome>") != string::npos) {
                    // Identifica o nome e o guarda na estrutura
                    scenary_info.nome = line.substr(line.find("<nome>") + 6, line.find("</nome>") - line.find("<nome>") - 6);
                }
                if (line.find("<altura>") != string::npos) {
                    // Identifica a altura e a guarda na estrutura
                    scenary_info.altura = stoi(line.substr(line.find("<altura>") + 8, line.find("</altura>") - line.find("<altura>") - 8));
                }
                if (line.find("<largura>") != string::npos) {
                    // Identifica a largura e a guarda na estrutura
                    scenary_info.largura = stoi(line.substr(line.find("<largura>") + 9, line.find("</largura>") - line.find("<largura>") - 9));
                }
                if (line.find("<x>") != string::npos) {
                    // Identifica o x e o guarda na estrutura
                    scenary_info.x = stoi(line.substr(line.find("<x>") + 3, line.find("</x>") - line.find("<x>") - 3));
                }
                if (line.find("<y>") != string::npos) {
                    // Identifica o y e o guarda na estrutura
                    scenary_info.y = stoi(line.substr(line.find("<y>") + 3, line.find("</y>") - line.find("<y>") - 3));
                }
                if (line.find("</cenario>") != string::npos) {

                    // Bota a informação do cenário na fila
                    fila.enqueue(scenary_info);
                }
            }
        }
    // Se não conseguiu abrir o arquivo, grita.
    } else {
        cout << "NAO ABRIU" << endl;
    }
    // Fecha o arquivo
    file.close();
    
    // Retorna a fila
    return fila;    
}

// Estrutura de uma coordenada, size_t pra não poder ser negativo
struct Coordenada {
    int x, y;
};

// Algoritmo de reconstrução do componente conexo usando uma fila
int area_a_ser_limpa(Info cenario) {
    
    // O tamanho máximo teórico da fila seria a quantidade de 1's da matriz original
    size_t tamanho = 0;
    for (int i = 0; i < cenario.altura; i++) {
        for (int j = 0; j < cenario.largura; j++) {
            if (cenario.matrix[i][j] == 1) tamanho ++;
        }
    }

    // Criar uma fila para guardar as coordenadas com esse tamanho
    structures::ArrayQueue<Coordenada> fila{tamanho};
    
    // Criar uma matriz R (reconstrução) de zeros com o mesmo tamanho da matriz original
    int ** reconstrucao = new int*[cenario.altura];
    for (int i = 0; i < cenario.altura; ++i) reconstrucao[i] = new int[cenario.largura];
    
    /// Preenche a matriz reconstrução com zeros
    for (int i = 0; i < cenario.altura; i++) {
        for (int j = 0; j < cenario.largura; j++) reconstrucao[i][j] = 0;
    }
    
    // Inicia o algoritmo (Preenchimento da matriz reconstrução):
    // Pega a coordenada (x, y)
    Coordenada c = {cenario.x, cenario.y};
    
    // Se na matriz original do cenário essa coordenada corresponder à 1
    if (cenario.matrix[c.x][c.y] == 1) {
        // Insere (x, y) na fila
        fila.enqueue(c);
        // Atribuir 1 na coordenada (x, y) da matriz reconstrução
        reconstrucao[c.x][c.y] = 1;  
    } 
    
    // Enquanto a fila não estiver vazia
    while (!fila.empty()) {
        // Pega a primeira coordenada da fila
        c = fila.dequeue();
        
        // Cria uma matriz de vizinhos (cada elemento é uma array com x e y)
        int vizinhos[4][2] = {{c.x - 1, c.y}, {c.x + 1, c.y}, {c.x, c.y - 1}, {c.x, c.y + 1}};
        
        // Pra cada coordenada dos vizinhos
        for (int i = 0; i < 4; i++) {
            // Verifica se ela é válida:
            // - Dentro do domínio da matriz
            // - 1 na matriz original
            // - 0 na matriz reconstrução
            if ((vizinhos[i][0] < cenario.altura) && (vizinhos[i][0] >= 0) && 
                (vizinhos[i][1] < cenario.largura) && (vizinhos[i][1] >= 0) && 
                (cenario.matrix[vizinhos[i][0]][vizinhos[i][1]] == 1) && (reconstrucao[vizinhos[i][0]][vizinhos[i][1]]) == 0) {
                    
                // Se for válido, coloca na fila
                c = {vizinhos[i][0], vizinhos[i][1]};
                fila.enqueue(c);
                
                // Coloca 1 na matriz reconstrução nessa coordenada
                reconstrucao[c.x][c.y] = 1;
            }
        }
    }
    
    // Agora que a matriz reconstrução está devidamente preenchida
    // A resposta da área a ser limpa é a quantidade de 1's na matriz reconstrução
    int resposta = 0;
    for (int i = 0; i < cenario.altura; i++) {
        for (int j = 0; j < cenario.largura; j++) {
            if (reconstrucao[i][j] == 1) resposta ++;
        }
    }

    // Retorna a resposta
    return resposta;
}

int main() {

    char xmlfilename[100];
    
    cin >> xmlfilename;  // entrada
    
    // Valida o arquivo XML, se ele estiver certinho continua
    if (xmlvalidator(xmlfilename)) {
        return 1;
    }
    // Determinação de área do espaço que o robô deve limpar.
    
    // Obtem a fila circular com as informações de cada cenário do arquivo
    structures::ArrayQueue<Info> fila = get_scenaries_infos(xmlfilename);
    
    // Cada elemento da fila, corresponde as informações de cada cenário
    // Enquanto a fila não estiver vazia 
    while (!fila.empty()) {
        // Pega a informação de um cenário da fila
        Info cenario = fila.dequeue();
        
        // Printa o nome do cenário seguido pelo resultado da chamada da função que determina a área a ser limpa pelo robo 
        cout << cenario.nome << " " << area_a_ser_limpa(cenario) << endl;
    }
    return 0;
}
