#ifndef _PRIMEDECOMPOSE_H_
#define _PRIMEDECOMPOSE_H_
#include <gmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "task_parameter.h"

void decomposeTask(TaskParameter* paramter);
int decompose(mpz_t n, mpz_t *o);
#endif
