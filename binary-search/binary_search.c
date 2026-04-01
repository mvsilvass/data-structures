#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

int codigo = 0;
typedef struct Livro{
    int codigo;
    char titulo[100];
}Livro;

typedef struct Node{
    Livro dadosLivro;
    struct Node *next;
}Node;

typedef struct Fila{
    Node *head;
    Node *tail;
    int size;
}Fila;

void limparTela(){
    printf("\nAperte qualquer tecla para continuar....\n");
    getch();
    system("cls");
}

Fila* criarFila(){
    Fila *fila = (Fila *)malloc(sizeof(Fila));

    fila->head = NULL;
    fila->tail = NULL;
    fila->size = 0;

    return fila;
}

Livro criarLivro(){
    Livro dadosLivro;

    dadosLivro.codigo = ++codigo;
    printf("Qual o titulo do livro: \n");
    scanf(" %[^\n]s", dadosLivro.titulo);
    
    return dadosLivro;
}

Node* criarNode(Livro dadosLivro){
    Node* newNode = (Node *)malloc(sizeof(Node)); 

    newNode->dadosLivro = dadosLivro;
    newNode->next = NULL;

    return newNode;
}

void liberarFila(Fila* fila){
    Node* currentNode = fila->head;
    Node* nextNode;

    while(currentNode != NULL){
        nextNode = currentNode;
        currentNode = currentNode->next;
        
        free(nextNode);
    }

    free(fila);
}

void imprimirFila(Fila* fila){
    Node* currentNode = fila->head;
    Node* nextNode;

    while(currentNode != NULL){
        nextNode = currentNode;
        
        printf("_________________________________________\n\n");
        printf(" Codigo: %03i\n", currentNode->dadosLivro.codigo);
        printf(" Titulo: %s\n", currentNode->dadosLivro.titulo);
        printf("_________________________________________\n");

        currentNode = currentNode->next;
    }
}

void inserirLivro(Fila* fila, Livro dadosLivro){
    Node* newNode = criarNode(dadosLivro);
    
    if(fila->head == NULL){
        fila->head = newNode;
        fila->tail = newNode;
    }else{
        fila->tail->next = newNode;
        fila->tail = newNode;
    }

    fila->size++;
}

void removerLivro(Fila* fila){
    Node* remover = fila->head;
    fila->head = fila->head->next;

    if (fila->head == NULL) {
        fila->tail = NULL;
    }

    free(remover);
    fila->size--;
}

void adicionarLivrosIniciais(Fila* fila){
    Livro dadosLivro;
    int i;

    char titulos[5][100] = {
        "O Senhor dos Aneis",
        "Dom Casmurro",
        "O Pequeno Principe",
        "A Revolucao dos Bichos",
        "Harry Potter e a Pedra Filosofal",
    };  

    for (i = 0; i < 5; i++) {
        if(i % 2 == 0) codigo++;
        dadosLivro.codigo = codigo;
        strcpy(dadosLivro.titulo, titulos[i]);
        inserirLivro(fila, dadosLivro);
    }
}

void buscaBinaria(Fila* fila, int codigoChave){
    // Converter a fila em um vetor
    int vetor[fila->size], i;
    Node* currentNode = fila->head;

    for(i = 0; i < fila->size; i++) {
        vetor[i] = currentNode->dadosLivro.codigo;
        currentNode = currentNode->next;
    }
    
    int fim = fila->size - 1;
    bool encontrado = false;
    int inicio = 0;
    int meio;

    while(inicio <= fim){
        meio = (inicio + fim) / 2;

        if(vetor[meio] == codigoChave){
            int j = meio - 1;
            while (j >= inicio && vetor[j] == codigoChave) {
                printf("%i\t", (j + 1));
                j--;
            }
            
            printf("%i\t", (meio + 1));
            
            j = meio + 1;
            while (j <= fim && vetor[j] == codigoChave) {
                printf("%i\t", (j + 1));
                j++;
            }

            encontrado = true;
            break;

        }else if(vetor[meio] > codigoChave){
            fim = meio - 1;
        }else{
            inicio = meio + 1;
        }
    }

    if(!encontrado){
        printf("Codigo nao encontrado!!");
    }
}

main(){
    Fila* filaDeLivros = criarFila();    
    adicionarLivrosIniciais(filaDeLivros);

    int opcao;
    while(true){
        system("cls");
        printf("======  MENU  ====== \n");
        printf("1 - Insirir livro;\n");
        printf("2 - Remover livro;\n");
        printf("3 - Buscar livro;\n");
        printf("4 - Imprimir tudo;\n");
        printf("5 - Sair do programa.\n");
        scanf("%i", &opcao);
        
        system("cls");
        if(opcao == 5){
            printf("Saindoooo....\n");
            liberarFila(filaDeLivros);
            break;
        }

        if(opcao == 1){
            inserirLivro(filaDeLivros, criarLivro());
        }else if(opcao >= 2 && opcao <= 4){
            if(filaDeLivros->head != NULL){
                if(opcao == 2){
                    removerLivro(filaDeLivros);
                }else if(opcao == 3){
                    int codigoBuscado;

                    printf("Qual codigo deseja buscar?\n");
                    scanf("%i", &codigoBuscado);
                    
                    printf("\nResultado da busca: ");
                    buscaBinaria(filaDeLivros, codigoBuscado);
                    printf("\n");
                
                }else{
                    imprimirFila(filaDeLivros);
                }

            }else{
                printf("Fila vazia!!\n");
            }
            
        }else{
            printf("Entrada invalida!!\n");
        }

        limparTela();
    }
}