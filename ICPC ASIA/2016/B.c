/* */
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
typedef struct {
    double x, y;
} point;
point pts[MaxSize];
double distance(point a, point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}
void Read()
{
    int i;
    for(i = 1; i <= size; i++){
        scanf("%lf%lf", &pts[i].x, &pts[i].y);
    }
}
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
        Read();
        #ifdef DBUGM
            printf("----------- Debug Message %d-----------\n", caseNumber);
        #endif
        double min = LargeINT;
        for(i = 1; i <= size; i++){
            for(j = 1; j <= size; j++){
                if(i == j) continue;
                if(distance(pts[i], pts[j]) < min-errorT) min = distance(pts[i], pts[j]);
            }
        }
        printf("%.2lf\n", min);



    }
    return 0;
}
