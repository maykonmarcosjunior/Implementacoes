//! Copyright [year] <Maykon Marcos Junior>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <stdexcept>  // C++ Exceptions
#include <cstdint>


namespace structures {

//! ...
template<typename T>
class LinkedList {
 public:
    //! ...
    LinkedList();  // construtor padrão
    //! ...
    ~LinkedList();  // destrutor
    //! ...
    void clear();  // limpar lista
    //! ...
    void push_back(const T& data);  // inserir no fim
    //! ...
    void push_front(const T& data);  // inserir no início
    //! ...
    void insert(const T& data, std::size_t index);  // inserir na posição
    //! ...
    void insert_sorted(const T& data);  // inserir em ordem
    //! ...
    T& at(std::size_t index);  // acessar um elemento na posição index
    //! ...
    T pop(std::size_t index);  // retirar da posição
    //! ...
    T pop_back();  // retirar do fim
    //! ...
    T pop_front();  // retirar do início
    //! ...
    void remove(const T& data);  // remover específico
    //! ...
    bool empty() const;  // lista vazia
    //! ...
    bool contains(const T& data) const;  // contém
    //! ...
    std::size_t find(const T& data) const;  // posição do dado
    //! ...
    std::size_t size() const;  // tamanho da lista

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

    Node* end() {  // último nodo da lista
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif

template<typename T>
structures::LinkedList<T>::LinkedList() {}

template<typename T>
structures::LinkedList<T>::~LinkedList() {
    clear();
    delete head;
}

template<typename T>
void structures::LinkedList<T>::clear() {
    while (static_cast<int>(size_) > 0) {
        pop_front();
    }
    head = nullptr;
}

template<typename T>
void structures::LinkedList<T>::push_back(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
    } else {
    end()->next(Elemento);
    }
    size_++;
}

template<typename T>
void structures::LinkedList<T>::push_front(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
    } else {
        Elemento->next(head);
        head = Elemento;
    }
    size_++;
}

template<typename T>
void structures::LinkedList<T>::insert(const T& data, size_t index) {
    if (static_cast<int>(index) < 0 || index > size_) {
        throw std::out_of_range("índice inválido");
    } else if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        auto it = head;
        for (int i = 1; i < static_cast<int>(index); ++i) {
            it = it->next();
        }
        Node* Elemento = new Node(data, it->next());
        it->next(Elemento);
        size_++;}
}

template<typename T>
void structures::LinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_back(data);
    } else {
        auto i = head;
        int k = 1;
        while (k <= static_cast<int>(size_) && i->data() < data) {
            i = i->next();
            k++;
        }
        k--;
        insert(data, k);
    }
}

template<typename T>
T structures::LinkedList<T>::pop(size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else {
        Node *it = head;
        for (int i = 1; i < static_cast<int>(index); ++i) {
            it = it->next();
        }
        auto temp = it->next();
        T temp2 = temp->data();
        it->next(temp->next());
        delete temp;
        size_--;
        return temp2;
    }
}

template<typename T>
T structures::LinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        auto it = head;
        for (int i = 1; i < static_cast<int>(size_); ++i) {
            it = it->next();
        }
        T temp = (*it).data();
        delete it;
        size_--;
        return temp;
    }
}

template<typename T>
T structures::LinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else {
        auto temp = head;
        T temp2 = temp->data();
        head = head->next();
        delete temp;
        size_--;
        return temp2;
    }
}

template<typename T>
void structures::LinkedList<T>::remove(const T& data) {
    size_t i = find(data);
    pop(i);
}

template<typename T>
bool structures::LinkedList<T>::empty() const {
    return 0 == static_cast<int>(size_);
}

template<typename T>
bool structures::LinkedList<T>::contains(const T& data) const {
    return find(data) < size();
}

template<typename T>
size_t structures::LinkedList<T>::find(const T& data) const {
    auto it = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if ((*it).data() == data) {
            return i;
        }
        it = it->next();
    } return size_;
}

template<typename T>
size_t structures::LinkedList<T>::size() const {
    return size_;
}

template<typename T>
T& structures::LinkedList<T>::at(size_t index) {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else {
        auto it = head;
        for (int i = 1; i <= static_cast<int>(index); i++) {
            it = it->next();
        }
        return (*it).data();
    }
}
