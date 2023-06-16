#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "trie.h"
#include "ArrayList.h"
#define MAX 200

using namespace std;

void le_arquivo(string filename,
                structures::Trie *buscador,
                structures::ArrayList<string> *saidas) {
    ifstream arquivo (filename);
    string linha;
    int checado[saidas->size()];
    memset(checado, 0, saidas->size());
    int start = -1, N, inicio;
    bool continuar;
    while (getline(arquivo, linha)) {
        string palavra;
        N = linha.length();
        continuar = false;
        for (int i = 0; i < N; ++i) {
            // contador de posições
            start++;
            if (continuar) {
                continue;
            }
            if (linha[i] == '[') {
                inicio = start;
            }
            else if (linha[i] == ']') {
                int index = saidas->find(palavra);
                if (index == saidas->size()) {
                    // continue;
                }
                checado[index] = index + 1;
                int prefixos = buscador->prefixos(palavra);
                string saidaT = palavra + " is ";
                if (prefixos) {
                    saidaT += "prefix of " + to_string(prefixos);
                    saidaT += " words\n";
                } else {
                    saidaT += "not a prefix\n";
                }
                saidaT += palavra + " is at (" + to_string(inicio);
                saidaT += ',' + to_string(N) + ")\n";
                saidas->replace(saidaT, index);
                continuar = true;
            }
            else {
                palavra.push_back(linha[i]);
            }
        }
        // para incluir a quebra de linha
        start++;
    }
    // para as entradas que não formem palavras
    for (int i = 0; i < saidas->size(); ++i) {
        if (!checado[i]) {
            checado[i] = i + 1;
            string saidaT = saidas->at(i);
            int prefixos = buscador->prefixos(saidaT);
            saidaT += " is ";
            if (prefixos) {
                saidaT += "prefix of " + to_string(prefixos);
                saidaT += " words\n";
            } else {
                saidaT += "not a prefix\n";
            }
            saidas->replace(saidaT, i);
        }
    }
}

int main() {
    
    structures::Trie buscador = structures::Trie();
    structures::ArrayList<string> saidas{MAX};
    string filename, word;
    cin >> filename; // entrada
    // leitura das palavras até encontrar "0"
    while (1) {
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        buscador.insert(word);
        saidas.push_back(word);
    }
    le_arquivo(filename, &buscador, &saidas);
    for (int i = 0; i < saidas.size(); ++i) {
        cout << saidas[i];
    }

    return 0;
}
