# 🎞️ Lista Encadeada Simples (Singly Linked List)

Este projeto implementa um catálogo de filmes utilizando uma **Lista Encadeada Simples**. É uma estrutura de dados linear onde cada elemento (nó) aponta para o próximo, permitindo o armazenamento dinâmico de informações.

## 🛠️ Funcionamento do Código

O programa simula um gerenciador de filmes (nome e duração) e oferece controle total sobre a estrutura:
* **Inserção Flexível:** Permite adicionar filmes no início, no final ou em qualquer posição específica da lista.
* **Remoção Precisa:** É possível remover elementos de qualquer ponto da lista, com tratamento automático para manter a integridade dos ponteiros.
* **Navegação Linear:** Percorre a lista do `head` (início) até o `tail` (fim) para exibição dos dados.
* **Dados Pré-carregados:** O sistema já inicia com clássicos como *O Poderoso Chefão* e *Interestelar* para testes imediatos.

## 💡 Conceitos Aplicados

### 1. Nó (Node) Simples
Cada nó da lista contém os dados do filme e apenas **um ponteiro** (`*next`), que guarda o endereço de memória do próximo elemento. Diferente da lista dupla, aqui o caminho é unidirecional.

### 2. Gerenciamento de Memória
Demonstra o uso de alocação dinâmica com `malloc` e a importância da função `liberarLista`, que utiliza um ponteiro auxiliar para deletar os nós um a um, evitando vazamentos de memória (memory leaks).

### 3. Lógica de Encadeamento
A implementação foca na manipulação de ponteiros para "costurar" a lista novamente após inserções ou remoções no meio da estrutura, garantindo que nenhum dado seja perdido.

---
*Implementação desenvolvida como parte dos estudos práticos de Estruturas de Dados I.*