// Copyright [2023] <Maykon Marcos Junior>
#include "ArrayList.h"

namespace structures {

template<typename T>
class BinaryTree {
public:
    ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    structures::ArrayList<T> pre_order() const;

    structures::ArrayList<T> in_order() const;

    structures::ArrayList<T> post_order() const;

    //******************************************************************
    // Prova prática - implementações necessárias:

    // (1) determinação da altura da árvore:
    int height();

    // (2) contagem do número de folhas:
    int leaves();

    // (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
    //     valor da árvore:
    ArrayList<T> limits();

    // (4) criação de uma duplicação, em memória, da árvore:
    BinaryTree<T> clone();

    // (5) remove nós pelo número de seus filhos:
    void filter(int n_child);

    // (6) criação de um nova árvore que tenha todos os valores e a
    //     menor altura possível, ou seja, balanceada com base apenas
    //     no estabelecimento de uma nova ordem de inserção:
    BinaryTree<T> balance();

private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        explicit Node(const T& newData) {
            data = newData;
            left = nullptr;
            right = nullptr;
        }
        ~Node() {
            delete left;
            delete right;
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
        void insert(Node* novo, const T& dataNew) {
            Node **vet[2] = {&right, &left};
            int cond = data > dataNew;
            *(vet[cond]) = novo;
        }
        // para percorrer a lista
        // buscando um elemento
        Node* avanca(const T& dataNew) {
            Node* vet[2] = {right, left};
            int cond = data > dataNew;
            return vet[cond];
        }
        // retorna 0 se tiver subárvores
        // esquerdas e direitas,
        // 1 se for um nodo terminal,
        // 2 se tiver só subárvore direita e
        // 3 se só tiver subárvore esquerda
        int terminal() {
            int cE = left != nullptr;
            int cR = right != nullptr;
            return 2*cE + cR + 1 - 4*cE*cR;
        }
    };

    Node* root = nullptr;
    std::size_t size_ = 0u;
};

}  // namespace structures

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    delete root;
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    Node *Novo = root, *pai = nullptr;
    while (Novo != nullptr) {
        pai = Novo;
        Novo = pai->avanca(data);
    }
    Novo = new Node(data);
    if (root == nullptr) {
        root = Novo;
    } else {
        pai->insert(Novo, data);
    }
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (empty()) {
        return;
    }
    Node *pai = root, *remover = root;
    while (remover->data != data) {
        pai = remover;
        remover = remover->avanca(data);
        if (remover == nullptr) {
            return;
        }
    }
    Node* escolha[2] = {remover->left, remover->right};
    int cond = remover->terminal();
    int iterou = 0;
    Node *substituto = escolha[cond != 3], *pai2 = pai;
    if (!cond) {  // se não for terminal
        while (substituto->left != nullptr) {
            pai2 = substituto;
            substituto = substituto->left;
        }
        // caso pelo menos uma iteração seja feita
        iterou = substituto != remover->right;
        Node *escolha2[3] = {pai2->left,
                             substituto->right,
                             remover->right};
        // se sim, substituto->right, se não, mantém
        pai2->insert(escolha2[iterou], data);
        // se sim, remover->right, se não, mantém
        substituto->insert(escolha2[iterou + 1],
                            remover->right->data);
        // independente de quantas iterações...
        substituto->insert(remover->left,
                            remover->left->data);
    }
    pai->insert(substituto, data);
    size_--;
    remover->left = remover->right = nullptr;
    delete remover;
}

template<typename T>
bool structures::BinaryTree<T>::contains(const T& data) const {
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
bool structures::BinaryTree<T>::empty() const {
    return static_cast<int>(size_) == 0;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}
// visita a raiz, a subarvore esquerda e depois a direita
template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root != nullptr) {
        root->pre_order(&v);
    }
    return v;
}
// visita a subarvore esquerda, a raiz, e a direita
template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root != nullptr) {
        root->in_order(&v);
    }
    return v;
}
// subarvore esquerda, direita e depois a raiz
template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root != nullptr) {
        root->post_order(&v);
    }
    return v;
}
