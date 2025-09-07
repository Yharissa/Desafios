#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10 // Capacidade máxima da mochila

// Definição da struct que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Funções obrigatórias
void inserirItem(Item mochila[], int *qtd);
void removerItem(Item mochila[], int *qtd);
void listarItens(Item mochila[], int qtd);
void buscarItem(Item mochila[], int qtd);

int main() {
    Item mochila[MAX_ITENS]; // Vetor de itens (a mochila)
    int qtd = 0;             // Quantidade atual de itens cadastrados
    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTARIO =====\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer do teclado

        switch (opcao) {
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
                printf("\nSaindo do sistema...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// Função para inserir item na mochila
void inserirItem(Item mochila[], int *qtd) {
    if (*qtd >= MAX_ITENS) {
        printf("\nMochila cheia! Não e possével adicionar mais itens.\n");
        return;
    }

    printf("\nDigite o nome do item: ");
    fgets(mochila[*qtd].nome, 30, stdin);
    mochila[*qtd].nome[strcspn(mochila[*qtd].nome, "\n")] = '\0'; 

    printf("Digite o tipo do item (arma, municao, cura...): ");
    fgets(mochila[*qtd].tipo, 20, stdin);
    mochila[*qtd].tipo[strcspn(mochila[*qtd].tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*qtd].quantidade);
    getchar();

    (*qtd)++; // aumenta a quantidade de itens cadastrados
    printf("\nItem adicionado com sucesso!\n");
}

// Função para remover item pelo nome
void removerItem(Item mochila[], int *qtd) {
    char nome[30];
    int i, j;

    if (*qtd == 0) {
        printf("\nA mochila está vazia, nada para remover.\n");
        return;
    }

    printf("\nDigite o nome do item a ser removido: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (i = 0; i < *qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            // Move os itens seguintes uma posição para trás
            for (j = i; j < *qtd - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*qtd)--;
            printf("\nItem '%s' removido com sucesso!\n", nome);
            return;
        }
    }
    printf("\nItem não encontrado na mochila.\n");
}

// Função para listar todos os itens
void listarItens(Item mochila[], int qtd) {
    int i;

    if (qtd == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\n===== Itens da Mochila =====\n");
    for (i = 0; i < qtd; i++) {
        printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função para buscar item pelo nome
void buscarItem(Item mochila[], int qtd) {
    char nome[30];
    int i;

    if (qtd == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nome, 30, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for (i = 0; i < qtd; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("\nItem não encontrado.\n");
}