//! Copyright [2023] <Enzo Nicolás Spotorno Bieger>

#include <stdexcept>

namespace structures {

template<typename T>
class DoublyCircularList {
 private:
    class Node {  // implementar cada um dos métodos de Node
     public:
        Node() {
        }

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
    DoublyCircularList();
    ~DoublyCircularList();
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
    // Node* sentinel{nullptr};  // sentinela
    std::size_t size_{0u};

    Node * posicao(std::size_t index) {
        Node *p;
        if (index < size_/2) {  // 1º metade
            p = head->next();
            for (std::size_t i = 0; i < index; i++) {
                p = p->next();
            }
        } else {  // 2º metade
            p = head->prev();
            for (std::size_t i = size_ - 1; i > index; i--) {
                p = p->prev();
            }
        }
        return p;
    }
};

}  // namespace structures

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {
    Node *sentinela = new Node();
    if (sentinela == NULL) {
        throw std::out_of_range("Lista Cheia");
    }
    head = sentinela;
    head->prev(head);
    head->next(head);
}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    // Desalocar cada um dos nós de lista existente.
    // Efetuar 'pop_front()' até que a lista se torne vazia.
    clear();
    delete head;  // Head is tail now
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    while (!empty()) {
        pop_front();
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    if (empty()) {
        push_front(data);
    } else {
        Node *novo = new Node(data);
        if (novo == NULL) {
            throw std::out_of_range("Lista Cheia");
        }
        novo->next(head);
        novo->prev(head->prev());
        head->prev()->next(novo);
        head->prev(novo);
        size_++;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node *novo = new Node(data);
    if (novo == NULL) {
        throw std::out_of_range("Lista Cheia");
    }
    novo->prev(head);
    if (empty()) {
        head->prev(novo);
        novo->next(head);
    } else {
        novo->next(head->next());
        head->next()->prev(novo);
    }
    head->next(novo);
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data,
std::size_t index) {
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
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
    Node *atual = head->next();
    if (empty()) {
        push_front(data);
    } else {
        std::size_t pos = 0;
        while ((atual->next() != head) && (data > atual->data())) {
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
T& structures::DoublyCircularList<T>::at(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if ((index < 0) || (index > size_ - 1)) {
        throw std::out_of_range("Indice Inválido");
    } else if (index == 0) {
        return head->next()->data();
    } else if (index == size_ - 1) {
        return head->prev()->data();
    } else {
        Node * p = posicao(index);
        return p->data();
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop(std::size_t index) {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if ((index < 0) || (index > size_ - 1)) {
        throw std::out_of_range("Indice Inválido");
    } else if (index == 0) {
        return pop_front();
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
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else if (size_ == 1) {
        return pop_front();
    }
    return pop(size_ - 1);
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    }
    Node * eliminar = head->next();
    T volta = eliminar->data();
    if (size_ == 1) {
        head->prev(head);
    } else {
        eliminar->next()->prev(head);
    }
    head->next(eliminar->next());
    delete eliminar;
    size_--;
    return volta;
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    Node *atual = head->next();
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        std::size_t pos = 0;
        while ((atual->data() != data) && (atual->next() != head)) {
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
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    Node *atual = head->next();
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        while ((atual->data() != data) && (atual->next() != head)) {
            atual = atual->next();
        }
        if (atual->data() != data) {
            return false;
        }
        return true;
    }
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::find(const T& data) const {
    Node *atual = head->next();
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        std::size_t pos = 0;
        while ((atual->data() != data) && (atual->next() != head)) {
            atual = atual->next();
            pos++;
        }
        if (atual->data() != data) return size_;
        return pos;
    }
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
std::size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}






