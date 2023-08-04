// Alunos: Déborah Raquel Bussolo Ferreira - 22103732
//         Enzo Nicolás Spotorno Bieger - 22100614

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
// Criar a estrutura da Trie
class Trie {
 private:
    struct NoTrie {
        // Vetor dos Filhos
        NoTrie * filhos[26];
        
        // Posição
        unsigned long posicao;
        
        // Comprimento (quando for uma terminação de palavra será diferente de 0)
        unsigned long comprimento;
    };
    
    // Construtor do nó
    NoTrie* Node() {
        
        // Aloca um nó
        NoTrie* No =  new NoTrie;
        
        // Inicializa as variáveis de posição e comprimento do nó
        No->posicao = 0;
        No->comprimento = 0;
        
        // Preenche cada filho com null pointer
        for (int i = 0; i < 26; i++)
            No->filhos[i] = nullptr;
        
        // Retorna o nó
        return No;
    }
    
    
 public:
 
    // Função de inserção na trie
    void insert(NoTrie *root, string palavra, unsigned long pos, unsigned long compr) {
        
        // Usamos um nó auxiliar para percorrer a trie
        NoTrie * auxiliar = root;
        
        // Para cada caracter da palavra
        for (int i = 0; i < palavra.length(); i++)
        {
            // Pega o índice dele no vetor dos filhos
            int index = palavra[i] - 'a';
            
            // Se não tiver filho nesse índice
            if (!auxiliar->filhos[index])
            
                // Cria um filho nesse índice
                auxiliar->filhos[index] = Node();
            
            // Faz o auxiliar ser o filho
            auxiliar = auxiliar->filhos[index];
        }
        
        // Uma vez que tenhamos chegado no caracter final da palavra
        // Preenche a posição e o comprimento da mesma
        auxiliar->posicao = pos;
        auxiliar->comprimento = compr;
    }
    
    // Função para calcular o número de palavras para as quais esse nó é prefixo
    int num_prefixos(NoTrie *self) {
        
        // Começa em zero
        int prefixos = 0;
        
        // Se esse nó for a terminação de uma palavra, incrementa em 1
        // Pois uma palavra é prefixo de si mesma
        if (self->comprimento != 0) prefixos++;
        
        // Para cada letra
        for (int i = 0; i < 26; i++) {
            
            // Se essa letra for um filho
            if (self->filhos[i] != nullptr) {
                
                // Calcula o número de palavras para as quais esse filho é prefixo e 
                // soma no total
                prefixos += num_prefixos(self->filhos[i]);
            }
        }   
        
        // Retorna o valor calculado
        return prefixos;
    }
    
    // Função que busca uma palavra na trie
    bool search(NoTrie *root, string palavra) {
        
        // Usamos um nó auxiliar para percorrer a trie
        NoTrie * auxiliar = root;
        
        // Para cada caracter da palavra
        for (int i = 0; i < palavra.length(); i++)
        {
            // Calcula o índice do filho desse caracter 
            int index = palavra[i] - 'a';
            
            // Se não existir um filho nesse índice
            if (!auxiliar->filhos[index]) {
                
                // Fala que essa palavra não é um prefixo
                cout << palavra << " is not prefix" << endl;
                
                // Retorna false, pois não encontrou a palavra
                return false;
            }
            
            // Se existir um filho nesse índice, faz o auxiliar ser o filho
            auxiliar = auxiliar->filhos[index];
        }
        
        // Após termos chegado no último caracter da palavra
        // Calcula a quantidade de palavras para as quais essa palavra é prefixo
        int n_prefixos = num_prefixos(auxiliar);
        
        // Se não for 0
        if (n_prefixos != 0) {
            
            // Printa esse valor
            cout << palavra << " is prefix of " << n_prefixos << " words" <<endl;    
        }
        
        // Se essa palavra for uma palavra que está de fato no dicionário
        if (auxiliar->comprimento != 0) {
            
            // Printa a posição e o comprimento dessa palavra
            cout << palavra << " is at " << "(" << auxiliar->posicao << "," << auxiliar->comprimento << ")" <<endl;
        }
        
        // Retorna true se essa palavra está no dicionário, false caso contrário
        return (auxiliar->comprimento != 0);
    }
    
    // Inicializa a raíz já
    NoTrie * root = Node();
};

int main() {
    
    // Nome do arquivo de entrada
    string filename;
    
    // Variável que vai pegar cada palavra que vamos buscar no dicionário da entrada  
    string word;
    
    Trie t; // Trie
    cin >> filename;  // entrada
    
    // Abrir arquivo
    ifstream file;
    file.open(filename);
    
    // Variável que vamos usar para percorrer as linhas do arquivo
    string line;
    
    // Construir a Trie a partir das palavras do arquivo de dicionário.
    // Percorrer a linha do arquivo de dicionário
    if (file.is_open()) {
        
        // Inicializa a posição e o comprimento em 0
        int posicao = 0;
        int comprimento = 0;
        
        // Enquanto tiver linhas no arquivo, pega uma linha
        while (getline(file, line)) {
            
            // O comprimento é o comprimento da linha, a posição foi calculada na iteração anterior
            comprimento = line.length();
            
            // Insere as informações na Trie
            t.insert(t.root, line.substr(1, line.find("]") - 1), posicao, comprimento);
            
            // Calcula a próxima posição
            posicao += comprimento + 1;
        }
        // Fecha o arquivo
        file.close();
    } else { // Se não conseguiu abrir o arquivo
        cout << "ERRO AO ABRIR O ARQUIVO" << endl;
    } 
    
    // Lê as palavras da entrada
    while (1) {  // leitura das palavras ate encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        
        // Busca elas na trie, printando todas as informações que foram requisitadas
        t.search(t.root, word);
    }

    // Retorna 0 se tudo deu certo
    return 0;
}


