#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

typedef struct Pessoa{
    bool isPrioridade;
    char nome[100];
}Pessoa;

typedef struct Node{
    Pessoa dadosPessoa;
    struct Node *next;
}Node;

typedef struct Fila{
    Node *head;
    Node *tail;

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

    return fila;
}

Pessoa criarPessoa(){
    Pessoa dadosPessoa;
    char resposta;

    printf("Qual o seu nome: \n");
    scanf(" %[^\n]s", dadosPessoa.nome); // Vetor/string → não usa &
    while (getchar() != '\n');

    do{
        printf("\nVoce e prioridade? (S ou N) \n");
        scanf(" %c", &resposta);

        if(resposta == 'S' || resposta == 's'){
            dadosPessoa.isPrioridade = true;
            break;
            
        }else if(resposta == 'N' || resposta == 'n'){
            dadosPessoa.isPrioridade = false;
            break;
        }
    

    }while(true);
    
    return dadosPessoa;
}

Node* criarNode(Pessoa dadosPessoa){
    Node* newNode = (Node *)malloc(sizeof(Node)); 

    newNode->dadosPessoa = dadosPessoa;
    newNode->next = NULL;

    return newNode;
}

void inserirPessoa(Pessoa dadosPessoa, Fila* filaComum, Fila* filaPrioritaria){
    Node* newNode = criarNode(dadosPessoa);

    if(newNode->dadosPessoa.isPrioridade){
        if(filaPrioritaria->head == NULL){
            filaPrioritaria->head = newNode;
            filaPrioritaria->tail = newNode;
        }else{
            filaPrioritaria->tail->next = newNode;
            filaPrioritaria->tail = newNode;
        }
    }else{
        if(filaComum->head == NULL){
            filaComum->head = newNode;
            filaComum->tail = newNode;
        }else{
            filaComum->tail->next = newNode;
            filaComum->tail = newNode;
        }
    }
}

void removerPessoa(Fila* fila){
    Node* removeNode = fila->head;
    fila->head = fila->head->next;

    free(removeNode);   
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

void imprimirFila(Fila* fila, char letra){
    Node* currentNode = fila->head;
    Node* nextNode;
    int codigo = 0;

    while(currentNode != NULL){
        nextNode = currentNode;
        
        printf("| 000%i%c - %s | ", ++codigo, letra, currentNode->dadosPessoa.nome);

        currentNode = currentNode->next;
    }
}

bool empty(Fila* fila){
    return fila->head == NULL;
}

int tamanho(Fila* fila){
    Node* currentNode = fila->head;
    Node* nextNode;

    int tamanho = 0;

    while(currentNode != NULL){
        nextNode = currentNode;
        currentNode = currentNode->next;
        
        tamanho++;
    }

    return tamanho;
}

main(){
    Fila* filaPrioritaria = criarFila();
    Fila* filaComum = criarFila();

    int opcao;

    while(true){
        system("cls");
        printf("===========  MENU  =========== \n\n");
        printf("1 - Insirir pessoa na fila; \n");
        printf("2 - Remover pessoa da fila;\n");
        printf("3 - Imprimir toda a fila; \n");
        printf("4 - Verificar se esta vazia; \n");
        printf("5 - Verificar o tamanho; \n");
        printf("6 - Sair do programa. \n");
        scanf("%i", &opcao);
        
        system("cls");
        if(opcao == 6){
            printf("Saindoooo....\n");
            liberarFila(filaPrioritaria);
            liberarFila(filaComum);
            break;
        }

        if(opcao == 1){
            inserirPessoa(criarPessoa(), filaComum, filaPrioritaria);
        }else if(opcao == 4){
            if(empty(filaComum) && empty(filaPrioritaria)){
                printf("\nFila esta vazia!\n");
            }else{
                printf("\nFila nao esta vazia!\n");
            }

        }else if(opcao >= 2 && opcao <= 5){
            if(empty(filaComum) && empty(filaPrioritaria)){
                printf("\nFila esta vazia!\n");
            }else{
                if(opcao == 2){
                    if(empty(filaPrioritaria)){
                        removerPessoa(filaComum);
                    }else{
                        removerPessoa(filaPrioritaria);
                    }
                    
                }else if(opcao == 3){
                    imprimirFila(filaPrioritaria, 'P');
                    imprimirFila(filaComum, 'C');
                    printf("\n");
                    
                }else{
                    int tamanhoTotal = tamanho(filaComum) + tamanho(filaPrioritaria);
                    printf("O tamanho atual da fila e: %i", tamanhoTotal);
                }
            }
        }else{
            printf("Opcao invalida!\n");
        }

        limparTela();
    }
}