#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 5

int array_lower[ARRAY_LENGTH] = {0, 2, 7, 19, 22};
int array_upper[ARRAY_LENGTH] = {9, 14, 15, 27, 30};
int array_lower_tri[ARRAY_LENGTH] = {0, 2, 7, 19, 22};
int array_upper_tri[ARRAY_LENGTH] = {9, 14, 15, 27, 30};

int statistic_target = 6; 		//nombre de bucket

float	*ft_equiwidth_freq(int *array_lower, int *array_upper)
{
	int		i;
	int		j;
	int		hist_length;
	int		lowest_bound;
	int		lower_bucket_bound;
	int		upper_bucket_bound;
	float	bucket_length;
	float	*bucket;
	float	increment;

	hist_length = array_upper_tri[ARRAY_LENGTH - 1] - array_lower_tri[0];
	bucket_length = hist_length / statistic_target;
	lowest_bound = array_lower_tri[0];
	lower_bucket_bound = lowest_bound;
	upper_bucket_bound = lower_bucket_bound + bucket_length;

	bucket = malloc(sizeof(float) * statistic_target + 1);
	if (!bucket)
		return NULL;
	bucket[statistic_target + 1] = '\0';

	for (i = 0; i < statistic_target; i++)
	{
		for(j = 0; j < ARRAY_LENGTH; j++)
		{

			if((array_lower[j] > lower_bucket_bound) && (array_lower[j] < upper_bucket_bound))
			{
				increment = (upper_bucket_bound - array_lower[j]) / bucket_length;
				bucket[i] += increment;
			}
			else if((array_lower[j] <= lower_bucket_bound) && (array_upper[j] >= upper_bucket_bound))
			{
				bucket[i] += 1 ;
			}
			else if((array_upper[j] < upper_bucket_bound) && (array_upper[j] > lower_bucket_bound))
			{
				increment = (array_upper[j] - lower_bucket_bound) / bucket_length;
				bucket[i] += increment ;
			}
		}
		lower_bucket_bound = upper_bucket_bound;
		upper_bucket_bound += bucket_length;
	}
	return (bucket);
}

int	main(void)
{
	float *bucket;
	int i = 0;
	bucket = ft_equiwidth_freq(array_lower, array_upper);

	while (i < statistic_target)
	{
		printf("\nbucket[%d] -> %.1f",i , bucket[i]);
		i++;
	}
	printf("\n");
	free (bucket);
	return (0);
}
