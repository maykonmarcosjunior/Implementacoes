// Copyright [2023] <Maykon Marcos Junior>
#include <stdio.h>
#include <cstdint>  // size_t
#include "array_list.h"

namespace structures {

template<typename T>
class AVLTree {
public:
    ~AVLTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    int height() const;

    structures::ArrayList<T> pre_order() const;

    structures::ArrayList<T> in_order() const;

    structures::ArrayList<T> post_order() const;

private:
    struct Node {
        T data;
        int height;
        Node* left;
        Node* right;

        explicit Node(const T& data_) {
            data = data_;
            height = 0;
            left = nullptr;
            right = nullptr;
        }

        int terminal() {
            int r = 0;
            if (left == nullptr && right == nullptr) {
                r = 1;
            } else if (left == nullptr) {
                r = 2;
            } else if (right == nullptr) {
                r = 3;
            }
            return r;
        }

        void pre_order(ArrayList<T>* v) const {
            v->push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>* v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v->push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>* v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v->push_back(data);
        }

        void atribui(Node* novo, const T& dado) {
            if (data > dado) {
                left = novo;
            } else if (data < dado) {
                right = novo;
            }
        }

        Node* avanca(const T& dataNew) {
            Node* saida = this;
            if (data > dataNew) {
                saida = left;
            } else if (data < dataNew) {
                saida = right;
            }
            return saida;
        }

        Node* simpleLeft() {
            this->height--;
            right->height--;
            left->height++;
            auto B = left;
            left = B->right;
            B->right = this;
            return B;
        }

        Node* simpleRight() {
            this->height--;
            left->height--;
            right->height++;
            auto B = right;
            right = B->left;
            B->left = this;
            return B;
        }

        Node* doubleLeft() {
            left = left->simpleRight();
            return this->simpleLeft();
        }

        Node* doubleRight() {
            right = right->simpleLeft();
            return this->simpleRight();
        }

        int fb() {
            int aux = terminal();
            int altura = 0;
            if (!aux) {
                altura = left->height - right->height;
            } else if (aux == 2) {
                altura = right->height + 1;
            } else if (aux == 3) {
                altura = left->height + 1;
            }
            return altura;
        }
        int dumb_height() {
            int esq = -1, dir = -1;
            if (left != nullptr) {
                esq = left->dumb_height();
            }
            if (right != nullptr) {
                dir = right->dumb_height();
            }
            int value = esq > dir? esq : dir;
            return value + 1;
        }
    };

    void destructor(Node* Nodo) {
        if (Nodo != nullptr) {
            destructor(Nodo->left);
            destructor(Nodo->right);
            delete Nodo;
        }
    }
    void rotacao(Node* filho) {
        if (filho != nullptr) {
            Node* aux;
            if (filho->fb() > 1) {
                if (filho->left->fb() > 0) {
                    aux = filho->simpleLeft();
                } else if (filho->left->fb() < 0) {
                    aux = filho->doubleLeft();
                }
            } else if (filho->fb() < -1) {
                if (filho->right->fb() < 0) {
                    aux = filho->simpleRight();
                } else if (filho->right->fb() > 0) {
                    aux = filho->doubleRight();
                }
            }
            if (filho != root && aux != nullptr) {
                Node* pai = root;
                while (pai->avanca(filho->data) != filho) {
                    pai = pai->avanca(filho->data);
                }
                pai->atribui(aux, aux->data);
            }
        }
    }
    void updateHeight(Node* pai, int value) {
        if (pai != nullptr) {
            int altE, altR;
            if (pai->left != nullptr) {
                altE = pai->left->height;
            } else {
                altE = -1;
            }
            if (pai->right != nullptr) {
                altR = pai->right->height;
            } else {
                altR = -1;
            }
            if (pai->height != altE + 1 && pai->height != altR + 1) {
                root->height = root->dumb_height();
                Node *caminho = root, *rota = root;
                while (caminho != pai) {
                    rota = caminho;
                    caminho = caminho->avanca(pai->data);
                    caminho->height = caminho->dumb_height();
                    if (abs(rota->fb()) > 1) {
                        rotacao(rota);
                    }
                }
            }
        }
    }

