#include <iostream>
#include <fstream>
#include <string.h>
#include "trie.h"

int main() {
    
    using namespace std;
    
    structures::Trie buscador = structures::Trie();
    string filename;
    string word;

    cin >> filename;  // entrada
    
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        cout << word << endl;
    }

    return 0;
}
