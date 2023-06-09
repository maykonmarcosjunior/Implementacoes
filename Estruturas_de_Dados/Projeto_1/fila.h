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
    explicit ArrayQueue(int max);
    //! destrutor padrao
    ~ArrayQueue();
    //! metodo enfileirar
    void enqueue(const T& data);
    //! metodo desenfileirar
    T dequeue();
    //! metodo retorna o ultimo
    T& back();
    //! metodo verifica se contém
    bool contains(const T& data) const;
    //! metodo limpa a fila
    void clear();
    //! metodo retorna tamanho atual
    int size();
    //! metodo retorna tamanho maximo
    int max_size();
    //! metodo verifica se vazio
    bool empty();
    //! metodo verifica se esta cheio
    bool full();

 private:
    T* contents;
    int size_ = 0;
    int max_size_;
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
structures::ArrayQueue<T>::ArrayQueue(int max) {
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
    } else if (!contains(data)) {
        size_++;
        end_ = (end_ + 1)%(static_cast<int>(max_size_));
        contents[end_] = data;    
    }
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        size_--;
        begin_ = (begin_ + 1)%(static_cast<int>(max_size_));
        return contents[begin_];
    }
}

template<typename T>
T& structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return contents[begin_ + 1]; 
    }
}

template<typename T>
bool structures::ArrayQueue<T>::contains(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data) {
            return true;
        }
    } return false;
}


template<typename T>
void structures::ArrayQueue<T>::clear() {
    end_ = -1;
    begin_ = -1;
    size_ = 0;
}

template<typename T>
int structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
int structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return 0 == static_cast<int>(size_); 
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    return size_ == max_size_;
}
