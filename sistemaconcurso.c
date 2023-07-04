#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PARTICIPANTES 50
#define NUM_NOTAS 3

typedef struct {
    char nome[50];
    int inscricao;
    float notas[NUM_NOTAS];
    float media;
    int aprovado;
} Part;

void menu();
void cadastrar(Part p[], int *n);
float media(float notas[]);
void verificarAprovacao(Part *p);
void classificacao(Part p[], int n);
void pesquisar(Part p[], int n);

int main() {
    Part participantes[MAX_PARTICIPANTES];
    int numParticipantes = 0;
    int opcao;

    do {
        menu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) {
            cadastrar(participantes, &numParticipantes);
        } else if (opcao == 2) {
            pesquisar(participantes, numParticipantes);
        } else if (opcao == 3) {
            classificacao(participantes, numParticipantes);
        } else if (opcao == 0) {
            printf("Encerrando o programa...\n");
        } else {
            printf("Opcao invalida! Tente novamente.\n");
        }

        printf("\n");
    } while (opcao != 0);

    return 0;
}

void menu() {
    printf("===== Menu =====\n");
    printf("1. Cadastrar\n");
    printf("2. Pesquisar\n");
    printf("3. Classificacao\n");
    printf("0. Sair\n");
}

void cadastrar(Part p[], int *n) {
    if (*n >= MAX_PARTICIPANTES) {
        printf("Limite atingido!\n");
        return;
    }

    printf("===== Cadastro =====\n");

    printf("Nome: ");
    fgets(p[*n].nome, sizeof(p[*n].nome), stdin);

    printf("Inscricao: ");
    scanf("%d", &p[*n].inscricao);
    getchar();

    for (int i = 0; i < NUM_NOTAS; i++) {
        printf("Nota %d: ", i + 1);
        scanf("%f", &p[*n].notas[i]);
        getchar();
    }

    p[*n].media = media(p[*n].notas);
    verificarAprovacao(&p[*n]);

    (*n)++;

    printf("Cadastrado com sucesso!\n");
}

float media(float notas[]) {
    float soma = 0.0;

    for (int i = 0; i < NUM_NOTAS; i++) {
        soma += notas[i];
    }

    return soma / NUM_NOTAS;
}

void verificarAprovacao(Part *p) {
    p->aprovado = (p->media >= 7.0);
}

void classificacao(Part p[], int n) {
    if (n == 0) {
        printf("Nenhum cadastrado!\n");
        return;
    }

    printf("===== Classificacao =====\n");

    Part temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].media < p[j + 1].media) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        printf("Posicao: %d\n", i + 1);
        printf("Nome: %s", p[i].nome);
        printf("Inscricao: %d\n", p[i].inscricao);
        printf("Media: %.2f\n", p[i].media);
        printf("Aprovado: %s\n", p[i].aprovado ? "Sim" : "Nao");
        printf("\n");
    }
}

void pesquisar(Part p[], int n) {
    if (n == 0) {
        printf("Nenhum cadastrado!\n");
        return;
    }

    int inscricao;
    printf("Digite a inscricao: ");
    scanf("%d", &inscricao);
    getchar();

    for (int i = 0; i < n; i++) {
        if (p[i].inscricao == inscricao) {
            printf("===== Participante Encontrado =====\n");
            printf("Nome: %s", p[i].nome);
            printf("Inscricao: %d\n", p[i].inscricao);
            printf("Media: %.2f\n", p[i].media);
            printf("Aprovado: %s\n", p[i].aprovado ? "Sim" : "Nao");
            return;
        }
    }

    printf("Nao encontrado!\n");
}
