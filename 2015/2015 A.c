#include <stdio.h>

int main()
{
    int i, j, k;
    int caseNumber = 0;
    scanf("%d", &caseNumber);
    while(caseNumber-- >= 1){
        int x1, y1, x2, y2, x3, y3;
        scanf("%d%d%d%d%d%d", &x1, &y1, &x2, &y2, &x3, &y3);
        int a = ( (y1-y2)*(x1-x3) - (y1-y3)*(x1-x2) )/( (x1*x1 - x2*x2)*(x1-x3) - (x1*x1 - x3*x3)*(x1-x2) );
        /*printf("%d/%d =  %d\n", ( (y1-y2)*(x1-x3) - (y1-y3)*(x1-x2) ), ( (x1*x1 - x2*x2)*(x1-x3) - (x1*x1 - x3*x3)*(x1-x2) ), a);*/
        /*printf("%d %d %d %d\n", (y1-y2), (x1-x3), (y1-y3), (x1-x2));*/
        int b = ( (y1-y2) - a*(x1*x1 - x2*x2) ) / (x1-x2);
        int c = y1 - x1*x1*a - x1*b;
        printf("%d %d %d\n", a, b, c);
    }
}
