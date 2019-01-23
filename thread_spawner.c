#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include "primedecompose.h"
#include "task_parameter.h"

#define OPTIONS "?t:i:n"

int main(int argc, char** argv)
{
    int opt;
    int taskTotal = 1, iterationMax = 10000;
    TaskParameter* parameterList = NULL;
    int testNumber = 0;
    pthread_t* threadList = NULL;
    FILE* testFile;
    char fileName[64];
    struct timeval start, end;
    double elapsedTime = 0;
    while( (opt = getopt(argc, argv, OPTIONS)) != -1)
    {
        switch (opt)
        {
            case 't':
                taskTotal = atoi(optarg);
                break;
            case 'i':
                iterationMax = atoi(optarg);
                break;
            case 'n':
                testNumber = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Supported arguments are -t number and -i number\n");
                return 1;

        }
    }
    sprintf(fileName,"ThreadTest-%dTasks-%dMax-TestNo%d.txt", taskTotal, iterationMax, testNumber);
    testFile = fopen(fileName, "a");
    parameterList = malloc(sizeof(TaskParameter) * taskTotal);
    threadList = malloc(sizeof(pthread_t) * (taskTotal - 1));


    allocateTasks(taskTotal, iterationMax, parameterList);
    gettimeofday(&start, NULL);
    for(int i = 1; i < taskTotal; ++i)
    {
        pthread_create(&threadList[i-1], NULL, decomposeTask, (void*)&parameterList[i]);
    }
    decomposeTask(&parameterList[0]);
    for(int i = 0; i < taskTotal - 1; ++i)
    {
        pthread_join(threadList[i], NULL);
    }
    gettimeofday(&end, NULL);
	elapsedTime = (end.tv_sec - start.tv_sec) * 1000;
	elapsedTime += (end.tv_usec - start.tv_usec) / 1000;
	fprintf(testFile, "Time elapsed: %f msec\n", elapsedTime);

    free(parameterList);
    free(threadList);
    fclose(testFile);
    return 0;
}