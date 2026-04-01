#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <string.h>

#define LARGURA_CAIXA 20

int i;
typedef struct Pessoa{
    int cpf;
    char nome[50];
    int idade;
}Pessoa;

typedef struct Node{
    Pessoa dadosPessoa;
    struct Node *prev;
    struct Node *next;
}Node;

typedef struct Pilha{
    Node *head;
    int size;
}Pilha;

Pilha* criarPilha(){
    Pilha *pilha = (Pilha *)malloc(sizeof(Pilha));

    pilha->head = NULL;
    pilha->size = 0;

    return pilha;
}

Node* criarNode(Pessoa dadosPessoa){
    Node *novoNode = (Node *)malloc(sizeof(Node));

    novoNode->dadosPessoa = dadosPessoa;
    novoNode->prev = NULL;
    novoNode->next = NULL;

    return novoNode;
}

bool validarCPF(Pilha *pilha, int cpf){
    bool valido = true;

    Node *currentNode = pilha->head;
    while(currentNode != NULL){
        if(currentNode->dadosPessoa.cpf == cpf){
            valido = false;
        }

        currentNode = currentNode->prev;
    }

    return valido;
}

Pessoa criarPessoa(Pilha *pilha){
    Pessoa dadosPessoa;
    int cpf;

    printf("\nInsira seu CPF: \n");
    scanf("%i", &cpf);

    while(!validarCPF(pilha, cpf)){
        system("cls");
        printf("\nCPF invalido, insira seu novamente CPF:\n");
        scanf("%i", &cpf);
    }

    dadosPessoa.cpf = cpf;

    while (getchar() != '\n');
    printf("\nInsira seu nome: \n");
    scanf(" %[^\n]", &dadosPessoa.nome);

    printf("\nInsira a sua idade: \n");
    scanf("%i", &dadosPessoa.idade);

    return dadosPessoa;
}

bool isVazia(Pilha *pilha){
    if(pilha->head == NULL){
        return true;
    }

    return false;
}

// função de empilhar
void inserirPessoa(Pilha *pilha, Pessoa dadosPessoa){
    Node *novoNode = criarNode(dadosPessoa);

    if(pilha->head == NULL){
        pilha->head = novoNode;
    }else{
        novoNode->prev = pilha->head;
        pilha->head->next = novoNode;
        pilha->head = novoNode;
    }

    pilha->size++;
}

// função de desempilhar
void removerPessoa(Pilha *pilha){
    Node *currentNode = pilha->head;
    Node *prevNode = pilha->head->prev;
    
    pilha->head = prevNode;
    if(prevNode != NULL){
        prevNode->next = NULL;
    }

    free(currentNode);
    pilha->size--;
}

void borda() {
    printf("+");
    for (i = 0; i < LARGURA_CAIXA; i++) printf("-");
    printf("+\n");
}

void seta() {
    int meio = LARGURA_CAIXA/2;
    for (i = 0; i < meio; i++) printf(" ");
    printf("^\n");
    for (i = 0; i < meio; i++) printf(" ");
    printf("|\n");
}

void caixaNull() {
    borda();
    printf("| %-*s |\n", LARGURA_CAIXA-2, "NULL");
    borda();
}

void caixaPessoa(const char *nome, int idade, int cpf) {
    borda();
    printf("| CPF: %-*d |\n", LARGURA_CAIXA-7, cpf);
    printf("| Nome: %-*s |\n", LARGURA_CAIXA-8, nome);
    printf("| Idade: %-*d |\n", LARGURA_CAIXA-9, idade);
    borda();
}

void imprimirHead(Pilha *pilha){
    printf("=== TOPO DA PILHA ===\n\n");
    caixaPessoa(pilha->head->dadosPessoa.nome, pilha->head->dadosPessoa.idade, pilha->head->dadosPessoa.cpf);
}

void imprimirPilha(Pilha *pilha){
    Node *currentNode = pilha->head;
    
    printf("PILHA DE PESSOAS (size = %d)\n\n", pilha->size);

    caixaNull();
    if (currentNode != NULL) seta();

    while(currentNode != NULL){
        caixaPessoa(currentNode->dadosPessoa.nome, currentNode->dadosPessoa.idade, currentNode->dadosPessoa.cpf);
        
        currentNode = currentNode->prev;

        if(currentNode != NULL) seta();
    }
}

void liberarPilha(Pilha *pilha){
    Node *currentNode = pilha->head;
    Node *nextNode; // próximo para liberar

    while(currentNode != NULL){
        nextNode = currentNode;
        currentNode = currentNode->prev;

        free(nextNode);
    }

    free(pilha);
}

void limparTela(){
    printf("\nAperte qualquer tecla para continuar....");
    getch();
    system("cls");
}

