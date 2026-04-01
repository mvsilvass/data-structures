# 🔍 Busca Binária em Sistema de Fila (Library Manager)

Este projeto demonstra a implementação do algoritmo de **Busca Binária** aplicado a uma **Fila Dinâmica** de livros. O objetivo é mostrar como otimizar a recuperação de dados mesmo em estruturas que, por padrão, não permitem acesso aleatório.

## 🛠️ O que o código faz?

O programa gerencia uma fila de livros (**FIFO - First In, First Out**) e permite as seguintes operações:

* **Inserção e Remoção:** Controle dinâmico de nós utilizando ponteiros e alocação de memória com `malloc` e `free`.
* **Busca Otimizada:** Implementação de busca binária para localizar livros através de seus códigos identificadores.
* **Conversão de Estrutura:** Para aplicar a busca binária, a fila (dinâmica) é convertida temporariamente em um vetor (estático), permitindo o cálculo do índice médio e o acesso aleatório necessário para o algoritmo.

## 💡 Conceitos de Destaque

### 1. Busca Binária $O(\log n)$
Diferente da busca linear, que verifica item por item, este algoritmo divide a lista ao meio a cada passo. No código, isso é feito após a transferência dos códigos dos livros para um array, garantindo uma performance muito superior em grandes volumes de dados.

### 2. Fila Dinâmica (Queue)
A estrutura principal utiliza ponteiros `head` (cabeça) e `tail` (cauda). Isso permite que a inserção de um novo livro seja extremamente rápida, com complexidade de tempo constante **$O(1)$**.

### 3. Tratamento de Múltiplos Registros
O algoritmo foi adaptado para encontrar **todas** as ocorrências de um código específico, percorrendo os vizinhos do elemento encontrado caso existam livros com o mesmo identificador na fila.

---

*Implementação desenvolvida como parte dos estudos práticos de Estruturas de Dados I.*