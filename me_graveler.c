#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int ATTEMPTS = 1000000000;
int rolls = ATTEMPTS;
int maxOnes = 0;
int score;
int number;

int main(void){
    clock_t start_time, end_time;
    double cpu_time_used;

    srand(time(NULL));

    start_time = clock();
    for(int i = 0; i < ATTEMPTS; i++){
        if(maxOnes >= 177){
            rolls = i;
            break;
        }
        score = 0;
        for (int j = 0; j < 231; ){
            number =  rand()*rand(); //rand is taking 2.5 seconds per million iterations
            
            while (number>4){
                score+= (number%4)==1;
                number = number / 4;
                j++;
                if (j == 231){
                    break;
                }
            }
            if ((maxOnes-score)>(231-j)){
                break;
            }
        }
        if(score > maxOnes){
            maxOnes = score;
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("highest roll: %d \n", maxOnes);
    printf("number of rolls: %d \n", rolls);
    printf("time taken: %f \n", cpu_time_used);

    return 0;
}

/*
TIME TAKEN FOR 1,000,000,000 656.576 seconds.
TIME TAKEN FOR 1,000,000 0.702 seconds
*/