#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "trie.h"

using namespace std;

void le_arquivo(string filename,
                structures::Trie *buscador) {
    ifstream arquivo (filename);
    string linha;
    int start = -1, N, inicio;
    bool continuar;
    while (getline(arquivo, linha)) {
        string palavra = "";
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
                buscador->insert(palavra, inicio, N);
                continuar = true;
            }
            else {
                palavra.push_back(linha[i]);
            }
        }
        // para incluir a quebra de linha
        start++;
    }
}

int main() {
    
    structures::Trie buscador = structures::Trie();
    string filename;
    cin >> filename; // entrada
    le_arquivo(filename, &buscador);
    string word;
    int vetor[4] = {0, 0, 0, 0};
    int prefixos = 0, inicio = 0, N = 0, is_word = 0;
    // leitura das palavras até encontrar "0"
    while (1) {
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        buscador.prefixos(word, vetor);
        prefixos = vetor[0];
        inicio = vetor[1];
        N = vetor[2];
        is_word = vetor[3];
        string saidaT = word + " is ";
        if (prefixos) {
            saidaT += "prefix of " + to_string(prefixos);
            saidaT += " words\n";
        } else {
            saidaT += "not prefix\n";
        }
        if (is_word) {
            saidaT += word + " is at (" + to_string(inicio);
            saidaT += ',' + to_string(N) + ")\n";
        }
        cout << saidaT;
    }

    return 0;
}
