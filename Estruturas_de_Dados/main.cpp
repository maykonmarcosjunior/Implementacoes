#include <iostream>
#include "countingsort.h"

int main () {
    int vetor[]= {1, 3, 5, 462, 39, 4, 7, 8, 9, 3};
    int size = sizeof(vetor) / (sizeof(int));
    countsort<int>(vetor, size, 462);
    for (int i = 0; i < size; ++i) {
        std::cout << vetor[i] << ' ';
    }
    std::cout << '\n';
    return 0;
}
