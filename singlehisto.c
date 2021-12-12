#include <stdio.h>
#include <stdlib.h>

int array_lower[5] = {3, 0, 7, 3, 10};
int array_upper[5] = {7, 5, 11, 5, 14};
int array_lower_tri[5] = {0, 3, 3, 7, 10};
int array_upper_tri[5] = {5, 5, 7, 11, 14};

int statistic_target = 7; 		//nombre de buckets

int		ft_array_length(int *arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("\n arr[i]: %d\n", arr[i]);
		i++;
		printf("\n arr[i]: %d\n", arr[i]);
		printf("ft_array_length : %d\n", i);
	}
	return (i);
}

int		*ft_range_length()
{
	int		length;
	int		i;
	int		j;
	int		*range_lengths;
	float	*buckets;

	length = ft_array_length(array_lower);
	printf("\nlength : %d\n", length);
	range_lengths = malloc(sizeof(int) * length);
	if (!range_lengths)
		return NULL;
	i = -1;
	while (i++ < length)
		range_lengths[i] = array_upper[i] - array_lower[i];
	return (range_lengths);
}

float	*ft_equiwidth_freq(int *array_lowerx, int *array_upperx, int *range_length)
{
	int		i;
	int		j;
	int		hist_length;
	int		lowest_bound;
	int		lower_bucket_bound;
	int		upper_bucket_bound;
	int		array_length;
	float	bucket_length;
	float	*buckets;
	float	increment;

	array_length = ft_array_length(array_lower);
	printf("array_length: %d\n", array_length);
	hist_length = array_upper_tri[array_length] - array_lower_tri[0];
	printf("%d", hist_length);
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
			// else -> nothing happens
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
	int *range_length = ft_range_length();

	bucket = ft_equiwidth_freq(array_lower, array_upper, range_length);
	while (i < statistic_target)
	{
		printf("\nbucket[%d] -> %.1f",i , bucket[i]);
		i++;
	}
	printf("\n");
	free (bucket);
	free (range_length);
	return (0);
}
