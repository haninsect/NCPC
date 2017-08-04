#include <stdio.h>
int play1[6];
int play2[6];
int table[10000000];
int ans1, ans2;
int mode = 0;
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void permute(int index, int n, int a[n])
{
    int i, j;
    if(index == n-1){
        int pow10 = 1;
        int tmpValue = 0;
        for(j = 0; j < n; j++){
            tmpValue += a[j]*pow10;
            pow10 *= 10;
        }

        if(mode == 0){
            if(table[tmpValue] == 0){
                table[tmpValue] = 1;
                ans1++;
            }
        }
        else {
            if(table[tmpValue] == 1){
                table[tmpValue] = 2;
                ans1--;
            }
            else {
                if(table[tmpValue] == 0){
                    table[tmpValue] = 2;
                    ans2++;
                }
            }
        }
    }
    else {
        for(i = index; i < n; i++){
            swap(&a[index], &a[i]);
            permute(index+1, n, a);
            swap(&a[index], &a[i]);
        }
    }
}
int main()
{
    int i, j, k;
    int caseNumber = 0;
    scanf("%d", &caseNumber);
    while(caseNumber-- >= 1){
        for(i = 0; i < 10000000; i++) table[i] = 0;
        ans1 = 0, ans2 = 0, mode = 0;
        for(i = 0; i < 6; i++) scanf("%d", &play1[i]);
        for(i = 0; i < 6; i++) scanf("%d", &play2[i]);
        int mask[7];
        int pow2 = 1;
        for(i = 0; i < 6; i++){
            mask[i] = pow2;
            pow2 *= 2;
        }
        for(i = 0; i < pow2; i++){
            int queue[6];
            int qn = 0;
            for(j = 0; j < 6; j++){
                if( (i & mask[j]) > 0) queue[qn++] = play1[j];
            }
            permute(0, qn, queue);
        }
        mode = 1;
        for(i = 0; i < pow2; i++){
            int queue[6];
            int qn = 0;
            for(j = 0; j < 6; j++){
                if( (i&mask[j]) > 0) {
                    queue[qn++] = play2[j];
                }
            }
            permute(0, qn, queue);
        }
        printf("%d %d\n", ans1, ans2);

    }
    return 0;
}
