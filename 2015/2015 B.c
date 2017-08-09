#include <stdio.h>
#define MaxQ 2005
#define Maxop 15
typedef struct {
    long long int queue[MaxQ];
    int qs;
    int table[MaxQ];
    int back[MaxQ];
    int left[MaxQ];
    int right[MaxQ];
} cell;
int prim;
char opt[15];
int opd[16];
int os;
int eq;
cell dp[16][16];
int lp[16];
int rp[16];

void Fill(int lt, int rt)
{
    /*printf("%d -> %d\n", lt, rt);*/
    if(lt == rt){
        dp[lt][rt].queue[dp[lt][rt].qs] = opd[lt]%prim;
        dp[lt][rt].qs++;
        return;
    }
    int i, j, k;
    for(i = lt; i < rt; i++){
        for( j = 0; j < dp[lt][i].qs; j++){
            for(k = 0; k < dp[i+1][rt].qs; k++){
                int value, min, max;
                if(opt[i] == '*') {
                    value = (dp[lt][i].queue[j] * dp[i+1][rt].queue[k])%prim;
                }
                else if(opt[i] == '+') {
                    value = (dp[lt][i].queue[j] + dp[i+1][rt].queue[k])%prim;

                }
                else if(opt[i] == '-') {
                    value = (dp[lt][i].queue[j] - dp[i+1][rt].queue[k])%prim;
                    if(value < 0 ) value += prim;
                }

                if(dp[lt][rt].table[value] == 0){
                    dp[lt][rt].table[value] = 1;
                    dp[lt][rt].queue[dp[lt][rt].qs] = value;
                    dp[lt][rt].qs++;
                    dp[lt][rt].back[value] = i;
                    dp[lt][rt].left[value] = dp[lt][i].queue[j];
                    dp[lt][rt].right[value] = dp[i+1][rt].queue[k];
                }
            }
        }


    }
}
void back(int s, int e, int q)
{
    //printf("back: (%d -> %d), %d\n", s, e, q);
    if(s == e)return;
    lp[s]++;
    rp[e]++;
    int bp = dp[s][e].back[q];
    //printf("%d\n", bp);
    //system("pause");
    back(s, bp, dp[s][e].left[q]);
    back(bp+1, e, dp[s][e].right[q]);
}
int main()
{
    freopen("output.out", "w", stdout);
    int i, j, k;
    int caseNumber;
    scanf("%d", &caseNumber);
    scanf("%d", &prim);
    while(caseNumber-- >= 1){
        for(i = 0; i < 15; i++){
            opt[i] = '\0';
            opd[i] = 0;
        }
        opd[i] = 0;
        for(i = 0; i < 16; i++){
            for(j = 0; j < 16; j++){
                dp[i][j].qs = 0;
                for(k = 0; k < MaxQ; k++){
                    dp[i][j].table[k] = 0;
                }
            }
        }
        os = 0;
        scanf("%d", &opd[os]);
        while(1){
            char c = getchar();
            if(c == '='){
                scanf("%d", &eq);
                break;
            }
            opt[os++] = c;
            scanf("%d", &opd[os]);
        }
        for(i = 0; i <= os; i++){
            for(j = 0; j <= os-i; j++){
                Fill(j, j+i);
            }
        }

        /*for(i = 0; i <= os; i++){
            for(j = 0; j <= os; j++){
                printf("%d -> %d:\n", i, j);
                for(k = 0; k < dp[i][j].qs; k++){
                    printf("%d ", dp[i][j].queue[k]);
                }
                printf("\n");
            }
        }*/
        int flag = 0;
        for(i = 0; i < 16; i++) lp[i] = 0, rp[i] = 0;
        for(i = 0; i < dp[0][os].qs; i++){
            /*printf("%d/%d: %d\n", i, dp[0][os].qs, dp[0][os].queue[i]);*/
            if(dp[0][os].queue[i] == eq){
                flag = 1;
                /*Back trace print ()*/
                int bp = dp[0][os].back[dp[0][os].queue[i]];
                back(0, bp, dp[0][os].left[dp[0][os].queue[i]]);
                back(bp+1, os, dp[0][os].right[dp[0][os].queue[i]]);
                for(i = 0; i < lp[0]; i++) printf("(");
                printf("%d", opd[0]);
                for(i = 0; i < rp[0]; i++) printf(")");
                for(i = 0; i < os; i++){
                    printf("%c", opt[i]);
                    for(j = 0; j < lp[i+1]; j++)printf("(");
                    printf("%d", opd[i+1]);
                    for(j = 0; j < rp[i+1]; j++)printf(")");
                }
                printf("=%d\n", eq);
                break;
            }
        }
        if(flag == 0) printf("0\n");
    }
    return 0;
}
