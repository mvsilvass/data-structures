# 👥 Fila Dinâmica com Prioridade (Queue)

Este projeto implementa um sistema de gerenciamento de filas de atendimento, utilizando **Filas Dinâmicas** para separar e organizar o fluxo entre usuários prioritários e comuns.

## 🛠️ Funcionamento do Sistema

O diferencial deste código é a gestão inteligente de duas filas simultâneas:
1. **Fila Prioritária:** Destinada a pessoas que possuem direito a atendimento preferencial.
2. **Fila Comum:** Destinada ao fluxo normal de atendimento.

### Regra de Negócio (Escalonamento)
O sistema aplica uma política de atendimento onde a **Fila Prioritária tem precedência total**. Uma pessoa da fila comum só será chamada para atendimento se não houver ninguém aguardando na fila prioritária.

## 💡 Conceitos de Estrutura de Dados

* **FIFO (First In, First Out):** Princípio fundamental de fila onde o primeiro a entrar é o primeiro a ser servido.
* **Nós Dinâmicos (Nodes):** Cada pessoa inserida gera um novo nó na memória via `malloc`, permitindo que a fila não tenha um tamanho fixo.
* **Ponteiros Head e Tail:** O uso de ponteiros para o início (head) e fim (tail) da fila garante que a inserção de novos elementos ocorra em tempo constante **$O(1)$**.

## 🚀 Funcionalidades

* **Inserção Setorizada:** Identifica o tipo de usuário e o aloca na fila correta.
* **Remoção com Regra de Prioridade:** Automatiza quem deve ser o próximo atendido baseado no status.
* **Verificação de Estado:** Funções para calcular o tamanho total das filas e verificar se estão vazias.
* **Limpeza de Memória:** Função dedicada para percorrer as filas e liberar (`free`) todos os nós alocados.

---
*Implementação desenvolvida como parte dos estudos práticos de Estruturas de Dados I.*