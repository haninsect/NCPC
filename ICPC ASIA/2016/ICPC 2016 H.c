#include <stdio.h>
#define LI 1e9
int adjMatrix[105][105];
int gSize;
int Dijkstra(int from, int to)
{
    int i, j;
    int valid[gSize], parent[gSize];
    int key[gSize];
    for(i = 0; i < gSize; i++) valid[i] = 1, parent[i] = -1, key[i] = LI;
    key[from] = 0;
    while(1){
        int deQ = -1;
        int min = LI;
        for(i = 1; i < gSize; i++){
            if(key[i] < min && valid[i] == 1){
                min = key[i];
                deQ = i;
            }
        }
        if(deQ == -1) break;
        valid[deQ] = 0;
        for(i = 1; i < gSize; i++){
            if(adjMatrix[deQ][i] > 0 && valid[i] == 1){
                if(key[deQ] + adjMatrix[deQ][i] < key[i]) {
                    key[i] = key[deQ] + adjMatrix[deQ][i];
                    parent[i] = deQ;
                }
            }
        }
    }
    /*Return length*/
    return key[to];
}

int main()
{

    /*freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);*/
    int i, j, k, l;
    while(1){
        int size;
        scanf("%d", &size);
        gSize = size+1;
        if(size == 0) break;
        for(i = 0; i < gSize; i++){
            for(j = 0; j < gSize; j++) adjMatrix[i][j] = 0;
        }
        for(i = 1; i < gSize; i++){
            while(1){
                int a;
                scanf("%d", &a);
                adjMatrix[i][a] = 1;
                adjMatrix[a][i] = 1;
                if(getchar() == '\n')break;
            }
        }
        int min = LI;
        for(i = 1; i < gSize; i++){
            for(j = 1; j < gSize; j++){
                if(adjMatrix[i][j] == 0) continue;
                adjMatrix[j][i] = 0;
                int tmp = Dijkstra(j, i);
                if(tmp+1 < min) min = tmp+1;
                adjMatrix[j][i] = 0;
            }
        }
        if(min == LI) printf("0\n");
        else printf("%d\n", min);

    }
    return 0;
}

