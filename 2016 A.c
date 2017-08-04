int main()
{
    int i, j, k;
    while(1){
        int n;
        scanf("%d", &n);
        if(n == 0 ) break;
        int input[105][105] = {0};
        for(i = 1; i <= n; i++){
            for(j = 1; j <= i; j++){
                scanf("%d", &input[i][j]);
            }
        }
        int table[105][105] = {0};
        for(i = 1; i <= n; i++){
            for(j = 1; j <= i; j++){
                if(table[i-1][j] + input[i][j] > table[i][j]) table[i][j] = table[i-1][j] + input[i][j];
                if(table[i-1][j-1] + input[i][j] > table[i][j]) table[i][j] = table[i-1][j-1] + input[i][j];
            }
        }
        /*for(i = 1; i <= n; i++){
            for(j = 1; j <= i; j++){
                printf("%d ", table[i][j]);
            }
            printf("\n");
        }
            printf("\n");*/
        int max = 0;
        for(i = 1; i <= n; i++ ){
            if(table[n][i] > max) max = table[n][i];
        }
        printf("%d\n", max);

    }
    return 0 ;
}
