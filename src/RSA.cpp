#include "include/RSA.h"

#include <time.h>
#include <math.h>

RSA::RSA()
{
    srand (static_cast <unsigned> (time(0)));
    gera_chaves();
}

void RSA::gera_chaves() {
    //gerar números primos
    this->p = gera_primos();
    this->q = gera_primos();
    this->n = this->p * this->q;
    int a = funcao_totiente(this->p);
    int b = funcao_totiente(this->q);
    this->totiente_n = a * b;
    this->e = gera_e();
}

int RSA::gera_primos() {

    int primo;
    int min = 1;
    int max = 100;

    do {
        primo = min + (rand() % max);
    } while(!eh_primo(primo));

    return primo;
}

bool RSA::eh_primo(int n) {

    int aux = n/2;
    for(int i = 2; i <= aux; i++){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

int RSA::funcao_totiente(unsigned int n) {

    unsigned int resultado = 1;
    for (int i = 2; i < n; i++) {
        if(mdc(i, n) == 1) {
            resultado++;
        }
    }

    return resultado;
}

int RSA::mdc(int a, int b) {

    if(a == 0) {
        return b;
    }
    return mdc(b % a, a);
}

int RSA::gera_e() {

    while(true) {
        int gerado = 2 + rand() % this->totiente_n;
        if(mdc(this->totiente_n, gerado) == 1) {
            return gerado;
        }
    }
}

int RSA::gera_chave_privada() {

    int d = 0;

    while(mod(d * this->e, this->totiente_n) != 1) {
        d++;
    }

    return d;
}

int RSA::mod(int a, int b) {

    if(a < b) {
        return a;
    }
    
    return a % b;
}

std::vector<int> RSA::retorna_chaves_publicas() {
    std::vector<int> vetor;

    vetor.push_back(this->n);
    vetor.push_back(this->e);

    return vetor;
}