#ifndef RSA_H
#define RSA_H

#include <stdlib.h>
#include <vector>

class RSA
{
private:
    int n; //Parte da chave pública resultado de p * q
    int e; //Parte da Chave Pública
    int p; //Número primo aleatório
    int q; //Número primo aleatório diferente de p
    int totiente_n; //Resultado da função totiente de n
    int d; //Chave privada

    void gera_chaves();
    int gera_primos();
    bool eh_primo(int n);
    int funcao_totiente(unsigned int n);
    int mdc(int a, int b);
    int gera_e();
    int gera_chave_privada();
    int mod(int a, int b);


public:
    RSA();

    std::vector<int> retorna_chaves_publicas(); 
};



#endif