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
        int terminal() {
            int cE = left != nullptr;
            int cD = right != nullptr;
            return 2*cE + cD + 1 - 4*cE*cD;
        }
        bool corrige_altura() {
            int esquerda = (left != nullptr)? left->height : -1;
            int direita = (right != nullptr)? right->height : -1;
            int certo = (direita > esquerda) ? direita : esquerda;
            bool saida = height != certo + 1;
            height = certo + 1;
            return saida;
        }
        void atribui(Node* novo, const T& dataNew) {
            Node **vet[3] = {&right, &left};
            int cond = data > dataNew;
            *(vet[cond]) = novo;
            if (novo != nullptr) {
                novo->pai = this;
            }
            corrige_altura();
        }
        Node* avanca(const T& dataNew) {
            Node* vet[3] = {this, left, right};
            int cE = data > dataNew;
            int cR = data < dataNew;
            return vet[cE + 2*cR];
        }
        void simpleLeft() {
            auto B = left;
            if (B == nullptr) {
                return;
            }
            atribui(B->right, B->data);
            B->atribui(this, data);
        }
        void simpleRight() {
            auto B = right;
            if (B == nullptr) {
                return;
            }
            atribui(B->left, B->data);
            B->atribui(this, data);
        }
        void doubleLeft() {
            // nesse caso, left tem
            // right não nulo, mas não
            // se garante o left dele
            left->simpleRight();
            simpleLeft();
        }
        void doubleRight() {
            // nesse caso, right tem
            // left não nulo, mas não
            // se garante o right dele
            right->simpleLeft();
            simpleRight();
        }
        int fb() {
            int altE = (left == nullptr)? -1 : left->height;
            int altR = (right == nullptr)? -1 : right->height;
            return altE - altR;
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
            if (abs(fb()) > 1) {
                rotacao();
            }
            if (pai != nullptr && pai->corrige_altura()) {
                pai->updateHeight();
            }
        }
    };

    void destructor(Node* Nodo) {
        if (Nodo != nullptr) {
            destructor(Nodo->left);
            destructor(Nodo->right);
            delete Nodo;
        }
    }

    Node* root = nullptr;
    std::size_t size_;
};

}  // namespace structures

template<typename T>
structures::AVLTree<T>::~AVLTree() {
    destructor(root);
}

template<typename T>
void structures::AVLTree<T>::insert(const T& data) {
    Node *Novo = root, *pai = nullptr;
    while (Novo != nullptr) {
        if (Novo->data == data) {
            return;
        }
        pai = Novo;
        Novo = pai->avanca(data);
    }
    Novo = new Node(data);
    if (root == nullptr) {
        root = Novo;
    } else {
        pai->atribui(Novo, data);
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
    while (remover->data != data) {
        pai = remover;
        remover = pai->avanca(data);
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
        pai2->atribui(escolha2[iterou], data);
        // se sim, remover->right, se não, mantém
        substituto->atribui(escolha2[iterou + 1],
                            remover->right->data);
        // independente de quantas iterações...
        substituto->atribui(remover->left,
                            remover->left->data);
    }
    pai->atribui(substituto, data);
    size_--;
    pai2->updateHeight();
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
