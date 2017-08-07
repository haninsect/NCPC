#include <stdio.h>
#define MaxSize 15
int graph[MaxSize][MaxSize];
int valid[MaxSize];
int vertex, eLimit;
int busn[MaxSize];
int start, end;
int ans;
void BandB(int now)
{
   /* printf("now: %d\n", now);*/
    int i;
    if(now == end){
        ans++;
        return;
    }
    for(i = 0; i < MaxSize; i++){
        if(valid[i] == 0) continue;
        if(graph[now][i] == 0) continue;
        valid[i] = 0;
        BandB(i);
        valid[i] = 1;
    }
    return;
}
int main()
{
    int i, j, k;
    int caseNumber = 0;
    scanf("%d", &caseNumber);
    while(caseNumber-- >= 1){
        ans = 0;
        for(i = 0; i < MaxSize; i++){
            valid[i] = 1;
            busn[i] = 0;
            for(j = 0; j < MaxSize; j++){
                graph[i][j] = 0;
            }
        }
        scanf("%d %d %d %d", &vertex, &eLimit, &start, &end);
        start--, end--;
        for(i = 0 ; i < vertex; i++){
            scanf("%d", &busn[i]);
            for(j = 0; j < busn[i]; j++){
                int b;
                scanf("%d", &b);
                b--;
                graph[i][b] = 1;
            }
        }
        valid[start] = 0;
        BandB(start);
        printf("%d\n", ans);
    }
    return 0;
}
