/*
usa o heap, uma estrutura similar à árvore binária
para ordenar o vetor, onde as subárvores sempre são
reorganizadas para que pais sejam maiores que filhos,
depois a raiz é substituída com uma das pontas,
reiterando o processo até o final 
*/
#define pai(i) (((i)-1)/2)

template<typename T>
void heapsort(T arr[], int n) {
    // function build Max Heap where value
    // of each child is always smaller
    // than value of their parent
    for (int i = 1; i < n; i++) {
        // if child is bigger than parent
        if (arr[i] > arr[pai(i)]) {
            int j = i;
     
            // swap child and parent until
            // parent is smaller
            while (arr[j] > arr[pai(j)]) {
                T temp = arr[j];
                arr[j] = arr[pai(j)];
                arr[pai(j)] = temp;

                j = pai(j);
            }
        }
    }

    for (int i = n - 1; i > 0; i--) {
        // swap value of first indexed
        // with last indexed

        T temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // maintaining heap property
        // after each swapping
        int j = 0, index;
         
        do {
            index = (2 * j) + 1;
             
            // if left child is smaller than
            // right child point index variable
            // to right child
            int cond = (index < (i - 1) && arr[index] < arr[index + 1]);
            index += cond;

            // if parent is smaller than child
            // then swapping parent with child
            // having higher value
            T temp_v[] = {arr[j], arr[index]};
            cond = (index < i && arr[j] < arr[index]);
            arr[j] = temp_v[cond];
            arr[index] = temp_v[!cond];

            j = index;
         
        } while (index < i);
    }
}
