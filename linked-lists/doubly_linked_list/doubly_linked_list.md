# 🔗 Lista Duplamente Encadeada (Doubly Linked List)

Este projeto implementa um sistema de gerenciamento de pedidos utilizando uma **Lista Duplamente Encadeada**. Diferente de uma lista simples, cada nó aqui possui ponteiros para o próximo (`next`) e para o anterior (`prev`), permitindo a navegação em ambas as direções.

## 🛠️ Funcionamento do Código

O programa simula o controle de uma fila de pedidos de uma loja ou restaurante, permitindo:
* **Inserção por Posição:** Você pode escolher exatamente onde inserir o pedido (no início, no meio ou no fim da lista).
* **Busca Dinâmica:** Localiza pedidos específicos através do ID único.
* **Remoção Segura:** Remove um nó da memória e ajusta automaticamente os ponteiros dos vizinhos para não quebrar a corrente.
* **Navegação Bidirecional:** A estrutura permite percorrer a lista do início para o fim ou vice-versa.

## 💡 Conceitos Aplicados

### 1. Estrutura do Nó (Double Node)
Cada elemento da lista (`Node`) guarda:
* Os dados do pedido (ID e Quantidade).
* Um ponteiro `*next` para o sucessor.
* Um ponteiro `*prev` para o antecessor.

### 2. Manipulação de Ponteiros
A lógica de inserção e remoção em listas duplas é mais complexa e robusta, exigindo o cuidado de atualizar até 4 ponteiros em uma única operação para manter a integridade da lista.

### 3. Gestão de Memória
Uso de alocação dinâmica com `malloc` para cada novo pedido e uma função de liberação (`liberarLista`) que percorre a estrutura garantindo que nenhum "memory leak" aconteça.

---
*Implementação desenvolvida como parte dos estudos práticos de Estruturas de Dados I.*