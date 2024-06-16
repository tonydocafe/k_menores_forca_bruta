# menores caminhos em um grafo 
Este script em C implementa um programa que cria um grafo direcionado ponderado, insere arestas nele e encontra os menores caminhos entre dois vértices, imprimindo os 
menores caminhos e seus custos. O programa também mede o tempo decorrido e o tempo de CPU usado durante a execução.

## Estruturas de Dados
#### Arestas

Estrutura que representa uma aresta no grafo com três campos sendo eles v1, v2  e peso .
#### Grafo

Estrutura que representa o grafo com dois campos é vtotal e matriz.
#### Caminho

Estrutura que representa um caminho no grafo com quatro campos sendo eles vertices, tamanho , custo e prox.
## Funções
#### CriaGrafo

Função que aloca memória e inicializa uma estrutura de grafo com um número especificado de vértices. A matriz de adjacência é inicializada com zeros.
#### AdicionaAresta

Função que adiciona uma aresta ao grafo, atualizando a matriz de adjacência com o peso da aresta entre dois vértices especificados.
#### insereCaminho

Função que insere um novo caminho em uma lista de caminhos, preservando a ordem dos custos.
#### imprimeKCaminhosMenores

Função que ordena os caminhos na lista pelo custo e imprime os caminhos de menor custo.
#### EncontraTodosCaminhosComCusto

Função recursiva que encontra todos os caminhos do vértice de origem ao vértice de destino, armazenando-os na lista de caminhos com seus respectivos custos.
#### foiVisitado

Função auxiliar que verifica se um vértice já foi visitado em um caminho atual, para evitar ciclos.
## Função Principal (main)
#### Leitura de Dados

Lê o número de vértices,
o número de arestas e o número
k (quantidade de menores caminhos a serem impressos).
#### Criação e Inicialização do Grafo

Cria o grafo com
V vértices e adiciona as arestas lidas.
#### Medição do Tempo de Execução

Marca o início do tempo de execução.
#### Busca e Impressão dos Caminhos

Encontra todos os caminhos do vértice de origem (0) ao vértice de destino (
V−1) e imprime os menores caminhos.
#### Liberação de Memória

Libera a memória alocada para o grafo e a lista de caminhos.
#### Medição do Tempo de CPU

Marca o fim do tempo de execução e calcula o tempo decorrido e o tempo de CPU utilizado.
## Saída
Caminhos
Imprime os menores caminhos encontrados, junto com seus custos.
Tempos
Imprime o tempo total decorrido e o tempo de CPU utilizado para a execução do programa.

## Execução

gcc força_bruta_test3.c -o executavel
./executavel 

4 4 2
1 2 10
1 3 15
2 4 10
3 4 5




- sendo numero de vertice/ arestas/ menores caminhos
- vertice /aresta/ peso
