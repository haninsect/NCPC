#include <stdio.h>
#define MaxSize 105
typedef struct node{
    int index;
    int choose;
    struct node* child;
    struct node* next;
} node;
int size;
node nd[MaxSize];
int root;
int Solve(node* n, int mode)
{
    if(n->child == NULL){
        n->choose = 1;
        return 1;
    }
    int g = 0, f = 1;
    int c = 0;
    if(mode == 1) c = 1;
    node *tmp = n->child;
    while(tmp != NULL){
        g += Solve(tmp, 0);
        if(tmp->choose == 1) c++;
        tmp->choose = 0;
        tmp = tmp->next;
    }
    if(c < 2) g = -1;
    c = 0;
    if(mode == 1) c = 1;
    tmp = n->child;
    while(tmp != NULL){
        f += Solve(tmp, 1);
        if(tmp->choose == 1) c++;
        tmp->choose = 0;
        tmp = tmp->next;
    }
    if(g == -1 || f <= g){
        n->choose = 1;
        return f;
    }
    else {
        n->choose = 0;
        return g;
    }
}
int main()
{
    int i, j, k;
    int caseNumber;
    scanf("%d", &caseNumber);
    while(caseNumber-- >= 1){
        scanf("%d", &size);
        for(i = 0; i < size; i++) {
            nd[i].child = NULL;
            nd[i].next = NULL;
            nd[i].choose = 0;
            nd[i].index = i;
        }
        for(i = 0; i < size; i++){
            int p;
            scanf("%d", &p);
            p--;
            if(p >= i) {
                root = i;
                continue;
            }
            node* tmp = nd[p].child;
            if(tmp == NULL) {
                nd[p].child = &nd[i];
                continue;
            }
            while(tmp->next != NULL){
                tmp = tmp->next;
            }
            tmp->next = &nd[i];
        }
        int ans = Solve(&nd[root], 0);
        printf("%d\n", ans);
    }

}
