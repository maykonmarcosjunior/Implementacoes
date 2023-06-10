// Copyright [2023] <Maykon Marcos Junior>
#define L 26
#define Lim 50
namespace structures {

template<typename T>
class Trie {
public:
    Trie();
    ~Trie();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    int size() const;

private:
    struct Node {
        T letra;
        Node* filhos[L];
        Node* pai;
        int size;
        int posicao;
        int prefixo;

        explicit Node(const T& newData, Node* NewPai) {
            letra = newData;
            pai = NewPai;
            size = 0;
            posicao = 0;
            prefixo = 0;
            if (pai != nullptr) {
                posicao = pai->posicao + 1; 
                prefixo = pai->prefixo; 
            }
        }
        
        bool contains(const T& dado) {
            for (int i = 0; i < size; ++i) {
                if (filhos[i]->letra == dado) {
                    return true;
                }
            }
            return false;
        }

        void remove(Node* remover, Node* substituto) {
            if (remover == nullptr || contains(remover->letra)) {
                return;
            }
            for (int i = 0; i < size; i++) {
                if (filhos[i] == remover) {
                    if (substituto != nullptr) {
                        filhos[i] = substituto;
                    } else {
                        for (int j = i; j < size-1; j++) {
                            filhos[j] = filhos[j+1];
                        }
                    }
                    delete remover;
                }
            }
        }

        bool insert(Node* novo) {
            bool saida = true;
            if (novo != nullptr && !contains(novo->letra)) {
                filhos[size] = novo;
                size++;
            } else {
                saida = false;
            }
            return saida;
        }

        Node* find(const T& dado) {
            for (int i = 0; i < size; ++i) {
                if (filhos[i]->letra == dado) {
                    return filhos[i];
                }
            }
            return nullptr;
        }
        
        bool search(T palavra[Lim], T busca[], int posP, int posB) {
            Node* teste = find(busca[posB]);
            if (teste != nullptr) {
                palavra[posP] = teste->letra;
                posP++;
                posB++;
                teste->search(palavra, busca, posP, posB);
                return true;
            }
            return false;
        }
    };

    void destructor(Node* Nodo) {
        if (Nodo != nullptr) {
            for (int i = 0; i < Nodo->size; i++) {
                destructor(Nodo->filhos[i]);
            }
            delete Nodo;
        }
    }

    Node* root;
    int size_;
};

}  // namespace structures

template<typename T>
structures::Trie<T>::Trie() {
    char temp = ' ';
    root = new Node(temp, nullptr);
    size_ = 0;
}

template<typename T>
structures::Trie<T>::~Trie() {
    destructor(root);
}

template<typename T>
void structures::Trie<T>::insert(const T& data) {
    Node *Novo = root, *pai = nullptr;
    while (Novo != nullptr) {
        if (Novo->data == data) {
            return;
        }
        pai = Novo;
        Novo = pai->find(data);
    }
    Novo = new Node(data, pai);
    pai->insert(Novo, data);
    size_++;
}

template<typename T>
void structures::Trie<T>::remove(const T& data) {
    if (empty()) {
        return;
    }
    Node *pai = root, *remover = root;
    while (remover->data != data) {
        pai = remover;
        remover = pai->find(data);
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
    size_--;
    delete remover;
}

template<typename T>
bool structures::Trie<T>::contains(const T& data) const {
    auto aux = root;
    while (aux != nullptr) {
        if (aux->data == data) {
            return true;
        }
        aux = aux->find(data);
    }
    return false;
}

template<typename T>
bool structures::Trie<T>::empty() const {
    return size_ == 0;
}

template<typename T>
int structures::Trie<T>::size() const {
    return size_;
}
