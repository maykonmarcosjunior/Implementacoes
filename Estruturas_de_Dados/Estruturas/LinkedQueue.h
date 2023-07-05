//! Copyright [2023] <Maykon Marcos Junior>

#include <stdexcept>  // C++ Exceptions
#include <cstdint>


namespace structures {

//! ...
template<typename T>
class LinkedQueue {
 public:
    LinkedQueue();  // construtor padrão
    ~LinkedQueue();  // destrutor
    void clear();  // limpar fila
    void enqueue(const T& data);  // enfileira
    T& front();  // primeiro inserido
    T& back();  // último inserido
    T dequeue();  // desenfileira
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

    Node* head;
    Node* tail;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    size_ = 0u;
}

template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

template<typename T>
void structures::LinkedQueue<T>::clear() {
    while (size_) {
        dequeue();
    }
    head = nullptr;
    tail = nullptr;
}

template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
        tail = Elemento;
    } else {
        tail->next(Elemento);
        tail = Elemento;
    }
    size_++;
}

template<typename T>
T structures::LinkedQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        Node* remover = head;
        head = head->next();
        T saida = remover->data();
        remover->next(nullptr);
        size_--;
        delete remover;
        if (!head) {
            tail = nullptr;
        }
        return saida;
    }
}

template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return !size_;
}

template<typename T>
size_t structures::LinkedQueue<T>::size() const {
    return size_;
}

template<typename T>
T& structures::LinkedQueue<T>::front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        return head->data();
    }
}

template<typename T>
T& structures::LinkedQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        return tail->data();
    }
}
