#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>
#include "../include/word.h"

using namespace std;

char alfabeto[26];
string palavrasTexto;
string logNome;
string outNome;
int parametroMediana = 0;
int maxParticao = 0;

int countWords(string texto)
{
    int count = 0;
    for(int i = 0; i < texto.length(); i++)
    {
        if(texto[i] == ' ' && texto[i+1] != ' ')
            count++;
    }
    
    return count;
}

int countRepetition(string palavra, string texto, int numPalavras)
{
    int repetidas = 0;
    stringstream buffer(texto);
    string aux;
    for(int i = 0; i < numPalavras; i++) {
      buffer >> aux;
      if(aux == palavra)
        repetidas++;
    }
    return repetidas;
}

string fix_word(string str) {
   string aux;
   //ASCII - upper[65 - 90] lower[97 - 122]
   int diff = 'a' - 'A';
   int x = str.length();
   for (int i = 0; i <= x; i++) {
      if ((str[i] >= 'A' && str[i] <= 'Z')) 
         aux += str[i] + diff;
      else if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= '0' && str[i] <= '9')) 
         aux += str[i];
      else if (str[i] == '-' && ((str[i+1] >= 'a' && str[i+1] <= 'z') || (str[i+1] >= 'A' && str[i+1] <= 'Z') || 
              (str[i-1] >= 'a' && str[i-1] <= 'z') || (str[i-1] >= 'A' && str[i-1] <= 'Z') )) 
         aux += str[i];
   }
   return aux;
}

void resetaOut() {
    ofstream fileOut(outNome);
    fileOut << "";
}

int main(int argc, char ** argv) {

    /*
      FASE 0 - > leitura e armazenamento dos dados de entrada: Alfabeto e Palavras
      FASE 1 - > criacao e preenchimento do array FINAL de palavras e 'encriptamento' da chave, criando as senhas
      FASE 2 - > ordenacao do vetor de palavras
    */

    //variaveis aleatorias
    int ordem = 0;
    int i = 0;
    string aux;
    string auxTexto;
    string teste;

    
    for(int i = 0; i < argc; i++)
    {
      aux = argv[i];
      if(aux == "-i" || aux == "-I")
        logNome = argv[i+1];
      else if(aux == "-o" || aux == "-O")
        outNome = argv[i+1];
      else if(aux == "-m" || aux == "-M")
        parametroMediana = atoi(argv[i+1]);
      else if(aux == "-s" || aux == "-S")
        maxParticao = atoi(argv[i+1]);
    }

    if(logNome.length() <= 0) {
      cout << "-I não definido" << endl;
      exit(1);
    }
    else if(parametroMediana <= 0) {
      cout << "-M não definido" << endl;
      exit(1);
    }
    else if(maxParticao <= 0) {
      cout << "-S não definido" << endl;
      exit(1);
    }
    else if(outNome.length() <= 0) {
      cout << "-O não definido" << endl;
      exit(1);
    }
    

    string line;
    ifstream FILE(logNome);
    // FILE.open(logNome);
    if(!FILE.is_open())
    {
      cout << "File could not be opened" << endl;
      exit(1);
    }
  
    while (FILE >> line) {
      if(ordem) {
        line[0] = tolower(line[0]);
        alfabeto[i] = line[0];
        i++;
      }
      if(line == "#ORDEM")
        ordem = 1;
      if (line == "#TEXTO") {
         // armazena as palavras do texto
         //cria o array de words com as palavras em lowercase (palavra espaço palavra [count_words])
         while (FILE >> line) {
            if (line == "#ORDEM") {
               ordem = 1;
               break;
            }
            aux = fix_word(line);
            palavrasTexto += aux;
            palavrasTexto += " ";
         }
      }
   }

    FILE.close();

    int add = 1;
    int numeroPalavras = countWords(palavrasTexto);
    int tamanhoFinal = 0;
    word vetPalavras[numeroPalavras];
    stringstream palavra(palavrasTexto);
    for(int i = 0; i < numeroPalavras; i++)
    {
      palavra >> aux;
      for(int j = 0; j < numeroPalavras; j++) {
        if(vetPalavras[j].chave == aux) {
          vetPalavras[j].quantidade++;
          add = 0;
        }
      }
      if(add) {
        vetPalavras[tamanhoFinal].chave = aux;
        tamanhoFinal++;
      }
      add = 1;
    }

    word finalPalavras[tamanhoFinal];
    for(int i = 0; i < tamanhoFinal; i++) {
      finalPalavras[i] = vetPalavras[i];
    }

    for(int i = 0; i < tamanhoFinal; i++){
      finalPalavras[i].defineSenha(alfabeto);
    }

    finalPalavras->QuickSort(finalPalavras, tamanhoFinal, maxParticao, parametroMediana);

    ofstream fileOut(outNome, std::ios::app);
    resetaOut();
    if(!fileOut.is_open())
    {
        cout << "here" << endl;
        exit(1);
    }
    for(int i = 0; i < tamanhoFinal; i++)
      fileOut << finalPalavras[i].chave << " " << finalPalavras[i].quantidade << endl;
    fileOut << "#FIM" << endl;

    fileOut.close();

    return 1;
}