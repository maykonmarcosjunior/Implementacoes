#include <iostream>
#include "heapsort.h"

int main () {
    int vetor[]= {1, 3, 5, 462, 39, 4, 7, 8, 9, 3};
    int size = sizeof(vetor) / (sizeof(int));
    heapsort<int>(vetor, size);
    for (int i = 0; i < size; ++i) {
        std::cout << vetor[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}
