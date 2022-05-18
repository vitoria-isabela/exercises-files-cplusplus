
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


#include "siga.h"

// Salva o arquivo binário em um arquivo de texto (.csv).
int main(int argc, char* argv[])
{
    Siga siga("estudantes.bin");

    siga.SalvaListaEstudanteEmTexto("estudantes.csv");

    return 0;
}
