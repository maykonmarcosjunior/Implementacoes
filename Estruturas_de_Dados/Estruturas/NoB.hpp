#ifndef NO_B_HPP
#define NO_B_HPP

template <typename T>
class NoB {
 private:
    int ordem;
    int numChaves;
    bool folha;

 public:
    explicit NoB(const T& dado, int ordem);
    virtual ~NoB();
    NoB<T>* inserir(const T& dado, NoB<T>* arv);
    T* busca(const T& dado, NoB<T>* arv);
    NoB<T>* remover(NoB<T>* arv, const T& dado);
    T* getDado(int index);
    int getNumChaves();
    NoB<T>* getSubnodo(int index);
};

#endif /* NO_B_HPP */
