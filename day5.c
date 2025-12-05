#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long ans1 = 0;
long long ans2 = 0;
int rngctr = 0;
long long ranges[1024][2];
int deleted_rng[1024] = {0};

long long part1(char *);
long long part2(void);
void removeX(void);
void splitter(char*);
int contains(long long arr[131072], int size, int k);
void merger(long long ranges[1024][2]);
long long min(long long, long long);
long long max(long long, long long);


int main(void){
    FILE * fp = fopen("day5.txt", "r");
    char line[1024] = {0};
    int ingredients = 0;
    while (fgets(line, sizeof line, fp) != NULL){
        printf("line is : %s", line);
        if (line[0] == '\0' || line[0] == ' ' || line[0] == '\n'){
            ingredients = 1;
        }
        if (ingredients == 0){
            splitter(line); 
            rngctr++;
        }
        else{
            ans1 += part1(line);
        }
    }
    printf("\nstart part 2:\n");
    ans2 = part2();
    printf("answer part 1: %lld\n", ans1);
    printf("answer part 2: %lld\n", ans2);
    fclose(fp);
}

long long part1(char *line){
    int idx = rngctr;
    long long num = atoll(line);
    for (int i = 0; i < idx; i++){
        if (num >= ranges[i][0] && num <= ranges[i][1]){
            return 1;
        }
    }
    return 0;
}

long long part2(void){
    merger(ranges);
    long long idlist[131072];
    long long tot = 0;
    for (int i = 0; i < rngctr; i++){
        if (deleted_rng[i] != 1){
            tot += ranges[i][1] - ranges[i][0] + 1;
            printf("%d     h %lld   l %lld   tot %lld\n", i, ranges[i][1], ranges[i][0], tot);
        }
        
    }
    
    return tot;
}

void splitter(char *line){
    char *p = line;
    char *q;
    int l1 = 0;
    while (line[l1] != '\0'){
        l1++;
    }
    char *e = &line[l1];
    
    int l2 = 0;
    while (line[l2] != '-'){
        l2++;
    }
    q = &line[l2 + 1];
    line[l2] = '\0';
    char high[100];
    char low[100];
    strcpy(high, p);
    strcpy(low, q);
    
    ranges[rngctr][0] = atoll(p);
    ranges[rngctr][1] = atoll(q);

    //printf("pointers: %c, and %c ", *p, *q);
    //printf("supposed values: %s, and %s\n", ranges[rngctr][0], ranges[rngctr][1]);

}

int contains(long long arr[131072], int size, int k){
    int i;
    for(i = 0; i < size; i ++){
        if(k == arr[i]){
            return 1;
        }
    }
    return 0;

}

void merger(long long ranges[1024][2]){
    int flag = 1;
    while(flag == 1){
        printf("going another round \n");
        flag = 0;
        for (int i = 0; i < rngctr; i++){
            for (int j = 0; j < rngctr; j++){
                if (j != i && deleted_rng[j] == 0 && deleted_rng[i] == 0){
                    long long low1 = min(ranges[i][0], ranges[i][1]);
                    long long high1 = max(ranges[i][0], ranges[i][1]);
                    long long low2 = min(ranges[j][0], ranges[j][1]);
                    long long high2 = max(ranges[j][0], ranges[j][1]);
                    
                    // cases of no overlap
                    if (high1 < low2 || high2 < low1){
                        continue;
                    }
                    else{ // in all other cases merge the ranges and delete the second one in the right manner
                        printf("priori deletion  %lld  %lld          %lld  %lld     ", low1, high1, low2, high2);

                        ranges[i][0] = min(low1, low2);
                        ranges[i][1] = max(high1, high2);
                        
                        deleted_rng[j] = 1;
                        flag = 1;
                        printf("post deletion i=%d %lld  %lld     j= %d  %lld  %lld\n", i, ranges[i][0], ranges[i][1], j, ranges[j][0], ranges[i][1]);                        
                    }

                }
            }
        }
    }
    for (int i = 0; i < rngctr; i++){
        //printf("%lld", *ranges[i][0]);
        if (deleted_rng[i] == 1){
            printf("delted indexes%d\n", i);
        }
    }
    for (int i = 0; i < rngctr; i++){
        //printf("%lld", *ranges[i][0]);
        if (deleted_rng[i] != 1){
            printf("not deleted indexes%d     %lld     %lld\n", i, ranges[i][0], ranges[i][1]);
        }
    }
}

long long min(long long a, long long b){
    if (a <= b){
        return a;
    }
    else{
        return b;
    }
}

long long max(long long a, long long b){
    if (a >= b){
        return a;
    }
    else{
        return b;
    }
}



