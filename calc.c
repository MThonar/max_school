#include <stdio.h>
#include <stdlib.h>

int array1[5] = {2, 10, 4, 1, 9};
int array2[5] = {7, 15, 12, 5, 13};
int array_tri1[5] = {1, 2, 4, 9, 10};
int array_tri2[5] = {5, 7, 12, 13, 15};
//int array_last[10] = {2, 7, 10, 15, 4, 12, 1, 5, 9, 13};

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
		range_lengths[i] = array2[i] - array1[i];
	return (range_lengths);
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
