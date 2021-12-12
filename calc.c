#include <stdio.h>
#include <stdlib.h>

int array_lower1[5] = {2, 10, 4, 1, 9};
int array_upper1[5] = {7, 15, 12, 5, 13};
int array_lower_tri1[5] = {1, 2, 4, 9, 10};
int array_upper_tri1[5] = {5, 7, 12, 13, 15};

int array_lower2[5] = {2, 0, 7, 19, 22};
int array_upper2[5] = {9, 14, 15, 27, 30};
int array_lower_tri2[5] = {0, 2, 7, 19, 22};
int array_upper_tri2[5] = {9, 14, 15, 27, 30};

int statistic_target = 5; 		//nombre de buckets

int		array_length(int *arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

int		*range_length()
{
	int		length;
	int		i;
	int		j;
	int		*range_lengths;
	float	*buckets;

	length = array_length(array1);
	range_lengths = malloc(sizeof(int) * length);
	if (!range_lengths)
		return NULL;
	i = -1;
	while (i++ < length)
		range_lengths[i] = array_upper1[i] - array_lower1[i];
	return (range_lengths);
}

int		hist_length()
{
	int first_length;
	int second_length;
	int array_length;
	int min_hist_length;

	array_length = array_length(array_upper_tri1);
	first_length = array_upper_tri1[array_length - 1] - array_lower_tri1[0];
	second_length = array_upper_tri2[array_length - 1] - array_lower_tri2[0];
	if (first_length < second_length)
		min_hist_length = first_length;
	else
		min_hist_length = second_length;
	return (min_hist_length);
}

void	equiwidth_freq()
{
	int i;
	int j;
	int bucket_length;
	int min_hist_length;
	int lower_bucket_bound = hist_lowest_bound;
	int upper_bucket_bound = lower_bucket_bound + bucket_length;

	min_hist_length = hist_length();
	bucket_length = min_hist_length /
	for (i=0, i < statistic_target, i++){

		for(j=0, j < hist_upper_nontrie.length , j++){

			if(hist_lower_nontrie[j] > lower_bucket_bound){
				int increment = (upper_bucket_bound - hist_lower_nontrie[j]) / bucket_length;
				buckets[i] += increment;
			}

			else if(hist_lower_nontrie[j] <= lower_bucket_bound && hist_upper_nontrie[j] >= upper_bucket_bound){
				buckets[i] += 1 ;
			}

			else if(hist_upper_nontrie[j] < upper_bucket_bound){
				int increment = (hist_upper_nontrie[j] - lower_bucket_bound) / bucket_length;
				buckets[i] += increment ;
			}
}

int	main(void)
{
	int i = 0;
	int *str = range_length();

	while (i < 5)
	{
		printf("%d", str[i]);
		i++;
	}
}
