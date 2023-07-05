//! Copyright [2023] <Maykon Marcos Junior>

#include <stdexcept>  // C++ Exceptions
#include <cstdint>


namespace structures {

//! ...
template<typename T>
class LinkedStack {
 public:
    LinkedStack();  // construtor padrão
    ~LinkedStack();  // destrutor
    void clear();  // limpar pilha
    void push(const T& data);  // empilha
    T& top();  // dado no topo
    T pop();  // retirar do fim
    bool empty() const;  // lista vazia
    std::size_t size() const;  // tamanho da pilha

 private:
    class Node {  // Elemento
     public:
        explicit Node(const T& newData) {
            data_ = newData;
            next_ = nullptr;
        }
        Node(const T &data, Node *next) {
            data_ = data;
            next_ = next;
        }
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

    Node* end() {  // último nodo da lista
        Node* it = head;
        for (std::size_t i = 1u; i < size_; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    head = nullptr;
    size_ = 0u;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

template<typename T>
void structures::LinkedStack<T>::clear() {
    while (size_) {
        pop();
    }
    head = nullptr;
}

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
    } else {
        end()->next(Elemento);
    }
    size_++;
}

template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        Node* it = head;
        for (std::size_t i = 1; i < size_ - 1; ++i) {
            it = it->next();
        }
        Node* remover = it->next();
        if (!remover) {
            remover = it;
        }
        it->next(nullptr);
        T saida = remover->data();
        remover->next(nullptr);
        size_--;
        delete remover;
        return saida;
    }
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return !size_;
}

template<typename T>
size_t structures::LinkedStack<T>::size() const {
    return size_;
}

template<typename T>
T& structures::LinkedStack<T>::top() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        return end()->data();
    }
}
