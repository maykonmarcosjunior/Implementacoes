//! Copyright [2023] <Maykon Marcos Junior>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <stdexcept>  // C++ Exceptions
#include <cstdint>

namespace structures {

template<typename T>
class CircularList {
 public:
    CircularList();
    ~CircularList();

    void clear();  // limpar lista

    void push_back(const T& data);  // inserir no fim
    void push_front(const T& data);  // inserir no início
    void insert(const T& data, std::size_t index);  // inserir na posição
    void insert_sorted(const T& data);  // inserir em ordem

    T& at(std::size_t index);  // acessar em um indice (com checagem de limites)
    const T& at(std::size_t index) const;  // versão const do acesso ao indice

    T pop(std::size_t index);  // retirar da posição
    T pop_back();  // retirar do fim
    T pop_front();  // retirar do início
    void remove(const T& data);  // remover dado específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // lista contém determinado dado?
    std::size_t find(const T& data) const;  // posição de um item na lista

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
        for (auto i = 1u; i < size_; ++i) {
            it = it->next();
        }
        return it;
    }

    Node* ache(std::size_t index) {
        auto it = head;
        for (auto i = 1u; i <= index; ++i) {
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
structures::CircularList<T>::CircularList() {}

template<typename T>
structures::CircularList<T>::~CircularList() {
    clear();
}

template<typename T>
void structures::CircularList<T>::clear() {
    while (static_cast<int>(size_) > 0) {
        auto temp = head;
        head = head->next();
        size_--;
        delete temp;
    }
    head = nullptr;
}

template<typename T>
void structures::CircularList<T>::push_back(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
        Elemento->next(Elemento);
    } else {
    end()->next(Elemento);
    Elemento->next(head);
    }
    size_++;
}

template<typename T>
void structures::CircularList<T>::push_front(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
        Elemento->next(Elemento);
    } else {
        end()->next(Elemento);
        Elemento->next(head);
        head = Elemento;
    }
    size_++;
}

template<typename T>
void structures::CircularList<T>::insert(const T& data, std::size_t index) {
    if (static_cast<int>(index) < 0 || index > size_) {
        throw std::out_of_range("índice inválido");
    } else if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        auto it = ache(index - 1);
        Node* Elemento = new Node(data, it->next());
        it->next(Elemento);
        size_++;
    }
}

template<typename T>
void structures::CircularList<T>::insert_sorted(const T& data) {
    auto i = head;
    int k = 1;
    while (k <= static_cast<int>(size_) && i->data() < data) {
        i = i->next();
        k++;
    }
    k--;
    insert(data, k);
}

template<typename T>
T structures::CircularList<T>::pop(size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else if (static_cast<int>(index) == 0) {
        return pop_front();
    } else if (index == size_ - 1) {
        return pop_back();
    } else {
        Node *it = ache(index - 1);
        auto temp = it->next();
        T temp2 = temp->data();
        it->next(temp->next());
        delete temp;
        size_--;
        return temp2;
    }
}

template<typename T>
T structures::CircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (size_ == 1u) {
        auto saida = head->data();
        delete head;
        size_--;
        return saida;
    } else {
        auto deletado = end();
        T temp = deletado->data();
        size_--;
        delete deletado;
        end()->next(head);
        return temp;
    }
}

template<typename T>
T structures::CircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (size_ == 1u) {
        auto saida = head->data();
        delete head;
        size_--;
        return saida;
    } else {
        auto temp = head;
        T temp2 = temp->data();
        head = head->next();
        size_--;
        delete temp;
        end()->next(head);
        return temp2;
    }
}

template<typename T>
void structures::CircularList<T>::remove(const T& data) {
    size_t i = find(data);
    pop(i);
}

template<typename T>
bool structures::CircularList<T>::empty() const {
    return 0 == static_cast<int>(size_);
}

template<typename T>
bool structures::CircularList<T>::contains(const T& data) const {
    return find(data) < size();
}

template<typename T>
size_t structures::CircularList<T>::find(const T& data) const {
    auto it = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if ((*it).data() == data) {
            return i;
        }
        it = it->next();
    } return size_;
}

template<typename T>
size_t structures::CircularList<T>::size() const {
    return size_;
}

template<typename T>
const T& structures::CircularList<T>::at(size_t index) const {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else {
        return ache(index)->data();
    }
}

