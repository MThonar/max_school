#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 5

int array_lower[ARRAY_LENGTH] = {1, 2, 4, 9, 10};
int array_upper[ARRAY_LENGTH] = {5, 7, 12, 13, 15};
int array_lower_tri[ARRAY_LENGTH] = {1, 2, 4, 9, 10};
int array_upper_tri[ARRAY_LENGTH] = {5, 7, 12, 13, 15};

int statistic_target = 7; 		//nombre de buckets

int		*ft_range_length()
{
	int		i;
	int		*range_lengths;

	range_lengths = malloc(sizeof(int) * ARRAY_LENGTH);
	if (!range_lengths)
		return NULL;
	i = -1;
	while (i++ < ARRAY_LENGTH)
		range_lengths[i] = array_upper[i] - array_lower[i];
	return (range_lengths);
}

float	*ft_equiwidth_freq(int *array_lower, int *array_upper)
{
	int		i;
	int		j;
	int		hist_length;
	int		lowest_bound;
	int		lower_bucket_bound;
	int		upper_bucket_bound;
	float	bucket_length;
	float	*buckets;
	float	increment;

	hist_length = array_upper_tri[ARRAY_LENGTH - 1] - array_lower_tri[0];
	bucket_length = hist_length / statistic_target;
	lowest_bound = array_lower_tri[0];
	lower_bucket_bound = lowest_bound;
	upper_bucket_bound = lower_bucket_bound + bucket_length;

	buckets = malloc(sizeof(float) * statistic_target + 1);
	if (!buckets)
		return NULL;
	buckets[statistic_target + 1] = '\0';

	for (i = 0; i < statistic_target; i++)
	{
		for(j = 0; j < ARRAY_LENGTH; j++)
		{

			if((array_lower[j] > lower_bucket_bound) && (array_lower[j] < upper_bucket_bound))
			{
				increment = (upper_bucket_bound - array_lower[j]) / bucket_length;
				buckets[i] += increment;
			}
			else if((array_lower[j] <= lower_bucket_bound) && (array_upper[j] >= upper_bucket_bound))
			{
				buckets[i] += 1 ;
			}
			else if((array_upper[j] < upper_bucket_bound) && (array_upper[j] > lower_bucket_bound))
			{
				increment = (array_upper[j] - lower_bucket_bound) / bucket_length;
				buckets[i] += increment ;
			}
		}
		lower_bucket_bound = upper_bucket_bound;
		upper_bucket_bound += bucket_length;
	}
	return (buckets);
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
	return (0);
}
