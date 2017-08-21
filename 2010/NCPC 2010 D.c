#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define DBUGM1
#define LargeINT 1000000000
#define errorT 0.000001
#define M_PI 3.14159265358979323846
#define MaxSize 10005
int size;
int *node[MaxSize];
int count[MaxSize] = {0};

int DFS(int from, int now, int len)
{
    //printf("---- %d -> (%d): %d ----\n", from, now, len);
    int i;
    int max = len;
    for(i = 1; i <= count[now]; i++){
        if(node[now][i] == from) continue;
        //printf("next: %d -> %d\n", now, node[now][i]);
        int tmp = DFS(now, node[now][i], len+1);
        if(tmp > max) max = tmp;
    }
    return max;
}
int main()
{
    #ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
    int i, j, k;
    while(1){
        scanf("%d", &size);
        if(size == 0) break;

        #ifdef DBUGM
            printf("----------- Debug Message %d-----------\n", caseNumber);
        #endif
        int tmpc[MaxSize] = {0};
        for(i = 0; i < MaxSize; i++) tmpc[i] = 1, node[i] = NULL, count[i] = 0;
        int input[MaxSize] = {0};
        for(i = 2; i <= size; i++) {
            scanf("%d", &input[i]);
            count[input[i]]++;
            count[i]++;
        }

        for(i = 1; i <= size; i++){
            node[i] = (int*)malloc(sizeof(int)*(count[i]+1));
        }
        for(i = 2; i <= size; i++){
            node[i][tmpc[i]++] = input[i];
            node[input[i]][tmpc[input[i]]++] = i;
        }

        /*for(i = 1; i <= size; i++){
            printf("%d: %d\n", i, count[i]);
            for(j = 1; j <= count[i]; j++){
                printf("%d ", node[i][j]);
            }
            printf("\n");
        }*/
        int min = LargeINT;
        int ansq[size+1], ans = 0;
        for(i = 1; i <= size; i++){
            int max = 0;
            for(j = 1; j <= count[i]; j++){
                //printf("Start %d %d/%d\n", i, j, count[i]);
                int pl = DFS(i, node[i][j], 1);
                if(pl > max) max = pl;
            }
            //printf("%d %d\n", max, min);
            if(max < min){
                ans = 0;
                ansq[++ans] = i;
                min = max;
            }
            else if(max == min){
                ansq[++ans] = i;
            }
        }
        printf("%d", ansq[1]);
        for(i = 2; i <= ans; i++){
            printf(" %d", ansq[i]);
        }
        printf("\n");


    }
    return 0;
}
