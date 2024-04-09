#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/resource.h>
#include <sys/time.h>
typedef struct {
    int v1;
    int v2;
    int peso;
} Arestas;

typedef struct {
    int vtotal;
    int **matriz;
} Grafo;

typedef struct caminho {
    int *vertices;
    int tamanho;
    int custo;
    struct caminho *prox;
} Caminho;

// declaração antecipada por usar ela antes do escopo main 
int foiVisitado(int *caminho, int tamanho, int vertice);

void *CriaGrafo(int vertices) {
   
   Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        printf("Erro\n");
        exit(0);
    }
    grafo->vtotal = vertices;

    grafo->matriz = (int**)malloc(vertices * sizeof(int*));
    if (grafo->matriz == NULL) {
        printf("Erro\n");
        exit(0);
    }

    for (int i = 0; i < vertices; i++) {
        grafo->matriz[i] = (int*)malloc(vertices * sizeof(int));
        if (grafo->matriz[i] == NULL) {
            printf("Erro\n");
            exit(0);
        }
    }

    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            grafo->matriz[i][j] = 0;
        }
    }

    return grafo;
}

void AdicionaAresta(Grafo *grafo, int v1, int v2, int peso) {
    if (v1 >= 0 && v1 < grafo->vtotal && v2 >= 0 && v2 < grafo->vtotal) {
        grafo->matriz[v1][v2] = peso;
        
    } else {
        printf("Vertices invalidos.\n");
    }
}



Caminho *insereCaminho(Caminho *lista, int *vertices, int tamanho, int custo) {
    Caminho *novo = (Caminho *)malloc(sizeof(Caminho));
    if (novo == NULL) {
        printf("Erro\n");
        exit(0);
    }

    novo->vertices = (int *)malloc(tamanho * sizeof(int));
    if (novo->vertices == NULL) {
        printf("Erro\n");
        exit(0);
    }

    for (int i = 0; i < tamanho; i++) {
        novo->vertices[i] = vertices[i];
    }

    novo->tamanho = tamanho;
    novo->custo = custo;
    novo->prox = NULL;

    if (lista == NULL) {
        return novo;
    }

    Caminho *atual = lista;
    while (atual->prox != NULL) {
        atual = atual->prox;
    }
    atual->prox = novo;

    return lista;
}

void imprimeKCaminhosMenores(Caminho *lista, int k) {
    // Implementa uma ordenação simples para os caminhos com base nos custos
    Caminho *atual = lista;
    int contador = 0;
    while (atual != NULL && contador < k) {
        Caminho *menor = atual;
        Caminho *proximo = atual->prox;

        while (proximo != NULL) {
            if (proximo->custo < menor->custo) {
                menor = proximo;
            }
            proximo = proximo->prox;
        }

        // Troca os valores dos caminhos
        int *temp_vertices = atual->vertices;
        int temp_tamanho = atual->tamanho;
        int temp_custo = atual->custo;

        atual->vertices = menor->vertices;
        atual->tamanho = menor->tamanho;
        atual->custo = menor->custo;

        menor->vertices = temp_vertices;
        menor->tamanho = temp_tamanho;
        menor->custo = temp_custo;

        // Imprime o caminho
        printf("Caminho encontrado: ");
        for (int i = 0; i < atual->tamanho; i++) {
            printf("%d ", atual->vertices[i] + 1); // Adicionando 1 para converter de índices base 0 para base 1
        }
        printf(" - Custo: %d\n", atual->custo);

        atual = atual->prox;
        contador++;
    }
}

void EncontraTodosCaminhosComCusto(Grafo *grafo, int origem, int destino, int *caminho, int tamanho, int custoTotal, Caminho **lista) {
    caminho[tamanho] = origem;
    tamanho++;

    if (origem == destino) {
        *lista = insereCaminho(*lista, caminho, tamanho, custoTotal);
    } else {
        for (int v = 0; v < grafo->vtotal; v++) {
            if (grafo->matriz[origem][v] && !foiVisitado(caminho, tamanho, v)) {
                int novoCustoTotal = custoTotal + grafo->matriz[origem][v];
                EncontraTodosCaminhosComCusto(grafo, v, destino, caminho, tamanho, novoCustoTotal, lista);
            }
        }
    }

    tamanho--;
}

int foiVisitado(int *caminho, int tamanho, int vertice) {
    for (int i = 0; i < tamanho; i++) {
        if (caminho[i] == vertice) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int num_viagens, V, k;
    int a, b, c;
    struct timeval start, end;
    struct rusage usage;
    scanf("%d %d %d", &V, &num_viagens, &k);
    
    Grafo *grafo = (Grafo*)CriaGrafo(V);
    for(int i = 0; i < num_viagens; i ++) {
        scanf("%d %d %d", &a, &b, &c);
        AdicionaAresta(grafo, a - 1, b - 1, c); // Ajuste para índices de 0 a V-1
    }
    gettimeofday(&start, NULL);//inicio da contagem

    int origem = 0; // primeiro vértice
    int destino = V - 1; // último vértice



    printf("Menores %d caminhos:\n", k);
    Caminho *lista = NULL;
    int *caminho = (int*)malloc(V * sizeof(int));
    EncontraTodosCaminhosComCusto(grafo, origem, destino, caminho, 0, 0, &lista);

    imprimeKCaminhosMenores(lista, k);



    for(int i = 0; i < V; i++) {
        free(grafo->matriz[i]);
    }
    free(grafo->matriz);
    free(grafo);
    gettimeofday(&end, NULL);// Fim da contagem 

    getrusage(RUSAGE_SELF, &usage);

    double elapsed_time = (end.tv_sec - start.tv_sec) + 
                          (end.tv_usec - start.tv_usec) / 1000000.0;
    double cpu_time = usage.ru_utime.tv_sec + usage.ru_utime.tv_usec / 1000000.0 +
                      usage.ru_stime.tv_sec + usage.ru_stime.tv_usec / 1000000.0;

    printf("Tempo decorrido: %.6f segundos\n", elapsed_time);
    printf("Tempo de CPU: %.6f segundos\n", cpu_time);

    return 0;
}
