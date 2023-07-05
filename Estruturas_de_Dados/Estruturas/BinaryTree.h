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

    int height();

    int leaves();

    ArrayList<T> limits();

    BinaryTree<T> clone();

    void filter(int n_child);

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
        // visita a raiz, a subarvore esquerda e depois a direita
        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left) {
                left->pre_order(v);
            }
            if (right) {
                right->pre_order(v);
            }
        }
        // visita a subarvore esquerda, a raiz, e a direita
        void in_order(ArrayList<T>& v) const {
            if (left) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right) {
                right->in_order(v);
            }
        }
        // subarvore esquerda, direita e depois a raiz
        void post_order(ArrayList<T>& v) const {
            if (left) {
                left->post_order(v);
            }
            if (right) {
                right->post_order(v);
            }
            v.push_back(data);
        }
        // Copia a árvore
        void clone(BinaryTree<T>& C) const {
            C.insert(data);
            if (left) {
                left->clone(C);
            }
            if (right) {
                right->clone(C);
            }
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
            saida += (right)? right->leaves() : 0;
            return saida;
        }
    };
    // elimina nodos com n_child filhos
    void subfilter(int n_child, Node* raiz) {
        if (!raiz) {
            return;
        }
        int filhos = 2 - !raiz->left - !raiz->right;
        if (n_child == filhos) {
            remove(raiz);
        }
        subfilter(n_child, raiz->left);
        subfilter(n_child, raiz->right);
    }
    // insere os elementos ordenamente
    void balance_tree(BinaryTree<T>& B, int start,
                      int end, ArrayList<T>& lista) {
        if (start <= end) {
            // é necessário particionar a lista
            int meio = (start + end) / 2;
            B.insert(lista[meio]);
            balance_tree(B, start, meio - 1, lista);
            balance_tree(B, meio + 1, end, lista);
        }
    }

    Node* root = nullptr;
    std::size_t size_ = 0u;
};

}  // namespace structures

template<typename T>
structures::BinaryTree<T>::~BinaryTree() {
    delete root;
}

// altura da árvore
template<typename T>
int structures::BinaryTree<T>::height() {
    return root? root->height() : -1;
}

// contagem do número de folhas:
template<typename T>
int structures::BinaryTree<T>::leaves() {
    return root->leaves();
}

// retorna uma lista com o menor
// (mínimo) e o maior (máximo)
// valor da árvore:
template<typename T>
ArrayList<T> structures::BinaryTree<T>::limits() {
    ArrayList<T> saida{2};
    if (empty()) {
        return saida;
    }
    bool LL = true, RR = true;
    Node *auxL = root, *auxR = root;
    Node* vetL[2] = {root, root->left};
    Node* vetR[2] = {root, root->right};
    while (LL || RR) {
        // se auxL->left não for nulo,
        // auxL vira auxL->left
        LL = auxL->left;
        auxL = vetL[LL];
        vetL[0] = auxL;
        vetL[1] = auxL->left;
        // ser auxR->right não for nulo,
        // auxR vira auxR->right
        RR = auxR->right;
        auxR = vetR[RR];
        vetR[0] = auxR;
        vetR[1] = auxR->right;
    }
    saida.push_back(vetR[0]->data);
    saida.pop_back(vetR[0]->data);
    return saida;
}

// criação de uma duplicação, em memória, da árvore:
template<typename T>
BinaryTree<T> structures::BinaryTree<T>::clone() {
    BinaryTree<T> C;
    root->clone(C);
    return C;
}

// remove nós pelo número de seus filhos:
template<typename T>
void structures::BinaryTree<T>::filter(int n_child) {
    subfilter(n_child, root);
}

// criação de um nova árvore que tenha todos os valores e a
// menor altura possível, ou seja, balanceada com base apenas
// no estabelecimento de uma nova ordem de inserção:
template<typename T>
BinaryTree<T> structures::BinaryTree<T>::balance() {
    ArrayList<T> lista = in_order();
    BinaryTree<T> B;
    std::size_t inicio = 0, fim = size_ - 1;
    balance_tree(B, inicio, fim, lista);
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
        root->pre_order(v);
    }
    return v;
}
// visita a subarvore esquerda, a raiz, e a direita
template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::in_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root) {
        root->in_order(v);
    }
    return v;
}
// subarvore esquerda, direita e depois a raiz
template<typename T>
structures::ArrayList<T> structures::BinaryTree<T>::post_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root) {
        root->post_order(v);
    }
    return v;
}
