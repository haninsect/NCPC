#include <stdio.h>
#define p31 2147483648
#define p32 2147483648*2
#define MaxNode (100000+2)*31
#define DBUGM1
#define DBUGM_Tree1
typedef struct {
    int totalNode;
    int lv;
    long long int originSum;
    long long int change[33];
    int ch[2];
}node;
node tree[MaxNode];
int cur_p, root;
int xor_flag;
long long int pow2[33];

void ShowTree(int n_node)
{
    if(n_node == -1) return;
    int i;
    printf("node id: %d\n", n_node);
    printf("   total node: %d\n", tree[n_node].totalNode);
    printf("   level: %d\n", tree[n_node].lv);
    printf("   Sum: %lld\n", tree[n_node].originSum);
    printf("   Change:");
    for(i = tree[n_node].lv; i >= 1; i--){
        printf(" %lld", tree[n_node].change[i]);
    }
    printf("\n");
    printf("   Children 0: %d, Children 1: %d\n", tree[n_node].ch[0], tree[n_node].ch[1]);
    if(tree[n_node].totalNode == 0) return;
    ShowTree(tree[n_node].ch[0]);
    ShowTree(tree[n_node].ch[1]);
}

long long int Sum(int now_p, int nodes)
{
    #ifdef DBUGM
        printf("  Sum %d/%d nodes, in %d ( sum: %lld, lv: %d )\n", nodes, tree[now_p].totalNode, now_p, tree[now_p].originSum, tree[now_p].lv);
    #endif
    if(now_p == -1){
        //printf("Error sum in -1\n");
    }
    int i;
    if(nodes == tree[now_p].totalNode){
        long long int change_value = 0;
        for(i = 32; i >= 1; i--){
            if( ((xor_flag >> (i-1))&1) > 0) change_value += tree[now_p].change[i];
        }
        #ifdef DBUGM
            printf("  Answer += %lld(%lld + %lld)\n", tree[now_p].originSum + change_value, tree[now_p].originSum, change_value);
        #endif
        return tree[now_p].originSum + change_value;
    }
    else {
        if(tree[now_p].lv == 1){
            long long int change_value = 0;
            for(i = 32; i >= 1; i--){
                if( ((xor_flag >> (i-1))&1) > 0) change_value += tree[now_p].change[i];
            }
            #ifdef DBUGM
                printf("  Answer += %lld (%lld + %lld)\n", (tree[now_p].originSum+change_value)/(long long int)tree[now_p].totalNode, tree[now_p].originSum, change_value);
            #endif
            return (tree[now_p].originSum+change_value)/(long long int)tree[now_p].totalNode * (long long int)nodes;
        }
        int small_ch = 0;
        if( ((xor_flag >> (tree[now_p].lv-2))&1) > 0)  small_ch = 1;
        if(tree[now_p].ch[small_ch] == -1){
            return Sum(tree[now_p].ch[!small_ch], nodes);
        }
        if(tree[ tree[now_p].ch[small_ch] ].totalNode < nodes){
            long long int partA = 0, partB = 0;
            if(tree[ tree[now_p].ch[small_ch] ].totalNode != 0) partA = Sum(tree[now_p].ch[small_ch], tree[ tree[now_p].ch[small_ch] ].totalNode);
            partB = Sum(tree[now_p].ch[!small_ch], nodes - tree[ tree[now_p].ch[small_ch] ].totalNode);
            return partA + partB;
        }
        return Sum(tree[now_p].ch[small_ch], nodes);
    }
}
void Merge(int new_r)
{
    int i;
    int m_node = root;
    int parent[32] = {0};
    int pp = 1;
    while(1){
        if(tree[m_node].lv == 1){
            /*Same value*/
            for(i = 32; i >= 1; i--){
                tree[m_node].change[i] += tree[new_r].change[i];
            }
            //printf("      %lld -> %lld\n",tree[m_node].change[i]- tree[new_r].change[i],tree[m_node].change[i] += tree[new_r].change[i]);
            tree[m_node].originSum += tree[new_r].originSum;
            tree[m_node].totalNode += tree[new_r].totalNode;
            break;
        }
        int n_bit = -1;
        if(tree[new_r].ch[0] != -1) n_bit = 0;
        else n_bit = 1;
        if(tree[m_node].ch[n_bit] == -1){
            tree[m_node].ch[n_bit] = tree[new_r].ch[n_bit];
            for(i = 32; i >= 1; i--){
                tree[m_node].change[i] += tree[new_r].change[i];
            }
            tree[m_node].originSum += tree[new_r].originSum;
            tree[m_node].totalNode += tree[new_r].totalNode;
            break;
        }
        else {
            cur_p--;
            tree[new_r].totalNode = 0;
            parent[pp++] = m_node;
            m_node = tree[m_node].ch[n_bit];
            new_r = tree[new_r].ch[n_bit];
        }
    }
    while(pp-- >= 1){
        for(i = 32; i >= 1; i--){
            tree[parent[pp]].change[i] += tree[new_r].change[i];
        }
        tree[parent[pp]].originSum += tree[new_r].originSum;
        tree[parent[pp]].totalNode += tree[new_r].totalNode;
    }

}
void ConstructTree(int value)
{
    int i;
    int o_v = value;
    int lv = 1;
    while(lv <= 32){
        tree[cur_p].totalNode = 1;
        tree[cur_p].lv = lv;
        tree[cur_p].originSum = o_v;
        for(i = lv-1; i >= 1; i--){
            tree[cur_p].change[i] = tree[cur_p-1].change[i];
        }
        if(lv == 1){
            if(((value)&1) > 0 ) tree[cur_p].change[lv] = -pow2[lv-1];
            else tree[cur_p].change[lv] = pow2[lv-1];
            tree[cur_p].ch[1] = -1;
            tree[cur_p].ch[0] = -1;
        }
        else {
            if(((value)&1) > 0 ) tree[cur_p].ch[1] = cur_p-1, tree[cur_p].ch[0] = -1;
            else tree[cur_p].ch[1] = -1, tree[cur_p].ch[0] = cur_p-1;
            if(((value >> 1)&1) > 0 ) tree[cur_p].change[lv] = -pow2[lv-1];
            else tree[cur_p].change[lv] = pow2[lv-1];
            value = value>>1;
        }
        lv++;
        cur_p++;
    }
    int tmp_p = cur_p-1;
    int tmp_parent = -1;
    while(tmp_p != -1){
        for(i = 32; i > tree[tmp_p].lv; i--){
            tree[tmp_p].change[i] = tree[tmp_parent].change[i];
        }
        tmp_parent = tmp_p;
        tmp_p = tree[tmp_p].ch[0];
        if(tmp_p == -1) tmp_p = tree[tmp_parent].ch[1];
    }
    if(root == -1) {
        root = cur_p-1;
    }
    return;
}
int main()
{
    //printf("%d\n", sizeof(tree));
    #ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
    int i, j, k;
    int caseNumber;
    scanf("%d", &caseNumber);
    long long int p2 = 1;
    for(i = 0; i < 33; i++) pow2[i] = p2, p2*=2;
    int c = 1;
    while(caseNumber-- >= 1){
        //printf("----- case: %d -----\n", c++);
        int size, opt;
        scanf("%d%d", &size, &opt);
        //for(i = 1; i < MaxNode; i++) tree[i].totalNode = 0;
        tree[root].ch[0] = -1, tree[root].ch[1] = -1;
        cur_p = 1, root = -1, xor_flag = 0;

        for(i = 1; i <= size; i++){
            int value;
            scanf("%d", &value);
            /*Construct sub tree*/
            ConstructTree(value);
            /*Merge*/
            if(i != 1) Merge(cur_p-1);
            #ifdef DBUGM_Tree
                ShowTree(root);
                system("pause");
            #endif
        }
        #ifdef DBUGM
            printf("Start Query\n");
        #endif

        for(i = 1; i <= opt; i++){
            int opt_k, opt_v;
            scanf("%d%d", &opt_k, &opt_v);
            #ifdef DBUGM
                printf("Query %d: %d %d\n", i, opt_k, opt_v);
            #endif
            if(opt_k == 1) {
               xor_flag = xor_flag^opt_v;
               //printf("%d\nflag:", opt_v);
               //for(j = 0; j < 32; j++) printf(" %d", (xor_flag>>j)&1 );
            }
            else {
                printf("%lld\n", Sum(root, opt_v));
            }
        }
    }
    return 0;
}
