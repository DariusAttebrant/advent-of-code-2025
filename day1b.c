#include <stdio.h>

int zeroctr = 0;

void modulocount(int, int);
int main(void){

    FILE *fp = fopen("day1.txt", "r"); 
    char s[1024];
    int x = 0;
    int ctr = 0;

    while (fgets(s, sizeof s, fp) != NULL){
        x = 0;
        for (int i = 1; s[i] != '\n' && s[i] != '\0'; i++) {
            x = x*10 + (s[i] - '0');
            }
        
        if(s[0] == 'L'){
            modulocount(-x, 1);
        }
        else{
            modulocount(x, 0);
        }
        ctr++;
    }
    fclose(fp);
    printf("%d compared to 6386\n", zeroctr);
}

void modulocount(int turns, int left){
    static int tick = 50;
    if (left == 1){
        if (tick == 0){// special case starting at zero, prevent double count
            zeroctr -= 1;
        }
        while (turns + tick < 0){
            turns += 100;
            zeroctr++;
        }
        tick += turns;
        if (tick == 0){
            zeroctr++;
        }
    }
    else{
        while (turns + tick > 99){
            turns -= 100;
            zeroctr++;
        }
        tick += turns;

    }
}

