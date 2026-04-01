#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

typedef struct Livro
{
    char codigo[15]; // ISSN/ISBN
    char nome[100];
} Livro;

typedef struct Node
{
    Livro livro;
    struct Node *direita;
    struct Node *esquerda;
} Node;

typedef struct Arvore
{
    Node *raiz;
} Arvore;

void limparTela()
{
    printf("\nAperte qualquer tecla para continuar....");
    getch();
    system("cls");
}

Node *criarNode(Livro livro)
{
    Node *novoNode = (Node *)malloc(sizeof(Node));
    novoNode->livro = livro;
    novoNode->esquerda = NULL;
    novoNode->direita = NULL;

    return novoNode;
}

Arvore *criarArvore()
{
    Arvore *arvore = (Arvore *)malloc(sizeof(Arvore));
    arvore->raiz = NULL;

    return arvore;
}

Livro criarLivro()
{
    Livro novoLivro;

    printf("\nInsira o codigo ISSN/ISBN do livro: \n");
    scanf(" %[^\n]", &novoLivro.codigo);

    printf("\nInsira o nome do livro: \n");
    scanf(" %[^\n]", &novoLivro.nome);

    return novoLivro;
}

void liberarNode(Node *node)
{
    if (node != NULL)
    {
        liberarNode(node->esquerda);
        liberarNode(node->direita);
        free(node);
    }
}

void liberarArvore(Arvore *arvore)
{
    if (arvore != NULL)
    {
        liberarNode(arvore->raiz);
        free(arvore);
    }
}

void inserirLivro(Arvore *arvore, Livro livro)
{
    Node *novoNode = criarNode(livro);

    if (arvore->raiz == NULL)
    {
        arvore->raiz = novoNode;
    }
    else
    {
        Node *currentNode = arvore->raiz;
        Node *nextNode = NULL;

        while (currentNode != NULL)
        {
            nextNode = currentNode;

            if (strcmp(livro.codigo, currentNode->livro.codigo) <= 0)
            {
                currentNode = currentNode->esquerda;
            }
            else
            {
                currentNode = currentNode->direita;
            }
        }

        if (strcmp(livro.codigo, nextNode->livro.codigo) <= 0)
        {
            nextNode->esquerda = novoNode;
        }
        else
        {
            nextNode->direita = novoNode;
        }
    }
}

Node *encontrarMinimo(Node *node)
{
    Node *atual = node;

    while (atual && atual->esquerda != NULL)
    {
        atual = atual->esquerda;
    }

    return atual;
}

Node *removerNode(Node *raiz, char *codigo)
{
    if (raiz == NULL)
        return NULL;

    int cmp = strcmp(codigo, raiz->livro.codigo);

    if (cmp < 0)
    {
        raiz->esquerda = removerNode(raiz->esquerda, codigo);
    }
    else if (cmp > 0)
    {
        raiz->direita = removerNode(raiz->direita, codigo);
    }
    else
    {

        // Caso 1: Nó com 0 ou 1 filho
        if (raiz->esquerda == NULL)
        {
            Node *temp = raiz->direita;
            free(raiz);

            return temp;
        }
        else if (raiz->direita == NULL)
        {
            Node *temp = raiz->esquerda;
            free(raiz);

            return temp;
        }

        // CASO 2: Dois filhos
        Node *temp = encontrarMinimo(raiz->direita);
        raiz->livro = temp->livro;
        raiz->direita = removerNode(raiz->direita, temp->livro.codigo);
    }

    return raiz;
}

void imprimirArvoreRecursivo(Node *raiz, int espacos)
{
    if (raiz == NULL)
    {
        return;
    }

    espacos += 12;

    imprimirArvoreRecursivo(raiz->direita, espacos);

    printf("\n");
    int i;
    for (i = 12; i < espacos; i++)
    {
        printf(" ");
    }

    if (espacos > 12)
    {
        printf("|---------- ");
    }

    printf("[%s] %s\n", raiz->livro.codigo, raiz->livro.nome);

    imprimirArvoreRecursivo(raiz->esquerda, espacos);
}

void mostrarArvore(Arvore *arvore)
{
    if (arvore == NULL || arvore->raiz == NULL)
    {
        printf("A arvore esta vazia!\n");
    }
    else
    {
        printf("\n------------- ESTRUTURA DA ARVORE  -------------\n");
        imprimirArvoreRecursivo(arvore->raiz, 0);
        printf("\n------------------------------------------------\n");
    }
}

