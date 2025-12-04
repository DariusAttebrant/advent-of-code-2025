#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ans1 = 0;
long long ans2 = 0;
char textblock[1024][256] = {0};
int ctr = 0;

int basic_count(void);
long long part2(void);
void removeX(void);

int main(void){
    FILE * fp = fopen("day4.txt", "r");
    char line[1024] = {0};
    while (fgets(line, sizeof line, fp)){
        strcpy(textblock[ctr], line);
        ctr++;

    }
    ans1 = basic_count();
    ans2 = part2();
    printf("answer part 1: %d\n", ans1);
    printf("answer part 2: %lld\n", ans2);
    /*
    for (int i = 0; i< ctr; i++){
        printf("%s", textblock[i]);
    }
    printf("%c", textblock[2][5]);
    */
    fclose(fp);
}

int basic_count(void){
    int adjacent = 0;
    int row = 0;
    int col = 0;
    int movable = 0;
    while (textblock[row][col] == '.' || textblock[row][col] == '@' || textblock[row][col] == 'x'){
            while (textblock[row][col] == '.' || textblock[row][col] == '@' || textblock[row][col] == 'x'){
                if (textblock[row][col] == '@' || textblock[row][col] == 'x'){
                    for (int i = -1; i <= 1; i++){
                        for (int j = -1; j <= 1; j++){
                            if (textblock[row + i][col + j] == '@' || textblock[row + i][col + j] == 'x'){
                                adjacent++;
                            }
                        }
                    }
                    if (adjacent <= 4){
                        movable++;
                        textblock[row][col] = 'x';
                    }
                }
                col++;
                adjacent = 0;
        }
        col = 0;
        row++;
    }
    return movable;
}

long long part2(void){
    int totcount = 0;
    int lastcount = 1;

    while (lastcount > 0){
    /*
        printf("\n");
        for (int i = 0; i< ctr; i++){
            printf("%s", textblock[i]);
        }
        printf("%c", textblock[2][5]);
        printf("\n");
    */
        lastcount = basic_count();
        totcount += lastcount;
        
        removeX();
    }
    return totcount;
}

void removeX(void){
    int row  = 0;
    int col  = 0;
    while (textblock[row][col] == '.' || textblock[row][col] == '@' || textblock[row][col] == 'x'){
        while (textblock[row][col] == '.' || textblock[row][col] == '@' || textblock[row][col] == 'x'){
            if (textblock[row][col] == 'x'){
                    textblock[row][col] = '.';
            }
            col++;
            }
        row++;  
        col = 0;
    }
    return;
}



