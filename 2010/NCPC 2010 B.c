#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define DBUGM1
#define LargeINT 1000000000
#define errorT 0.000001
#define M_PI 3.14159265358979323846
#define MaxSize 5005
int size;
int main()
{
    #ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
    int i, j, k;
    int caseNumber = 1;
    scanf("%d", &caseNumber);
    while(caseNumber-- >= 1){
        scanf("%d", &size);
        if(size == 0) break;
        #ifdef DBUGM
            printf("----------- Debug Message %d-----------\n", caseNumber);
        #endif
        int ans = 1;
        for(i = 1; i <= size; i++){
            int a = 0, s = 0;
            for(j = 1; j <= size; j++){
                int d, f;
                scanf("%d.%d", &d, &f);
                if(i == j) a = abs(d)*10+f;
                else s += abs(d)*10+f;
            }
            if(a <= s) ans = 0;
        }
        if(ans == 1) printf("Y");
        else printf("N");


    }
    printf("\n");
    return 0;
}
