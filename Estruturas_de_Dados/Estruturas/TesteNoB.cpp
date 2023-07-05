#include "gtest/gtest.h"
#include "NoB.hpp"

#define INIT_I   80
#define GRAU     2
#define LOOP_MAX 32

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

class NoBTest: public ::testing::Test {
 public:
    virtual void SetUp() {
        this->inteiro = new NoB<int>(INIT_I, GRAU);
    }

    virtual void TearDown() {
        delete this->inteiro;
    }

 protected:
    NoB<int> *inteiro;
};

template <typename T>
void checaNodo(NoB<T>* node, T* array, int size) {
    EXPECT_EQ(node->getNumChaves(), size);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(*(node->getDado(i)), array[i]);
    }
}

NoB<int>* inserirSlidesPasso1(NoB<int>* inteiro) {
    inteiro = inteiro->inserir(50, inteiro);
    inteiro = inteiro->inserir(95, inteiro);
    inteiro = inteiro->inserir(90, inteiro);
    inteiro = inteiro->inserir(60, inteiro);
    return inteiro;
}

NoB<int>* inserirSlidesPasso2(NoB<int>* inteiro) {
    inteiro = inserirSlidesPasso1(inteiro);
    inteiro = inteiro->inserir(65, inteiro);
    inteiro = inteiro->inserir(70, inteiro);
    inteiro = inteiro->inserir(75, inteiro);
    return inteiro;
}

NoB<int>* inserirSlidesPasso3(NoB<int>* inteiro) {
    inteiro = inserirSlidesPasso2(inteiro);
    inteiro = inteiro->inserir(55, inteiro);
    inteiro = inteiro->inserir(64, inteiro);
    inteiro = inteiro->inserir(51, inteiro);
    return inteiro;
}

NoB<int>* inserirSlidesPasso4(NoB<int>* inteiro) {
    inteiro = inserirSlidesPasso3(inteiro);
    inteiro = inteiro->inserir(76, inteiro);
    inteiro = inteiro->inserir(77, inteiro);
    inteiro = inteiro->inserir(78, inteiro);
    return inteiro;
}

NoB<int>* inserirSlidesPasso5(NoB<int>* inteiro) {
    inteiro = inserirSlidesPasso4(inteiro);
    inteiro = inteiro->inserir(98, inteiro);
    inteiro = inteiro->inserir(99, inteiro);
    inteiro = inteiro->inserir(96, inteiro);
    return inteiro;
}

NoB<int>* removerSlidesInsercoes(NoB<int>* inteiro) {
    inteiro = inserirSlidesPasso5(inteiro);
    inteiro = inteiro->inserir(62, inteiro);
    inteiro = inteiro->inserir(79, inteiro);
    inteiro = inteiro->inserir(91, inteiro);
    inteiro = inteiro->inserir(93, inteiro);
    inteiro = inteiro->inserir(97, inteiro);
    return inteiro;
}

TEST_F(NoBTest, inserirSlidesPasso1) {
    NoB<int>* tmp;
    inteiro = inserirSlidesPasso1(inteiro);
    checaNodo(inteiro, new int[1]{80}, 1);

    tmp = inteiro->getSubnodo(0);
    checaNodo(tmp, new int[2]{50, 60}, 2);

    tmp = inteiro->getSubnodo(1);
    checaNodo(tmp, new int[2]{90, 95}, 2);
}

TEST_F(NoBTest, inserirSlidesPasso2) {
    NoB<int>* tmp;
    inteiro = inserirSlidesPasso2(inteiro);

    checaNodo(inteiro, new int[2]{65, 80}, 2);

    tmp = inteiro->getSubnodo(0);
    checaNodo(tmp, new int[2]{50, 60}, 2);

    tmp = inteiro->getSubnodo(1);
    checaNodo(tmp, new int[2]{70, 75}, 2);

    tmp = inteiro->getSubnodo(2);
    checaNodo(tmp, new int[2]{90, 95}, 2);
}


