#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Contato
{
    char nome[50];
    char telefone[20];
    struct Contato *proximo;
} Contato;

typedef struct
{
    Contato **tabela;
    int capacidade;
} HashTable;

int hashFunction(const char *nome, int capacidade)
{
    int hash = 0;
    for (int i = 0; nome[i] != '\0'; i++)
    {
        hash += nome[i];
    }
    return hash % capacidade;
}

HashTable *inicializarTabela(int capacidade)
{
    HashTable *tabelaHash = (HashTable *)malloc(sizeof(HashTable));
    tabelaHash->capacidade = capacidade;
    tabelaHash->tabela = (Contato **)calloc(capacidade, sizeof(Contato *));
    return tabelaHash;
}

void adicionarContato(HashTable *tabelaHash, const char *nome, const char *telefone)
{
    int indice = hashFunction(nome, tabelaHash->capacidade);

    Contato *atual = tabelaHash->tabela[indice];
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            printf("Erro: Nome duplicado. Contato não adicionado.\n");
            return;
        }
        atual = atual->proximo;
    }

    Contato *novoContato = (Contato *)malloc(sizeof(Contato));
    strcpy(novoContato->nome, nome);
    strcpy(novoContato->telefone, telefone);
    novoContato->proximo = tabelaHash->tabela[indice];
    tabelaHash->tabela[indice] = novoContato;

    printf("Contato adicionado com sucesso.\n");
}

void buscarContato(HashTable *tabelaHash, const char *nome)
{
    int indice = hashFunction(nome, tabelaHash->capacidade);
    Contato *atual = tabelaHash->tabela[indice];

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            printf("Telefone de %s: %s\n", nome, atual->telefone);
            return;
        }
        atual = atual->proximo;
    }
    printf("Contato não encontrado.\n");
}


void removerContato(HashTable *tabelaHash, const char *nome)
{
    int indice = hashFunction(nome, tabelaHash->capacidade);
    Contato *atual = tabelaHash->tabela[indice];
    Contato *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            if (anterior == NULL)
            {
                tabelaHash->tabela[indice] = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Contato removido com sucesso.\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Contato não encontrado.\n");
}


void mostrarContatos(HashTable *tabelaHash)
{
    printf("Lista de contatos:\n");
    for (int i = 0; i < tabelaHash->capacidade; i++)
    {
        Contato *atual = tabelaHash->tabela[i];
        while (atual != NULL)
        {
            printf("Nome: %s, Telefone: %s\n", atual->nome, atual->telefone);
            atual = atual->proximo;
        }
    }
}


void liberarTabela(HashTable *tabelaHash)
{
    for (int i = 0; i < tabelaHash->capacidade; i++)
    {
        Contato *atual = tabelaHash->tabela[i];
        while (atual != NULL)
        {
            Contato *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(tabelaHash->tabela);
    free(tabelaHash);
}

int main()
{
    int capacidade = 10;
    HashTable *listaTelefonica = inicializarTabela(capacidade);

    int opcao;
    char nome[50];
    char telefone[20];

    do
    {
        printf("\nEscolha uma opção:\n");
        printf("1 - Adicionar contato\n");
        printf("2 - Buscar contato por nome\n");
        printf("3 - Remover contato\n");
        printf("4 - Exibir todos os contatos\n");
        printf("0 - Sair\n");
        printf("Digite uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            printf("Nome: ");
            scanf("%s", nome);
            printf("Telefone: ");
            scanf("%s", telefone);
            adicionarContato(listaTelefonica, nome, telefone);
            break;

        case 2:
            printf("Nome: ");
            scanf("%s", nome);
            buscarContato(listaTelefonica, nome);
            break;

        case 3:
            printf("Nome: ");
            scanf("%s", nome);
            removerContato(listaTelefonica, nome);
            break;

        case 4:
            mostrarContatos(listaTelefonica);
            break;

        case 0:
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    liberarTabela(listaTelefonica);
    return 0;
}