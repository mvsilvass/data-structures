#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Filme{
    char nome[100];
    int duracao;
}Filme;

typedef struct Node{
    Filme dadosFilme;
    struct Node *next;
}Node;

typedef struct Lista{
    Node *head;
    Node *tail;
    int size;
}Lista;

void limparTela(){
    printf("\nAperte qualquer tecla para continuar....");
    getch();
    system("cls");
}

Lista* criarLista(){
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;

    return lista;
}

Node* criarNode(Filme dadosFilme){
    Node *novoNode = (Node *)malloc(sizeof(Node));
    novoNode->dadosFilme = dadosFilme;
    novoNode->next = NULL;

    return novoNode;
}

void inserirNoFinalDaLista(Lista *lista, Filme dadosFilme){
    Node *novoNode = criarNode(dadosFilme);

    if(lista->head == NULL){
        lista->head = novoNode;
        lista->tail = novoNode;
    }else{
        lista->tail->next = novoNode;
        lista->tail = novoNode;
    }
    
    lista->size++;
}

void inserirNoInicioDaLista(Lista *lista, Filme dadosFilme){
    Node *novoNode = criarNode(dadosFilme);

    if(lista->head == NULL){
        lista->head = novoNode;
        lista->tail = novoNode;
    }else{
        novoNode->next = lista->head;
        lista->head = novoNode;
    }
    
    lista->size++;
}

void inserirEmUmaPosicaoEspecifica(Lista *lista, Filme dadosFilme){
    int posicao, i;

    do{
        printf("\nQual a posicao q deseja inserir? \n");
        scanf("%i", &posicao);

        if(posicao < 1 || posicao > lista->size){
            printf("Posicao invalida!! ");
            limparTela();
        } 

    }while(posicao < 1 || posicao > lista->size);
    system("cls");

    if(posicao == 1) {
        inserirNoInicioDaLista(lista, dadosFilme);

    }else if(posicao == lista->size){
        inserirNoFinalDaLista(lista, dadosFilme);

    }else{
        Node *novoNode = criarNode(dadosFilme);
        Node *current = lista->head;

        for(i = 0; i < (posicao - 1); i++){
            current = current->next;
        }
        
        novoNode->next = current->next;
        current->next = novoNode;

        lista->size++;
    }

}


void removerNoInicioDaLista(Lista *lista){
    Node *remover = lista->head;
    lista->head = lista->head->next;

    if(remover == lista->tail){
        lista->tail = NULL;
    }

    lista->size--;
    free(remover);
}

void removerNoFinalDaLista(Lista *lista){
    Node *currentNode = lista->head;
    Node *remover;

    if (lista->head->next == NULL){
        removerNoInicioDaLista(lista);
    }else{
        while(currentNode->next->next != NULL){
            currentNode = currentNode->next;
        }

        remover = currentNode->next;  
        currentNode->next = NULL;
        lista->tail = currentNode;

        lista->size--;
        free(remover);
    }
    
}

void removerEmUmaPosicaoEspecifica(Lista *lista){
    int posicao;
    int i;

    do{
        printf("\nQual a posicao q deseja remover? \n");
        scanf("%i", &posicao);

        if(posicao < 1 || posicao > lista->size){
            printf("Posicao invalida!! ");
            limparTela();
        } 

    }while(posicao < 1 || posicao > lista->size);
    system("cls");

    if(posicao == 1) {
        removerNoInicioDaLista(lista);
    }

    Node *current = lista->head;
    for(i = 1; i < (posicao - 1); i++){
        current = current->next;
    }

    Node *remover = current->next;
    current->next = remover->next;

    if(remover == lista->tail){
        lista->tail = current;
    }

    lista->size--;
    free(remover);
}

Filme criarFilme(){
    Filme novoFilme;

    printf("Qual o nome do filme? \n");
    scanf(" %[^\n]", &novoFilme.nome);

    printf("\nQual a duracao do filme em minutos? \n");
    scanf("%i",  &novoFilme.duracao);

    return novoFilme;
}

void imprimirLista(Lista *lista){
    Node *currentNode = lista->head;

    while(currentNode != NULL){
        printf("Nome:  %s\n", currentNode->dadosFilme.nome);
        printf("Duracao: %i\n", currentNode->dadosFilme.duracao);
        printf("----------------------------------\n");
 
        currentNode = currentNode->next;
    }
}

void liberarLista(Lista *lista){
    Node *currentNode = lista->head;
    Node *nextNode; 
    
    while(currentNode != NULL){
        nextNode = currentNode;
        currentNode = currentNode->next;

        free(nextNode);
    }

    free(lista);
}

main(){
    Lista *listaDeFilmes = criarLista();
    int opcao;

    Filme f1 = {"O Poderoso Chefao", 175};
    Filme f2 = {"Interestelar", 169};    
    Filme f3 = {"Matrix", 136};
    Filme f4 = {"O Senhor dos Aneis: A Sociedade do Anel", 178};

    inserirNoFinalDaLista(listaDeFilmes, f1);
    inserirNoFinalDaLista(listaDeFilmes, f2);
    inserirNoFinalDaLista(listaDeFilmes, f3);
    inserirNoFinalDaLista(listaDeFilmes, f4);

    while(true){
        printf("------ MENU ------\n");
        printf("1 - Inserir filme (no inicio da lista); \n");
        printf("2 - Inserir filme (no final da lista); \n");
        printf("3 - Inserir filme (posicao especifica); \n");
        printf("4 - Remover filme (no inicio da lista); \n");
        printf("5 - Remover filme (no final da lista); \n");
        printf("6 - Remover filme (posicao especifica); \n");
        printf("7 - Imprimir filmes; \n");
        printf("8 - Sair do programa. \n\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);

        system("cls");
        if(opcao == 8){
            liberarLista(listaDeFilmes);
            printf("SAINDOOO.....");
            break;
        }

        if(opcao == 1){
            inserirNoInicioDaLista(listaDeFilmes, criarFilme());
            limparTela();

        }else if(opcao == 2){
            inserirNoFinalDaLista(listaDeFilmes, criarFilme());
            limparTela();

        }else if(opcao == 3){
            inserirEmUmaPosicaoEspecifica(listaDeFilmes, criarFilme());
            limparTela();

        }else if(opcao >= 4 && opcao <= 7){
            if (listaDeFilmes->head == NULL) {
                printf("Nenhum filme encontrado...\n");

            }else{
                if (opcao >= 4 && opcao <= 6) {
                    char confirmacao;
                    printf("Deseja mesmo remover? (s/n): \n");
                    scanf(" %c", &confirmacao);

                    if(confirmacao == 's' || confirmacao == 'S'){
                        if(opcao == 4){
                            removerNoInicioDaLista(listaDeFilmes);

                        }else if(opcao == 5){
                            removerNoFinalDaLista(listaDeFilmes);
                            
                        }else if(opcao == 6){
                            removerEmUmaPosicaoEspecifica(listaDeFilmes);
                        }

                        printf("\nRemocao concluida!\n");

                    }else{
                        printf("\nOperacao cancelada.\n");
                    }

                }else if(opcao == 7){
                    imprimirLista(listaDeFilmes);
                }
            }

            limparTela();

        }else{
            printf("Opcao invalida...\n");
            limparTela();
        }

    }

}