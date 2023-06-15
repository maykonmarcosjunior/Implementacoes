// Copyright [2023] <Maykon Marcos Junior>
#include <string.h>
#define L 26
#define LIM 50

namespace structures {

class Trie {
public:
    Trie();
    
    ~Trie();

    void insert(const char& data);

    void insert_str(const char palavra[]);

    void remove(const char& data);

    bool contains(const char data[]) const;

    bool empty() const;

    int size() const;

private:
    struct Node {
        char letra;
        Node* filhos[L];
        Node* pai;
        int size;
        int posicao;
        int prefixo;

        explicit Node(const char& newData, Node* NewPai) {
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

        Node* find(const char& dado) {
            for (int i = 0; i < size; ++i) {
                if (filhos[i]->letra == dado) {
                    return filhos[i];
                }
            }
            return nullptr;
        }

        void insert(Node* novo) {
            if (novo == nullptr) {
                return;
            }
            auto aux = find(novo->letra);
            if (aux == nullptr) {
                filhos[size] = novo;
                size++;
            } else {
                aux->insert(novo);
            }
        }
        
        bool contains(const char palavra[], char busca[], int pos) {
            Node* teste = find(palavra[pos]);
            if (teste != nullptr) {
                busca[pos] = teste->letra;
                pos++;
                return teste->contains(palavra, busca, pos);
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

structures::Trie::Trie() {
    char temp = ' ';
    root = new Node(temp, nullptr);
    size_ = 0;
}

structures::Trie::~Trie() {
    destructor(root);
}

void structures::Trie::insert(const char& data) {
    Node *Novo = root, *pai = nullptr;
    while (Novo != nullptr) {
        pai = Novo;
        Novo = pai->find(data);
    }
    Novo = new Node(data, pai);
    pai->insert(Novo);
    size_++;
}

void structures::Trie::insert_str(const char palavra[]) {
    Node *pai = root, *aux = root->find(palavra[0]);
    int i = 0, max = strlen(palavra);
    while (aux != nullptr && i < max) {
        pai = aux;
        aux = pai->find(palavra[i]);
        i++;
    }
    if (i == max) {
        return;
    }
    for (;i < max; ++i) {
        Node* Novo = new Node(palavra[i], pai);
        pai->insert(Novo);
        pai = Novo;
        size_++;
    }
}

bool structures::Trie::contains(const char data[]) const {
    char busca[LIM];
    return root->contains(data, busca, 0);
}

bool structures::Trie::empty() const {
    return size_ == 0;
}

int structures::Trie::size() const {
    return size_;
}
