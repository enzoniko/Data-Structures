//! Copyright [2023] <Enzo Nicolás Spotorno Bieger>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>


namespace structures {

//! ...
template<typename T>
class CircularList {
 public:
    //! ...
    CircularList();  // construtor padrão
    //! ...
    ~CircularList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

 private:
    class Node {  // Elemento
     public:
        Node() {
            next_ = nullptr;
        }

        explicit Node(const T& data):
            data_{data}
        {}

        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* next() {  // getter: próximo
            return next_;
        }

        const Node* next() const {  // getter const: próximo
            return next_;
        }

        void next(Node* node) {  // setter: próximo
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    Node* sentinela{nullptr};
    Node* tail{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

template<typename T>
structures::CircularList<T>::CircularList() {
    Node *novo = new Node();
    sentinela = novo;
}

template<typename T>
structures::CircularList<T>::~CircularList() {
    // Desalocar cada um dos nós de lista existente.
    // Efetuar 'pop_front()' até que a lista se torne vazia.
    clear();
    delete tail;
    delete sentinela;
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
    // size_ = 0; // pop_front does this already
}

template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *novo = new Node(data);
        if (novo == NULL) {
            throw std::out_of_range("Lista Cheia");
        }
        novo->next(sentinela->next());
        tail->next(novo);
        tail = novo;
        size_++;
    }
}

template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    if (novo == NULL) {
        throw std::out_of_range("Lista Cheia");
    }
    if (empty()) {
        tail = novo;
        tail->next(novo);
    }
    novo->next(sentinela->next());
    sentinela->next(novo);
    size_++;
}

template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    Node *anterior = sentinela->next();
    if ((index < 0) || (index > size_)) {
        throw std::out_of_range("Indice Inválido");
    } else if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        for (std::size_t i = 0; i < index - 1; i++) {
            anterior = anterior->next();
        }
        Node *novo = new Node(data);
        if (novo == NULL) {
            throw std::out_of_range("Lista Cheia");
        }
        novo->next(anterior->next());
        anterior->next(novo);
        size_++;
    }
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    Node *atual = sentinela->next();
    if (empty()) {
        push_front(data);
    } else {
        std::size_t pos = 0;
        while ((atual->next() != nullptr) && (data > atual->data())) {
            atual = atual->next();
            pos++;
        }
        if (data > atual->data()) {
            push_back(data);
        } else {
            insert(data, pos);
        }
    }
}

template<typename T>
T& structures::CircularList<T>::at(std::size_t index) {
    Node *anterior = sentinela->next();
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if ((index < 0) || (index > size_ - 1)) {
        throw std::out_of_range("Indice Inválido");
    } else if (index == 0) {
        return sentinela->next()->data();
    } else if (index == size_ - 1) {
        return tail->data();
    } else {
        for (std::size_t i = 0; i < index - 1; i++) {
            anterior = anterior->next();
        }
        return anterior->next()->data();;
    }
}

template<typename T>
T structures::CircularList<T>::pop(std::size_t index) {
    Node *anterior = sentinela->next();
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if ((index < 0) || (index > size_ - 1)) {
        throw std::out_of_range("Indice Inválido");
    } else if (index == 0) {
        return pop_front();
    } else {
        for (std::size_t i = 0; i < index - 1; i++) {
            anterior = anterior->next();
        }
        Node *eliminar = anterior->next();
        T volta = eliminar->data();
        anterior->next(eliminar->next());
        delete eliminar;
        size_--;
        return volta;
    }
}

template<typename T>
T structures::CircularList<T>::pop_back() {
    return pop(size_ - 1);
}

template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    }
    Node *saiu = sentinela->next();
    T volta = saiu->data();
    if (size_ == 1) {
        tail = nullptr;
    }
    sentinela->next(saiu->next());
    delete saiu;
    size_--;
    return volta;
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {
    Node *atual = sentinela->next();
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        std::size_t pos = 0;
        while ((atual->data() != data) && (atual->next() != nullptr)) {
            atual = atual->next();
            pos++;
        }
        if (atual->data() != data) {
        } else {
            pop(pos);
        }
    }
}

template<typename T>
bool structures::CircularList<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    Node *atual = sentinela->next();
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        std::size_t pos = 0;
        while ((atual->data() != data) && (atual->next() != nullptr)) {
            atual = atual->next();
            pos++;
        }
        if (atual->data() != data) {
            return false;
        }
        return true;
    }
}

template<typename T>
std::size_t structures::CircularList<T>::find(const T& data) const {
    Node *atual = sentinela->next();
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        std::size_t pos = 0;
        while ((atual->data() != data) && (atual->next() != nullptr)) {
            atual = atual->next();
            pos++;
        }
        if (atual->data() != data) return size_;
        return pos;
    }
}

template<typename T>
std::size_t structures::CircularList<T>::size() const {
    return size_;
}

