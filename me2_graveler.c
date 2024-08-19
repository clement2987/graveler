#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int ALL_ATTEMPTS = 1000000;
int all_threads = 1;

typedef struct {
    int id;
    int rolls;
    int score;
} threadData;

void work(threadData* data);
DWORD count_threads(void);

// Function to be executed by the thread
DWORD WINAPI ThreadFunction(LPVOID lpParam) {
    threadData* data = (threadData*)lpParam;
    printf("Thread %d is running.\n", data->id);
    work(data);
    printf("Thread %d is finished.\n", data->id);
    return 0;
}

int main(int argc, char* argv[]) {

    clock_t start_time, end_time;
    double cpu_time_used;
    start_time = clock();

    srand(time(NULL));

    
    DWORD numCPU = count_threads();
    // safety checks
    if (argc != 2){
        printf("Number of logical processors: %u\n", numCPU);
        printf("make sure all_threads are set to a number smaller than %u and recompile\nthen run ./graveler.exe s to execute the program with all threads");
        return 0;
    }
    if (argv[1][0] != 's'){
        printf("s must be the first command line argument to indicate the user is confident it is safe to run");
        return 1;
    }
    if (all_threads > numCPU){
        printf("attempting to run %d threads when only %u are available. exiting the program\n");
        return 2;
    }

    


    HANDLE threads[all_threads];
    DWORD threadIDs[all_threads];
    threadData threadParams[all_threads]; // Parameters for the threads

    for (int i = 0; i < all_threads; i++){
        threadParams[i].id = i+1;
        threadParams[i].score = 0;
        threadParams[i].rolls = 0;
    }

    // Create two threads
    for (int i = 0; i < all_threads; i++) {
        threads[i] = CreateThread(
            NULL,                   // Default security attributes
            0,                      // Default stack size
            ThreadFunction,         // Thread function
            &threadParams[i],       // Parameter to the thread function
            0,                      // Default creation flags
            &threadIDs[i]           // Receives the thread identifier
        );

        if (threads[i] == NULL) {
            printf("Error creating thread %d\n", i + 1);
            return 1;
        }
    }

    // Wait for both threads to finish
    WaitForMultipleObjects(all_threads, threads, TRUE, INFINITE);

    // Close thread handles
    for (int i = 0; i < all_threads; i++) {
        CloseHandle(threads[i]);
    }

    // report data
    int best_score = 0;
    int total_rolls = 0;
    for (int i = 0; i < all_threads; i++) {
        total_rolls+= threadParams[i].rolls;
        if (threadParams[i].score > best_score){
            best_score = threadParams[i].score;
        }
    }

    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("highest roll: %d \n", best_score);
    printf("number of rolls: %d \n", total_rolls);
    printf("time taken: %f \n", cpu_time_used);
    return 0;
}

void work(threadData* data){
    int score = 0;
    int number;
    const int ATTEMPTS = ALL_ATTEMPTS / all_threads;
    data->rolls = ATTEMPTS;
    for(int i = 0; i < ATTEMPTS; i++){
        if(score >= 177){
            data->rolls = i;
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
            if ((data->score-score)>(231-j)){
                break;
            }
        }
        if(score > data->score){
            data->score = score;
        }
    }
    return;
}

DWORD count_threads(void){
    SYSTEM_INFO sysinfo;
    GetSystemInfo(&sysinfo);

    // Number of logical processors
    DWORD numCPU = sysinfo.dwNumberOfProcessors;

    return numCPU;
}

/*
TIME TAKEN FOR 1,000,000,000 120.35 seconds with 10 threads.
TIME TAKEN FOR 1,000,000 0.134 seconds
*/