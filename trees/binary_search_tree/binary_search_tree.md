# 🌳 Árvore Binária de Busca (Binary Search Tree)

Este projeto implementa uma **BST (Binary Search Tree)** para o gerenciamento de um acervo de livros. Diferente das estruturas lineares (listas e pilhas), a árvore organiza os dados de forma hierárquica, permitindo buscas e inserções extremamente eficientes.

## 🛠️ Funcionamento do Código

O sistema utiliza o código **ISSN/ISBN** dos livros como chave de ordenação:
* **Inserção Inteligente:** Livros com códigos "menores" seguem para a esquerda, e "maiores" para a direita, mantendo a árvore balanceada logicamente para buscas rápidas.
* **Remoção Recursiva:** Trata os três casos clássicos de remoção em árvores (nó folha, nó com um filho e nó com dois filhos).
* **Visualização Estrutural:** Inclui uma função que imprime a árvore de forma lateral no console, facilitando a visualização da hierarquia e dos níveis.

## 💡 Conceitos de ED-II Aplicados

### 1. Percursos (Traversals)
A implementação demonstra os três tipos fundamentais de caminhamento em árvores:
* **Pré-Ordem (Root, Left, Right):** Útil para copiar a árvore.
* **Em-Ordem (Left, Root, Right):** Resulta nos dados perfeitamente ordenados (crescente).
* **Pós-Ordem (Left, Right, Root):** Ideal para liberar a memória (delete) dos nós.

### 2. Recursividade
Quase todas as operações (remoção, impressão, percursos) utilizam recursão, que é a base para manipular estruturas não-lineares.

### 3. Busca Binária Dinâmica
Enquanto a busca binária em vetores exige que o array esteja previamente ordenado e tenha tamanho fixo, a BST permite que os dados cheguem em qualquer ordem e mantenham a propriedade de busca $O(\log n)$ em casos médios.

---
*Implementação desenvolvida como parte dos estudos práticos de Estruturas de Dados II.*