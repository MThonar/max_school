#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 5
#define STATISTIC_TARGET 5

int array_lower1[ARRAY_LENGTH] = {68, 27, 55, 24, 83, 35, 67, 64, 46, 25};
int array_upper1[ARRAY_LENGTH] = {122, 102, 149, 25, 109, 40, 69, 157, 71, 37};
int array_lower_tri1[ARRAY_LENGTH] = {24, 25, 27, 35, 46, 55, 64, 67, 68, 83};
int array_upper_tri1[ARRAY_LENGTH] = {25, 37, 40, 69, 71, 102, 109, 122, 149, 157};

int array_lower2[ARRAY_LENGTH] = {80, 97, 87, 40, 18, 80, 56, 50, 38, 67};
int array_upper2[ARRAY_LENGTH] = {135, 177, 168, 100, 105, 91, 86, 124, 45, 95};
int array_lower_tri2[ARRAY_LENGTH] = {18, 38, 40, 50, 56, 67, 80, 80, 87, 97};
int array_upper_tri2[ARRAY_LENGTH] = {45, 86, 91, 95, 100, 105, 124, 135, 168, 177};

int		*ft_hist_length()
{
	int	first_length;
	int	second_length;
	int	array_length;
	int	min_hist_length;
	int	hist_lower_bound;
	int	*return_array;

	return_array = malloc(sizeof(int) * 3);
	if (!return_array)
		return NULL;
	return_array[2] = '\0';
	array_length = sizeof(array_upper_tri1)/sizeof(array_upper_tri1[0]);
	first_length = array_upper_tri1[array_length - 1] - array_lower_tri1[0];
	second_length = array_upper_tri2[array_length - 1] - array_lower_tri2[0];
	if (first_length <= second_length)
	{
		min_hist_length = first_length;
		hist_lower_bound = array_lower_tri1[0];
	}
	else
	{
		min_hist_length = second_length;
		hist_lower_bound = array_lower_tri2[0];
	}
	return_array[0] = min_hist_length;
	return_array[1] = hist_lower_bound;
	return (return_array);
}

float	*ft_equiwidth_freq(int *array_lowerx, int *array_upperx)
{
	int		i;
	int		j;
	int		min_hist_length;
	int		hist_lowest_bound;
	int		lower_bucket_bound;
	int		upper_bucket_bound;
	int		array_length;
	float	bucket_length;
	float	*buckets;
	float	increment;

	min_hist_length = ft_hist_length()[0];
	bucket_length = min_hist_length / STATISTIC_TARGET;
	hist_lowest_bound = ft_hist_length()[1];
	lower_bucket_bound = hist_lowest_bound;
	upper_bucket_bound = lower_bucket_bound + bucket_length;
	array_length = sizeof(array_upper1)/sizeof(array_upper1[0]);

	buckets = malloc(sizeof(float) * STATISTIC_TARGET + 1);
	if (!buckets)
		return NULL;
	buckets[STATISTIC_TARGET] = '\0';

	for (i = 0; i < STATISTIC_TARGET; i++)
	{
		for(j = 0; j < array_length; j++)
		{

			if((array_lowerx[j] > lower_bucket_bound) && (array_lowerx[j] < upper_bucket_bound))
			{
				increment = (upper_bucket_bound - array_lowerx[j]) / bucket_length;
				buckets[i] += increment;
			}
			else if((array_lowerx[j] <= lower_bucket_bound) && (array_upperx[j] >= upper_bucket_bound))
			{
				buckets[i] += 1 ;
			}
			else if((array_upperx[j] < upper_bucket_bound) && (array_upperx[j] > lower_bucket_bound))
			{
				increment = (array_upperx[j] - lower_bucket_bound) / bucket_length;
				buckets[i] += increment ;
			}
		}
		lower_bucket_bound = upper_bucket_bound;
		upper_bucket_bound += bucket_length;
	}
	return (buckets);
}

float estimation_cardinality_join(float* bucket1, float* bucket2)
{
    float list_join[STATISTIC_TARGET];
    int i = 0;
    for (i=0; i < STATISTIC_TARGET ; i++){
        list_join[i] = bucket1[i] * bucket2[i];
    }

    float estimation;
    for(i=0; i < STATISTIC_TARGET; i++){
        estimation += list_join[i] ;
    }
    return (estimation);
}

int    main(void)
{
	int i = 0;
    float *bucket1 = NULL;
    float *bucket2 = NULL;
    float estimation;
    bucket1 = ft_equiwidth_freq(array_lower1, array_upper1);
    /*printf("bucket1 = ( ");
	for(i = 0; i < STATISTIC_TARGET; i++)
		printf("%f ", bucket1[i]);
	printf(")\n");*/
    bucket2 = ft_equiwidth_freq(array_lower2, array_upper2);
   	/*printf("bucket2 = ( ");
	for(i = 0; i < STATISTIC_TARGET; i++)
		printf("%f ", bucket2[i]);
	printf(")\n");*/
    estimation = estimation_cardinality_join(bucket1, bucket2);
    free (bucket1);
    free (bucket2);
    printf("Join cardinality estimation = %f\n", estimation);
    return (0);
}
