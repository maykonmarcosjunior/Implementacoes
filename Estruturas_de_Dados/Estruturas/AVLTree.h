// Copyright [2023] <Maykon Marcos Junior>
#include "ArrayList.h"

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
        Node* pai;
        Node* left;
        Node* right;

        explicit Node(const T& data_) {
            data = data_;
            height = 0;
            left = nullptr;
            right = nullptr;
            pai = nullptr;
        }
        ~Node() {
            delete left;
            delete right;
        }
        int HLeft() {
            int altE = (left)? left->height : -1;
            return altE;
        }
        int HRight() {
            int altR = (right)? right->height : -1;
            return altR;
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
        // retorna 0 se tiver subárvores
        // esquerdas e direitas,
        // 1 se for um nodo terminal,
        // 2 se tiver só subárvore direita e
        // 3 se só tiver subárvore esquerda
        int terminal() {
            int cE = left != nullptr;
            int cD = right != nullptr;
            return 2*cE + cD + 1 - 4*cE*cD;
        }
        // faz com que a altura seja igual
        // à maior das subárvore + 1
        void corrige_altura() {
            int LL = HLeft(), RR = HRight();
            height = (RR > LL) ? RR + 1 : LL + 1;
        }
        // para o percorrer da lista
        // buscando um elemento
        // iterativamente
        Node* avanca(const T& dataNew) {
            Node* vet[2] = {right, left};
            return vet[data > dataNew];
        }
        // centraliza a inserção
        void insert(Node* novo, const T& dataNew) {
            Node **vet[2] = {&right, &left};
            int cond = data > dataNew;
            *(vet[cond]) = novo;
            if (novo) {
                novo->pai = this;
            }
            corrige_altura();
        }
        void simpleLeft() {
            Node *paiA = pai;
            Node *B = this->left;
            // A->left = B->right
            insert(B->right, B->data);
            // B->right = A
            B->insert(this, data);
            // B->pai = paiA
            B->pai = nullptr;
            if (paiA) {
                paiA->insert(B, B->data);
            }
        }
        void simpleRight() {
            Node *paiA = pai;
            Node *B = this->right;
            // A->right = B->left
            insert(B->left, B->data);
            // B->left = A
            B->insert(this, data);
            // B->pai = paiA
            B->pai = nullptr;
            if (paiA) {
                paiA->insert(B, B->data);
            }
        }
        void doubleLeft() {
            left->simpleRight();
            simpleLeft();
        }
        void doubleRight() {
            right->simpleLeft();
            simpleRight();
        }
        int fb() {
            return HLeft() - HRight();
        }
        void rotacao() {
            if (fb() > 1) {
                // não tem como left
                // ser nullptr se fb > 0
                if (left->fb() > 0) {
                    // left também tem
                    // um left não nulo
                    simpleLeft();
                } else if (left->fb() < 0) {
                    // nesse caso, left tem
                    // right não nulo, mas não
                    // se garante o left dele
                    doubleLeft();
                }
            } else if (fb() < -1) {
                // não tem como right
                // ser nullptr se fb < 0
                if (right->fb() < 0) {
                    // right também precisa
                    // ter right não nulo
                    simpleRight();
                } else if (right->fb() > 0) {
                    // nesse caso, right tem
                    // left não nulo, mas não
                    // se garante o right dele
                    doubleRight();
                }
            }
        }
        void updateHeight() {
            corrige_altura();
            if (abs(fb()) > 1) {
                rotacao();
            }
            if (pai) {
                pai->updateHeight();
            }
        }
    };

    Node* root = nullptr;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    delete root;
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
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
    Novo->updateHeight();
}

template<typename T>
void structures::AVLTree<T>::remove(const T& data) {
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
    pai2->updateHeight();
}

template<typename T>
int structures::AVLTree<T>::height() const {
    return root? root->height : -1;
}

template<typename T>
bool structures::AVLTree<T>::contains(const T& data) const {
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
bool structures::AVLTree<T>::empty() const {
    return !size_;
}

template<typename T>
std::size_t structures::AVLTree<T>::size() const {
    return size_;
}
// visita a raiz, a subarvore esquerda e depois a direita
template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::pre_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root) {
        root->pre_order(&v);
    }
    return v;
}
// visita a subarvore esquerda, a raiz, e a direita
template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::in_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root) {
        root->in_order(&v);
    }
    return v;
}
// subarvore esquerda, direita e depois a raiz
template<typename T>
structures::ArrayList<T> structures::AVLTree<T>::post_order() const {
    ArrayList<T> v = ArrayList<T>(size_);
    if (root) {
        root->post_order(&v);
    }
    return v;
}
