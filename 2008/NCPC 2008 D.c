#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define DBUGM1
#define LargeINT 1000000000
#define errorT 0.000001
#define M_PI 3.14159265358979323846
#define MaxSize 105
int size;
int table[MaxSize][MaxSize];
int st[MaxSize][MaxSize][MaxSize];
void Read()
{
    int i, j, k, l;
    for(i = 0; i < MaxSize; i++){
        for(j = 0; j < MaxSize; j++) table[i][j] = 0;
    }
    for(i = 0; i < MaxSize; i++){
        for(j = 0; j < MaxSize; j++) {
            for(k = 0; k < MaxSize; k++){
                st[i][j][k] = 0;
            }
        }
    }
    for(i = 1; i <= size; i++){
        for(j = 1; j <= size; j++) scanf("%d", &table[i][j]);
    }
    for(i = 1; i <= size; i++){
        for(j = 1; j <= size; j++) {
            for(k = 1; k <= size; k++){
                for(l = j; l <= k; l++) st[i][j][k] += table[l][i];
            }
        }
    }
}
int Rec1D(int len, int array[MaxSize])
{
    int i;
    int max = -LargeINT, sum = 0;
    for(i = 1; i <= len; i++){
        //printf("a[i]: %d ", array[i]);
        if(array[i] > max) max = array[i];
        if(sum + array[i] > max) max = sum + array[i];

        if(sum + array[i] >= 0) sum = sum + array[i];
        else sum = 0;
        //printf("Sum %d: %d\n", i, sum);
    }
    return max;
}
int Rec2D(int fx, int tx, int fy, int ty)
{
    int i, j, k, l;
    int max = -LargeINT;
    for(k = fx; k <= tx; k++){
        for(l = k; l <= tx; l++){
            //printf("from %d to %d:\n", k, l);
            int array[MaxSize] = {0};
            /*for(j = fy; j <= ty; j++){
                for(i = k; i <= l; i++){
                    array[j-fy+1] += table[i][j];
                }
            }*/
            for(j = 1; j <= ty-fy+1; j++) array[j] = st[fy+j-1][k][l];
            int tmp = Rec1D(ty-fy+1, array);
            if(tmp > max) max = tmp;
        }
    }
    return max;
}
int main()
{
    #ifndef ONLINE_JUDGE
		//freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
    int i, j, k;
    while(1){
        scanf("%d", &size);
        if(size == 0) break;
        Read();
        #ifdef DBUGM
            printf("----------- Debug Message %d-----------\n", caseNumber);
        #endif
        int max = -LargeINT;
        for(i = 1; i < size; i++){
            int tmp = Rec2D(1, i, 1, size);
            #ifdef DBUGM
            printf("-------");
            #endif
            int tmp2 = Rec2D(i+1, size, 1, size);
            if(tmp+tmp2 > max) max = tmp+tmp2;
            #ifdef DBUGM
            printf("%d: %d+%d\n", i, tmp, tmp2);
            #endif
        }
        for(i = 1; i < size; i++){
            int tmp = Rec2D(1, size, 1, i);
            #ifdef DBUGM
            printf("-------");
            #endif
            int tmp2 = Rec2D(1, size, i+1, size);
            if(tmp+tmp2 > max) max = tmp+tmp2;
            #ifdef DBUGM
            printf("%d: %d+%d\n", i, tmp, tmp2);
            #endif
        }
        printf("%d\n", max);
    }
    return 0;
}
