// Copyright [2018] <Maykon Marcos Junior>
#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! classe ArrayQueue
class ArrayQueue {
 public:
    //! construtor padrao
    ArrayQueue();
    //! construtor com parametro
    explicit ArrayQueue(unsigned int max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    // retorna o primeiro
    // dado inserido
    T& front();
    // retorna o ultimo
    // dado inserido
    T& back();
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    unsigned int size();
    //! metodo retorna tamanho maximo
    unsigned int max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    unsigned int size_ = 0;
    unsigned int max_size_;
    int begin_ = -1;  // indice do inicio (para fila circular)
    int end_ = -1;  // indice do fim (para fila circular)
    static const auto DEFAULT_SIZE = 10u;
};

}  // namespace structures

#endif

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(unsigned int max) {
    max_size_ = max;
    contents = new T[max_size_];
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete [] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T& data) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    } else if (data != NULL) {
        size_++;
        end_ = (end_ + 1)%(max_size_);
        contents[end_] = data;    
    }
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        size_--;
        begin_ = (begin_ + 1)%(max_size_));
        return contents[begin_];
    }
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return contents[end];
    }
}

template<typename T>
T& structures::ArrayQueue<T>::front() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return contents[begin_ + 1];
    }
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    end_ = -1;
    begin_ = -1;
    size_ = 0;
}

template<typename T>
unsigned int structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
unsigned int structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return 0u == size_; 
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    return size_ == max_size_;
}
