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
