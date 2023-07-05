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
            if (left) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }
        void in_order(ArrayList<T>* v) const {
            if (left) {
                left->in_order(v);
            }
            v->push_back(data);
            if (right) {
                right->in_order(v);
            }
        }
        void post_order(ArrayList<T>* v) const {
            if (left) {
                left->post_order(v);
            }
            if (right) {
                right->post_order(v);
            }
            v->push_back(data);
        }
        // centraliza a inserção
        void insert(Node* novo, const T& dataNew) {
            Node **vet[2] = {&right, &left};
            *(vet[data > dataNew]) = novo;
        }
        // para percorrer a lista
        // buscando um elemento
        // iterativamente
        Node* avanca(const T& dataNew) {
            Node* vet[2] = {right, left};
            return vet[data > dataNew];
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
        // encontrando a altura
        int height() {
            int HL = (left)? left->leaves() : -1;
            int HR = (right)? right->leaves() : -1;
            int saida = (HR > HL) ? HR : HL;
            return saida + 1;
        }
        // contando só as folhas
        int leaves() {
            int saida = (left)? left->leaves() : 1;
            int saida += (right)? right->leaves() : 0;
            return saida;
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
int structures::BinaryTree<T>::height() {
    return root->height();
}

// (2) contagem do número de folhas:
template<typename T>
int structures::BinaryTree<T>::leaves() {
    return root->leaves();
}

// (3) criação de uma lista com o menor (mínimo) e o maior (máximo)
//     valor da árvore:
template<typename T>
ArrayList<T> structures::BinaryTree<T>::limits() {
    ArrayList<T> saida{2};
    bool LL = true, RR = true;
    if (!empty()) {
        Node *auxL = root, *auxR = root;
        while (LL || RR) {
            if (auxL->left) {
                auxL = auxL->left;
            }
            else if (LL) {
                saida.push_front(auxL->data);
                LL = false;
            }
            if (auxR->right) {
                auxR = auxR->right;
            }
            else if (RR) {
                saida.push_back(auxR->data);
                RR = false;
            }
        }
    }
    return saida;
}

// (4) criação de uma duplicação, em memória, da árvore:
template<typename T>
BinaryTree<T> structures::BinaryTree<T>::clone() {

}

// (5) remove nós pelo número de seus filhos:
template<typename T>
void structures::BinaryTree<T>::filter(int n_child) {

}

// (6) criação de um nova árvore que tenha todos os valores e a
//     menor altura possível, ou seja, balanceada com base apenas
//     no estabelecimento de uma nova ordem de inserção:
template<typename T>
BinaryTree<T> structures::BinaryTree<T>::balance() {
    
}

template<typename T>
void structures::BinaryTree<T>::insert(const T& data) {
    Node *Novo = root, *pai = nullptr;
    while (Novo) {
        pai = Novo;
        Novo = pai->avanca(data);
    }
    Novo = new Node(data);
    if (root) {
        pai->insert(Novo, data);
    } else {
        root = Novo;
    }
    size_++;
}

template<typename T>
void structures::BinaryTree<T>::remove(const T& data) {
    if (empty()) {
        return;
    }
    Node *pai = root, *remover = root;
    while (remover && remover->data != data) {
        pai = remover;
        remover = remover->avanca(data);
    }
    if (!remover) {
        return;
    }
    Node* escolha[2] = {remover->left, remover->right};
    int cond = remover->terminal();
    // cond == 3 significa que o nodo a remover só tem
    // subárvore esquerda, o único caso em que o substituto
    // não será a subárvore direita (porque, se a subárvore
    // direita também for nula, não precisa de substituto)
    Node *substituto = escolha[cond != 3], *pai2 = pai;
    if (!cond) {  // se tiver ambas as subárvores
        while (substituto->left) {
            pai2 = substituto;
            substituto = substituto->left;
        }
        // caso pelo menos uma iteração seja feita
        int iterou = substituto != remover->right;
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
    while (aux) {
        if (aux->data == data) {
            return true;
        }
        aux = aux->avanca(data);
    }
    return false;
}

template<typename T>
bool structures::BinaryTree<T>::empty() const {
    return !size_;
}

template<typename T>
std::size_t structures::BinaryTree<T>::size() const {
    return size_;
}
// visita a raiz, a subarvore esquerda e depois a direita
template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::pre_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root) {
        root->pre_order(&v);
    }
    return v;
}
// visita a subarvore esquerda, a raiz, e a direita
template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root) {
        root->in_order(&v);
    }
    return v;
}
// subarvore esquerda, direita e depois a raiz
template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root) {
        root->post_order(&v);
    }
    return v;
}
