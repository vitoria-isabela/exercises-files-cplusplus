
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "siga.h"

// Altera o cadastro, através da matricula, de um estudante que esteja armazendo no arquivo.
int main(int argc, char* argv[])
{
    Siga siga("estudantes.bin");
    int matricula; 
    char nome[STR_MAX_SIZE+1];
    int ano;
    float nota;

#ifndef CLASSROOM 
    cout << "Entre com a matricula: ";
#endif

    cin >> matricula; 

    #ifndef CLASSROOM 
    cout << "Entre com a nome: ";
    #endif
    cin.ignore();
    cin.getline(nome,STR_MAX_SIZE,'\n');
    #ifndef CLASSROOM 
    cout << "Entre com o ano: ";  
    #endif
    cin >> ano;
    #ifndef CLASSROOM 
    cout << "Entre com a nota: ";
    #endif  
    cin >> nota;
    siga.AlteraCadastroEstudante(Estudante(nome, matricula, ano, nota));
    
    return 0;
}
