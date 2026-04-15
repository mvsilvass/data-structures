#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

typedef struct Aluno {
    int matricula;
    char nome[100];
} Aluno;

typedef struct Node {
    Aluno aluno;
    struct Node *direita;
    struct Node *esquerda;
    int altura;
} Node;

typedef struct Arvore {
    Node *raiz;
} Arvore;

void limparTela() {
    printf("\nAperte qualquer tecla para continuar....");
    getch();
    system("cls");
}

int altura(Node *node) {
    return (node == NULL) ? 0 : node->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalanceamento(Node *node) {
    return (node == NULL) ? 0 : altura(node->esquerda) - altura(node->direita);
}

Aluno criarAluno() {
    Aluno novoAluno;

    printf("Insira a matricula do aluno: \n");
    scanf("%i", &novoAluno.matricula);

    printf("\nInsira o nome do aluno: \n");
    scanf(" %[^\n]", novoAluno.nome);

    return novoAluno;
}

Node *criarNode(Aluno aluno) {
    Node *novoNode = (Node *)malloc(sizeof(Node));
    novoNode->aluno = aluno;
    novoNode->esquerda = NULL;
    novoNode->direita = NULL;
    novoNode->altura = 1;
    return novoNode;
}

Arvore *criarArvore() {
    Arvore *arvore = (Arvore *)malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    return arvore;
}

Node *rotarDireita(Node *node) {
    Node *esquerda = node->esquerda;
    Node *meio = esquerda->direita;

    esquerda->direita = node;
    node->esquerda = meio;

    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));
    esquerda->altura = 1 + max(altura(esquerda->esquerda), altura(esquerda->direita));

    return esquerda;
}

Node *rotarEsquerda(Node *node) {
    Node *direita = node->direita;
    Node *meio = direita->esquerda;

    direita->esquerda = node;
    node->direita = meio;

    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));
    direita->altura = 1 + max(altura(direita->esquerda), altura(direita->direita));

    return direita;
}

Node* balancear(Node* node) {
    if (node == NULL) return node;

    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));
    int balanceamento = getBalanceamento(node);

    // CASO 1: Inclinação total à Esquerda (Linha Reta /)
    if (balanceamento > 1) {

        // Se o filho esquerdo pende para a direita (Formato <)
        // Precisamos alinhar primeiro para virar uma linha reta (/)
        if (getBalanceamento(node->esquerda) < 0) {
            node->esquerda = rotarEsquerda(node->esquerda);
        }
        return rotarDireita(node);
    }

    // CASO 2: Inclinação total à Direita (Linha Reta \)
    if (balanceamento < -1) {
        
        // Se o filho direito pende para a esquerda (Formato >)
        // Precisamos alinhar primeiro para virar uma linha reta (\)
        if (getBalanceamento(node->direita) > 0) {
            node->direita = rotarDireita(node->direita);
        }

        return rotarEsquerda(node);
    }

    return node;
}

Node *inserir(Node *node, Aluno aluno) {
    if (node == NULL) return criarNode(aluno);

    if (aluno.matricula < node->aluno.matricula)
        node->esquerda = inserir(node->esquerda, aluno);
    else if (aluno.matricula > node->aluno.matricula)
        node->direita = inserir(node->direita, aluno);
    else 
        return node;  

    return balancear(node);
}

Node *menorNode(Node *node) {
    Node *atual = node;

    while (atual->esquerda != NULL) 
        atual = atual->esquerda;

    return atual;
}

Node *remover(Node *node, int matricula) {
    if (node == NULL) return node;

    if (matricula < node->aluno.matricula){
        node->esquerda = remover(node->esquerda, matricula);
    }else if (matricula > node->aluno.matricula){
        node->direita = remover(node->direita, matricula);
    }else {
        if ((node->esquerda == NULL) || (node->direita == NULL)) {
            Node *temp = node->esquerda ? node->esquerda : node->direita;

            if (temp == NULL) { 
                temp = node; 
                node = NULL; 
            }else {
                *node = *temp;
            }
            
            free(temp);
        } else {
            Node *temp = menorNode(node->direita);
            node->aluno = temp->aluno;
            node->direita = remover(node->direita, temp->aluno.matricula);
        }
    }

    return balancear(node);
}

void buscar(Node *node, int matricula) {
    if (node == NULL) {
        printf("\nAluno %d nao encontrado!", matricula);
        return;
    }

    if (matricula < node->aluno.matricula){
        buscar(node->esquerda, matricula);
    }else if(matricula > node->aluno.matricula){
        buscar(node->direita, matricula);
    }else{
        printf("\nEncontrado: %s", node->aluno.nome);
    }
}

void imprimirArvoreRecursivo(Node *node, int espacos) {
    if (node == NULL) return;

    espacos += 10;
    imprimirArvoreRecursivo(node->direita, espacos);
    printf("\n");

    int i;
    for (i = 10; i < espacos; i++) {
        printf(" ");
    }

    if (espacos > 10) { 
        printf("|--- ");
    } else {
        printf("> ");
    }

    printf("[%d] %s\n", node->aluno.matricula, node->aluno.nome);
    imprimirArvoreRecursivo(node->esquerda, espacos);
}
void mostrarArvore(Arvore *arvore) {
    if (arvore == NULL || arvore->raiz == NULL) {
        printf("A arvore esta vazia!\n");
    } else {
        printf("\n------------- ESTRUTURA DA ARVORE (AVL) -------------\n");
        imprimirArvoreRecursivo(arvore->raiz, 0);
        printf("\n-----------------------------------------------------\n");
    }
}

main() {
    Arvore *arvoreAlunos = criarArvore();
    int opcao, codigoBuscado, i;

    Aluno iniciais[] = {
        {10, "Alice"},
        {20, "Bruno"},
        {30, "Caio"},
        {15, "Debora"},
        {25, "Erick"},
        {5,  "Fabio"}
    };

    int n = sizeof(iniciais) / sizeof(iniciais[0]);
    for (i = 0; i < n; i++) {
        arvoreAlunos->raiz = inserir(arvoreAlunos->raiz, iniciais[i]);
    }

    while (true) {
        printf("1 - Inserir Aluno\n");
        printf("2 - Remover Aluno\n");
        printf("3 - Buscar Aluno\n");
        printf("4 - Imprimir Arvore\n");
        printf("5 - Sair\n");
        printf("Escolha uma opcao: \n");
        scanf("%i", &opcao);

        system("cls");
        if (opcao == 5){
            printf("SAINDOO.....");
            break;
        }

        switch (opcao) {
            case 1:
                arvoreAlunos->raiz = inserir(arvoreAlunos->raiz, criarAluno());
                break;
            case 2:
                printf("Matricula para remover: "); 
                scanf("%i", &codigoBuscado);

                arvoreAlunos->raiz = remover(arvoreAlunos->raiz, codigoBuscado);
                break;
            case 3:
                printf("Matricula para buscar: "); 
                scanf("%i", &codigoBuscado);
                
                buscar(arvoreAlunos->raiz, codigoBuscado);
                break;
            case 4:
                mostrarArvore(arvoreAlunos);
                break;
        }

        limparTela();
    }
}
