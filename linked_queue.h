//! Copyright [2023] <Enzo Nicolás Spotorno Bieger>
namespace structures {


template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();

    ~LinkedQueue();

    void clear();  // limpar

    void enqueue(const T& data);  // enfilerar

    T dequeue();  // desenfilerar

    T& front() const;  // primeiro dado

    T& back() const;  // último dado

    bool empty() const;  // fila vazia

    std::size_t size() const;  // tamanho

 private:
    class Node {  // Elemento
     public:
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

    Node* head{nullptr};  // nodo-cabeça
    Node* tail{nullptr};  // nodo-fim
    std::size_t size_{0u};  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    // Já esta implementado na classe.
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    // Desalocar cada um dos nós de lista existente.
    // Efetuar 'pop_front()' até que a lista se torne vazia.
    clear();
    delete head;  // Head is tail now
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (!empty()) {
        dequeue();
    }
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node *novo = new Node(data);
    if (novo == NULL) {
        throw std::out_of_range("Fila Cheia");
    }
    if (empty()) {
        head = novo;
        tail = novo;
        head->next(nullptr);
        tail->next(nullptr);
    } else {
        novo->next(nullptr);
        tail->next(novo);
        tail = novo;
    }
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        Node * eliminar = head;
        T valor = eliminar->data();
        head = eliminar->next();
        delete eliminar;
        size_--;
        return valor;
    }
}

template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        return head->data();
    }
}

template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        return tail->data();
    }
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}






