# 🌳 Árvore AVL (Self-Balancing Binary Search Tree)

Este projeto implementa uma **Árvore AVL**, uma evolução da Árvore Binária de Busca (BST) que garante eficiência máxima através do **autobalanceamento**. O sistema é voltado para o gerenciamento de um cadastro de alunos, onde a estrutura se reorganiza automaticamente a cada inserção ou remoção.

## 🛠️ Funcionamento do Código

O sistema utiliza a **matrícula** do aluno como chave de ordenação e equilíbrio:
* **Balanceamento Automático:** A cada operação, a árvore calcula o **Fator de Equilíbrio** de cada nó. Se a diferença de altura entre as subárvores for maior que 1, o sistema dispara rotações automáticas.
* **Rotações Dinâmicas:** Implementa os quatro tipos de rotação (Simples à Direita, Simples à Esquerda, Dupla à Direita e Dupla à Esquerda) para corrigir inclinações e alinhar a estrutura.
* **Remoção de Alta Complexidade:** Trata a remoção de nós garantindo que, mesmo após a exclusão de um nó com dois filhos, a árvore encontre um substituto adequado (menor nó da direita) e se reequilibre imediatamente.
* **Visualização Lateral:** Inclui uma função de impressão recursiva que desenha a hierarquia no console, facilitando o acompanhamento das rotações em tempo real.

## 💡 Conceitos de ED-II Aplicados

### 1. Fator de Equilíbrio ($fb$)
A árvore mantém a propriedade AVL onde para cada nó $u$, a diferença de altura entre as subárvores esquerda e direita respeita:
$$|fb(u)| \le 1$$
Isso impede que a árvore se torne "degenerada" (vire uma lista encadeada), garantindo que a altura seja sempre $O(\log n)$.

### 2. Rotações (Rebalanceamento)
Diferente de uma árvore binária comum, a AVL é "exigente" com sua estrutura. Ela identifica onde o peso está acumulado usando as direções **L (Left/Esquerda)** e **R (Right/Direita)** e aplica correções automáticas:

* **Rotações Simples (Casos LL e RR):** Aplicadas quando a árvore pende para um lado só, formando uma **linha reta**.
  - **LL (Esquerda-Esquerda):** O peso está todo à esquerda. O sistema realiza uma rotação para a direita para equilibrar.
  - **RR (Direita-Direita):** O peso está todo à direita. O sistema realiza uma rotação para a esquerda.

* **Rotações Duplas (Casos LR e RL):** Aplicadas quando os nós formam um **"zigue-zague"** (um "cotovelo" na estrutura).
  - **LR (Esquerda-Direita):** O nó pai pende para a esquerda, mas o filho pende para a direita. O sistema primeiro alinha o filho e depois rotaciona o pai.
  - **RL (Direita-Esquerda):** O nó pai pende para a direita, mas o filho pende para a esquerda. Também exige dois movimentos para trazer o centro de gravidade de volta ao meio.

### 3. Custo Computacional Otimizado
Enquanto uma  árvore binária comum pode levar $O(n)$ em operações de busca no pior caso (árvore zig-zag ou linear), a AVL garante que, mesmo com milhares de registros, qualquer operação termine em tempo logarítmico.

### 4. Recursividade e Ponteiros
O projeto faz uso intensivo de recursão para navegação na árvore e manipulação de ponteiros duplos para garantir que as alterações de endereço feitas nas rotações reflitam corretamente em toda a estrutura.

---
*Implementação desenvolvida como parte dos estudos práticos de Estruturas de Dados II.*