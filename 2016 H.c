#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxBody 10005
#define MaxMove 102
typedef struct {
    int alive;
    int len;
    int dir;
    char id[3];
    int body[MaxBody][2];
    char moves[MaxMove][3];
} Snake;

int map[MaxMove][MaxMove];
int maxlen, ms;
const int dy[4] = {+1, 0, -1, 0};
const int dx[4] = {0, +1, 0, -1};
int sn;
Snake snakes[26];
int mn;
int cmp(const void* a, const void* b)
{
    Snake* ap= (Snake*)a;
    Snake* bp= (Snake*)b;
    return strcmp(ap->id, bp->id);
}
void showMap(int r)
{
    int i, j;
    for(i = r; i >= 0; i--){
        for(j = 0; j <= r; j++){
            printf("%d ", map[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}
void Move(int round, int nowSnake)
{

    /*showMap(100);*/
    int i;
    if(snakes[nowSnake].moves[round][0] == 'R'){
        snakes[nowSnake].dir = (snakes[nowSnake].dir+1)%4;
    }
    else if(snakes[nowSnake].moves[round][0] == 'L'){
        snakes[nowSnake].dir = (snakes[nowSnake].dir-1+4)%4;
    }
    /*Forwording*/
    for(i = 0; i < snakes[nowSnake].len; i++){
        map[snakes[nowSnake].body[i][0]][snakes[nowSnake].body[i][1]] = 0;
    }
    int na = snakes[nowSnake].body[0][0] + dx[snakes[nowSnake].dir];
    int nb = snakes[nowSnake].body[0][1] + dy[snakes[nowSnake].dir];
    if(map[na][nb] == 2){
        snakes[nowSnake].len++;
        map[na][nb] = 0 ;
    }
    for(i = 0; i < snakes[nowSnake].len; i++){
        int tmpa = snakes[nowSnake].body[i][0];
        int tmpb = snakes[nowSnake].body[i][1];
        snakes[nowSnake].body[i][0] = na;
        snakes[nowSnake].body[i][1] = nb;
        na = tmpa;
        nb = tmpb;
    }
    /*Check Collision*/

    int col = 0;
    if(snakes[nowSnake].body[0][0] < 0 || snakes[nowSnake].body[0][0] >= 100) col = 1;
    if(snakes[nowSnake].body[0][1] < 0 || snakes[nowSnake].body[0][1] >= 100) col = 1;
    if(col != 1){
        if(map[snakes[nowSnake].body[0][0]][snakes[nowSnake].body[0][1]] == 1) col = 1;
    }

    if(col == 1){
        snakes[nowSnake].alive = 0;
        for(i = 1; i < snakes[nowSnake].len; i++){
            map[snakes[nowSnake].body[i][0]][snakes[nowSnake].body[i][1]] = 2;
        }
        return;
    }
    /*set map*/
    for(i = 0; i < snakes[nowSnake].len; i++){
        map[snakes[nowSnake].body[i][0]][snakes[nowSnake].body[i][1]] = 1;
    }

}
int main()
{
    #ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
    int i, j;
    int caseNumber;
    scanf("%d", &caseNumber);
    while(caseNumber-- >= 1){
        maxlen = 0;
        for(i = 0; i < MaxMove; i++){
            for(j = 0; j < MaxMove; j++){
                map[i][j] = 0;
            }
        }
        scanf("%d", &sn);
        for(i = 0; i < sn; i++){
            scanf("%s", (snakes[i].id));
            snakes[i].len = 0;
            snakes[i].alive = 1;
            char c;
            while((c = getchar() )!= '\n'){
                if(c == ' ') continue;
                else ungetc(c, stdin);
                scanf("%d %d", &snakes[i].body[snakes[i].len][0], &snakes[i].body[snakes[i].len][1]);
                map[snakes[i].body[snakes[i].len][0]][snakes[i].body[snakes[i].len][1]] = 1;
                snakes[i].len++;
            }

            for(j = 0; j < 4; j++){
                if(dx[j] == snakes[i].body[0][0] - snakes[i].body[1][0] && dy[j] == snakes[i].body[0][1] - snakes[i].body[1][1]) {
                    snakes[i].dir = j;
                }
            }
        }
        scanf("%d", &mn);
        for(i = 0; i < sn; i++){
            char id[2];
            scanf("%s", id);
            int tmps = -1;
            for(j = 0; j < sn; j++){
                if(id[0] == snakes[j].id[0]) {
                    tmps = j;
                    break;
                }
            }
            if(tmps == -1) exit(1);
            for(j = 0; j < mn; j++){
                scanf("%s", snakes[tmps].moves[j]);
            }
        }
        qsort(snakes, sn, sizeof(Snake), cmp);
        for(i = 0; i < mn; i++){
            for(j = 0; j < sn; j++){
                if(snakes[j].alive == 0) continue;
                Move(i, j);

            }
        }
        maxlen = 0;
        ms = -1;
        for(i = 0; i < sn; i++){
            if(snakes[i].alive == 0) continue;
            if(maxlen < snakes[i].len) {
                maxlen = snakes[i].len;
                ms = i;
            }
            else if(maxlen == snakes[i].len) {
                if(strcmp(snakes[ms].id, snakes[i].id) == 1){
                    ms = i;
                }
            }
        }
        if(ms == -1) printf("null\n");
        else printf("%c %d\n", snakes[ms].id[0], maxlen);
    }
    return 0;
}