void consultarPorPosicao(Pilha *pilha){
    int posicao;

    printf("\nInsira a posicao que deseja consultar:\n");
    scanf("%i", &posicao);
    
    if(posicao < 1){
        posicao = 1;
    }else if(posicao > pilha->size){
        posicao = pilha->size;
    }

    Node *currentNode = pilha->head;
    for(i = 0; i < (posicao - 1); i++){
        currentNode = currentNode->prev;
    }

    system("cls");
    printf("RESULTADO DA CONSULTA\n\n");
    caixaPessoa(currentNode->dadosPessoa.nome, currentNode->dadosPessoa.idade, currentNode->dadosPessoa.cpf);
}

void consultarPorNome(Pilha *pilha){
    int nomesEncontrados = 0;
    char nome[50];

    printf("\nInsira o nome que deseja consultar:\n");
    scanf(" %[^\n]s", &nome);

    system("cls");
    Node *currentNode = pilha->head;
    while(currentNode != NULL){
        if(strcmp(nome, currentNode->dadosPessoa.nome) == 0){
            nomesEncontrados++;

            if(nomesEncontrados == 1){
                printf("RESULTADO DA CONSULTA\n\n");
            }
            
            caixaPessoa(currentNode->dadosPessoa.nome, currentNode->dadosPessoa.idade, currentNode->dadosPessoa.cpf);
            printf("\n");
        }

        currentNode = currentNode->prev;
    }

    if(nomesEncontrados == 0){
        printf("Sem resultado!\n");
    }
}

void consultarPorCPF(Pilha *pilha){
    bool encontrado = false;
    int cpf;
    
    printf("\nInsira o CPF que deseja consultar:\n");
    scanf("%i", &cpf);

    system("cls");
    Node *currentNode = pilha->head;
    while(currentNode != NULL){
        if(currentNode->dadosPessoa.cpf == cpf){
            printf("RESULTADO DA CONSULTA\n\n");
            caixaPessoa(currentNode->dadosPessoa.nome, currentNode->dadosPessoa.idade, currentNode->dadosPessoa.cpf);
            printf("\n");

            encontrado = true;
            break;
        }

        currentNode = currentNode->prev;
    }

    if(!encontrado){
        printf("Sem resultado!\n");
    }

}

void consultar(Pilha *pilha){
    int opcao;

    while(true){
        printf("====== MENU DE CONSULTA ======\n\n");
        printf("1 - Consultar por posicao;\n");
        printf("2 - Consultar por nome;\n");
        printf("3 - Consultar por CPF;\n");
        printf("4 - Voltar ao menu inicial.\n");
        scanf("%i", &opcao);
        system("cls");
        
        if(opcao >= 1 && opcao <= 4){
            if(opcao == 1){
                consultarPorPosicao(pilha);
            }else if(opcao == 2){
                consultarPorNome(pilha);
            }else if(opcao == 3){
                consultarPorCPF(pilha);
            }else{
                printf("Voltando ao menu principal....\n");
            }

            break;
        }else{
            printf("\nOpcao invalida!!\n");
            limparTela();
        }
    }
}

main(){
    Pilha *pilhaDePessoas = criarPilha();
    int opcao;

    // Adicionando pessoas manualmente para iniciar a pilha
    Pessoa p1 = {54, "Ana", 25};
    Pessoa p2 = {31, "Ana", 25};
    Pessoa p3 = {45, "Carlos", 32};
    Pessoa p4 = {23, "Beatriz", 19};

    inserirPessoa(pilhaDePessoas, p1);
    inserirPessoa(pilhaDePessoas, p2);
    inserirPessoa(pilhaDePessoas, p3);
    inserirPessoa(pilhaDePessoas, p4);

    while(true){
        printf("========== MENU ==========\n\n");
        printf("1 - Verificar se esta vazia;\n");
        printf("2 - Inserir (empilhar); \n");
        printf("3 - Remover (desempilhar); \n");
        printf("4 - Verificar o topo; \n");
        printf("5 - Consultar pessoa; \n");
        printf("6 - Imprimir pessoas; \n");
        printf("7 - Sair do programa. \n\n");
        printf("Escolha uma opcao: \n");
        scanf("%i", &opcao);

        system("cls");
        if(opcao == 7){
            printf("SAINDOOOOO......\n");
            liberarPilha(pilhaDePessoas);
            break;
        }

        if(opcao == 1){
            if(isVazia(pilhaDePessoas)){
                printf("\nPilha esta vazia!!\n");
            }else{
                printf("\nPilha tem %i pessoas!!\n", pilhaDePessoas->size);
            }

        }else if(opcao == 2){
            inserirPessoa(pilhaDePessoas, criarPessoa(pilhaDePessoas));  

        }else if(opcao >= 3 && opcao <= 6){
            if(!isVazia(pilhaDePessoas)){
                if(opcao == 3){ 
                    removerPessoa(pilhaDePessoas);
                    printf("\nRemocao concluida!\n");
                }else if(opcao == 4){
                    imprimirHead(pilhaDePessoas);
                }else if(opcao == 5){
                    consultar(pilhaDePessoas);
                }else{
                    imprimirPilha(pilhaDePessoas);
                }

            }else{
                printf("\nPilha esta vazia!!\n");
            }
            
        }else{
            printf("\nOpcao invalida!!\n");
        }

        limparTela();
    }

}