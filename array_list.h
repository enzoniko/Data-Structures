// Copyright [2023] <Enzo Nicolás Spotorno Bieger>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};
}  // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    size_ = 0;
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max) {
    size_ = 0;
    max_size_ = max;
    contents = new T[max_size_];
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    size_ = 0;
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw std::out_of_range("Lista Cheia");
    } else {
        size_++;
        contents[size_ - 1] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    std::size_t pos;
    if (full()) {
        throw std::out_of_range("Lista Cheia");
    } else {
        size_++;
        pos = size_ - 1;
        while (pos > 0) {
            contents[pos] = contents[pos - 1];
            pos--;
        }
        contents[0] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    std::size_t pos;
    if (full()) {
        throw std::out_of_range("Lista Cheia");
    } else if (index > size_) {
        throw std::out_of_range("Erro Posição");
    } else {
        size_++;
        pos = size_ - 1;
        while (pos > index) {
            contents[pos] = contents[pos - 1];
            pos--;
        }
        contents[index] = data;
    }
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    std::size_t pos = 0;
    if (empty()) {
        insert(data, 0);
    } else {
        while ((pos <= size_ - 1) && (data > contents[pos])) {
            pos++;
        }
        insert(data, pos);
    }
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    std::size_t pos;
    T valor;
    if (index > size_ - 1) {
        throw std::out_of_range("Erro Posição");
    } else if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        valor = contents[index];
        pos = index;
        while (pos <= size_ - 1) {
            contents[pos] = contents[pos + 1];
            pos++;
        }
        size_--;
        return valor;
    }
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        size_--;
        return contents[size_];
    }
}

template<typename T>
T structures::ArrayList<T>::pop_front() {
    int pos;
    T valor;
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        valor = contents[0];
        pos = 0;
        while (pos <= static_cast<int>(size_) - 1) {
            contents[pos] = contents[pos + 1];
            pos++;
        }
        size_--;
        return valor;
    }
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    std::size_t pos;
    if (empty()) {
        throw std::out_of_range("Lista Vazia");
    } else {
        pos = find(data);
        if (pos < 0) {
            throw std::out_of_range("Erro Posição");
        } else {
            pop(pos);
        }
    }
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    if (size_ == max_size_) {
        return true;
    }
    return false;
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    if (size_ == 0) {
        return true;
    }
    return false;
}

template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    for (std::size_t pos = 0; pos < size_; pos++) {
        if (contents[pos] == data) {
            return true;
        }
    }
    return false;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    std::size_t pos = 0;
    while ((pos <= size_ - 1) && (data != contents[pos])) {
        pos++;
    }
    if (pos > size_) {
        throw std::out_of_range("Erro Posição");
    }
    return pos;
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (index > size_) {
        throw std::out_of_range("Erro Posição");
    } else {
        return contents[index];
    }
}

template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}

template<typename T>
const T& structures::ArrayList<T>::at(std::size_t index) const {
    if (index > size_ - 1) {
        throw std::out_of_range("Erro Posição");
    } else {
        return contents[index];
    }
}

template<typename T>
const T& structures::ArrayList<T>::operator[](std::size_t index) const {
    return contents[index];
}


















