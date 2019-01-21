#include "task_parameter.h"

void allocateTasks(int taskTotal, int maxIteration, TaskParameter* parameterList)
{
    int increment = (int) ceil(maxIteration/taskTotal);
    int index = 0, startValue = 2; 
    int endValue = taskTotal == 1? maxIteration: startValue + increment -1;
    setRange(&parameterList[index], startValue, endValue);
    openFiles(&parameterList[index], startValue, endValue);
    if(taskTotal == 1)
    {
        return;
    }
    ++index;
    for(; index < taskTotal-1; ++index)
    {
        startValue = ++endValue;
        endValue = startValue + increment - 1;
        setRange(&parameterList[index], startValue, endValue);
        openFiles(&parameterList[index], startValue, endValue);
    }
    startValue = ++endValue;
    endValue = maxIteration;
    setRange(&parameterList[index], startValue, endValue);
    openFiles(&parameterList[index], startValue, endValue);
}

void setRange(TaskParameter* parameter, int start, int end)
{
    parameter->start = start;
    parameter->end = end;
}

void openFiles(TaskParameter* parameter, int start, int end)
{
    char fileName[FILENAMESIZE];
    sprintf(fileName, "Task %d-%d.txt", start, end);
    parameter->outputFile = fopen(fileName, "w");
    sprintf(fileName, "Debug %d-%d.txt", start, end);
    parameter->debugFile = fopen(fileName, "w");
}
void closeFiles(TaskParameter* parameter)
{
    fclose(parameter->outputFile);
    fclose(parameter->debugFile);
}

