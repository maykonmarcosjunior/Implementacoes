// Copyright [2023] <Maykon Marcos Junior>
#include <string.h>
#define L 26

namespace structures {

class Trie {
public:
    Trie();
    
    ~Trie();

    void insert(std::string palavra);

    bool contains(std::string palavra) const;

    bool prefixos(std::string palavra) const;

    bool empty() const;

    int size() const;

private:
    struct Node {
        char letra;
        Node* filhos[L];
        Node* pai;
        int size;
        int posicao;
        int prefixos;
        bool is_word;

        explicit Node(const char& newData, Node* NewPai) {
            letra = newData;
            pai = NewPai;
            size = 0;
            is_word = false;
            posicao = (pai == nullptr) ? 0 : pai->posicao + 1;
            prefixos = (pai == nullptr)? 0 : pai->prefixos;
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
        void pref_update() {
            prefixos++;
            if (pai != nullptr) {
                pai->pref_update();
            }
        }
        bool contains(std::string palavra) {
            if (posicao == static_cast<int>(palavra.length())) {
                return true;
            }
            Node* teste = find(palavra[posicao]);
            if (teste != nullptr) {
                return teste->contains(palavra);
            }
            return false;
        }
        int prefixos(std::string palavra) {
            if (posicao == static_cast<int>(palavra.length())) {
                return prefixos;
            }
            Node* teste = find(palavra[posicao]);
            if (teste != nullptr) {
                return teste->contains(palavra);
            }
            return 0;
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
    // root nunca vai ser nullptr
    root = new Node(temp, nullptr);
    size_ = 0;
}

structures::Trie::~Trie() {
    destructor(root);
}
void structures::Trie::insert(std::string palavra) {
    Node *pai = root, *aux = root->find(palavra[0]);
    int i = 0, max = static_cast<int>(palavra.length());
    // verificando quais letras já estão lá
    while (aux != nullptr && i < max) {
        pai = aux;
        aux = pai->find(palavra[i]);
        i++;
    }
    // significa que palavra é 
    // um prefixo já inserido
    if (i == max) {
        return;
    }
    // caso contrário
    // deve-se inserir
    // as letras restantes
    Node *Novo;
    for (; i < max; ++i) {
        Novo = new Node(palavra[i],
                        pai);
        pai->insert(Novo);
        pai = Novo;
        size_++;
    }
    Novo->is_word = true;
    Novo->pref_update();
}

bool structures::Trie::contains(std::string palavra) const {
    return root->contains(palavra);
}

bool structures::Trie::contains(std::string palavra) const {
    return root->prefixos(palavra);
}

bool structures::Trie::empty() const {
    return size_ == 0;
}

int structures::Trie::size() const {
    return size_;
}
