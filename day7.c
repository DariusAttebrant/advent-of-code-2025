#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ans1 = 0;
long long ans2 = 0;
char textblock[1024][256] = {0};
int ctr = 0;
int linelen = 0;

int part1(void);
long long part2(void);

int main(void){
    FILE * fp = fopen("day7.txt", "r");
    char line[1024] = {0};
    while (fgets(line, sizeof line, fp)){
        strcpy(textblock[ctr], line);
        ctr++;
    }
    ans1 = part1();
    ans2 = part2();
    printf("\nanswer part 1: %d\n", ans1);
    printf("answer part 2: %lld\n", ans2);
    /*
    for (int i = 0; i< ctr; i++){
        printf("%s", textblock[i]);
    }
    printf("%c", textblock[2][5]);
    */
    fclose(fp);
}

int part1(void){
    printf("\np1 start\n");
    
    int row = 1;
    int col = 0;
    int count = 0;

    while (textblock[linelen][0] != '\0'){
        linelen++;
    }

    //printf("%d\n", linelen);
    while (row <= ctr){
        /*
        printf("%c %c", '\n','\n');
        for (int i = 0; i< ctr; i++){
            printf("%s", textblock[i]);
        }
        */
        while (col < linelen){
            if (textblock[row - 1][col] == 'S' || textblock[row - 1][col] == '|'){
                if (textblock[row][col] == '.'){
                    textblock[row][col] = '|';
                }
                if (textblock[row][col] == '^'){
                    if (col > 0){
                        textblock[row][col - 1] = '|';
                    }
                    if (col < linelen){
                        textblock[row][col + 1] = '|';
                    }
                    count++;
                
                }
            }
            col++;
        }
        col = 0;
        row++;
    }
    printf("\np1 end %d\n", count);
    return count;
}

long long part2(void){
    printf("p2 start");
    int row = 1;
    int col = 0;
    long long count2 = 0;
    long long numblock[1048][256] = {0};

    while (row <= ctr){
        while (col < linelen){
            if (textblock[row][col] == '|'){
                if (textblock[row - 1][col] == 'S'){
                    numblock[row][col] = 1;
                }
                if (textblock[row - 1][col] == '|'){
                    numblock[row][col] += numblock[row - 1][col];
                }
                if (col > 0 && textblock[row][col - 1] == '^'){
                    numblock[row][col] += numblock[row - 1][col - 1];
                }
                if (col < linelen && textblock[row][col + 1] == '^'){
                    numblock[row][col] += numblock[row - 1][col + 1];
                }
            }
            col++;
        }
        col = 0;
        row++;
    }

    for (int i = 0; i < linelen; i++){
        count2 += numblock[ctr - 1][i];
        //printf("%lld\n", numblock[ctr][i]);
    }
    /*
    printf("%c %c", '\n','\n');
    for (int i = 0; i< ctr; i++){
        for (int j = 0; j < linelen; j++){
            printf("%lld", numblock[i][j]);
        }
        printf("\n");
    }
    */
    
    return count2;
}
