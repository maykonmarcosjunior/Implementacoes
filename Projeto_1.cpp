//! Copyright [2023] <Maykon Marcos Junior>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "pilha.h"
#include "fila.h"

#define n 100

using namespace std;

struct coordenada {
    int i, j;
};
int robo(coordenada atual, coordenada dimensoes, vector<vector<char>> matriz) {
    structures::ArrayQueue<coordenada> caminho{dimensoes.i*dimensoes.j};
    structures::ArrayQueue<coordenada> passos{dimensoes.i*dimensoes.j};
    if (matriz[atual.i][atual.j] == '1') {
        caminho.enqueue(atual);
    } else {return 0;}
    passos.enqueue(atual);
    static coordenada direita, esquerda, cima, baixo;
    bool i_me, j_me, i_ma, j_ma;
    while (true) {
        esquerda = direita = cima = baixo = atual;
        direita.j++; esquerda.j--; cima.i++; baixo.i--;
        i_me = cima.i < dimensoes.i && matriz[cima.i][cima.j] == '1';
        j_me = direita.j < dimensoes.j && matriz[direita.i][direita.j] == '1';
        i_ma = baixo.i >= 0 && matriz[baixo.i][baixo.j] == '1';
        j_ma = esquerda.j >= 0 && matriz[esquerda.i][esquerda.j] == '1';
    
        if (j_me && !caminho.contains(direita)) {
            caminho.enqueue(direita);
            passos.enqueue(direita);
        }
        if (i_me && !caminho.contains(cima)) {
            caminho.enqueue(cima);
            passos.enqueue(cima);
        }
        if (j_ma && !caminho.contains(esquerda)) {
            caminho.enqueue(esquerda);
            passos.enqueue(esquerda);
        }
        if (i_ma && !caminho.contains(baixo)) {
            caminho.enqueue(baixo);
            passos.enqueue(baixo);
        }
        if (passos.size() > 1) {
            passos.dequeue();
            atual = passos.back();
        } else {
            return caminho.size();
        }
    }
}

void Aninhamento (string arquivo, structures::ArrayQueue<string>* saida) {
    structures::ArrayStack<string> pilha(10*n);
    coordenada temp_xy, temp_lc;
    bool le_matriz = false;
    vector<vector<char>> matriz;
    int c = 0, l = 0;
    string line;
    ifstream myfile (arquivo);
    
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '<') {
                    int j = i;
                    string palavra;
                    if (line[i+1] != '/') {
                        string temporario;
                        while (line[j] != '>') {
                            palavra.push_back(line[j]);
                            j++;
                        }
                        palavra.push_back(line[j]);
                        pilha.push(palavra);
                        
        // printando o nome do cenário ---------------------------------------
                        if (palavra == "<nome>"){
                            int k = j+1; 
                            while (line[k] != '<'){
                                temporario.push_back(line[k]);
                                k++;
                            } temporario.push_back(' ');
                            saida->enqueue(temporario);
                            j = k - 1;
                        }
        // Coletando tags de dimensao da matriz -------------------------------
                        else if (palavra == "<altura>"){
                            int k = j+1;
                            while (line[k] != '<') {
                                temporario.push_back(line[k]);
                                ++k; 
                            }
                            stringstream conversor(temporario);
                            conversor >> temp_lc.i;
                            j = k - 1;
                        } else if (palavra == "<largura>"){
                            int k = j+1;
                            while (line[k] != '<'){
                                temporario.push_back(line[k]);
                                k++;
                            }
                            stringstream conversor(temporario);
                            conversor >> temp_lc.j;
                            j = k - 1;
                        }
        // Coletando tags x e y
                        else if (palavra == "<x>") {
                            int k = j + 1;
                            while (line[k] != '<'){
                                temporario.push_back(line[k]);
                                k++;
                            }
                            stringstream conversor(temporario);
                            conversor >> temp_xy.i;
                            j = k - 1;
                        } else if (palavra == "<y>") {
                            int k = j + 1;
                            while (line[k] != '<'){
                                temporario.push_back(line[k]);
                                k++;
                            }
                            stringstream conversor(temporario);
                            conversor >> temp_xy.j;
                            j = k - 1;
                        }
        // transcrevendo a matriz ----------------------------------------------
                        else if (palavra == "<matriz>") {
                            if (!le_matriz) {
                                le_matriz = true;
                            } break;
                        }
        //----------------------------------------------------------------------
                        
                    } else {
                        while (line[j] != '>') {
                            if (line[j] != '/') {
                                palavra.push_back(line[j]);
                            } 
                            j++;
                        } palavra.push_back(line[j]);
                      
                        if (!pilha.empty()) {
                            if (pilha.pop() != palavra) {
                                saida->clear(); saida->enqueue("erro\n");
                                return;
                            }
                        } else {
                            saida->clear(); saida->enqueue("erro\n");
                            return;
                        }
                    
                    }
                    i = j;
                } else if (le_matriz) {
                    vector<char> temp;
                    for (int j = 0; j < line.length(); ++j) { 
                        if (line[j] == '1' || line[j] == '0') {
                            temp.push_back(line[j]);
                            c++;
                            if (c == temp_lc.j) {
                                c = 0; l++;
                            }
                        }
                    } matriz.push_back(temp);
                    if (l == temp_lc.i) {
                        saida->enqueue(to_string(robo(temp_xy, temp_lc, matriz)) + '\n');
                        le_matriz = false; matriz.clear(); l = 0;
                    } break;
                }
            }
        }
        myfile.close();
        if (!pilha.empty()) {
            saida->clear(); saida->enqueue("erro\n");
            return;
        }
    } else { 
        saida->clear(); saida->enqueue("erro\n");
        return;
    }
  return;
}

int main() {
    
    structures::ArrayQueue<string> saida{20*n};
    
    string xmlString = "cenarios1.xml";
    cin >> xmlString;  // entrada
    Aninhamento(xmlString, &saida);
    while (saida.size()) {
        cout << saida.dequeue();
    }
    return 0;
}
