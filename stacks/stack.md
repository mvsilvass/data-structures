# 📚 Pilha Dinâmica (Stack)

Este projeto implementa uma **Pilha Dinâmica** para o gerenciamento de cadastros de pessoas (CPF, Nome e Idade). A estrutura segue o princípio fundamental das pilhas: o último a entrar é o primeiro a sair.

## 🛠️ Funcionamento do Código

O diferencial desta implementação é a interface visual no console, que desenha as "caixas" e setas para representar graficamente o empilhamento dos dados.

* **Lógica LIFO (Last In, First Out):** As operações de inserção (`Push`) e remoção (`Pop`) acontecem sempre no topo da estrutura.
* **Validação de Dados:** O sistema inclui uma função de validação para garantir que não existam dois CPFs iguais dentro da mesma pilha.
* **Sistema de Consulta:** Permite localizar dados específicos por posição, nome ou CPF, percorrendo a estrutura a partir do topo.

## 💡 Conceitos Aplicados

### 1. O Topo (Head)
Diferente de uma fila, onde focamos no início e no fim, na pilha toda a atividade importante acontece no `head`. Quando uma nova pessoa é inserida, ela se torna o novo topo, e seu ponteiro `prev` aponta para a pessoa que estava lá antes.

### 2. Navegação e Busca
Embora a pilha seja feita para acessar apenas o topo, esta implementação demonstra como realizar buscas transversais para encontrar informações específicas sem desempilhar os elementos.
