// Copyright [2023] <Maykon Marcos Junior>
#include <stdio.h>
#include <cstdint>  // size_t
#include <stdexcept>  // C++ Exceptions
#include <iostream>

using namespace std;

namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, size_t index);
    void insert_sorted(const T& data);
    T pop(size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    size_t find(const T& data) const;
    size_t size() const;
    size_t max_size() const;
    T& at(size_t index);
    T& operator[](size_t index); // permite acessar com []
    const T& at(size_t index) const;
    const T& operator[](size_t index) const;

 private:
    T* contents;
    size_t size_;
    size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}  // namespace structures
using namespace structures;

template<typename T>
ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
ArrayList<T>::ArrayList(size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void ArrayList<T>::push_back(const T& data) {
    if (full()) {
        throw out_of_range("lista cheia");
    } else {
    contents[size_] = data;
    size_++;}
}

template<typename T>
void ArrayList<T>::push_front(const T& data) {
    if (full()) {
        throw out_of_range("lista cheia");
    } else {
    for (int i = static_cast<int>(size_);
    i > 0; i--) {
        contents[i] = contents[i-1];
    } contents[0] = data; size_++;}
}

template<typename T>
void ArrayList<T>::insert(const T& data, size_t index) {
    if (full()) {
        throw out_of_range("lista cheia");
    } else if (static_cast<int>(index) < 0 || index > size_) {
        throw out_of_range("índice inválido");
    } else {
        for (int i = static_cast<int>(size_);
        i > static_cast<int>(index); i--) {
            contents[i] = contents[i-1];
        }
        contents[index] = data;
        size_++;};
}

template<typename T>
void ArrayList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_back(data);
    } else {
    int i = 0;
    while (i < static_cast<int>(size_) && contents[i] < data)
    {i++;} insert(data, i);
    }
}

template<typename T>
T ArrayList<T>::pop(size_t index) {
    if (empty()) {
        throw out_of_range("lista vazia");
    } else if (static_cast<int>(index) < 0 || index >= size_) {
        throw out_of_range("índice inválido");
    } else {
        T temp = contents[index];
        for (int i = static_cast<int>(index);
        i < static_cast<int>(size_) - 1; i++) {
            contents[i] = contents[i + 1];
        } size_--; return temp;
    }
}

template<typename T>
T ArrayList<T>::pop_back() {
    if (empty()) {
        throw out_of_range("lista vazia");
    } else {
        return contents[--size_];
    }
}

template<typename T>
T ArrayList<T>::pop_front() {
    if (empty()) {
        throw out_of_range("lista vazia");
    } else {
        T temp = contents[0];
        for (int i = 0;
        i < static_cast<int>(size_) - 1; i++) {
            contents[i] = contents[i + 1];
        } size_--; return temp;
    }
}

template<typename T>
void ArrayList<T>::remove(const T& data) {
    for (int i = 0;
    i < static_cast<int>(size_); i++) {
        if (contents[i] == data) {
            pop(i);
            break;
        }
    }
}

template<typename T>
bool ArrayList<T>::full() const {
    return size() == max_size();
}
  
template<typename T>
bool ArrayList<T>::empty() const {
    return 0 == static_cast<int>(size_);
}

template<typename T>
bool ArrayList<T>::contains(const T& data) const {
    for (int i = 0; i < size_; i++) {
        if (contents[i] == data) {
            return true;
        }
    } return false;
}

template<typename T>
size_t ArrayList<T>::find(const T& data) const {
    for (int i = 0;
    i < static_cast<int>(size_); i++) {
        if (contents[i] == data) {
            return i;
        }
    } return size_;
}

template<typename T>
size_t ArrayList<T>::size() const {
    return size_;
}

template<typename T>
size_t ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
T& ArrayList<T>::at(size_t index) {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw out_of_range("índice inválido");
    } return contents[index];
}

// recomenda-se não testar o indice no operator, por eficiencia
template<typename T>
T& ArrayList<T>::operator[](size_t index) {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw out_of_range("índice inválido");
    } return contents[index];
}

// const sinaliza que essa funçã é só de consulta
template<typename T>
const T& ArrayList<T>::at(size_t index) const {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw out_of_range("índice inválido");
    } return contents[index];
}

// recomenda-se não testar o indice no operator, por eficiencia
template<typename T>
const T& ArrayList<T>::operator[](size_t index) const {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw out_of_range("índice inválido");
    } return contents[index];
}
