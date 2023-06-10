//! Copyright [2023] <Maykon Marcos Junior>

#include <stdexcept>  // C++ Exceptions
#include <cstdint>

namespace structures {

template<typename T>
class DoublyCircularList {
 public:
    DoublyCircularList();
    ~DoublyCircularList();

    void clear();

    void push_back(const T& data);  // insere no fim
    void push_front(const T& data);  // insere no início
    void insert(const T& data, std::size_t index);  // insere na posição
    void insert_sorted(const T& data);  // insere em ordem

    T pop(std::size_t index);  // retira da posição
    T pop_back();  // retira do fim
    T pop_front();  // retira do início
    void remove(const T& data);  // retira específico

    bool empty() const;  // lista vazia
    bool contains(const T& data) const;  // contém

    T& at(std::size_t index);  // acesso a um elemento (checando limites)
    const T& at(std::size_t index) const;  // getter constante a um elemento

    std::size_t find(const T& data) const;  // posição de um dado
    std::size_t size() const;  // tamanho

 private:
    class Node {
     public:
        explicit Node(const T& data) {
            data_ = data;
            next_ = nullptr;
            prev_ = nullptr;
        }

        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
            prev_ = nullptr;
        }

        Node(const T& data, Node* prev, Node* next) {
            data_ = data;
            next_ = next;
            prev_ = prev;
        }

        T& data() {
            return data_;
        }

        const T& data() const {
            return data_;
        }

        Node* prev() {
            return prev_;
        }

        const Node* prev() const {
            return prev_;
        }

        void prev(Node* node) {
            prev_ = node;
        }

        Node* next() {
            return next_;
        }

        const Node* next() const {
            return next_;
        }

        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    std::size_t size_ = 0u;
    Node* ache(std::size_t index) {
        auto it = head;
        if (index < size_/2) {
            for (auto i = 1u; i <= index; ++i) {
                it = it->next();
                }
        } else {
            for (auto i = size_; i > index; --i) {
                it = it->prev();
                }
        }
        return it;
    }
};

}  // namespace structures

template<typename T>
structures::DoublyCircularList<T>::DoublyCircularList() {}

template<typename T>
structures::DoublyCircularList<T>::~DoublyCircularList() {
    clear();
}

template<typename T>
void structures::DoublyCircularList<T>::clear() {
    for (int i = 0; i < static_cast<int>(size_); ++i) {
        auto temp = head;
        head = head->next();
        delete temp;
    }
    size_ = 0u;
    head = nullptr;
}

template<typename T>
void structures::DoublyCircularList<T>::push_back(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
        Elemento->next(Elemento);
        Elemento->prev(Elemento);
    } else if (size_ == 1u) {
        head->next(Elemento);
        Elemento->prev(head);
        head->prev(Elemento);
        Elemento->next(head);
    } else {
        (head->prev())->next(Elemento);
        Elemento->prev(head->prev());
        head->prev(Elemento);
        Elemento->next(head);
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::push_front(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
        Elemento->next(Elemento);
        Elemento->prev(Elemento);
    } else if (size_ == 1u) {
        head->next(Elemento);
        Elemento->prev(head);
        head->prev(Elemento);
        Elemento->next(head);
        head = Elemento;
    } else {
        (head->prev())->next(Elemento);
        Elemento->prev(head->prev());
        head->prev(Elemento);
        Elemento->next(head);
        head = Elemento;
    }
    size_++;
}

template<typename T>
void structures::DoublyCircularList<T>::insert(const T& data, size_t index) {
    if (static_cast<int>(index) < 0 || index > size_) {
        throw std::out_of_range("índice inválido");
    } else if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        auto it = ache(index - 1);
        Node* Elemento = new Node(data, it, it->next());
        (it->next())->prev(Elemento);
        it->next(Elemento);
        size_++;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::insert_sorted(const T& data) {
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
T structures::DoublyCircularList<T>::pop(size_t index) {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else if (static_cast<int>(index) == 0) {
        return pop_front();
    } else if (index == size_ - 1) {
        return pop_back();
    } else {
        auto temp = ache(index);
        T saida = temp->data();
        (temp->next())->prev(temp->prev());
        (temp->prev())->next(temp->next());
        delete temp;
        size_--;
        return saida;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (size_ == 1u) {
        auto saida = head->data();
        delete head;
        size_--;
        return saida;
    } else {
        auto deletado = head->prev();
        T saida = deletado->data();
        (deletado->prev())->next(head);
        head->prev(deletado->prev());
        size_--;
        delete deletado;
        return saida;
    }
}

template<typename T>
T structures::DoublyCircularList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (size_ == 1u) {
        auto saida = head->data();
        delete head;
        size_--;
        return saida;
    } else {
        auto temp = head;
        T saida = temp->data();
        (temp->next())->prev(temp->prev());
        (temp->prev())->next(temp->next());
        head = head->next();
        size_--;
        delete temp;
        return saida;
    }
}

template<typename T>
void structures::DoublyCircularList<T>::remove(const T& data) {
    size_t i = find(data);
    pop(i);
}

template<typename T>
bool structures::DoublyCircularList<T>::empty() const {
    return 0 == static_cast<int>(size_);
}

template<typename T>
bool structures::DoublyCircularList<T>::contains(const T& data) const {
    return find(data) < size_;
}

template<typename T>
size_t structures::DoublyCircularList<T>::find(const T& data) const {
    auto it = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if ((*it).data() == data) {
            return i;
        }
        it = it->next();
    } return size_;
}

template<typename T>
size_t structures::DoublyCircularList<T>::size() const {
    return size_;
}

template<typename T>
const T& structures::DoublyCircularList<T>::at(size_t index) const {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else {
        return ache(index)->data();
    }
}

template<typename T>
T& structures::DoublyCircularList<T>::at(size_t index) {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else {
        return ache(index)->data();
    }
}
/*
#include <iostream>

int main() {
    structures::DoublyCircularList<int> list;
    
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
}
*/