void buscarLivro(Arvore *arvore, char *codigo)
{
    Node *currentNode = arvore->raiz;
    Node *nextNode = NULL;

    while (currentNode != NULL)
    {
        nextNode = currentNode;

        if (strcmp(codigo, currentNode->livro.codigo) == 0)
        {
            system("cls");
            printf("Livro Encontrado: %s - %s\n", currentNode->livro.codigo, currentNode->livro.nome);
            return;
        }

        if (strcmp(codigo, currentNode->livro.codigo) < 0)
        {
            currentNode = currentNode->esquerda;
        }
        else
        {
            currentNode = currentNode->direita;
        }
    }

    printf("Livro com codigo %s nao encontrado.\n", codigo);
}

void percorrerPreOrdem(Node *raiz)
{
    if (raiz != NULL)
    {
        printf("[%s] %s\n", raiz->livro.codigo, raiz->livro.nome);
        percorrerPreOrdem(raiz->esquerda);
        percorrerPreOrdem(raiz->direita);
    }
}

void percorrerEmOrdem(Node *raiz)
{
    if (raiz != NULL)
    {
        percorrerEmOrdem(raiz->esquerda);
        printf("[%s] %s\n", raiz->livro.codigo, raiz->livro.nome);
        percorrerEmOrdem(raiz->direita);
    }
}

void percorrerPosOrdem(Node *raiz)
{
    if (raiz != NULL)
    {
        percorrerPosOrdem(raiz->esquerda);
        percorrerPosOrdem(raiz->direita);
        printf("[%s] %s\n", raiz->livro.codigo, raiz->livro.nome);
    }
}

main()
{
    Arvore *arvoreLivros = criarArvore();
    char buscaCodigo[15];
    int opcao;

    Livro l1 = {"978-04", "Matrix"};
    Livro l2 = {"978-02", "Interestelar"};
    Livro l3 = {"978-06", "O Senhor dos Aneis"};
    Livro l4 = {"978-01", "O Poderoso Chefao"};
    Livro l5 = {"978-03", "Blade Runner"};
    Livro l6 = {"978-05", "Duna"};
    Livro l7 = {"978-07", "Neuromancer"};

    inserirLivro(arvoreLivros, l1);
    inserirLivro(arvoreLivros, l2);
    inserirLivro(arvoreLivros, l3);
    inserirLivro(arvoreLivros, l4);
    inserirLivro(arvoreLivros, l5);
    inserirLivro(arvoreLivros, l6);
    inserirLivro(arvoreLivros, l7);

    while (true)
    {
        printf("------------ MENU ------------\n");
        printf("1 - Inserir livro; \n");
        printf("2 - Remover livro; \n");
        printf("3 - Buscar livro; \n");
        printf("4 - Percorrer Pre-ordem; \n");
        printf("5 - Percorrer Em-ordem; \n");
        printf("6 - Percorrer Pos-ordem; \n");
        printf("7 - Imprimir arvore; \n");
        printf("8 - Sair do programa. \n\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);

        system("cls");
        if (opcao == 8)
        {
            liberarArvore(arvoreLivros);
            printf("SAINDOOO.....");
            break;
        }

        switch (opcao)
        {

        case 1:
            inserirLivro(arvoreLivros, criarLivro());
            break;

        case 2:
            printf("Digite o codigo para remover: \n");
            scanf(" %s", &buscaCodigo);

            removerNode(arvoreLivros->raiz, buscaCodigo);
            break;

        case 3:
            printf("Digite o codigo para remover: \n");
            scanf(" %s", &buscaCodigo);

            buscarLivro(arvoreLivros, buscaCodigo);
            break;
        case 4:
            mostrarArvore(arvoreLivros);
            printf("--- PERCURSO PRE-ORDEM ---\n");
            percorrerPreOrdem(arvoreLivros->raiz);
            printf("\n");
            break;
        case 5:
            mostrarArvore(arvoreLivros);
            printf("--- PERCURSO EM-ORDEM ---\n");
            percorrerEmOrdem(arvoreLivros->raiz);
            printf("\n");
            break;
        case 6:
            mostrarArvore(arvoreLivros);
            printf("--- PERCURSO POS-ORDEM ---\n");
            percorrerPosOrdem(arvoreLivros->raiz);
            printf("\n");
            break;
        case 7:
            mostrarArvore(arvoreLivros);
            break;

        default:
            printf("Opcao invalida...\n");
            break;
        }

        limparTela();
    }
}