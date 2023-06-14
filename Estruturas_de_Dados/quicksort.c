/*
Pertence à categoria Exchange Sort e usa o paradigma Divide and Conquer 
Abordagem recursiva onde o vetor é ramificado várias vezes pelo método partition():
1 - Escolhe um elemento pivô (normalmente o último)
2 - Percorre a lista com uma variável i para controlar quais elementos foram trocados
3 - Se o elemento checado for menor que o pivô, ele é trocado com o da variável i
4 - O valor de i é incrementado quando uma troca acontece
4 - Ao percorrer toda a lista, troca o pivô com a posição atual de i
5 - Retorna i, valendo a posição do pivô
6 - Chama recursivamente o método com a sequência à esquerda e à direita do pivô
*/

// end é a última posição, não o tamanho do vetor
void quicksort (int *elements, const int start, const int end) {
    if (start >= end) {
        return;
    }
    int i = start;
    int swap;
    for (int j = start; j < end; j++) {
    	if (elements[j] <= elements[end]) {
            swap = elements[i];
            elements[i] = elements[j];
            elements[j] = swap;
            i++;
        }
    }
    swap = elements[end];
    elements[end] = elements[i];
    elements[i] = swap;

    quicksort(elements, start, i - 1);
    quicksort(elements, i + 1, end); 
}