TEST_F(NoBTest, inserirSlidesPasso3) {
    NoB<int>* tmp;
    inteiro = inserirSlidesPasso3(inteiro);

    checaNodo(inteiro, new int[3]{55, 65, 80}, 3);

    tmp = inteiro->getSubnodo(0);
    checaNodo(tmp, new int[2]{50, 51}, 2);

    tmp = inteiro->getSubnodo(1);
    checaNodo(tmp, new int[2]{60, 64}, 2);

    tmp = inteiro->getSubnodo(2);
    checaNodo(tmp, new int[2]{70, 75}, 2);

    tmp = inteiro->getSubnodo(3);
    checaNodo(tmp, new int[2]{90, 95}, 2);
}

TEST_F(NoBTest, inserirSlidesPasso4) {
    NoB<int>* tmp;
    inteiro = inserirSlidesPasso4(inteiro);

    checaNodo(inteiro, new int[4]{55, 65, 76, 80}, 4);

    tmp = inteiro->getSubnodo(0);
    checaNodo(tmp, new int[2]{50, 51}, 2);

    tmp = inteiro->getSubnodo(1);
    checaNodo(tmp, new int[2]{60, 64}, 2);

    tmp = inteiro->getSubnodo(2);
    checaNodo(tmp, new int[2]{70, 75}, 2);

    tmp = inteiro->getSubnodo(3);
    checaNodo(tmp, new int[2]{77, 78}, 2);

    tmp = inteiro->getSubnodo(4);
    checaNodo(tmp, new int[2]{90, 95}, 2);
}

TEST_F(NoBTest, inserirSlidesPasso5) {
    NoB<int> *tmp, *nodoE, *nodoD;
    inteiro = inserirSlidesPasso5(inteiro);

    checaNodo(inteiro, new int[1]{76}, 1);

    nodoE = inteiro->getSubnodo(0);
    checaNodo(nodoE, new int[2]{55, 65}, 2);

    tmp = nodoE->getSubnodo(0);
    checaNodo(tmp, new int[2]{50, 51}, 2);
    tmp = nodoE->getSubnodo(1);
    checaNodo(tmp, new int[2]{60, 64}, 2);
    tmp = nodoE->getSubnodo(2);
    checaNodo(tmp, new int[2]{70, 75}, 2);


    nodoD = inteiro->getSubnodo(1);
    checaNodo(nodoD, new int[2]{80, 96}, 2);

    tmp = nodoD->getSubnodo(0);
    checaNodo(tmp, new int[2]{77, 78}, 2);
    tmp = nodoD->getSubnodo(1);
    checaNodo(tmp, new int[2]{90, 95}, 2);
    tmp = nodoD->getSubnodo(2);
    checaNodo(tmp, new int[2]{98, 99}, 2);
}

TEST_F(NoBTest, removerSlidesPasso1) {
    NoB<int> *tmp, *nodoE, *nodoD;
    inteiro = removerSlidesInsercoes(inteiro);
    inteiro = inteiro->remover(inteiro, 90);

    checaNodo(inteiro, new int[1]{76}, 1);

    nodoE = inteiro->getSubnodo(0);
    checaNodo(nodoE, new int[2]{55, 65}, 2);

    tmp = nodoE->getSubnodo(0);
    checaNodo(tmp, new int[2]{50, 51}, 2);
    tmp = nodoE->getSubnodo(1);
    checaNodo(tmp, new int[3]{60, 62, 64}, 3);
    tmp = nodoE->getSubnodo(2);
    checaNodo(tmp, new int[2]{70, 75}, 2);

    nodoD = inteiro->getSubnodo(1);
    checaNodo(nodoD, new int[2]{80, 96}, 2);

    tmp = nodoD->getSubnodo(0);
    checaNodo(tmp, new int[3]{77, 78, 79}, 3);
    tmp = nodoD->getSubnodo(1);
    checaNodo(tmp, new int[3]{91, 93, 95}, 3);
    tmp = nodoD->getSubnodo(2);
    checaNodo(tmp, new int[3]{97, 98, 99}, 3);
}

