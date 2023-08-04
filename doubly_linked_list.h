//! Copyright [2023] <Enzo Nicolás Spotorno Bieger>

#include <stdexcept>

namespace structures {

template<typename T>
class DoublyLinkedList {
 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        explicit Node(const T& data) {
            data_ = data;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            next_ = next;
            prev_ = prev;
        }

        T& data() {  // getter: dado
            return data_;
        }

        const T& data() const {  // getter const: dado
            return data_;
        }

        Node* prev() {  // getter: prev
            return prev_;
        }
        const Node* prev() const {  // getter const: prev
            return prev_;
        }

        void prev(Node* node) {  // setter: prev
            prev_ = node;
        }

        Node* next() {  // getter: next
            return next_;
        }

        const Node* next() const {  // getter const: next
            return next_;
        }

        void next(Node* node) {  // setter: next
            next_ = node;
        }

     private:
        T data_;
        Node* prev_{nullptr};
        Node* next_{nullptr};
    };

 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    // const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

    Node* head{nullptr};  // primeiro da lista
    Node* tail{nullptr};  // ultimo da lista
    std::size_t size_{0u};

    Node * posicao(std::size_t index) {
        Node *p;
        if (index < size_/2) {  // 1º metade
            p = head;
            for (std::size_t i = 0; i < index; i++) {
                p = p->next();
            }
        } else {  // 2º metade
            p = tail;
            for (std::size_t i = size_ - 1; i > index; i--) {
                p = p->prev();
            }
        }
        return p;
    }
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {
    // Já esta implementado na classe.
}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    // Desalocar cada um dos nós de lista existente.
    // Efetuar 'pop_front()' até que a lista se torne vazia.
    clear();
    delete head;  // Head is tail now
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *novo = new Node(data);
        if (novo == NULL) {
            throw std::out_of_range("Lista Cheia");
        }
        novo->next(nullptr);
        novo->prev(tail);
        tail->next(novo);
        tail = novo;
        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    if (novo == NULL) {
        throw std::out_of_range("Lista Cheia");
    }
    novo->prev(nullptr);
    if (empty()) {
        tail = novo;
        novo->next(nullptr);
    } else {
        novo->next(head);
        head->prev(novo);
    }
    head = novo;
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, std::size_t index) {
    if ((index < 0) || (index > size_)) {
        throw std::out_of_range("Indice Inválido");
    } else if (index == size_) {
        push_back(data);
    } else if (index == 0) {
        push_front(data);
    } else {
        Node *novo = new Node(data);
        if (novo == NULL) {
            throw std::out_of_range("Lista Cheia");
        }
        Node * p = posicao(index);
        p->prev()->next(novo);
        novo->prev(p->prev());
        p->prev(novo);
        novo->next(p);
        size_++;
    }
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    Node *atual = head;
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
T& structures::DoublyLinkedList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if ((index < 0) || (index > size_ - 1)) {
        throw std::out_of_range("Indice Inválido");
    } else if (index == 0) {
        return head->data();
    } else if (index == size_ - 1) {
        return tail->data();
    } else {
        Node * p = posicao(index);
        return p->data();
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if ((index < 0) || (index > size_ - 1)) {
        throw std::out_of_range("Indice Inválido");
    } else if (index == 0) {
        return pop_front();
    } else if (index == size_ - 1) {
        return pop_back();
    } else {
        Node * eliminar = posicao(index);
        T volta = eliminar->data();
        eliminar->prev()->next(eliminar->next());
        eliminar->next()->prev(eliminar->prev());
        delete eliminar;
        size_--;
        return volta;
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if (size_ == 1) {
        return pop_front();
    }
    Node * eliminar = tail;
    T valor = eliminar->data();
    eliminar->prev()->next(nullptr);
    tail = eliminar->prev();
    delete eliminar;
    size_--;
    return valor;
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    }
    Node * eliminar = head;
    T volta = eliminar->data();
    if (size_ == 1) {
        tail = nullptr;
    } else {
        eliminar->next()->prev(nullptr);
    }
    head = eliminar->next();
    delete eliminar;
    size_--;
    return volta;
}

template<typename T>
void structures::DoublyLinkedList<T>::remove(const T& data) {
    Node *atual = head;
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
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    Node *atual = head;
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        while ((atual->data() != data) && (atual->next() != nullptr)) {
            atual = atual->next();
        }
        if (atual->data() != data) {
            return false;
        }
        return true;
    }
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    Node *atual = head;
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
bool structures::DoublyLinkedList<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
std::size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}






