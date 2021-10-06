#include "include/RSA.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {

    RSA rsa;
    RSA rsa2;
    //teste

    cout << "Teste de chaves RSA" << endl;
    cout << "Chaves públicas: ";
    for ( auto i : rsa.retorna_chaves_publicas() ) {
        cout << i << endl;
    }


    return 0;
}