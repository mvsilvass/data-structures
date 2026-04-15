#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <math.h> 

#define TAM_NOME 50
#define TAM_TABELA 43
#define TAM_BARRA 50 

// == LISTA ENCADEADA ==

typedef struct Node{
    char nome[TAM_NOME];
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

Node* criarNode(char *nome){
    Node *newNode = (Node *)malloc(sizeof(Node));

    strcpy(newNode->nome, nome);
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode; 
}

void inserirNoInicioDaLista(Lista *lista, char *nome) {
    Node *newNode = criarNode(nome);

    if (lista->head == NULL) {
        lista->head = newNode;
        lista->tail = newNode;
    }else {
        newNode->next = lista->head;
        lista->head->prev = newNode;
        lista->head = newNode;
    }

    lista->size++;
}

void inserirOrdenadoNaLista(Lista *lista, char *nome){
    Node *newNode = criarNode(nome);

    // 1. Caso: Lista vazia OU Inserção no início
    if (lista->head == NULL || strcmp(nome, lista->head->nome) < 0) {
        if (lista->head == NULL) {
            lista->head = newNode;
            lista->tail = newNode;
        } else {
            newNode->next = lista->head;
            lista->head->prev = newNode;
            lista->head = newNode;
        }
    } 
    
    // 2. Caso: Inserção no final
    else if (strcmp(nome, lista->tail->nome) >= 0) {
        lista->tail->next = newNode;
        newNode->prev = lista->tail;
        lista->tail = newNode;
    }
    
    // 3. Caso: Inserção no meio
    else {
        Node *current = lista->head->next;
        
        while (current != NULL && strcmp(current->nome, nome) < 0) { 
            current = current->next;
        }
        
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        
    }

    lista->size++;
}

bool removerDaLista(Lista *lista, char *nome) {
    Node *current = lista->head;

    // Percorre a lista para encontrar o nó com o nome
    while (current != NULL && strcmp(current->nome, nome) != 0) {
        current = current->next;
    }

    if (current != NULL) {

        // Se for o primeiro nó, atualiza a cabeça da lista.
        // Se não ajusta o ponteiro do nó anterior
        if (current->prev == NULL) {
            lista->head = current->next;  
        } else {
            current->prev->next = current->next;
        }

        // Se for o último nó, atualiza a cauda da lista
        // Se não ajusta o ponteiro do próximo nó
        if (current->next == NULL) {
            lista->tail = current->prev; 
        } else {
            current->next->prev = current->prev;
        }

        free(current);
        lista->size--;

       return true;
    }

    return false;
}

void imprimirLista(Lista* lista) {
    if (lista != NULL &&  lista->size >= 0) {
        Node *current = lista->head;
        int indexNome = 0;

        printf("========== LISTA DE NOMES (Total: %d) ==========\n\n", lista->size);

        while (current != NULL) {
            printf("(%04d) NOME: %s\n", indexNome, current->nome);
            current = current->next;
            indexNome++;
        }
        
    }else{
        printf("\nA lista esta vazia.\n");
    }
}

void liberarLista(Lista* lista){
    Node *current = lista->head;
    Node *next; 

    while(current != NULL){
        next = current; 
        current = current->next;
        
        free(next);
    }

    free(lista);
}

// ======= Quick Sort =======

void trocar(Node *a, Node *b) {
    char temp[100];

    strcpy(temp, a->nome);
    strcpy(a->nome, b->nome);
    strcpy(b->nome, temp);
}

Node* particionar(Node *head, Node *tail) {
    char pivo[100];
    strcpy(pivo, tail->nome);

    Node *i = head->prev;
    Node *j;

    for (j = head; j != tail; j = j->next) {

        // Verifica se j vem antes do pivô
        if (strcmp(j->nome, pivo) < 0) { 

            if (i == NULL) {
                i = head;
            } else {
                i = i->next;
            }

            trocar(i, j);
        }
    }

    Node *pivoFinal;

    if (i == NULL) {
        pivoFinal = head;
    } else {
        pivoFinal = i->next; 
    }

    trocar(pivoFinal, tail);

    return pivoFinal;
}

void quickSortLista(Node *head, Node *tail) {

    // Verifica se ainda tem mais de um elemento e existe para ordenar.
    if (tail != NULL && head != tail && head != tail->next) {
        Node *p = particionar(head, tail);
        quickSortLista(head, p->prev);
        quickSortLista(p->next, tail);
    }
}

// ======= Tabela Hash =======

// Declaração global da tabela hash 
// Todos os ponteiros já são inicializados como NULL por padrão
Lista *tabelaHash[TAM_TABELA];

// Função de hash (ALGORITMO DJB2)
unsigned long hash(const char *key) {
    unsigned long hash = 5381;
    int c;
    
    // Desloca os bits do hash 5 posições para a esquerda
    while ((c = *key++)) { 
        hash = ((hash << 5) + hash) + c;
    }

    return hash % TAM_TABELA;
}

void inserirNaTabela(char *nome) {
    unsigned long index = hash(nome);

    // cria lista no balde se estiver vazia
    if (tabelaHash[index] == NULL) {
        tabelaHash[index] = criarLista();
    }

    inserirNoInicioDaLista(tabelaHash[index], nome);
}

void inserirOrdenadoNaTabela(char *nome) {
    unsigned long index = hash(nome);

    // cria lista no balde se estiver vazia
    if (tabelaHash[index] == NULL) {
        tabelaHash[index] = criarLista();
    }

    inserirOrdenadoNaLista(tabelaHash[index], nome);

    printf("\n '%s' foi inserido com sucesso no balde numero %d.\n", nome, index);
}

void removerDaTabela(char *nome) {
    unsigned long index = hash(nome);
    Lista *lista = tabelaHash[index];

    if (lista != NULL && lista->head != NULL) {
        if (removerDaLista(lista, nome)) {
            printf("\n '%s' foi removido com sucesso do balde numero %lu.\n", nome, index);
        } else {
            printf("\n '%s' nao foi encontrado na tabela.\n", nome);
        }
    }else{
        printf("\n '%s' nao foi encontrado na tabela.\n", nome);
    }
    
}

int buscarNome(char *nome) {
    unsigned long index = hash(nome);
    Lista *lista = tabelaHash[index];

    if (lista == NULL || lista->head == NULL){
        return -1;
    } 

    Node *current = lista->head;
    while (current != NULL) {
        if (strcmp(current->nome, nome) == 0){
            return index;
        }

        current = current->next;
    }

    return -1;
}

void ordenaBaldes() {
    int i;

    for(i = 0; i < TAM_TABELA; i++){
        if(tabelaHash[i] != NULL && tabelaHash[i]->head != NULL){
            quickSortLista(tabelaHash[i]->head, tabelaHash[i]->tail);
        }
    }
}

void carregarNomes(char *arquivo) {
    FILE *file = fopen(arquivo, "r");

    if (!file) {
        printf("Erro ao abrir o arquivo!\n");
    }else{
        char nome[TAM_NOME];
            while (fgets(nome, TAM_NOME, file)) {
            nome[strcspn(nome, "\n")] = 0;

            inserirNaTabela(nome);
        }
    }

    fclose(file);
}

void liberarTabela(){
    int i;

    for(i = 0; i < TAM_TABELA; i++){
        if (tabelaHash[i] != NULL && tabelaHash[i]->head != NULL) {
            liberarLista(tabelaHash[i]);
            tabelaHash[i] = NULL;
        }
    }
}

int obterTamanhoDoMaiorBalde() {
    int maiorTamanho = 0;
    int i;
    
    for (i = 0; i < TAM_TABELA; i++) {
        if(tabelaHash[i] != NULL && tabelaHash[i]->size > maiorTamanho){
            maiorTamanho = tabelaHash[i]->size;
        }
    }

    return maiorTamanho;
}

int obterTamanhoDoMenorBalde() {
    int menorBalde = obterTamanhoDoMaiorBalde();
    int i;

    for (i = 0; i < TAM_TABELA; i++) {
        if(tabelaHash[i] != NULL && tabelaHash[i]->size < menorBalde){
            menorBalde = tabelaHash[i]->size;
        }
    }

    return menorBalde;
}

int obterTotalDeElementos(){
    int totalElementos = 0;
    int i;

    for (i = 0; i < TAM_TABELA; i++) {
        if (tabelaHash[i] != NULL){
            totalElementos += tabelaHash[i]->size;   
        } 
        
    }
    
    return totalElementos;
}

void mostrarHistograma() {
    int i, j;

    int tamanhoMaximo = obterTamanhoDoMaiorBalde(); 
    if (tamanhoMaximo == 0)  tamanhoMaximo = 1; 

    printf("========================== HISTOGRAMA ===========================\n\n");
    for (i = 0; i < TAM_TABELA; i++) {
        int quantidade = tabelaHash[i]->size;
        int barras = (quantidade * TAM_BARRA) / tamanhoMaximo;

        printf(" %02d (%d): ", i, quantidade);

        for (j = 0; j < barras; j++) {
            printf("*");
        }

        printf("\n");
    }

    printf("\n=================================================================\n\n");
    printf(" OBS: Cada * representa aproximadamente %.2f nomes\n", (float) tamanhoMaximo / TAM_BARRA);
}

void gerarRelatorio() {
    int maiorBalde = obterTamanhoDoMaiorBalde();
    int menorBalde = obterTamanhoDoMenorBalde();
    int totalElementos = obterTotalDeElementos();
    float media = (float) totalElementos / TAM_TABELA;
    int maiorDiferenca = maiorBalde - menorBalde;

    float somasDasDiferencas = 0;
    float somaQuadrados = 0;
    float diferenca;
    int tamanho, i;

    for (i = 0; i < TAM_TABELA; i++) {
        if (tabelaHash[i] != NULL){
            tamanho = tabelaHash[i]->size;     
            diferenca = tamanho - media;
            somaQuadrados +=  pow(diferenca, 2);
            somasDasDiferencas += fabs(diferenca);
        }

    }

    float variancia = somaQuadrados / TAM_TABELA;
    float desvioPadrao = sqrt(variancia);
    float uniformidade = 1.0f - (variancia / (media*media + 1));

    if(totalElementos >= 0){
        printf("=========================== RELATORIO ============================\n\n");
        printf(" Balde com mais elementos..............................: %04d\n", obterTamanhoDoMaiorBalde());
        printf(" Balde com menos elementos.............................: %04d\n", obterTamanhoDoMenorBalde());
        printf(" Maior diferenca entre baldes..........................: %04d\n", maiorDiferenca);
        printf(" Media de elementos por balde..........................: %.1f\n", media);
        printf(" Diferenca total da distribuicao.......................: %.1f\n\n", somasDasDiferencas);

        printf(" Variancia............................................: %.2f\n", variancia);
        printf(" Desvio padrao........................................: %.4f\n", desvioPadrao);
        printf(" Uniformidade (0 a 1).................................: %.4f\n\n", uniformidade);
    }else{
        printf(" A tabela esta vazia.\n");
    }
}

// ======= Utilitários =======
void limparTela(){
    printf("\n-----------------------------------------------------------------\n");
    printf(" Pressione qualquer tecla para continuar......   ");
    printf("\n-----------------------------------------------------------------\n");
    getch();
    getchar();
    system("cls");
}

main() {
    carregarNomes("nomes.txt");
    ordenaBaldes();
    
    int opcao;
    while(true){
        printf("============= MENU =============\n\n");
        printf(" 1 - Inserir nome na tabela;\n");
        printf(" 2 - Remover nome da tabela;\n");
        printf(" 3 - Buscar nome na tabela;\n");
        printf(" 4 - Imprimir nomes de um balde;\n");
        printf(" 5 - Exibir histograma;\n");
        printf(" 6 - Relatorio completo;\n");
        printf(" 7 - Sair do programa.\n\n");
        printf("================================\n\n");
        printf(" Escolha uma opcao: ");
        scanf("%i", &opcao);

        system("cls");
        if(opcao == 7){
            printf("\n SAINDOO.......\n");
            liberarTabela();
            break;
        }

        if(opcao == 1){
            char novoNome[TAM_NOME];

            printf("Digite o nome que deseja inserir: \n");
            scanf(" %[^\n]", novoNome);

            system("cls");
            inserirOrdenadoNaTabela(novoNome);
                    
        }else if(opcao == 2){
            char nomeParaRemover[TAM_NOME];

            printf("Digite o nome que deseja remover: \n");
            scanf(" %[^\n]", nomeParaRemover);

            system("cls");
            removerDaTabela(nomeParaRemover);
            
        }else if(opcao == 3){
            char nomeBusca[TAM_NOME];
            
            printf("Digite o nome que deseja buscar: \n");
            scanf(" %[^\n]", nomeBusca);

            system("cls");
            int balde = buscarNome(nomeBusca);
            if(balde >= 0){
                printf("\n '%s' foi encontrado no balde de numero %d.\n", nomeBusca, balde);
            }else{
                printf("\n '%s' nao foi encontrado na tabela.\n", nomeBusca);
            }

        }
        else if(opcao == 4){
            int numeroDoBalde;

            printf("Digite o numero do balde que deseja ver: \n");
            scanf("%i", &numeroDoBalde);

            system("cls");
            if (numeroDoBalde >= 0 && numeroDoBalde < TAM_TABELA) {
                imprimirLista(tabelaHash[numeroDoBalde]);
            } else {
                printf("\n Numero do balde invalido!\n");
            }
        }
        else if(opcao == 5){     
            mostrarHistograma();
        }
        else if(opcao == 6){
            gerarRelatorio();
            mostrarHistograma();
        }else{
            printf("\n Opcao invalida!\n");
        }

        limparTela();
    }
}