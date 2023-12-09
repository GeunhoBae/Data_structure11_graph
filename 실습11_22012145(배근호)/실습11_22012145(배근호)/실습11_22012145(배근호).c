#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
#define TRUE 1
#define FALSE 0

//함수구현
int** make_graph(int n) {
    int** temp;
    temp = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        temp[i] = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                temp[i][j] = 0;
            else
                temp[i][j] = 99999;
        }
    }

    return temp;
}

void free_graph(int** graph, int n) {
    for (int i = 0; i < n; i++)
        free(graph[i]);
    free(graph);
}

void print_graph(int** graph, int n) {
    printf("	");
    for (int i = 0; i < n; i++) //[0] [1]...
        printf("[%d]	", i);
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("[%d]	", i);
        for (int j = 0; j < n; j++)
            printf("%d	", graph[i][j]);
        printf("\n");
    }
}

void insert_edge(int** graph) {
    int from, to, w;
    while (1) {
        printf("에지 정보(from to weight): ");
        scanf("%d %d %d", &from, &to, &w);
        if (from < 0 || to < 0 || w < 0)
            break;
        graph[from][to] = w;
    }
}

int choose(int distance[], int n, short int found[]) {
    int i, min, minpos;

    min = 99999;
    minpos = -1;
    for (i = 0; i < n; i++)
        if (distance[i] < min && found[i] == FALSE) {
            min = distance[i];
            minpos = i;
        }
    return minpos;
}

void shortestpath(int v, int** graph, int* distance, int n, short int* found) {
    int i, u, w;
    for (i = 0; i < n; i++) {
        found[i] = FALSE;
        distance[i] = graph[v][i];
    }

    found[v] = TRUE;
    distance[v] = 0;
    for (i = 0; i < n - 2; i++) {
        u = choose(distance, n, found);
        found[u] = TRUE;
        for (w = 0; w < n; w++) {
            if (found[w] == FALSE)
                if (distance[u] + graph[u][w] < distance[w])
                    distance[w] = distance[u] + graph[u][w];
        }
    }
}

void allcosts(int** graph, int** distance, int n) {
    int i, j, k;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            distance[i][j] = graph[i][j];
    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (distance[i][k] + distance[k][j] < distance[i][j])
                    distance[i][j] = distance[i][k] + distance[k][j];
}

//main 함수
void main() {
    //11.1
    printf("11.1 인접 행렬 형태의 방향성 그래프 생성");
    int n;
    printf("노드 수(n); ");
    scanf("%d", &n);
    int** graph;
    graph = make_graph(n);
    insert_edge(graph);
    print_graph(graph, n);
    printf("\n");

    //11.2
    printf("11.2 최단 경로 (단일 출발점)\n");
    int v;
    int* distance = (int*)malloc(sizeof(int) * n);
    short int* found = (short int*)malloc(sizeof(short int) * n);
    while (1) {
        printf("시작 노드 (v): ");
        scanf("%d", &v);
        if (v == -1)
            break;
        shortestpath(v, graph, distance, n, found);
        printf("Distance: ");
        for (int i = 0; i < n; i++)
            printf("%d ", distance[i]);
        printf("\n");
    }
    free(distance);
    free(found);
    printf("\n");

    //11.3
    printf("11.3 최다 경로(모든 경로)\n");
    printf("All Path Distance: \n");
    int** distance_all;
    distance_all = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
        distance_all[i] = (int*)malloc(sizeof(int) * n);

    allcosts(graph, distance_all, n);
    print_graph(distance_all, n);

    free_graph(distance_all, n);
    free_graph(graph, n); //메모리 해제
}