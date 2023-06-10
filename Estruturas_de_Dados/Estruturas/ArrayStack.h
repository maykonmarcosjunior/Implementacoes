#ifndef STRUCTURES_ARRAY_STACK_H // muitos arquivos podem chamar pilha
#define STRUCTURES_ARRAY_STACK_H // usar ifndef evita redundância

#include <stdexcept>  // inclui C++ exceptions

namespace structures {

template<typename T> // para que aceite qualquer tipo

//! CLASSE PILHA
class ArrayStack {
 public:
    //! construtor simples
    ArrayStack();
    //! construtor com parâmetro tamanho
    explicit ArrayStack(unsigned int); // não precisa dar nome ao parâmetro
    //! destrutor
    ~ArrayStack();
    //! método empilha
    void push(const T&);
    //! metodo desempilha
    T pop();
    //! método retorna o topo
    T& top();
    //! método limpa pilha
    void clear();
    //! método retorna tamanho
    unsigned int size();
    //! método retorna capacidade máxima
    unsigned int max_size();
    //! verifica se está vazia
    bool empty();
    //! verifica se está cheia
    bool full();

 private:
    T* contents;
    int top_;
    unsigned int max_size_;
    // constante estática com tipo definido pelo auto como unsigned
    static const auto DEFAULT_SIZE = 10u;
};
}  // fecha o namespace structures

#endif

// definir só os protótipos antes permite que as funções chamem umas às outras sem erro de função
// não-implementada (que aconteceria pois a função é definida mais em baixo)
// Além disso, o certo seria fazer o protótipo em um arquivo.h e o resto em um arquivo.cpp

template<typename T>
structures::ArrayStack<T>::ArrayStack() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::ArrayStack(unsigned int max) {
    max_size_ = max;
    contents = new T[max_size_];
    top_ = -1;
}

template<typename T>
structures::ArrayStack<T>::~ArrayStack() {
    delete [] contents;
}

template<typename T>
void structures::ArrayStack<T>::push(const T& data) {
    if (full()) {
        throw std::out_of_range("pilha cheia");
    } else {
        top_++;
        contents[top_] = data;
    }
}

template<typename T>
T structures::ArrayStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("pilha vazia"); // exceção mais usada
    } else {
        top_--; return contents[top_ + 1];
    }
}

template<typename T>
T& structures::ArrayStack<T>::top() {
    return contents[top_];
}

template<typename T>
void structures::ArrayStack<T>::clear() {
    top_ = -1;
}

template<typename T>
unsigned int structures::ArrayStack<T>::size() {
    return (top_ + 1);
}

template<typename T>
unsigned int structures::ArrayStack<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayStack<T>::empty() {
    return top_ == -1;
}

template<typename T>
bool structures::ArrayStack<T>::full() {
   return top_ + 1 == static_cast<int>(max_size_);
}
