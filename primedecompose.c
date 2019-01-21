#include "primedecompose.h"

#define MAX_FACTORS	1024
void* decomposeTask(void* taskparameter)
{
	TaskParameter* parameter = (TaskParameter*) taskparameter;
	mpz_t dest[MAX_FACTORS];
	mpz_t n;
  	int i,j, l;
	char numberStr[24];
	struct timeval start, end;
	double elapsedTime;
	gettimeofday(&start, NULL);
	for(j=parameter->start; j <= parameter->end; ++j)
	{
		sprintf(numberStr,"%d", j);
		fprintf(parameter->outputFile, "%s = ",numberStr);
		mpz_init_set_str(n, numberStr, 10);
		l = decompose(n, dest);
	
		for(i=0; i < l; i++) 
		{
				gmp_fprintf(parameter->outputFile, "%s%Zd", i?" * ":"", dest[i]);
				mpz_clear(dest[i]);
		}
		fprintf(parameter->outputFile, "\n");

	}
	gettimeofday(&end, NULL);
	elapsedTime = (end.tv_sec - start.tv_sec) * 1000;
	elapsedTime += (end.tv_usec - start.tv_usec) / 1000;
	fprintf(parameter->debugFile, "Time elapsed: %f msec\n", elapsedTime);
	return NULL;

}

int decompose (mpz_t n, mpz_t *o) 
{
	int i = 0;
  	mpz_t tmp, d;
 
	mpz_init(tmp);
  	mpz_init(d);
 
  	while (mpz_cmp_si (n, 1)) 
	{
    		mpz_set_ui(d, 1);
    		do 
		{
      			mpz_add_ui(tmp, d, 1);
      			mpz_swap(tmp, d);
    		} while(!mpz_divisible_p(n, d));
    		mpz_divexact(tmp, n, d);
    		mpz_swap(tmp, n);
    		mpz_init(o[i]);
    		mpz_set(o[i], d);
    		i++;
  	}
  	return i;
}
