#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

//  Estrutura da peça 
typedef struct {
    char nome;
    int id;
} Peca;

// Fila circular 
typedef struct {
    Peca itens[TAM_FILA];
    int frente, tras, tamanho;
} Fila;

//  Pilha 
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

//  Variáveis globais 
int contadorID = 0; // gera IDs únicos para as peças

//  Função gerar peça 
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

//  Operações da fila 
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
    for (int i = 0; i < TAM_FILA; i++) {
        f->itens[i] = gerarPeca();
        f->tamanho++;
        f->tras = (f->tras + 1) % TAM_FILA;
    }
}

int filaVazia(Fila *f) {
    return f->tamanho == 0;
}

int filaCheia(Fila *f) {
    return f->tamanho == TAM_FILA;
}

Peca removerFila(Fila *f) {
    if (filaVazia(f)) {
        Peca vazio = {'-', -1};
        return vazio;
    }
    Peca removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    f->tamanho--;
    return removida;
}

void inserirFila(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->tras = (f->tras + 1) % TAM_FILA;
    f->itens[f->tras] = p;
    f->tamanho++;
}

//  Operações da pilha 
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

void push(Pilha *p, Peca x) {
    if (pilhaCheia(p)) return;
    p->itens[++p->topo] = x;
}

Peca pop(Pilha *p) {
    if (pilhaVazia(p)) {
        Peca vazio = {'-', -1};
        return vazio;
    }
    return p->itens[p->topo--];
}

Peca topoPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        Peca vazio = {'-', -1};
        return vazio;
    }
    return p->itens[p->topo];
}

//  Ações do jogo 
void jogarPeca(Fila *f) {
    Peca jogada = removerFila(f);
    if (jogada.id != -1) {
        printf("Jogou peça [%c %d]\n", jogada.nome, jogada.id);
        inserirFila(f, gerarPeca());
    }
}

void reservarPeca(Fila *f, Pilha *p) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia! Não é possível reservar.\n");
        return;
    }
    Peca movida = removerFila(f);
    push(p, movida);
    printf("Reservou peça [%c %d]\n", movida.nome, movida.id);
    inserirFila(f, gerarPeca());
}

void usarReservada(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Nada para usar.\n");
        return;
    }
    Peca usada = pop(p);
    printf("Usou peça [%c %d]\n", usada.nome, usada.id);
}

void trocarAtual(Fila *f, Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia! Não é possível trocar.\n");
        return;
    }
    Peca tmp = f->itens[f->frente];
    f->itens[f->frente] = p->itens[p->topo];
    p->itens[p->topo] = tmp;
    printf("Troca realizada!\n");
}

void trocaMultipla(Fila *f, Pilha *p) {
    if (f->tamanho < 3 || p->topo < 2) {
        printf("Não há peças suficientes para troca múltipla.\n");
        return;
    }
    for (int i = 0; i < 3; i++) {
        int idx = (f->frente + i) % TAM_FILA;
        Peca tmp = f->itens[idx];
        f->itens[idx] = p->itens[p->topo - i];
        p->itens[p->topo - i] = tmp;
    }
    printf("Troca múltipla realizada!\n");
}

// Exibir estado 
void exibirEstado(Fila *f, Pilha *p) {
    printf("\n--- Estado atual ---\n");
    printf("Fila de peças: ");
    for (int i = 0; i < f->tamanho; i++) {
        int idx = (f->frente + i) % TAM_FILA;
        printf("[%c %d] ", f->itens[idx].nome, f->itens[idx].id);
    }
    printf("\nPilha de reserva (Topo -> Base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
    }
    printf("\n---------------------\n");
}

// Programa principal
int main() {
    srand(time(NULL));
    Fila fila;
    Pilha pilha;
    inicializarFila(&fila);
    inicializarPilha(&pilha);

    int opcao;
    do {
        exibirEstado(&fila, &pilha);
        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("4 - Trocar peça atual\n");
        printf("5 - Troca múltipla\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: jogarPeca(&fila); break;
            case 2: reservarPeca(&fila, &pilha); break;
            case 3: usarReservada(&pilha); break;
            case 4: trocarAtual(&fila, &pilha); break;
            case 5: trocaMultipla(&fila, &pilha); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}