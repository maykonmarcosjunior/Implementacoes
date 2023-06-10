//! Copyright [2023] <Maykon Marcos Junior>

#include <stdexcept>  // C++ Exceptions
#include <cstdint>


namespace structures {

template<typename T>
class DoublyLinkedList {
 public:
    DoublyLinkedList();
    ~DoublyLinkedList();
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
    class Node {  // implementar cada um dos métodos de Node
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

    Node* posicao(std::size_t index)  {
        if (static_cast<int>(index) < 0 || index >= size_) {
            throw std::out_of_range("índice inválido");
        } else {
            Node *it;
            if (index < size()/2) {
                it = head;
                for (int i = 0; i < static_cast<int>(index); ++i) {
                    it = it->next();
                }
            } else {
                it = tail;
                for (std::size_t i = size() - 1; i > index; --i) {
                    it = it->prev();
                }
            }
            return it;
            }
        }

    Node* head = nullptr;  // primeiro da lista
    Node* tail = nullptr;  // ultimo da lista
    std::size_t size_ = 0;
};

}  // namespace structures

template<typename T>
structures::DoublyLinkedList<T>::DoublyLinkedList() {}

template<typename T>
structures::DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
    delete head;
}

template<typename T>
void structures::DoublyLinkedList<T>::clear() {
    while (static_cast<int>(size_) > 0) {
        pop_front();
    }
    head = nullptr;
    tail = nullptr;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_back(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
        tail = Elemento;
    } else {
    tail->next(Elemento);
    Elemento->prev(tail);
    tail = Elemento;
    }
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::push_front(const T& data) {
    Node* Elemento = new Node(data);
    if (empty()) {
        head = Elemento;
        tail = Elemento;
    } else {
        Elemento->next(head);
        head->prev(Elemento);
        head = Elemento;
    }
    size_++;
}

template<typename T>
void structures::DoublyLinkedList<T>::insert(const T& data, size_t index) {
    if (static_cast<int>(index) < 0 || index > size_) {
        throw std::out_of_range("índice inválido");
    } else if (index == 0) {
        push_front(data);
    } else if (index == size_) {
        push_back(data);
    } else {
        auto it = posicao(index);
        Node* Elemento = new Node(data, it->prev(), it);
        (it->prev())->next(Elemento);
        it->prev(Elemento);
        size_++;}
}

template<typename T>
void structures::DoublyLinkedList<T>::insert_sorted(const T& data) {
    if (empty()) {
        push_back(data);
    } else {
        auto i = head;
        int k = 0;
        while (k < static_cast<int>(size_) && i->data() < data) {
            i = i->next();
            k++;
        }
        insert(data, k);
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop(size_t index) {
    if (static_cast<int>(index) == 0) {
        return pop_front();
    } else if (index == (size_ - 1)) {
        return pop_back();
    } else if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else {
        auto it = posicao(index - 1);
        auto temp = it->next();
        T temp2 = (temp)->data();
        (temp->next())->prev(it);
        it->next(temp->next());
        delete temp;
        size_--;
        return temp2;
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (static_cast<int>(size_) == 1) {
        auto temp = head;
        T temp2 = temp->data();
        head = nullptr;
        tail = nullptr;
        delete temp;
        size_--;
        return temp2;
    } else {
        auto temp = tail;
        tail = temp->prev();
        T temp2 = temp->data();
        delete temp;
        size_--;
        return temp2;
    }
}

template<typename T>
T structures::DoublyLinkedList<T>::pop_front() {
    if (empty()) {
        throw std::out_of_range("lista vazia");
    } else if (static_cast<int>(size_) == 1) {
        auto temp = head;
        T temp2 = head->data();
        head = nullptr;
        tail = nullptr;
        delete temp;
        size_--;
        return temp2;
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
void structures::DoublyLinkedList<T>::remove(const T& data) {
    size_t i = find(data);
    pop(i);
}

template<typename T>
bool structures::DoublyLinkedList<T>::empty() const {
    return 0 == static_cast<int>(size_);
}

template<typename T>
bool structures::DoublyLinkedList<T>::contains(const T& data) const {
    return find(data) < size();
}

template<typename T>
size_t structures::DoublyLinkedList<T>::find(const T& data) const {
    auto it = head;
    for (int i = 0; i < static_cast<int>(size_); i++) {
        if ((*it).data() == data) {
            return i;
        }
        it = it->next();
    } return size_;
}

template<typename T>
size_t structures::DoublyLinkedList<T>::size() const {
    return size_;
}

template<typename T>
T& structures::DoublyLinkedList<T>::at(size_t index) {
    return (posicao(index))->data();
}

template<typename T>
const T& structures::DoublyLinkedList<T>::at(size_t index) const {
    if (static_cast<int>(index) < 0 || index >= size_) {
        throw std::out_of_range("índice inválido");
    } else {
        return (posicao(index))->data();
    }
}

/*
#include <iostream>

int main()
{
    structures::DoublyLinkedList<int> list;
    

    std::cout << "Teste Insert Sorted\n";

    
    for (auto i = 9; i >= 0; --i) {
        list.insert_sorted(i);
    }
    for (auto i = 0; i < 10; ++i) {
        std::cout << i << " = " << list.at(i) << std::endl;
    }
    list.clear();
    
    
    list.insert_sorted(10);
    list.insert_sorted(-10);
    list.insert_sorted(42);
    list.insert_sorted(0);
    std::cout << -10 << " = " << list.at(0) << std::endl;
    std::cout << 0 << " = " << list.at(1) << std::endl;
    std::cout << 10 << " = " << list.at(2) << std::endl;
    std::cout << 42 << " = " << list.at(3) << std::endl;

    list.clear();

    
    std::cout << "Teste Insert\n";

    for (auto i = 0; i < 5; ++i) {
        list.push_back(i);
    }
    for (auto i = 6; i < 10; ++i) {
        list.push_back(i);
    }
    list.insert(5, 5u);

    for (auto i = 0; i < 10; ++i) {
        std::cout << i << " = " << list.at(i) << std::endl;
    }

    list.clear();
    

    std::cout << "Teste Basic Push Back\n";
    
    list.push_back(0);
    std::cout << "1 = " << list.size() << std::endl;
    std::cout << "0 = " << list.at(0) << std::endl;
    
    list.push_back(-1);
    std::cout << "2 = " << list.size() << std::endl;
    std::cout << "0 = " << list.at(0) << std::endl;
    std::cout << "-1 = " << list.at(1) << std::endl;
    
    list.clear();

    
    std::cout << "Teste Push Back\n";
    
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    std::cout << "10 = " << list.size() << std::endl;

    for (int i = 0; i < 10; ++i) {
        std::cout << i << " = " << list.at(i) << std::endl;
    }

    list.clear();
    

    
    std::cout << "Teste Basic Push Front\n";
    
    list.push_front(0);
    std::cout << "1 = " << list.size() << std::endl;
    std::cout << "0 = " << list.at(0) << std::endl;

    list.push_front(-1);
    std::cout << "2 = " << list.size() << std::endl;
    std::cout << "-1 = " << list.at(0) << std::endl;
    std::cout << "0 = " << list.at(1) << std::endl;

    list.clear();
    
    
    
    std::cout << "Teste Push Front\n";

    for (int i = 0; i < 10; ++i) {
        list.push_front(i);
    }
    std::cout << "10 = " << list.size() << std::endl;
    for (auto i = 0u; i < 10u; ++i) {
        std::cout << (9 - i) << " = " << list.at(i) << std::endl;
    }

    list.clear();
    
    
    
    std::cout << "Teste Empty\n";

    std::cout << "true == " << list.empty() << std::endl;

    list.push_back(1);
    std::cout << "false == " << list.empty() << std::endl;

    list.clear();
    
    
    
    std::cout << "Teste Clear\n";
    
    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    list.clear(); 
    std::cout << "0 = " << list.size() << std::endl;
    
    
    
    std::cout << "Teste Find\n";

    for (auto i = 0u; i < 10u; ++i) {
        list.push_back(i);
    }

    for (auto i = 0u; i < 10u; ++i) {
        std::cout << i << " = " << list.find(i) << std::endl;
    }
    std::cout << list.size() << " = " << list.find(10) << std::endl;

    list.clear();
    
    
    
    std::cout << "Teste Contains\n";

    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    std::cout << "true == " << list.contains(0) << std::endl;
    std::cout << "true == " << list.contains(5) << std::endl;
    std::cout << "false == " << list.contains(10) << std::endl;

    list.clear();
    

    
    std::cout << "Teste at\n";

    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 0u; i < 10u; ++i) {
        std::cout << i << " = " << list.at(i) << std::endl;
    }
    list.clear();
    
    for (auto i = 10; i > 0; --i) {
        list.push_back(i);
    }
    for (auto i = 0u; i < 10u; ++i) {
        std::cout << (10 - i) << " = " << list.at(i) << std::endl;
    }
    list.clear();
    

    
    std::cout << "Teste at Bondary Checks\n";


    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 0; i < 10; ++i) {
        std::cout << i << " = " << list.at(i) << std::endl;
    }
    try {
        std::cout << list.at(-1) << " ERRO"  << std::endl;
    } catch (std::out_of_range) {
        std::cout << "Tudo Certo\n";
    }

    list.clear();
    

    
    std::cout << "Teste Insert Bondary\n";
    
    try {
        list.insert(1u, 1);
        list.insert(-1, 1);
        std::cout << list.pop_back() << " ERRO"  << std::endl;
    } catch (std::out_of_range) {
        std::cout << "Tudo Certo\n";
    }

    list.clear();
    

    
    std::cout << "Teste Empty Pop Back\n";
    
    try {
        std::cout << list.pop_back() << " ERRO" << std::endl;
    } catch (std::out_of_range) {
        std::cout << "Tudo Certo\n";
    }

    list.clear();
    

    
    std::cout << "Teste Pop Back\n";

    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    for (auto i = 9; i >= 0; --i) {
        std::cout << i << " = " << list.pop_back() << std::endl;
    }
    std::cout << "true = " << list.empty() << std::endl;

    list.clear();
    

    
    std::cout << "Teste Empty Pop Front\n";

    for (auto i = 9; i >= 0; --i) {
        list.push_front(i);
    }
    for (auto i = 0; i < 10; ++i) {
        std::cout << i << " = " << list.pop_front() << std::endl;
    }
    std::cout << "true = " << list.empty() << std::endl;

    list.clear();
    

    
    std::cout << "Teste Pop\n";

    for (auto i = 0; i < 10; ++i) {
        list.insert(i, i);
    }
    std::cout << 5 << " = " << list.pop(5) << std::endl;
    std::cout << 6 << " = " << list.pop(5) << std::endl;
    std::cout << 8 << " = " << list.size() << std::endl;
    try {
        std::cout << list.pop(8) << " ERRO" << std::endl;
    } catch (std::out_of_range) {
        std::cout << "Tudo Certo\n";
    }

    list.clear();
    

    
    std::cout << "Teste Remove\n";


    for (auto i = 0; i < 10; ++i) {
        list.push_back(i);
    }
    list.remove(4);
    std::cout << 9 << " = " << list.size() << std::endl;
    std::cout << "false = " << list.contains(4) << std::endl;
    

    return 0;
} */
