#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10
#define M 20
#define INF 9999

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adj[N]; 
int visited[N];
int dist[N];
int parent[N];

void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}

void bfs(int start) {
    int queue[N], front = 0, rear = 0;
    for (int i = 0; i < N; i++) {
        visited[i] = 0;
        dist[i] = INF;
        parent[i] = -1;
    }

    visited[start] = 1;
    dist[start] = 0;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        for (Node* cur = adj[u]; cur != NULL; cur = cur->next) {
            int v = cur->vertex;
            if (!visited[v]) {
                visited[v] = 1;
                dist[v] = dist[u] + 1;
                parent[v] = u;
                queue[rear++] = v;
            }
        }
    }
}

void printPath(int start, int end) {
    if (end == -1) return;
    if (end == start)
        printf("%d", start);
    else {
        printPath(start, parent[end]);
        printf("->%d", end);
    }
}

void generateRandomGraph() {
    int edges = 0;
    int used[N][N] = { 0 };
    srand(time(NULL));

    while (edges < M) {
        int u = rand() % N;
        int v = rand() % N;
        if (u != v && !used[u][v] && !used[v][u]) {
            used[u][v] = used[v][u] = 1;
            addEdge(u, v);
            addEdge(v, u);
            edges++;
        }
    }
}

int main() {
    generateRandomGraph();

    printf("=== 모든 노드 쌍의 최단 경로 (총 45쌍) ===\n");
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            bfs(i);
            printf("[%d → %d] ", i, j);
            if (dist[j] == INF) {
                printf("도달 불가\n");
            }
            else {
                printf("거리: %d, 경로: ", dist[j]);
                printPath(i, j);
                printf("\n");
            }
        }
    }

    for (int i = 0; i < N; i++) {
        Node* cur = adj[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }

    return 0;
}