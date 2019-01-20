#ifndef _TASK_PARAMETER_H_
#define _TASK_PARAMETER_H_

#include <math.h>
#include <stdio.h>
#define FILENAMESIZE 64

typedef struct TaskParameter
{
    FILE* outputFile;
    FILE* debugFile;
    int start;
    int end;
} TaskParameter;

void allocateTasks(int taskTotal, int maxIteration, TaskParameter* parameterList);
void setRange(TaskParameter* parameter, int start, int end);
void openFiles(TaskParameter* parameter, int start, int end);
void closeFiles(TaskParameter* parameter);

#endif