#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5  // tamanho fixo da fila

// Estrutura que representa cada peça
typedef struct {
    char nome; // tipo da peça ('I', 'O', 'T', 'L')
    int id;    // identificador único
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[MAX];
    int frente;
    int tras;
    int tamanho;
} Fila;

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->tamanho == MAX;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

// Gera uma peça automaticamente
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4]; // sorteia entre I, O, T, L
    nova.id = id;
    return nova;
}

// Insere peça no fim da fila (enqueue)
int enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("⚠️ A fila já está cheia! Não é possível inserir nova peça.\n");
        return 0;
    }
    f->tras = (f->tras + 1) % MAX;
    f->itens[f->tras] = p;
    f->tamanho++;
    return 1;
}

// Remove peça da frente da fila (dequeue)
Peca desenfileirar(Fila *f) {
    Peca removida = {'-', -1}; // valor padrão caso esteja vazia
    if (filaVazia(f)) {
        printf("⚠️ A fila está vazia! Nenhuma peça para jogar.\n");
        return removida;
    }
    removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % MAX;
    f->tamanho--;
    return removida;
}

// Exibe o estado atual da fila
void exibirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila de peças: [vazia]\n");
        return;
    }

    printf("Fila de peças:\n");
    int i, pos = f->frente;
    for (i = 0; i < f->tamanho; i++) {
        printf("[%c %d] ", f->itens[pos].nome, f->itens[pos].id);
        pos = (pos + 1) % MAX;
    }
    printf("\n");
}

int main() {
    Fila fila;
    int opcao, idGlobal = 0;

    srand(time(NULL)); // semente para gerar peças aleatórias
    inicializarFila(&fila);

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < MAX; i++) {
        enfileirar(&fila, gerarPeca(idGlobal++));
    }

    do {
        printf("\n--------------------------\n");
        exibirFila(&fila);
        printf("\nOpções de ação:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca jogada = desenfileirar(&fila);
                if (jogada.id != -1) {
                    printf("✅ Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                }
                break;
            }
            case 2: {
                Peca nova = gerarPeca(idGlobal++);
                if (enfileirar(&fila, nova)) {
                    printf("✅ Nova peça inserida: [%c %d]\n", nova.nome, nova.id);
                }
                break;
            }
            case 0:
                printf("👋 Saindo do jogo...\n");
                break;
            default:
                printf("⚠️ Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}