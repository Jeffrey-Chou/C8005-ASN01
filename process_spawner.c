#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/wait.h>
#include "primedecompose.h"
#include "task_parameter.h"

int main(int argc, char** argv)
{
    pid_t childpid = 0;
    pid_t* childList;
    int taskTotal = 8, iterationMax = 100;
    TaskParameter* parameterList = malloc(sizeof(TaskParameter) * taskTotal);
    childList = malloc(sizeof(pid_t) * taskTotal - 1);

    allocateTasks(taskTotal, iterationMax, parameterList);

    for(int i = 1; i < taskTotal; ++i)
    {
        childpid = fork();
        if(childpid == 0)
        {
            decomposeTask(&parameterList[i]);
            return 0;
        }
        else
        {
            childList[i-1] = childpid;
        }
    }
    decomposeTask(&parameterList[0]);
    for(int i = 0; i < taskTotal - 1; ++i)
    {
        waitpid(childList[i], NULL, 0);
    }

    free(childList);
    free(parameterList);
    return 0;
}