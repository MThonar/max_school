int str1[5] = {2, 10, 4, 1, 9};
int str2[5] = {7, 15, 12, 5, 13};
int str_tri1[5] = {1, 2, 4, 9, 10}:
int str_tri2[5] = {5, 7, 12, 13, 15};
int str_last[10] = {2, 7, 10, 15, 4, 12, 1, 5, 9, 13};

int	strlng(int *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