template<typename T>
T& structures::CircularList<T>::at(size_t index) {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else {
        return ache(index)->data();
    }
}
/*
#include <iostream>

int main() {
    structures::CircularList<int> list;
    
    // --------------------------------------
    
    std::cout << "BasicPushBack" << std::endl;
    list.push_back(0);
    if (1u == list.size()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    if (0 == list.at(0)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }

    list.push_back(-1);
    if (2u == list.size()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    if (0 == list.at(0)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    if (-1 == list.at(1)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    list.clear();
    
    // --------------------------------------
    
    std::cout << "PushBack" << std::endl;
    
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }

    if (10u == list.size()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }

    for (auto i = 0u; i < 10u; ++i) {
        if (i == list.at(i)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    }
    list.clear();
    
    // --------------------------------------
    
    std::cout << "BasicPushFront" << std::endl;
    
    list.push_front(0);
    if (1u == list.size()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    if (0 == list.at(0)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }

    list.push_front(-1);
    if (2u == list.size()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    if (-1 == list.at(0)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    if (0 == list.at(1)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    
    list.clear();     
    // --------------------------------------
    
    std::cout << "PushFront" << std::endl;

    for (auto i = 0; i < 10; ++i) {
        list.push_front(i);
    }

    if (10u == list.size()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    
    for (auto i = 0u; i < 10u; ++i) {
        if (9-i == list.at(i)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    }
    
    list.clear();
    // --------------------------------------
    
    std::cout << "empty" << std::endl;
    
    if (list.empty()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    list.clear();
    
    // --------------------------------------
    
    std::cout << "NotEmpty" << std::endl;
    
    if (list.empty()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }

    list.push_back(1);
    if (!list.empty()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    list.clear();
    // --------------------------------------
    
    std::cout << "Clear" << std::endl;

    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    list.clear();
    if (0u == list.size()) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    list.clear();
    // --------------------------------------
    
    std::cout << "Find" << std::endl;
    
    for (auto i = 0u; i < 10u; ++i) {
        list.push_back(i);
    }

    for (auto i = 0u; i < 10u; ++i) {
        if (i == list.find(i)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    }
    if (list.size() == list.find(10)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    
 list.clear();     // --------------------------------------
    
    std::cout << "Contains" << std::endl;
    
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    if (list.contains(0)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    if (list.contains(5)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    if (!list.contains(10)) {
        std::cout << "ok" << std::endl;
    } else {
        std::cout << "ERRO" << std::endl;
    }
    list.clear();
    // --------------------------------------
    
    std::cout << "AccessAt" << std::endl;
    
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    
    for (auto i = 0u; i < 10u; ++i) {
        if (i == list.at(i)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    }

    list.clear();
    for (auto i = 10; i > 0; --i) {
        list.push_back(i);
    }
    
    for (auto i = 0u; i < 10u; ++i) {
        if (10-i == list.at(i)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    }
    list.clear();
    
    // --------------------------------------
    
    std::cout << "AccessAtBoundCheck" << std::endl;
    
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 0; i < 10; ++i) {
        try { 
            list.at(i);
            std::cout << "ok" << std::endl;
        }  catch (std::out_of_range) {
            std::cout << "ERRO\n";
        }
    }
    try { 
        list.pop(8);
        std::cout << "ok" << std::endl;
    }  catch (std::out_of_range) {
        std::cout << "ERRO\n";
    }
    try {
        std::cout << list.at(-1) << "ERRO" << std::endl;
    } catch (std::out_of_range) {
        std::cout << "ok" << std::endl;
    }
    list.clear();
    // --------------------------------------
    
    std::cout << "Insert" << std::endl;
    
    for (auto i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    for (auto i = 6; i < 10; ++i) {
        list.push_back(i);
    }
    list.insert(5, 5u);

    for (auto i = 0; i < 10; ++i) {
        if (i == list.at(i)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    }
    
 list.clear();     // --------------------------------------
    
    std::cout << "InsertionInOrder" << std::endl;
    
    for (auto i = 9; i >= 0; --i) {
        list.insert_sorted(i);
    }
    for (auto i = 0; i < 10; ++i) {
        if (i == list.at(i)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    }

    list.clear();

    list.insert_sorted(10);
    list.insert_sorted(-10);
    list.insert_sorted(42);
    list.insert_sorted(0);
    if (-10 == list.at(0)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    if (0 == list.at(1)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    if (10 == list.at(2)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    if (42 == list.at(3)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    
 list.clear();     // --------------------------------------
    
    std::cout << "InsertionBounds" << std::endl;
    
    try {
        list.insert(1u, 1);
            std::cout << "ERRO" << std::endl;
    } catch (std::out_of_range) {
            std::cout << "ok" << std::endl;
        }
    try {
        list.insert(-1, 1);
            std::cout << "ERRO" << std::endl;
    } catch (std::out_of_range) {
            std::cout << "ok" << std::endl;
        }
    
 list.clear();     // --------------------------------------
    
    std::cout << "EmptyPopBack" << std::endl;
    
    try {
        list.pop_back();
            std::cout << "ERRO" << std::endl;
    } catch (std::out_of_range) {
            std::cout << "ok" << std::endl;
        }
    
 list.clear();     // --------------------------------------
    
    std::cout << "PopBack" << std::endl;
    
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 9; i >= 0; --i) {
        if (i == list.pop_back()) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    }
    if (list.empty()) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    
 list.clear();     // --------------------------------------
    
    std::cout << "EmptyPopFront" << std::endl;
    
    try {
        list.pop_front();
            std::cout << "ERRO" << std::endl;
    } catch (std::out_of_range) {
            std::cout << "ok" << std::endl;
        }
    
 list.clear();     // --------------------------------------
    
    std::cout << "PopFront" << std::endl;
    
    for (auto i = 9; i >= 0; --i) {
        list.push_front(i);
    }
    for (auto i = 0; i < 10; ++i) {
        if (i == list.pop_front()) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    }
    if (list.empty()) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    
 list.clear();     // --------------------------------------
    
    std::cout << "PopAt" << std::endl;
    
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    if (5 == list.pop(5)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    if (6 == list.pop(5)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    if (8u == list.size()) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    try {
        list.pop(8);
            std::cout << "ERRO" << std::endl;
    } catch (std::out_of_range) {
            std::cout << "ok" << std::endl;
        }
    
 list.clear();     // --------------------------------------
    
    std::cout << "RemoveElement" << std::endl;
    
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    list.remove(4);
    if (9u == list.size()) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }
    if (!list.contains(4)) {
            std::cout << "ok" << std::endl;
        } else {
            std::cout << "ERRO" << std::endl;
        }


    return 0;
} */
