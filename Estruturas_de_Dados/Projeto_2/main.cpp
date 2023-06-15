#include <iostream>
#include <fstream>
#include <string.h>
#include "trie.h"
#include "ArrayList.h"
#define MAX 100

using namespace std;

void le_arquivo(string filename,
                structures::Trie *buscador,
                structures::ArrayList<string> *saidas,
                structures::ArrayList<string> *palavras) {
    ifstream arquivo (filename);
    string linha;
    int checado[palavras->size()];
    memset(checado, 0, palavras->size());
    if (!arquivo.is_open()) {
        cout << "arquivo inexistente";
        return;
    }
    int start = -1, N, inicio;
    while (getline(arquivo, linha)) {
        string palavra;
        N = linha.length();
        bool continuar = false;
        for (int i = 0; i < N; ++i) {
            // contador de posições
            start++;
            if (continuar) {
                continue;
            }
            if (linha[i] == '[')
            {
                inicio = start;
            }
            else if (linha[i] == '[')
            {
                int index = palavras->contains(palavra);
                if (index == palavras->size()) {
                    continue;
                }
                checado[index] = 1;
                int prefixos = buscador->prefixos(palavra);
                string saidaT = palavra + " is ";
                if (prefixos) {
                    saidaT += "prefix of " + static_cast<char>(prefixos);
                    saidaT += " words\n";
                    saidaT += palavra + "is at (";
                    saidaT += static_cast<char>(inicio) + ',';
                    // menos 1 é para ignorar a quebra de linha
                    saidaT += static_cast<char>(N-1) + ")\n";
                }
                else {
                    saidaT += "not a prefix\n";
                }
                saidas->insert(saidaT, index);
                continuar = true;
            }
            else
            {
                palavra.push_back(linha[i]);
            }
        }
    }
    // para as entradas que não formem palavras
    for (int i = 0; i < palavras->size(); ++i) {
        if (!checado[i]) {
            string saidaT = palavras->at(i);
            int prefixos = buscador->prefixos(saidaT);
            saidaT += " is ";
            if (prefixos) {
                saidaT += "prefix of " + static_cast<char>(prefixos);
                saidaT += " words\n";
            } else {
                saidaT += "not a prefix\n";
            }
            saidas->insert(saidaT, i);
        }
    }
}

int main() {
    
    structures::Trie buscador = structures::Trie();
    string filename, word;
    structures::ArrayList<string> saidas{MAX}, palavras{MAX};
    cin >> filename; // entrada
    while (1) {  // leitura das palavras até encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        buscador.insert(word);
        palavras.push_back(word);
    }
    le_arquivo(filename, &buscador, &saidas, &palavras);
    for (int i = 0; i < saidas.size(); ++i) {
        cout << saidas[i];
    }

    return 0;
}
