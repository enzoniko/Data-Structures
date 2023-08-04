//! Copyright [2023] <Enzo Nicolás Spotorno Bieger>

namespace structures {

template<typename T>
class LinkedStack {
 public:
    LinkedStack();

    ~LinkedStack();

    void clear();  // limpa pilha

    void push(const T& data);  // empilha

    T pop();  // desempilha

    T& top() const;  // dado no topo

    bool empty() const;  // pilha vazia

    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        T& data() {  // getter: info
            return data_;
        }
        const T& data() const {  // getter-constante: info
            return data_;
        }
        Node* next() {  // getter: próximo
            return next_;
        }
        const Node* next() const {  // getter-constante: próximo
            return next_;
        }
        void next(Node* next) {  // setter: próximo
            next_ = next;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* top_{nullptr};  // nodo-topo
    std::size_t size_{0u};  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    // Já esta implementado na classe.
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    // Desalocar cada um dos nós da pilha existente.
    // Efetuar 'pop()' até que a pilha se torne vazia.
    clear();
    delete top_;
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (!empty()) {
        pop();
    }
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node *novo = new Node(data);
    if (novo == NULL) {
        throw std::out_of_range("Lista Cheia");
    }
    if (empty()) {
        novo->next(nullptr);
        top_ = novo;
    } else {
        novo->next(top_);
        top_ = novo;
    }
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    }
    Node *saiu = top_;
    T volta = saiu->data();
    top_ = saiu->next();
    delete saiu;
    size_--;
    return volta;
}

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    }
    return top_->data();
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return size_;
}













