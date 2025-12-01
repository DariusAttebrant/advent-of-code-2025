#include <stdio.h>

int runningcount(int x){
    static int a = 50;
    a += x;
    while(a < 0){
        a = 100 + a;
    }
    while(a > 99){
        a = a - 100;
    }

    return a;
}

int my_strlen(char *s) {
    int count = 0;
    while (s[count] != '\0') // Single quotes for single char
        count++; 
    return count;
}

int main(void){

    FILE *fp; 
    int c;
    char s[1024];
    int zerocount = 0;
    int x = 0;
    int temp = 0;
    int ctr = 0;
    int len;
    fp = fopen("day1.txt", "r"); 

    while (fgets(s, sizeof s, fp) != NULL){
        x = 0;
        len = my_strlen(s) - 2;
        //for(int i = 1; i < len; i++){
        //    x += (10^(len - i - 1))*(s[i] - '0');
        //}
        for (int i = 1; s[i] != '\n'; i++) {
            x = x*10 + (s[i] - '0');
            }
        if(s[0] == 'L'){
            temp = runningcount(-x);
        }
        else{
            temp = runningcount(x);
        }
        if (temp == 0){
            zerocount++;
        }
        ctr++;
        printf("%s #0:s %d temp %d ctr %d x %d\n", s, zerocount, temp, ctr, x);
    }
    fclose(fp);


}




