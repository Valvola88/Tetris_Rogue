#include <string.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int score = 10;
    char score_array[8];

    char score_char[8];

    for(int i = 0; i< 8;i++){
        int sc = score;
        memset(score_array, '0', 8);
        printf("Score_1: %d ", score);
        sprintf(score_char, "%i", score);
        //printf("Score_2: %d ", score);
        sprintf(&score_array[8 - strlen(score_char)], "%s", score_char);
        //printf("Score_3: %d ", score);
        //printf("%s | %d\n",score_array, score);
        score = score * 10;
    }

    return 0 ;
}