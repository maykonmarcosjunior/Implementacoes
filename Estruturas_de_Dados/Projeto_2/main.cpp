#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "trie.h"
#include "ArrayList.h"
#define MAX 200

using namespace std;

void le_arquivo(int checado[],
                string filename,
                structures::Trie *buscador,
                structures::ArrayList<string> *saidas,
                structures::ArrayList<string> *palavras) {
    ifstream arquivo (filename);
    string linha;
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
                int index = palavras->find(palavra);
                if (index == palavras->size()) {
                    // continue;
                }
                checado[index] = index + 1;
                int prefixos = buscador->prefixos(palavra);
                string saidaT = palavra + " is ";
                if (prefixos) {
                    saidaT += "prefix of " + to_string(prefixos);
                    saidaT += " words\n";
                    saidaT += palavra + "is at (" + to_string(inicio);
                    saidaT += ',' + to_string(N) + ")\n";
                }
                else {
                    // saidaT += "not a prefix\n";
                }
                saidas->push_back(saidaT);
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
            checado[i] = i + 1;
            string saidaT = palavras->at(i);
            int prefixos = buscador->prefixos(saidaT);
            saidaT += " is ";
            if (prefixos) {
                saidaT += "prefix of " + to_string(prefixos);
                saidaT += " words\n";
            } else {
                saidaT += "not a prefix\n";
            }
            saidas->push_back(saidaT);
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
    int checado[palavras.size()];
    memset(checado, 0, palavras.size());
    le_arquivo(checado, filename, &buscador, &saidas, &palavras);
    for (int i = 0; i < saidas.size(); ++i) {
        cout << saidas[checado[i]-1];
    }

    return 0;
}