    Node* root;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    destructor(root);
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    Node *Novo = root, *pai;
    while (Novo != nullptr) {
        if (Novo->data == data) {
            return;
        }
        pai = Novo;
        Novo = Novo->avanca(data);
    }
    Novo = new Node(data);
    if (root == nullptr) {
        root = Novo;
    } else {
        pai->atribui(Novo, data);
    }
    size_++;
    updateHeight(pai, 1);
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
    if (empty()) {
        return;
    }
    Node *pai = root, *remover = root;
    while (remover->data != data) {
        pai = remover;
        remover = pai->avanca(data);
        if (remover == nullptr) {
            return;
        }
    }
    Node *substituto = remover, *pai2 = pai;
    // verifica se é terminal
    int cond = remover->terminal();
    if (cond == 1) {  // se for terminal
        substituto = nullptr;
    } else if (cond == 2) {  // se o right não for nulo
        substituto = remover->right;
    } else if (cond == 3) {  // se left não for nulo
        substituto = remover->left;
    } else {
        substituto = remover->right;
        while (substituto->left != nullptr) {
            pai2 = substituto;
            substituto = substituto->left;
        }
        if (substituto != remover->right) {
            pai2->left = substituto->right;
            substituto->right = remover->right;
        }
        substituto->left = remover->left;
    }
    pai->atribui(substituto, data);
    updateHeight(pai2, -1);
    if (substituto != nullptr) {
        substituto->height = remover->height;
    }
    size_--;
    delete remover;
}

template<typename T>
int structures::AVLTree<T>::height() const {
    if (root == nullptr) {
        return -1;
    }
    return root->height;
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
    auto aux = root;
    while (aux != nullptr) {
        if (aux->data == data) {
            return true;
        }
        aux = aux->avanca(data);
    }
    return false;
}

template<typename T>
bool structures::AVLTree<T>::empty() const {
    return static_cast<int>(size_) == 0;
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}
// visita a raiz, a subarvore esquerda e depois a direita
template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root != nullptr) {
        root->pre_order(&v);
    }
    return v;
}
// visita a subarvore esquerda, a raiz, e a direita
template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root != nullptr) {
        root->in_order(&v);
    }
    return v;
}
// subarvore esquerda, direita e depois a raiz
template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root != nullptr) {
        root->post_order(&v);
    }
    return v;
}

namespace {


/**
 * Classe com propósito de oferecer maior robustez aos testes.
 */
class Dummy {
public:
    Dummy() = default;
    explicit Dummy(double value):
        value_{value}
    {}

    /**
     * Valor encapsulado
     */
    double value() const {
        return value_;
    }

    bool operator<(const Dummy& other) const {
        return value() < other.value();
    }

    bool operator<=(const Dummy& other) const {
        return value() <= other.value();
    }

    bool operator>(const Dummy& other) const {
        return value() > other.value();
    }

    bool operator>=(const Dummy& other) const {
        return value() >= other.value();
    }

    bool operator==(const Dummy& other) const {
        return value() == other.value();
    }

    bool operator!=(const Dummy& other) const {
        return value() != other.value();
    }

private:
    /**
     * Valor encapsulado
     */
    double value_{0.};
};

/**
 * Sobrescrita do operador std::ostream<<(Dummy) para possibilitar printar um
 * Dummy através do std::cout.
 *//*
std::ostream& operator<<(std::ostream& os, const Dummy& dummy) {
    os << dummy.value();
    return os;
} */



#include <iostream>
#include <string>
#include <vector>

