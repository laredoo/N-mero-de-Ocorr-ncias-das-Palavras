#include "../include/word.h"
#include <string>
#include <cmath>
#include <iostream>

#define Troca(A, B) {word c = A; A = B; B = c; }

/*
    a b c
    z e f

    bac --> ezf

*/

void word::defineSenha(char ordem[])
{
    string key = this->chave;
    string auxKey;
    int diff = 'a';
    int j;  
    char caractereAux;
    int tamanhoChave = key.length();
    for (int i = 0; i < tamanhoChave; i++)
    {
        if(key[i] == '-')
            auxKey += '-';
        else if(key[i] >= '0' && key[i] <= '9')
            auxKey += key[i];
        else {
            caractereAux = key[i];
            for(j = 0; j < 26; j++) {
                if(ordem[j] == caractereAux)
                    break;
            }
            auxKey += diff + j;
        }   
    }
    this->senha = auxKey;
}

// M = 4 a b c d 
// M = 3 a b c

void Bolha(word *v, int n) {
    int i, j;
    for(i = 0; i < n-1; i++)
        for(j = 1; j < n-i; j++)
            if (v[j].senha < v[j-1].senha)
                Troca(v[j-1], v[j]);
}

void selectionsort(word *array, int esq, int dir, int n) {
   int i, j, min;
   n += esq; j = dir;

   for (i = esq; i < n - 1; i++) {
      min = i;
      for (j = i + 1 ; j < n; j++) {
         if (array[j].senha < array[min].senha)
            min = j;
      }
      swap(array[i], array[min]);
   }
}

/*
    Esq = 0
    Dir = 3
    M = 3
*/

void word::Particao(int Esq, int Dir, int *i, int *j, word *A, int parametroMediana) {
    word x, w;
    *i = Esq; *j = Dir;
    word xMedian[parametroMediana]; //crio o subvetor para descobrir a mediana e pegar como pivo    
    if(Dir - Esq >= parametroMediana) {
        //populo o novo vetor
        for(int t = 0; t < parametroMediana; t++)
            xMedian[t] = A[Esq + t];

        Bolha(xMedian, parametroMediana); //ordeno o subvetor

        x = xMedian[parametroMediana/2]; /* obtem o pivo x */
    }
    x = A[(*i + *j)/2]; /* obtem o pivo x */
    do
    {
        while (x.senha > A[*i].senha) (*i)++;
        while (x.senha < A[*j].senha) (*j)--;
        if (*i <= *j)
        {
            w = A[*i]; A[*i] = A[*j]; A[*j] = w;
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

void word::Ordena(int Esq, int Dir, word *A, int maxParticao, int parametroMediana){
    int i;
    int j;
    int maxTam = Dir - Esq + 1;

    if(maxTam <= maxParticao)
        selectionsort(A, Esq, Dir, maxTam);
    else {
        Particao(Esq, Dir, &i, &j, A, parametroMediana);
        if (Esq < j) Ordena(Esq, j, A, maxParticao, parametroMediana);
        if (i < Dir) Ordena(i, Dir, A, maxParticao, parametroMediana);
    }    
}

void word::QuickSort(word *A, int n, int maxParticao, int parametroMediana)
{
    Ordena(0, n-1, A, maxParticao, parametroMediana);
}

