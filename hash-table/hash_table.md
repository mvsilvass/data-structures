# 🗄️ Tabela Hash (DJB2 & Doubly Linked List)

Este projeto implementa uma **Tabela Hash** de alta performance desenvolvida em linguagem C para o armazenamento e busca de uma base de dados massiva, contendo mais de **100 mil nomes**. O sistema foca na eficiência de dispersão e no tratamento robusto de colisões, utilizando uma combinação de algoritmos clássicos e estruturas dinâmicas para garantir performance mesmo com grandes volumes de dados.

## 🛠️ Funcionamento do Código

O sistema utiliza a técnica de **Encadeamento Externo** para garantir a integridade dos dados, mesmo com grandes volumes de inserção:
* **Algoritmo de Dispersão:** Utiliza a função **DJB2**, reconhecida por sua eficiência e excelente capacidade de distribuição de chaves.
* **Tratamento de Colisões:** Implementa **Listas Duplamente Encadeadas** em cada balde (bucket). Isso permite que elementos que colidem sejam armazenados diretamente na lista correspondente, facilitando a inserção e remoção.
* **Ordenação Interna:** O código permite a organização dos dados dentro dos baldes através do algoritmo **Quick Sort**.
* **Análise Estatística:** O sistema monitora a uniformidade da distribuição através de métricas como variância e desvio padrão.

## 💡 Conceitos de Estrutura de Dados Aplicados

### 1. Eficiência do Hashing (DJB2)
A tabela foi estruturada com **43 baldes**, número definido após testes mostrarem que este valor apresentava a melhor distribuição para o conjunto de dados. A função DJB2 garante que as chaves sejam dispersas de maneira uniforme, evitando sobrecarga em baldes específicos.

### 2. Hipótese do Hashing Uniforme
O projeto valida a teoria de que cada chave tem a mesma probabilidade de ocupar qualquer balde. Os resultados estatísticos comprovam a eficiência da implementação:
* **Uniformidade:** **0,9998** (valores próximos de 1 indicam distribuição altamente uniforme).
* **Desvio Padrão:** **36,9178**, um valor extremamente baixo considerando a média de 2343,9 elementos por balde.
* **Diferença entre Baldes:** A variação entre o balde mais cheio e o mais vazio é de apenas **161 elementos**.

### 3. Distribuição Visual (Histograma)
O sistema gera um histograma onde a semelhança na altura das barras evidencia visualmente o equilíbrio da estrutura. Isso garante que as operações de busca, inserção e remoção mantenham um tempo de execução estável.

### 4. Gestão de Memória Dinâmica
Através do encadeamento duplo, cada balde cresce dinamicamente conforme a necessidade, mantendo o acesso rápido e permitindo uma solução robusta e escalável.



## 📂 Documentação Adicional
O relatório técnico detalhado, contendo os gráficos de colunas e a análise completa dos testes, está disponível no link abaixo:
* [📄 Relatório Técnico (PDF)](./Relatório.pdf)

---
*Implementação desenvolvida para a disciplina de Estruturas de Dados I.*