    /**
     * Testa uma inserção simples em uma lista.
     */
    template <typename T, typename U>
    void simple_insertion(T& list, U& values) {
        if(list.empty()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        list.insert(values[0]);
        if(!list.empty()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        if(1 == list.size()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
    }

    /**
     * Testa a inserção de múltiplos valores em uma lista.
     */
    template <typename T, typename U>
    void multiple_insertion(T& list, const U& values) {
        if(list.empty()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        for (auto& value : values) {
            list.insert(value);
        }
        if(!list.empty()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        if(values.size() == list.size()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
    }

    /**
     * Testa se todos os valores inseridos estão na lista.
     */
    template <typename T, typename U>
    void contains_all(const T& list, const U& values) {
        for (auto& value : values) {
            if(list.contains(value)) {
                std::cout << "ok\n";
            } else {
                std::cout << "erro\n";
            }
        }
    }

int main() {
    /**
     * Lista para teste com inteiros.
     */
    structures::AVLTree<int> int_list{};
    /**
     * Lista para teste com strings.
     */
    structures::AVLTree<std::string> string_list{};
        /**
    * Valores a serem inseridos na árvore de inteiros.
    */
    const auto int_values = std::vector<int>{10, 5, 8, 20, 25,
     15, -5, -10, 30, -15};

    /**
    * Valores a serem inseridos na árvore de strings.
    */
    const auto string_values = std::vector<std::string>{"AAA", "BBB",
     "123", "Hello, World!", "Goodbye, World!"};

/**
 * Testa se a árvore informa corretamente quando está vazia.
 */
    std::cout << "Teste Empty\n";
    if(int_list.empty()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }
    if(string_list.empty()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }

/**
 * Testa se a árvore de inteiros permite corretamente a inserção de um elemento.
 */
    std::cout << "Teste SingleIntegerInsertion\n";
    simple_insertion(int_list, int_values);

/**
 * Testa se a árvore de strings permite corretamente a inserção de um elemento.
 */
std::cout << "Teste SingleStringInsertion\n";
    simple_insertion(string_list, string_values);

/**
 * Testa se a árvore de inteiros permite corretamente a inserção de vários
 * elementos.
 */
std::cout << "Teste MultipleIntegerInsertion\n";
    multiple_insertion(int_list, int_values);
    if(3 == int_list.height()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }

/**
 * Testa se a árvore de strings permite corretamente a inserção de vários
 * elementos.
 */
std::cout << "Teste MultipleStringInsertion\n";
    multiple_insertion(string_list, string_values);
    if(2 == string_list.height()) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }

/**
 * Testa se a árvore checa corretamente a presença de um elemento.
 */
std::cout << "Teste Contains\n";
    multiple_insertion(int_list, int_values);
    multiple_insertion(string_list, string_values);

    contains_all(int_list, int_values);
    contains_all(string_list, string_values);

/**
 * Testa se a árvore checa corretamente a ausência de um elemento.
 */
std::cout << "Teste NotContains\n";
    multiple_insertion(int_list, int_values);
    multiple_insertion(string_list, string_values);

    if(!int_list.contains(3)) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }
    if(!string_list.contains("Hallo, World!")) {
        std::cout << "ok\n";
    } else {
        std::cout << "erro\n";
    }

/**
 * Testa se a remoção de um elemento na árvore funciona como previsto.
 */
std::cout << "Teste Remove\n";
        multiple_insertion(int_list, int_values);
        unsigned int size = int_list.size();
        if(int_list.contains(-15)) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        int_list.remove(-15);
        if(!int_list.contains(-15)) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        if(size-1 == int_list.size()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        if(3 == int_list.height()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }

        multiple_insertion(string_list, string_values);
        size = string_list.size();
        if(string_list.contains("Hello, World!")) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        string_list.remove("Hello, World!");
        if(!string_list.contains("Hello, World!")) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        if(size-1 == string_list.size()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }
        if(2 == string_list.height()) {
            std::cout << "ok\n";
        } else {
            std::cout << "erro\n";
        }

/**
 * Testa se a árvore gera corretamente uma lista por pré-ordem.
 */
std::cout << "Teste PreOrder\n";
        multiple_insertion(int_list, int_values);

        auto preordered_int = int_list.pre_order();
        auto pre_expected_int = {10, 5, -10, -15, -5, 8, 20, 15, 25, 30};
        unsigned int i = 0u;
        for (auto& value : pre_expected_int) {
            if(value == preordered_int[i]) {
                std::cout << "ok\n";
            } else {
                std::cout << "erro\n";
            }
            ++i;
        }
        multiple_insertion(string_list, string_values);

        auto preordered_str = string_list.pre_order();
        auto pre_expected_str = {
            "AAA", "123", "Goodbye, World!", "BBB", "Hello, World!"
        };
        i = 0u;
        for (auto& value : pre_expected_str) {
            if(value == preordered_str[i]) {
                std::cout << "ok\n";
            } else {
                std::cout << "erro\n";
            }
            ++i;
        }

/**
 * Testa se a árvore gera corretamente uma lista por em-ordem.
 */
std::cout << "Teste InOrder\n";
       multiple_insertion(int_list, int_values);

        auto inordered_int = int_list.in_order();
        auto in_expected_int = {-15, -10, -5, 5, 8, 10, 15, 20, 25, 30};
        i = 0u;
        for (auto& value : in_expected_int) {
            if(value == inordered_int[i]) {
                std::cout << "ok\n";
            } else {
                std::cout << "erro\n";
            }
            ++i;
        }

        multiple_insertion(string_list, string_values);

        auto inordered_str = string_list.in_order();
        auto in_expected_str = {
            "123", "AAA", "BBB", "Goodbye, World!", "Hello, World!"
        };
        i = 0u;
        for (auto& value : in_expected_str) {
            if(value == inordered_str[i]) {
                std::cout << "ok\n";
            } else {
                std::cout << "erro\n";
            }
            ++i;
        }

/**
 * Testa se a árvore gera corretamente uma lista por pós-ordem.
 */
std::cout << "Teste PostOrder\n";
        multiple_insertion(int_list, int_values);

        auto postordered_int = int_list.post_order();
        auto pos_expected_int = {-15, -5, -10, 8, 5, 15, 30, 25, 20, 10};
        i = 0u;
        for (auto& value : pos_expected_int) {
            if(value == postordered_int[i]) {
                std::cout << "ok\n";
            } else {
                std::cout << "erro\n";
            }
            ++i;
        }

        multiple_insertion(string_list, string_values);

        auto postordered_str = string_list.post_order();
        auto pos_expected_str = {
            "123", "BBB", "Hello, World!", "Goodbye, World!", "AAA"};
        i = 0u;
        for (auto& value : pos_expected_str) {
            if(value == postordered_str[i]) {
                std::cout << "ok\n";
            } else {
                std::cout << "erro\n";
            }
            ++i;
        }

    return 0;
}
