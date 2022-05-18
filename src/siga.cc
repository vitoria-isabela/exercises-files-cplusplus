#include <string>
#include <fstream>
#include <math.h>

using namespace std;

#include "siga.h"

Siga::Siga(string arquivo_dados_estudante)
{
    this->arquivo_nome = arquivo_dados_estudante;
    this->file_stream.open(this->arquivo_nome, ios::in | ios::out | ios::binary ); // Binary: garante que os dados sejam lidos ou gravados sem traduzir novos caracteres de linha para \r e \n.

    if(this->file_stream.is_open())
    {
        cout << "SIGA: Inicializado com sucesso" << endl;
    }
    else
    {
        cout << "SIGA: Erro ao abrir arquivo" << endl;
        return; 
    }

    cout << this->ObterNumeroEstudantesArmazenados() << " registros de estudantes" << endl;
}

int  Siga::PesquisaPorMatricula(int matricula)
{
    //Posicionando o cursor no inicio do arquivo
    this->file_stream.seekg(0, this->file_stream.beg);

    //Declarando Estudante
    Estudante est = Estudante();

    for ( int i = 0; i < this->n_estudantes; i++)
    {
        //Ler do arquivo binário
        est.LerDoArquivoBinario(this->file_stream);
        //Verifica se a matricula é a mesma
        if ( est.ObterMatricula() == matricula )
            return i;
    }

    //Retornando o cursor pro fim de leitura
    this->file_stream.seekg(0, this->file_stream.end);

    //Caso não encontrar a matrícula retorna -1
    return -1;
}
        
void Siga::CadastraEstudante(Estudante est)
{
    //Verifica se est já está cadastrado
    if( PesquisaPorMatricula(est.ObterMatricula() ) != -1 )
        return;

    //Colocando o Cursor no Fim do arquivo binario
    this->file_stream.seekp(0, this->file_stream.end);

    //Adicionando o aluno
    est.EscreverNoArquivoBinario(this->file_stream);

    //Incrementando o número de estudantes
    this->n_estudantes = this->n_estudantes + 1;
}
        
void Siga::ImprimeEstudantePorMatricula(int matricula)
{
    int index = PesquisaPorMatricula(matricula);
    if( index == -1)
        cout << "Estudante não cadastrado" << endl;
    else 
    {
        this->file_stream.seekg((index * ESTUDANTE_SIZE), this->file_stream.beg ); // posição em que o Aluno se encontra no arquivo binario
        Estudante est = Estudante();

        est.LerDoArquivoBinario(this->file_stream);

        est.Imprimir();
    }
}
        
void Siga::SalvaListaEstudanteEmTexto(string arquivo_txt)
{
    //Cursor no inicio do arquivo binário
    this->file_stream.seekg(0, this->file_stream.beg);

    //Verifica se o arquivo está vazio
    if(this->n_estudantes == 0)
        return;

    fstream arq;
    //Abre o arquivo
    arq.open(arquivo_txt, ios::in | ios::out | ios::trunc); // trunc: (abreviação de truncate ) significa que quando o arquivo é aberto, o conteúdo antigo é removido imediatamente.
    if(!arq.is_open())
    {
        cout << "FALHA AO ABRIR O ARQUIVO" << endl;
        return;
    }

    //Cria um vetor de alunos
    Estudante estudante;
        
    //Salva a primeira linha
    arq << "Matricula;Nome;Ano de Ingresso;IRA" << endl;

    //Le o vetor de Estudantes
    for( int i = 0; i < this->n_estudantes; i++)
    {
        estudante.LerDoArquivoBinario(this->file_stream);
        arq << estudante.ObterMatricula() << ";";
        arq << estudante.ObterNome() << ";";
        arq << estudante.ObterAnoIngresso() << ";";
        arq << estudante.ObterIRA() << endl;
    }

    //Fechando o arquivo
    arq.close();
}
       
        
void Siga::AlteraCadastroEstudante(Estudante est)
{
    //Pesquisa o aluno
    int index = PesquisaPorMatricula( est.ObterMatricula() );

    //Caso nao encontrado imprime e retorna
    if ( index == -1 )
    {
        cout << "Estudante não cadastrado" << endl;
        return;
    }

    //Coloca o cursor no estudante que será reescrito
    this->file_stream.seekp(index * ESTUDANTE_SIZE, this->file_stream.beg);

    //Reescreve os dados dele
    est.EscreverNoArquivoBinario(this->file_stream);

    cout << "Dados Alterados" << endl;
}
        
Siga::~Siga()
{
    this->file_stream.close();
}

int Siga::ObterNumeroEstudantesArmazenados()
{
    if ( this->file_stream.is_open() )
    {
        //Cursor no fim do arquivo binário
        this->file_stream.seekg(0, this->file_stream.end);

        // tellg() Retorna a posição do caractere atual no fluxo de entrada,
        // e como o cursor está no fim do arquivo binário, retorna o tamanho do arquivo binário.
        int length = this->file_stream.tellg();

         //Cursor no inicio do arquivo binário
        this->file_stream.seekg(0, this->file_stream.beg);

        this->n_estudantes = length / ESTUDANTE_SIZE;

        return this->n_estudantes;
    } else 
    {
        return 0;
    }
}