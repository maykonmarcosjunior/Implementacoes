#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "trie.h"

void le_arquivo(std::string filename,
                structures::Trie *buscador) {
    std::ifstream arquivo (filename);
    std::string linha;
    int start = -1;
    while (getline(arquivo, linha)) {
        std::string palavra = "";
        int N = linha.length();
        int inicio;
        for (int i = 0; i < N; ++i) {
            // contador de posições
            start++;
            if (linha[i] == '[') {
                inicio = start;
            }
            else if (linha[i] == ']') {
                buscador->insert(palavra, inicio, N);
                start += (N - i);
                break;
            }
            else {
                palavra.push_back(linha[i]);
            }
        }
    }
}

int main() {
    
    structures::Trie buscador = structures::Trie();
    std::string filename;
    std::cin >> filename; // entrada
    le_arquivo(filename, &buscador);
    std::string word;
    std::string vetor_prefixos[2] = {" is not prefix\n", ""};
    std::string vetor_is_word[2] = {"", ""};
    int vetor[4] = {0, 0, 0, 0};
    int prefixos = 0, inicio = 0, N = 0, is_word = 0;
    // leitura das palavras até encontrar "0"
    while (1) {
        std::cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        buscador.prefixos(word, vetor);
        prefixos = vetor[0];
        inicio = vetor[1];
        N = vetor[2];
        is_word = vetor[3];
        std::string saidaT = word;
        vetor_prefixos[1] = " is prefix of ";
        vetor_prefixos[1] += std::to_string(prefixos);
        vetor_prefixos[1] += " words\n";
        // equivalente a um if prefixos > 0
        saidaT += vetor_prefixos[!(!prefixos)];
        vetor_is_word[1] = word;
        vetor_is_word[1] += " is at (";
        vetor_is_word[1] += std::to_string(inicio);
        vetor_is_word[1] += "," + std::to_string(N) + ")\n";
        // equivalente a um if is_word
        saidaT += vetor_is_word[is_word];
        
        std::cout << saidaT;
    }

    return 0;
}   
