#include <stdio.h>

int zeroctr = 0;

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
    int x = 0;
    int ctr = 0;
    int len;
    fp = fopen("day1.txt", "r"); 

    while (fgets(s, sizeof s, fp) != NULL){
        static int dial = 50;
        x = 0;
        len = my_strlen(s) - 2;
        for (int i = 1; s[i] != '\n' && s[i] != '\0'; i++) {
            x = x*10 + (s[i] - '0');
            }
        
        if(s[0] == 'L'){
            for(int j = 0; j < x; j++){
                dial--;
                if (dial < 0){
                    dial = 99;
                }
                if (dial == 0){
                    zeroctr++;
                }
            }
        }
        else{
            for(int j = 0; j < x; j++){
                dial++;
                if (dial >99){
                    dial = 0;
                }
                if (dial == 0){
                    zeroctr++;
                }
            }        
        }

        ctr++;
        //printf("%s #0:s %d x %d\n", s, zeroctr, x);
    }
    fclose(fp);
    printf("ans = %d\n", zeroctr);

}




