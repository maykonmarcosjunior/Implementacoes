// Copyright [2023] <Maykon Marcos Junior>
#include <string.h>
#define L 26

namespace structures {

class Trie {
public:
    Trie();
    
    ~Trie();

    void insert(std::string palavra, const int inicio, const int N);

    bool contains(std::string palavra) const;

    void prefixos(std::string palavra, int saida[4]);

    bool empty() const;

    int size() const;

private:
    struct Node {
        char letra;
        Node* filhos[L];
        Node* pai;
        int posicao;
        int prefixos;
        int inicio;
        int N;
        int is_word;

        explicit Node(const char& newData, Node* NewPai) {
            letra = newData;
            pai = NewPai;
            inicio = 0;
            N = 0;
            is_word = 0;
            posicao = (pai == nullptr) ? 0 : pai->posicao + 1;
            prefixos = 0;
            for (int i = 0; i < L; ++i) {
                filhos[i] = nullptr;
            }
        }
        
        Node* find(const char& dado) {
            int i = dado - 'a';
            return filhos[i];
        }

        void insert(Node* novo) {
            if (novo != nullptr) {
                int i = novo->letra - 'a';
                filhos[i] = novo;
            }
        }
        void pref_update() {
            prefixos++;
            if (pai != nullptr) {
                pai->pref_update();
            }
        }
        bool contains(std::string palavra, int SIZE) {
            if (posicao < SIZE) {
                Node* teste = find(palavra[posicao]);
                if (teste != nullptr) {
                    return teste->contains(palavra, SIZE);
                }
                return false;
            }
            return true;
        }
        void prefix(std::string palavra, int saida[4], int SIZE) {
            if (posicao < SIZE) {
                Node* teste = find(palavra[posicao]);
                if (teste != nullptr) {
                    teste->prefix(palavra, saida, SIZE);
                } else {
                    saida[0] = 0;
                    saida[1] = 0;
                    saida[2] = 0;
                    saida[3] = 0;
                }
            } else {
                saida[0] = prefixos;
                saida[1] = inicio;
                saida[2] = N;
                saida[3] = is_word;
            }
        }
    };

    void destructor(Node* Nodo) {
        if (Nodo != nullptr) {
            for (int i = 0; i < L; i++) {
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
void structures::Trie::insert(std::string palavra, int inicio, int N) {
    Node *pai = root, *Novo = root->find(palavra[0]);
    int i = 0, max = static_cast<int>(palavra.length());
    // verificando quais letras já estão lá
    while (Novo != nullptr && i < max) {
        i++;
        pai = Novo;
        Novo = pai->find(palavra[i]);
    }
    // significa que palavra é 
    // um prefixo de outra já inserida
    if (i == max && !pai->is_word) {
        pai->inicio = inicio;
        pai->N = N;
        pai->is_word = true;
        pai->pref_update();
        return;
    }
    // caso contrário
    // deve-se inserir
    // as letras restantes
    for (; i < max; ++i) {
        Novo = new Node(palavra[i], pai);
        pai->insert(Novo);
        pai = Novo;
        size_++;
    }
    Novo->inicio = inicio;
    Novo->N = N;
    Novo->is_word = 1;
    Novo->pref_update();
}

bool structures::Trie::contains(std::string palavra) const {
    int SIZE = static_cast<int>(palavra.length());
    return root->contains(palavra, SIZE);
}

void structures::Trie::prefixos(std::string palavra, int saida[4]) {
    int SIZE = static_cast<int>(palavra.length());
    root->prefix(palavra, saida, SIZE);
}

bool structures::Trie::empty() const {
    return size_ == 0;
}

int structures::Trie::size() const {
    return size_;
}