TEST_F(NoBTest, removerSlidesPasso2) {
    NoB<int> *tmp, *nodoE, *nodoD;
    inteiro = removerSlidesInsercoes(inteiro);
    inteiro = inteiro->remover(inteiro, 90);
    inteiro = inteiro->remover(inteiro, 76);

    checaNodo(inteiro, new int[1]{77}, 1);

    nodoE = inteiro->getSubnodo(0);
    checaNodo(nodoE, new int[2]{55, 65}, 2);

    tmp = nodoE->getSubnodo(0);
    checaNodo(tmp, new int[2]{50, 51}, 2);
    tmp = nodoE->getSubnodo(1);
    checaNodo(tmp, new int[3]{60, 62, 64}, 3);
    tmp = nodoE->getSubnodo(2);
    checaNodo(tmp, new int[2]{70, 75}, 2);

    nodoD = inteiro->getSubnodo(1);
    checaNodo(nodoD, new int[2]{80, 96}, 2);

    tmp = nodoD->getSubnodo(0);
    checaNodo(tmp, new int[2]{78, 79}, 2);
    tmp = nodoD->getSubnodo(1);
    checaNodo(tmp, new int[3]{91, 93, 95}, 3);
    tmp = nodoD->getSubnodo(2);
    checaNodo(tmp, new int[3]{97, 98, 99}, 3);
}

TEST_F(NoBTest, removerSlidesPasso3) {
    NoB<int> *tmp, *nodoE, *nodoD;
    inteiro = removerSlidesInsercoes(inteiro);
    inteiro = inteiro->remover(inteiro, 90);
    inteiro = inteiro->remover(inteiro, 76);
    inteiro = inteiro->remover(inteiro, 79);

    checaNodo(inteiro, new int[1]{77}, 1);

    nodoE = inteiro->getSubnodo(0);
    checaNodo(nodoE, new int[2]{55, 65}, 2);

    tmp = nodoE->getSubnodo(0);
    checaNodo(tmp, new int[2]{50, 51}, 2);
    tmp = nodoE->getSubnodo(1);
    checaNodo(tmp, new int[3]{60, 62, 64}, 3);
    tmp = nodoE->getSubnodo(2);
    checaNodo(tmp, new int[2]{70, 75}, 2);

    nodoD = inteiro->getSubnodo(1);
    checaNodo(nodoD, new int[2]{91, 96}, 2);

    tmp = nodoD->getSubnodo(0);
    checaNodo(tmp, new int[2]{78, 80}, 2);
    tmp = nodoD->getSubnodo(1);
    checaNodo(tmp, new int[2]{93, 95}, 2);
    tmp = nodoD->getSubnodo(2);
    checaNodo(tmp, new int[3]{97, 98, 99}, 3);
}

TEST_F(NoBTest, removerSlidesPasso4) {
    NoB<int> *tmp;
    inteiro = removerSlidesInsercoes(inteiro);
    inteiro = inteiro->remover(inteiro, 90);
    inteiro = inteiro->remover(inteiro, 76);
    inteiro = inteiro->remover(inteiro, 79);
    inteiro = inteiro->remover(inteiro, 77);

    checaNodo(inteiro, new int[4]{55, 65, 78, 96}, 4);

    tmp = inteiro->getSubnodo(0);
    checaNodo(tmp, new int[2]{50, 51}, 2);

    tmp = inteiro->getSubnodo(1);
    checaNodo(tmp, new int[3]{60, 62, 64}, 3);

    tmp = inteiro->getSubnodo(2);
    checaNodo(tmp, new int[2]{70, 75}, 2);

    tmp = inteiro->getSubnodo(3);
    checaNodo(tmp, new int[4]{80, 91, 93, 95}, 4);

    tmp = inteiro->getSubnodo(4);
    checaNodo(tmp, new int[3]{97, 98, 99}, 3);
}

TEST_F(NoBTest, busca) {
    for (int i = 0; i < LOOP_MAX; i++) {
        inteiro->inserir(i, inteiro);
    }

    for (int i = 0; i < LOOP_MAX; i++) {
        ASSERT_NO_THROW(inteiro->busca(i, inteiro));
    }

    for (int i = LOOP_MAX; i < 2*LOOP_MAX; i++) {
        ASSERT_ANY_THROW(inteiro->busca(i, inteiro));
    }
}
