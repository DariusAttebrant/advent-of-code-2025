#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *token;
char *ranges[1024][2];
char line[1024];
char *p = line;
int ctr = 0;
long long int ans1 = 0;
long long int ans2 = 0;
long long int ans2list[2048];
long long int ans2listmirror[2048] = {0};
int ans2tracker = 0;
int ans2mirrortracker = 0;

void splitter(char *line);
long long int part1(char *ranges[][2]);
long long int part2(char *ranges[][2]);

int main(void) {
    FILE *fp = fopen("day2.txt", "r");

    while (fgets(line, sizeof line, fp)) {
        p = line;
        splitter(line);
        ans1 = part1(ranges);
        ans2 = part2(ranges);
    }

    for (int i = 0; i < ctr; i++) {
        //printf("[%d] low=%s  high=%s\n", i, ranges[i][0], ranges[i][1]);
    }

    printf("\nfinal answer part 1: %lld\n",ans1);
}

void splitter(char *line){
    while ((token = strsep(&p, ",")) != NULL) {
        char *q = token;
        ranges[ctr][0] = strsep(&q, "-"); // low
        ranges[ctr][1] = strsep(&q, "-"); // high
        ctr++;
    }
}

long long int part1(char *ranges[][2]){
    for (int i = 0; i < ctr; i++) {
        long long int low = atoll(ranges[i][0]);
        long long int high = atoll(ranges[i][1]);
        //printf("low %lld high %lld\n", low, high);
        for (long long j = low; j <= high; j++){ // cycle through all possible values
            int digits[1024];
            int k = 0;
            long long num = j;
            // find length k of the value
            while (num > 0){
                digits[k] = num % 10;
                num = num / 10;
                k++;
            }
            if (k%2 == 0){
                int m = 1;
                char str[2048];
                sprintf(str, "%lld", j);
                str[k/2] = '\0';
                long long int prev = atoll(str);
                sprintf(str, "%lld", j);
                char current_str[2048];
                strncpy(current_str, str + m*k/2, k/2);
                current_str[k/2] = '\0';
                long long int current = atoll(current_str);
                if (current == prev){ // is it repeating?
                    ans1 += j;
                    //printf("%lld\n",ans1);
                }
            }
        }
    }
    printf("%lld\n",ans1);
    return ans1;
}


long long int part2(char *ranges[][2]){
    for (int i = 0; i < ctr; i++) {
        long long int low = atoll(ranges[i][0]);
        long long int high = atoll(ranges[i][1]);
        printf("low %lld high %lld\n", low, high);
        for (long long int j = low; j <= high; j++){
            int digits[1024];
            int k = 0;
            long long int num = j;
            while (num > 0){
                digits[k] = num % 10;
                num = num / 10;
                k++;
            }

            // modulo up to k/2 to find which lengths it is divisible by for possible lengths of repeats
            int len_poss[k/2];
            int pos = 0;
            for (int m = 1; m <= k/2; m++){
                if (k%m == 0){
                    len_poss[pos] = m;
                    pos++;
                }
            }
            //        printf("pos: %d k: %d\n", pos, k);
            

            // test if any of the possible repeat lengths give an invalid id
            for (int a = 0; a < pos; a++){ // loop that steps through all possible lengths
                long long int m = 1;
                char str[2048];
                sprintf(str, "%lld", j);
                str[len_poss[a]] = '\0';
                int prev = atoll(str);
                //printf("m %d\n",m);
                while (m*len_poss[a] <= k){ // for a given length checks if the id is invalid
                    sprintf(str, "%lld", j);
                    char current_str[2048];
                    strncpy(current_str, str + m*len_poss[a], len_poss[a]);
                    current_str[len_poss[a]] = '\0';
                    long long int current = atoll(current_str);
                    //printf("prev %d current %d\n", prev, current);

                    if (current == prev){ // is it the same as last check?
                        prev = current;
                        m++;
                    }
                    else{
                        m = 1024;
                    }
                    if (m*len_poss[a] == k){
                        //ans1 += j;
                        ans2list[ans2tracker] = j;
                        ans2tracker++;
                        //printf("%lld", ans2list[ans2tracker-1]);
                    }
                    
                }
            }
            }
    }
    

    for (int c = 0;c < ans2tracker; c++){
        int exists = 0;
        for (int d = 0; d < ans2tracker; d++){
            if (ans2list[c] == ans2listmirror[d]){
                exists = 1;
                break;
            }

        }
        if (!exists){
            ans2listmirror[ans2mirrortracker] = ans2list[c];
            ans2mirrortracker++;
        }
    }
    for (int e = 0; e < ans2mirrortracker; e++){
        ans2 += ans2listmirror[e];
    }
    printf("ans2 = %lld", ans2);

    return ans2;
}
