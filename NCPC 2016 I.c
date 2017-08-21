#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define DBUGM1
#define LargeINT 1000000000
#define errorT 0.000001
#define M_PI 3.14159265358979323846
#define MaxSize 260
int pn, qn;
typedef struct {
    int flow;
    int capacity;
    int edgeLen;
} edge;
void ShowGraph(int size, edge graph[size+1][size+1])
{
    size++;
    int i, j, k;
    printf("Capacity:\n");
    for(i = 1; i < size; i++){
        for(j = 1; j < size; j++){
            printf("%2d ", graph[i][j].capacity);
        }printf("\n");
    }printf("\n");

    printf("flow:\n");
    for(i = 1; i < size; i++){
        for(j = 1; j < size; j++){
            printf("%2d ",graph[i][j].flow);
        }printf("\n");
    }printf("\n");

    printf("edgeLen:\n");
    for(i = 1; i < size; i++){
        for(j = 1; j < size; j++){
            printf("%2d ",graph[i][j].edgeLen);
        }printf("\n");
    }printf("\n");
}
int ConstructGraph(int size, edge graph[size+1][size+1], int source[pn+1], int target[qn+1])
{
    /*0 is super source, size-1 is super target, 1~n is source n+1~2n is target*/
    int i, j, k;
    for(i = 0; i <= size; i++){
        for(j = 0; j <= size; j++) {
            graph[i][j].edgeLen = 0;
            graph[i][j].flow = 0;
            graph[i][j].capacity = -1;
        }
    }
    for(i = 1; i <= pn; i++){
        graph[1][i+1].edgeLen = 0;
        graph[1][i+1].capacity = source[i];
        graph[i+1][1].edgeLen = 0;
        graph[i+1][1].capacity = source[i];
        graph[i+1][1].flow = source[i];
    }
    for(i = 1; i <= qn; i++){
        graph[size][i+pn+1].edgeLen = 0;
        graph[size][i+pn+1].capacity = target[i];
        graph[size][i+pn+1].flow = target[i];
        graph[i+pn+1][size].edgeLen = 0;
        graph[i+pn+1][size].capacity = target[i];
    }

    for(i = 1; i <= pn; i++){
        for(j = 1; j <= qn; j++){
            graph[i+1][j+pn+1].edgeLen = 0;
            graph[i+1][j+pn+1].capacity = 1;
            graph[j+pn+1][i+1].edgeLen = 0;
            graph[j+pn+1][i+1].capacity = 1;
            graph[j+pn+1][i+1].flow = 1;
        }
    }
    return 1;
}
int MinCostMaxFlow(int size, edge graph[size+1][size+1])
{
    int i, j, k;
    int p;
    while( 1 ){
        int parent[size+1];
        if(!SPFA(size, graph, parent, 1, size)) break;
        int bottleneck = LargeINT;
        int p = size;
        while(1){
            if(parent[p] == -1)break;
            if(bottleneck > graph[parent[p]][p].capacity - graph[parent[p]][p].flow) bottleneck = graph[parent[p]][p].capacity - graph[parent[p]][p].flow;
            p = parent[p];
        }
        p = size;
        while(1){
            if(parent[p] == -1)break;
            graph[parent[p]][p].flow += bottleneck;
            graph[p][parent[p]].flow -= bottleneck;
            p = parent[p];
        }
    }
    int flow = 0;
    for(i = 1; i <= size; i++){
        if(graph[i][size].flow > 0) {
            flow += graph[i][size].flow;
        }
    }
    return flow;
}

/*SPFA*/
int SPFA (int size, edge graph[size+1][size+1], int parent[size+1], int root, int target)
{
    /*initial parent as -1*/
    int i, j, k;
    for(i = 0; i <= size; i++) parent[i] = -1;

    /*Modify Dijkstra's  Shortest path for negative edge*/
    int key[size+1], visited[size+1], vn = 0;
    for(i = 0; i <= size; i++) key[i] = LargeINT, visited[i] = 0;

    key[root] = 0;
    while(1){
        int deQ = -1;
        for(i = 1; i <= size; i++){
            if(visited[i] == 0) {
                deQ = i;
                break;
            }
        }
        if(deQ == -1) break;
        for(i = 1; i <= size; i++){
            if(graph[deQ][i].capacity > graph[deQ][i].flow && graph[deQ][i].edgeLen + key[deQ] < key[i]){
                key[i] = graph[deQ][i].edgeLen + key[deQ];
                parent[i] =deQ;
                visited[i] = 0;
            }
        }
        visited[deQ] = 1;
        vn++;
    }
    /*for(i = 1; i <= size; i++) printf("%d ", parent[i]);
    printf("\n");*/
    return parent[target] != -1;
}
void Read()
{
    int i, j;
}
int main()
{
    #ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
    int i, j, k;
    int caseNumber = 1;
    while(1){
        scanf("%d%d", &pn, &qn);
        if(pn == 0 && qn == 0) break;
        #ifdef DBUGM
            printf("----------- Debug Message %d-----------\n", caseNumber);
        #endif
        int pa[pn+1];
        for(i = 1; i <= pn; i++) scanf("%d", &pa[i]);
        int qa[qn+1];
        for(i = 1; i <= qn; i++) scanf("%d", &qa[i]);
        int gsize = pn+1+qn+1;
        edge graph[gsize+1][gsize+1];
        ConstructGraph(gsize, graph, pa, qa);
        int ans = MinCostMaxFlow(gsize, graph);
        printf("%d\n", ans);

    }
    return 0;
}
