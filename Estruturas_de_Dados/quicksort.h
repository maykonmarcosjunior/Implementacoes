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
template<typename T>
void quicksort (T *elements, const int start, const int end) {
    // end é a última posição, não o tamanho do vetor
    if (start >= end) {
        return;
    }
    int i = start;
    T swap;
    T pivo = elements[end];
    T vet[2];
    for (int j = start; j < end; j++) {
        vet[0] = elements[j];
        vet[1] = elements[i];
        int cond = elements[j] <= pivo;
        elements[j] = vet[cond];
        elements[i] = vet[!cond];
        i += cond;
    }
    elements[end] = elements[i];
    elements[i] = pivo;

    quicksort(elements, start, i - 1);
    quicksort(elements, i + 1, end); 
}



  
// A utility function to swap two elements
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
  
/* This function is same in both iterative and recursive*/
int partition(int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);
  
    for (int j = l; j <= h - 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}
/* A[] --> Array to be sorted,
l --> Starting index, 
h --> Ending index
*/
void quickSortIterative(int arr[], int l, int h)
{
    // Create an auxiliary stack
    int stack[h - l + 1];
  
    // initialize top of stack
    int top = -1;
  
    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;
  
    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];
  
        // Set pivot element at its correct position
        // in sorted array
        int p = partition(arr, l, h);
  
        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }
  
        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}
