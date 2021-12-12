#include <stdio.h>
#include <stdlib.h>

int array_lower1[5] = {3, 0, 7, 3, 10};
int array_upper1[5] = {7, 5, 11, 5, 14};
int array_lower_tri1[5] = {0, 3, 3, 7, 10};
int array_upper_tri1[5] = {5, 5, 7, 11, 14};

int array_lower2[5] = {11, 9, 3, 12, 0};
int array_upper2[5] = {17, 15, 7, 14, 8};
int array_lower_tri2[5] = {0, 3, 9, 11, 12};
int array_upper_tri2[5] = {7, 8, 14, 15, 17};

int statistic_target = 7; 		//nombre de buckets

int		ft_array_length(int *arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int		*ft_range_length()
{
	int		length;
	int		i;
	int		j;
	int		*range_lengths;
	float	*buckets;

	length = ft_array_length(array_lower1);
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
	array_length = ft_array_length(array_upper_tri1);
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

float	*ft_equiwidth_freq(int *array_lowerx, int *array_upperx, int *range_length)
{
	int		i;
	int		j;
	int		min_hist_length;
	int		hist_lowest_bound;
	int		lower_bucket_bound;
	int		upper_bucket_bound;
	float	bucket_length;
	float	*buckets;
	float	increment;

	min_hist_length = ft_hist_length()[0];
	bucket_length = min_hist_length / statistic_target;
	hist_lowest_bound = ft_hist_length()[1];
	lower_bucket_bound = hist_lowest_bound;
	upper_bucket_bound = lower_bucket_bound + bucket_length;

	buckets = malloc(sizeof(float) * statistic_target + 1);
	if (!buckets)
		return NULL;
	buckets[statistic_target + 1] = '\0';

	for (i = 0; i < statistic_target; i++)
	{
		for(j = 0; j < ft_array_length(array_upperx); j++)
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
	float *bucket1;
	float *bucket2;
	int i = 0;
	int *range_length = ft_range_length();
	int sauce;

	sauce = ft_array_length(array_lower1);
	bucket1 = ft_equiwidth_freq(array_lower1, array_upper1, range_length);
	bucket2 = ft_equiwidth_freq(array_lower2, array_upper2, range_length);

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
	free (bucket1);
	free (bucket2);
	free (range_length);
	return (0);
}
