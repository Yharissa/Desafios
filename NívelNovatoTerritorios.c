//Bibliotecas Necessárias
#include <stdio.h>
#include <locale.h>
#include <string.h>

struct Territorios
{
    char nome[30];
    char cor[10];
    int tropas;
};

int main(){

    struct Territorios vetor[5];

    for (int i = 0; i < 5; i++) {
        printf("Digite o nome do Território %d: ", i + 1);
        scanf("%s", vetor[i].nome);

        printf("Digite a cor do Território %d: ", i + 1);
        scanf("%s", vetor[i].cor);

        printf("Digite o número de tropas no Território %d: ", i + 1);
        scanf("%d", &vetor[i].tropas);

        printf("\n");
    }

    printf("=== Lista de Territórios ===\n");
    for (int i = 0; i < 5; i++) {
        printf("Território %d: Nome: %s | Cor: %s | Tropas: %d\n",
               i + 1, vetor[i].nome, vetor[i].cor, vetor[i].tropas);
    }

    
    return 0;

}