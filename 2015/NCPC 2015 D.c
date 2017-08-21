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
int fb[41];
int primes[41];
void Read()
{
    int i, j;
}
int main()
{
    #ifndef ONLINE_JUDGE
		//freopen("input.in", "r", stdin);
		//freopen("output.out", "w", stdout);
	#endif
    int i, j, k;
    int caseNumber = 1;
    scanf("%d", &caseNumber);
    fb[0] = 1, fb[1] = 1;
    for(i = 2; i <= 40; i++){
        fb[i] = fb[i-1] + fb[i-2];
    }
    primes[1] = 0;
    for(i = 2; i < 41; i++){
        primes[i] = 1;
        for(j = 2; j < i; j++) if(i%j == 0) primes[i] = 0;
    }
    while(caseNumber-- >= 1){
        scanf("%d", &size);
        #ifdef DBUGM
            printf("----------- Debug Message %d-----------\n", caseNumber);
        #endif
        int people[size+1], rm = size, dir = 1;
        for(i = 0; i <= size; i++) people[i] = i;
        for(i = 0; i < size-1; i++){
            //for(j = 1; j <= rm; j++) printf("%d ", people[j]);
            //printf("\nrm: %d/%d\n\n", rm, size);
            int c = 1, pt = 0;
            for(c = 1; c <= fb[i]; c++){
                pt += 1*dir;
                if(pt == 0)pt = rm;
                else if( pt == rm+1) pt = 1;
                else if( pt < 0) pt = rm;
            }
            if(primes[people[pt]] == 1) dir*=-1;
            //printf("kill %d\n", people[pt]);
            people[pt] = 0;
            int q2[size+1];
            pt+=1;
            for(j = 0; j <= size; j++) q2[j] = 0;
            for(c = 1; c <= rm-1; c++){
                if(pt == rm+1) pt = 1;
                q2[c] = people[pt];
                pt++;
            }
            for(c = 1; c <= rm-1; c++)people[c] = q2[c];
            rm--;

        }
        printf("%d\n", people[1]);
    }
    return 0;
}
