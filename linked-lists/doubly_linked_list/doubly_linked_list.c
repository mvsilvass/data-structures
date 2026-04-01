#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

int codigoPedido = 0;
typedef struct Pedido{
    int id;
    int quantProdutos;
}Pedido;

typedef struct Node{
    Pedido dadosPedido;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct Lista{
    Node *head;
    Node *tail;
    int size;
}Lista;

Lista* criarLista(){
    Lista *lista = (Lista *)malloc(sizeof(Lista)); 
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;

    return lista;
}

Node* criarNode(Pedido dadosPedido){
    Node *novoNode = (Node *)malloc(sizeof(Node));

    novoNode->dadosPedido = dadosPedido;
    novoNode->next = NULL;
    novoNode->prev = NULL;

    return novoNode; 
}

Pedido criarPedido(){
    Pedido novoPedido;

    printf("\nInsira a quantidade de produtos: \n");
    scanf("%i", &novoPedido.quantProdutos);

    novoPedido.id = codigoPedido + 1;

    return novoPedido;
}

void liberarLista(Lista* lista){
    Node *currentNode = lista->tail;
    Node *prevNode; 

    while(currentNode != NULL){
        prevNode = currentNode; 
        currentNode = currentNode->prev;
        
        free(prevNode);
    }

    free(lista);
}

void inserirPedido(Lista* lista, Pedido dadosPedido){
    Node *novoNode = criarNode(dadosPedido);
    int posicao, i;

    printf("\nInsira a posicao que deseja inserir:\n");
    scanf("%i", &posicao);

    if(posicao < 1 || posicao > (lista->size + 1)){
        printf("\nPosicao invalida!\n");
    }else{
        if(posicao == 1){
            if(lista->head == NULL){
                lista->head = novoNode;
                lista->tail = novoNode;
            }else{ 
                lista->head->prev = novoNode;
                novoNode->next = lista->head;
                lista->head = novoNode;
            }
        }else if(posicao == (lista->size + 1)){
            lista->tail->next = novoNode;
            novoNode->prev = lista->tail;
            lista->tail = novoNode;
        }else{
            Node *currentNode = lista->head;
            Node *nextNode;
            
            for(i = 1; i < (posicao - 1); i++){
                currentNode = currentNode->next;
            }

            nextNode = currentNode->next;

            novoNode->prev = currentNode;
            novoNode->next = nextNode;

            nextNode->prev = novoNode;
            currentNode->next = novoNode;

        }
        
        lista->size++;
        codigoPedido++;
    }
}

Node* buscarPedido(Lista* lista, int codigo){
    Node *currentNode = lista->head;

    while(currentNode != NULL){
        if(currentNode->dadosPedido.id == codigo){
            return currentNode;
        }

        currentNode = currentNode->next;
    }

    return NULL;
}

void removerPedido(Lista* lista, Node* pedidoParaRemover){
    Node *prev = pedidoParaRemover->prev;
    Node *next = pedidoParaRemover->next;

    if(prev == NULL){
        lista->head = next;
        if(next != NULL) {
            next->prev = NULL;
        }

    }else{
        prev->next = next;
    }

    if(next == NULL){
        lista->tail = prev;
        if(prev != NULL){
            prev->next = NULL;
        }

    }else{
        next->prev = prev;
    }

    free(pedidoParaRemover);
    lista->size--; 
}

void imprimirPedido(Node* nodePedido){
    printf("--------------------------------------------\n");
    printf("\t  DETALHES DO PEDIDO\t\t\n");
    printf("--------------------------------------------\n");
    printf("Codigo do pedido: #00000%i\n", nodePedido->dadosPedido.id);
    printf("Quant de produtos: %i\n", nodePedido->dadosPedido.quantProdutos);
    printf("--------------------------------------------\n");
}

void imprimirLista(Lista* lista){
    Node *currentNode = lista->head;

    printf("------ LISTA DE PEDIDOS (tamanho = %d) ------\n\n", lista->size);
    while(currentNode != NULL){
        printf("--------------------------------------------\n");
        printf("Codigo do pedido: #00000%i\n", currentNode->dadosPedido.id);
        printf("Quant de produtos: %i\n", currentNode->dadosPedido.quantProdutos);

        currentNode = currentNode->next;
    }

    printf("--------------------------------------------\n");
}

void limparTela(){
    printf("\n--------------------------------------------\n");
    printf("Pressione qualquer tecla para continuar...   ");
    printf("\n--------------------------------------------\n");
    getch();
    getchar();
    system("cls");
}

main(){
    Lista *listaDePedidos = criarLista();
    int opcao, codigo;

    while(true){
        printf("------ MENU ------\n");
        printf("1 - Inserir pedido; \n");
        printf("2 - Remover pedido; \n");
        printf("3 - Buscar pedido; \n");
        printf("4 - Imprimir pedidos; \n");
        printf("5 - Sair do programa. \n\n");
        printf("Escolha uma opcao: \n");
        scanf("%i", &opcao);

        system("cls");
        if(opcao == 5){
            printf("\nSAINDOO............\n");
            liberarLista(listaDePedidos);
            break;
        }

        if(opcao == 1){
            inserirPedido(listaDePedidos, criarPedido());
        }else if(opcao >= 2 && opcao <= 5){
            if(listaDePedidos->head != NULL){
                if(opcao == 2){
                    printf("\nInsira o codigo que deseja remover: \n");
                    scanf("%i", &codigo);

                    Node *pedidoParaRemover = buscarPedido(listaDePedidos, codigo);
                    char confirmacao;
                    
                    system("cls");
                    if(pedidoParaRemover != NULL){
                        imprimirPedido(pedidoParaRemover);
                        printf("\nDeseja remover esse pedido? (S ou N) \n");
                        scanf(" %c", &confirmacao);
                        
                        system("cls");
                        if(confirmacao == 'S' || confirmacao == 's'){
                            removerPedido(listaDePedidos, pedidoParaRemover);
                            printf("\nPedido removido com sucesso!\n");
                        }else if(confirmacao == 'N' || confirmacao == 'n'){
                            printf("\nNada foi removido...\n");
                        }else{
                            printf("\nEntrada invalida! Nada foi removido...\n");
                        }
                        
                    }else{
                        printf("\nPedido nao encontrado!\n");
                    }


                }else if(opcao == 3){
                    printf("\nInsira o codigo que deseja buscar: \n");
                    scanf("%i", &codigo);

                    Node *pedidoBuscado = buscarPedido(listaDePedidos, codigo);
                    
                    system("cls");
                    if(pedidoBuscado != NULL){
                        imprimirPedido(pedidoBuscado);
                    }else{
                        printf("\nPedido nao encontrado!\n");
                    }

                }else if(opcao == 4){
                    imprimirLista(listaDePedidos);
                }
            
            }else{
                printf("\nNenhum pedido cadrastrado!\n");
            }

        }else{
            printf("\nOpcao invalida!\n");
        }
        
        limparTela();
    }
}