#include <stdio.h>
#include <stdlib.h>

int array_lower1[5] = {1, 2, 4, 9, 10};
int array_upper1[5] = {5, 7, 12, 13, 15};
int array_lower_tri1[5] = {1, 2, 4, 9, 10};
int array_upper_tri1[5] = {5, 7, 12, 13, 15};

int array_lower2[5] = {0, 2, 7, 19, 22};
int array_upper2[5] = {9, 14, 15, 27, 30};
int array_lower_tri2[5] = {0, 2, 7, 19, 22};
int array_upper_tri2[5] = {9, 14, 15, 27, 30};

int statistic_target = 7; 		//nombre de buckets

int		*ft_range_length()
{
	int		length;
	int		i;
	int		*range_lengths;

	length = sizeof(array_lower1)/sizeof(array_lower1[0]);
	range_lengths = malloc(sizeof(int) * length);
	if (!range_lengths)
		return NULL;
	i = -1;
	while (i++ < length)
		range_lengths[i] = array_upper1[i] - array_lower1[i];
	return (range_lengths);
}

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
    int     array_length;
	float	bucket_length;
	float	*buckets;
	float	increment;

	min_hist_length = ft_hist_length()[0];
	bucket_length = min_hist_length / statistic_target;
	hist_lowest_bound = ft_hist_length()[1];
	lower_bucket_bound = hist_lowest_bound;
	upper_bucket_bound = lower_bucket_bound + bucket_length;
    array_length = sizeof(array_upper1)/sizeof(array_upper1[0]);


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
		}
		lower_bucket_bound = upper_bucket_bound;
		upper_bucket_bound += bucket_length;
	}
	return (buckets);
}

int	main(void)
{
	float *bucket1;
	float *bucket2;
	int i = 0;
	bucket1 = ft_equiwidth_freq(array_lower1, array_upper1);
	bucket2 = ft_equiwidth_freq(array_lower2, array_upper2);

	while (i < statistic_target)
	{
		printf("\nbucket1[%d] -> %.1f",i , bucket1[i]);
		i++;
	}
	printf("\n");
	i = 0;
	while (i < statistic_target)
	{
		printf("\nbucket2[%d] -> %.1f",i , bucket2[i]);
		i++;
	}
	printf("\n");
	return (0);
}
