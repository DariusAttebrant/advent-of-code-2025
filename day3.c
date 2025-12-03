#include <stdio.h>
#include <stdlib.h>

int ans1 = 0;
long long ans2 = 0;
char indexlist[12] = {0}; 

int part1(char[1024]);
long long part2(char[1024]);
int findbiggest(char[1024], int, int);

int main(void){
    FILE * fp = fopen("day3.txt", "r");
    char line[1024] = {0};
    
    while (fgets(line, sizeof line, fp)) {
        ans1 += part1(line);
        ans2 += part2(line);
    }
    printf("answer part 1: %d\n", ans1);
    printf("answer part 2: %lld\n", ans2);
}

int part1(char *line){
    int decade = 0;
    int singularis = 0;
    for (int i = 0; line[i+1] - '0' > 0; i++){
        int numd = line[i] - '0';
        if (numd < 1){
            break;
        }
        if (numd > decade){
            decade = numd;
            singularis = 1;
        }
        for (int j = i+1; line[j] - '0' > 0; j++){
            int nums = line[j] - '0';
            if (nums < 1){
                break;
            }
            if (nums > singularis && numd >= decade){
                singularis = nums;
            }
        }
    }
    return (decade*10 + singularis);
}

long long part2(char *line){
    char biggest[12] = {0}; 
    biggest[0] = findbiggest(line, 0, 0);
    for (int i = 1; i < 12; i++){
        biggest[i]= findbiggest(line, indexlist[i - 1] + 1, i);

    }
    char tempstr[13];
    for (int n = 0; n < 12; n++){
        tempstr[n] = biggest[n] + '0';
    }
    tempstr[12] = '\0';
    printf("test %lld\n", ans2);

    return atoll(tempstr);
}

int findbiggest(char *line, int start, int its){
    int localbig = 0;
    for (int k = start; line[k + 11 - its] - '0' > 0; k++){
        if (line[k] - '0' > localbig){
            localbig = line[k] - '0';
            indexlist[its] = k;
            if (localbig == 9){
                break;
            }
        }

    }
    printf("biggest %d index %d\n", localbig, indexlist[its]);
    return localbig;
}


