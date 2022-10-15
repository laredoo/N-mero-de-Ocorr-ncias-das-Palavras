#ifndef WORD_H
#define WORD_H

#include <iostream>
#include <string>

using namespace std;


class word {
    public:
        string chave;
        int quantidade;
        string senha;
        word() {
            this->quantidade = 1;
        };
        word(string chave) {
            this->chave = chave;
            this->quantidade = 1;
        }
        //metodos
        void defineSenha(char ordem[]);
        //metodos de ordenacao
        void Particao(int Esq, int Dir,int *i, int *j, word *A, int parametroMediana);
        void Ordena(int Esq, int Dir, word *A, int maxParticao, int parametroMediana);
        void QuickSort(word *A, int n, int maxParticao, int parametroMediana);

};



#endif