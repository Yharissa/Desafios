#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_ITENS 10

//Estrutura do Item do Inventário
typedef struct
{
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);

int main(){
    Item mochila[MAX_ITENS];
    int qtd = 0;
    int opcao;

    do
    {
        printf("\n====SISTEMA DE INVENTARIO====\n");
        printf("1 - Inserir Item\n");
        printf("2 - Remover Item\n");
        printf("3 - Listar Itens\n");
        printf("4 - Buscar Itens\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao)
        {
        case 1:
            inserirItem(mochila, &qtd);
            listarItens(mochila, qtd);
            break;
        case 2:
            removerItem(mochila, &qtd);
            listarItens(mochila, qtd);
            break;
        case 3:
            listarItens(mochila, qtd);
            break;
        case 4:
            buscarItem(mochila, qtd);
            break;

        case 0:
            printf("Saindo do Sistema...\n");
            break;
        default:
            printf("Opção Inválida! Tente novamente.\n");
        }

    } while (opcao != 0);
    
    return 0;
}

