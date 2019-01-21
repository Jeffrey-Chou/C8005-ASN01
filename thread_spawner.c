#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include "primedecompose.h"
#include "task_parameter.h"

#define OPTIONS "?t:i:"

int main(int argc, char** argv)
{
    int opt;
    int taskTotal = 5, iterationMax = 10000;
    TaskParameter* parameterList = NULL;
    pthread_t* threadList = NULL;
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
            default:
                fprintf(stderr, "Supported arguments are -t number and -i number\n");
                return 1;

        }
    }

    parameterList = malloc(sizeof(TaskParameter) * taskTotal);
    threadList = malloc(sizeof(pthread_t) * (taskTotal - 1));


    allocateTasks(taskTotal, iterationMax, parameterList);

    for(int i = 1; i < taskTotal; ++i)
    {
        pthread_create(&threadList[i-1], NULL, decomposeTask, (void*)&parameterList[i]);
    }
    decomposeTask(&parameterList[0]);
    for(int i = 0; i < taskTotal - 1; ++i)
    {
        pthread_join(threadList[i], NULL);
    }


    free(parameterList);
    free(threadList);
    return 0;
}