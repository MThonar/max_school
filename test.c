#include <stdio.h>
#include <stdlib.h>

int		ft_array_length(int *arr)
{
	int i = sizeof(arr)/sizeof(arr[0]);
	return (i);
}

int     main(void)
{
    int		arr[] = {0, 2, 3, 4, 5};
    int     length = sizeof(arr)/sizeof(arr[0]);
    printf("\nlength: %d\n", length);
	return (0);
}
