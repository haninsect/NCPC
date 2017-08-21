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
        scanf("%d", &size);
        if(size == 0) break;
        #ifdef DBUGM
            printf("----------- Debug Message %d-----------\n", caseNumber);
        #endif
        int input[105] = {0};
        input[1] = size;
        int in = 1;
        char c;
        while((c = getchar())== ' ');
        if(c == '\n') {
            printf("1\n");
            continue;
        }
        ungetc(c, stdin);
        int sn;
        while(1){
            scanf("%d", &input[++in]);
            while((c = getchar())== ' ');
            if(c == '\n') {
                sn = input[in];
                break;
            }
            ungetc(c, stdin);
        }
        //for(i = 1; i <= in; i++) printf("%d ", input[i]);
        int bf = 0;
        for(i = 1; i < in && bf == 0; i++){
            if(input[i] < sn){
                for(j = i+1; j < in; j++){
                    if(input[i] >= input[j]) {
                        bf = 1;
                        break;
                    }
                }
            }
            else if(input[i] > sn){
                for(j = i+1; j < in; j++){
                    if(input[i] <= input[j]) {
                        bf = 1;
                        break;
                    }
                }
            }
            else {
                bf = 1;
                break;
            }
        }
        if(bf == 1) printf("0\n");
        else printf("1\n");

    }
    return 0;
}
