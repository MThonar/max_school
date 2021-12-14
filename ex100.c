#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 100
#define STATISTIC_TARGET 5

int array_lower1[ARRAY_LENGTH] = {2, 37, 52, 53, 16, 75, 85, 62, 75, 65, 21, 12, 96, 83, 51, 45, 80, 71, 99, 23, 63, 44, 29, 28, 26, 62, 25,
55, 5, 67, 16, 57, 8, 86, 93, 88, 86, 8, 29, 6, 80, 21, 1, 42, 30, 79, 19, 69, 6, 51, 85, 94, 91, 81, 8, 82, 75, 52, 26, 88, 61, 47, 72, 78,
39, 45, 68, 98, 91, 45, 7, 41, 70, 98, 3, 51, 92, 8, 26, 88, 89, 88, 61, 56, 91, 0, 94, 51, 97, 0, 85, 57, 73, 85, 50, 19, 42, 1, 61, 71};

int array_upper1[ARRAY_LENGTH] = {32, 96, 134, 71, 22, 131, 154, 133, 155, 82, 118, 13, 172, 172, 61, 67, 137, 80, 132, 53, 76, 95, 110, 78,
57, 78, 40, 62, 79, 142, 24, 143, 82, 172, 148, 164, 180, 82, 86, 78, 117, 89, 88, 80, 125, 103, 51, 112, 10, 137, 119, 177, 120, 170, 63,
140, 166, 74, 123, 124, 74, 143, 152, 136, 46, 96, 164, 127, 186, 115, 80, 123, 163, 176, 96, 150, 140, 42, 100, 98, 144, 179, 79, 62, 158,
39, 146, 93, 163, 51, 103, 70, 119, 144, 53, 70, 56, 20, 65, 135};

int array_lower_tri1[ARRAY_LENGTH] = {0, 0, 1, 1, 2, 3, 5, 6, 6, 7, 8, 8, 8, 8, 12, 16, 16, 19, 19, 21, 21, 23, 25, 26, 26, 26, 28, 29, 29,
30, 37, 39, 41, 42, 42, 44, 45, 45, 45, 47, 50, 51, 51, 51, 51, 52, 52, 53, 55, 56, 57, 57, 61, 61, 61, 62, 62, 63, 65, 67, 68, 69, 70, 71,
71, 72, 73, 75, 75, 75, 78, 79, 80, 80, 81, 82, 83, 85, 85, 85, 85, 86, 86, 88, 88, 88, 88, 89, 91, 91, 91, 92, 93, 94, 94, 96, 97, 98, 98, 99};

int array_upper_tri1[ARRAY_LENGTH] = {10, 13, 20, 22, 24, 32, 39, 40, 42, 46, 51, 51, 53, 53, 56, 57, 61, 62, 62, 63, 65, 67, 70, 70, 71, 74,
74, 76, 78, 78, 78, 79, 79, 80, 80, 80, 82, 82, 82, 86, 88, 89, 93, 95, 96, 96, 96, 98, 100, 103, 103, 110, 112, 115, 117, 118, 119, 119, 120,
123, 123, 124, 125, 127, 131, 132, 133, 134, 135, 136, 137, 137, 140, 140, 142, 143, 143, 144, 144, 146, 148, 150, 152, 154, 155, 158, 163, 163,
164, 164, 166, 170, 172, 172, 172, 176, 177, 179, 180, 186};

int array_lower2[ARRAY_LENGTH] = {50, 24, 71, 31, 92, 64, 60, 18, 14, 89, 22, 38, 14, 25, 77, 84, 70, 97, 56, 56, 83, 51, 55, 49, 44, 2, 57, 60,
39, 69, 94, 53, 72, 19, 98, 37, 40, 56, 88, 14, 14, 54, 72, 78, 72, 68, 77, 39, 83, 34, 10, 79, 98, 74, 72, 13, 71, 12, 70, 70, 30, 82, 76, 84,
67, 48, 84, 34, 31, 93, 67, 53, 19, 88, 96, 68, 7, 63, 83, 45, 4, 79, 75, 13, 82, 89, 16, 96, 54, 86, 33, 98, 20, 88, 23, 22, 14, 66, 88, 38};

int array_upper2[ARRAY_LENGTH] = {108, 123, 163, 66, 183, 160, 141, 43, 42, 138, 79, 51, 106, 64, 118, 156, 117, 153, 136, 141, 120, 121, 99,
148, 52, 61, 109, 149, 60, 162, 147, 99, 137, 68, 185, 130, 105, 72, 187, 93, 49, 140, 144, 163, 136, 132, 81, 64, 177, 129, 67, 80, 192, 116,
170, 90, 168, 66, 163, 102, 89, 131, 128, 175, 159, 101, 142, 81, 47, 160, 76, 59, 43, 142, 115, 134, 89, 150, 93, 111, 19, 116, 113, 76, 122,
105, 36, 180, 124, 173, 71, 189, 92, 107, 90, 28, 32, 98, 105, 65};

int array_lower_tri2[ARRAY_LENGTH] = {2, 4, 7, 10, 12, 13, 13, 14, 14, 14, 14, 14, 16, 18, 19, 19, 20, 22, 22, 23, 24, 25, 30, 31, 31, 33, 34,
34, 37, 38, 38, 39, 39, 40, 44, 45, 48, 49, 50, 51, 53, 53, 54, 54, 55, 56, 56, 56, 57, 60, 60, 63, 64, 66, 67, 67, 68, 68, 69, 70, 70, 70, 71,
71, 72, 72, 72, 72, 74, 75, 76, 77, 77, 78, 79, 79, 82, 82, 83, 83, 83, 84, 84, 84, 86, 88, 88, 88, 88, 89, 89, 92, 93, 94, 96, 96, 97, 98, 98, 98};

int array_upper_tri2[ARRAY_LENGTH] = {19, 28, 32, 36, 42, 43, 43, 47, 49, 51, 52, 59, 60, 61, 64, 64, 65, 66, 66, 67, 68, 71, 72, 76, 76, 79, 80,
81, 81, 89, 89, 90, 90, 92, 93, 93, 98, 99, 99, 101, 102, 105, 105, 105, 106, 107, 108, 109, 111, 113, 115, 116, 116, 117, 118, 120, 121, 122,
123, 124, 128, 129, 130, 131, 132, 134, 136, 136, 137, 138, 140, 141, 141, 142, 142, 144, 147, 148, 149, 150, 153, 156, 159, 160, 160, 162, 163,
163, 163, 168, 170, 173, 175, 177, 180, 183, 185, 187, 189, 192};

float	*ft_equiwidth_freq(int *array_lower, int *array_upper, int *array_lower_tri, int *array_upper_tri)
{
	int		i;
	int		j;
	int		hist_length;
	float	lowest_bound;
	float	lower_bucket_bound;
	float	upper_bucket_bound;
	float	bucket_length;
	float	*bucket;
	float	increment;

	hist_length = array_upper_tri[ARRAY_LENGTH - 1] - array_lower_tri[0];
	bucket_length = (float)hist_length / (float)STATISTIC_TARGET;
	lowest_bound = array_lower_tri[0];
	lower_bucket_bound = lowest_bound;
	upper_bucket_bound = lower_bucket_bound + bucket_length;
	bucket = malloc(sizeof(float) * STATISTIC_TARGET);

	if (!bucket)
		return NULL;

	for (i = 0; i < STATISTIC_TARGET; i++)
	{
		for(j = 0; j < ARRAY_LENGTH; j++)
		{
			if((array_lower[j] > lower_bucket_bound) && (array_upper[j] < upper_bucket_bound))
			{
				increment = (array_upper[j] - array_lower[j]) / bucket_length;
				bucket[i] += increment;
			}
			else if((array_lower[j] > lower_bucket_bound) && (array_lower[j] < upper_bucket_bound))
			{
				increment = (upper_bucket_bound - array_lower[j]) / bucket_length;
				bucket[i] += increment;
			}
			else if((array_lower[j] <= lower_bucket_bound) && (array_upper[j] >= upper_bucket_bound))
			{;
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

float multiplication(float* bucket1, float* bucket2)
{
	int		i;
	int		j;
	int		hist_length1;
	int		hist_length2;
	float	lower_bucket_bound1;
	float	lower_bucket_bound2;
	float	upper_bucket_bound1;
	float	upper_bucket_bound2;
	float	bucket_length1;
	float	bucket_length2;
	float   min_hist_value1;
	float   min_hist_value2;
	float	max_hist_value1;
	float	max_hist_value2;
	float 	resultat;

	min_hist_value1 = array_lower_tri1[0];
	min_hist_value2 = array_lower_tri2[0];
	max_hist_value1 = array_upper_tri1[ARRAY_LENGTH - 1];
	max_hist_value2 = array_upper_tri2[ARRAY_LENGTH - 1];
	hist_length1 = max_hist_value1 - min_hist_value1;
	hist_length2 = max_hist_value2 - min_hist_value2;
	bucket_length1 = (float)hist_length1 / (float)STATISTIC_TARGET;
	bucket_length2 = (float)hist_length2 / (float)STATISTIC_TARGET;
	lower_bucket_bound1 = min_hist_value1;
	upper_bucket_bound1 = lower_bucket_bound1 + bucket_length1;
	for (i = 0; i < STATISTIC_TARGET; i++)
	{
		lower_bucket_bound2 = min_hist_value2;
		upper_bucket_bound2 = lower_bucket_bound2 + bucket_length2;
		for(j = 0; j < STATISTIC_TARGET; j++)
		{
			if( (lower_bucket_bound1 <= lower_bucket_bound2) && (upper_bucket_bound1 >= lower_bucket_bound2) )
				resultat += bucket1[i]*bucket2[j];
			else if( (lower_bucket_bound1 <= upper_bucket_bound2) && (upper_bucket_bound1 >= upper_bucket_bound2) )
				resultat += bucket1[i]*bucket2[j];
			lower_bucket_bound2 = upper_bucket_bound2;
			upper_bucket_bound2 += bucket_length2;
		}
		lower_bucket_bound1 = upper_bucket_bound1;
		upper_bucket_bound1 += bucket_length1;
	}
	//printf("\nfirst estimation = %f\n", resultat);
	return (resultat);
}

float moyenne(float* bucket)
{
	float moyenne = 0;
	int i;
	for (i = 0; i < STATISTIC_TARGET; i++){
		//printf("\nmoyenne = %f\n", moyenne);
		moyenne += bucket[i];
		}
	moyenne = moyenne / ARRAY_LENGTH;
	//printf("\nmoyenneFINALE = %f\n", moyenne);
	return (moyenne);
	}

int	main(void)
{
	int	i;
	float *bucket1;
	float *bucket2;
	bucket1 = ft_equiwidth_freq(array_lower1, array_upper1, array_lower_tri1, array_upper_tri1);
	printf("bucket1 = ( ");
	for(i = 0; i < STATISTIC_TARGET; i++)
		printf("%f ", bucket1[i]);
	printf(")\n");
	bucket2 = ft_equiwidth_freq(array_lower2, array_upper2, array_lower_tri2, array_upper_tri2);
	printf("bucket2 = ( ");
	for(i = 0; i < STATISTIC_TARGET; i++)
		printf("%f ", bucket2[i]);
	printf(")\n");
	float resultat;
	resultat = multiplication(bucket1,bucket2);
	printf("First estimation = %f\n", resultat);
	float moyenne1 = moyenne(bucket1);
	printf("First table average = %f\n", moyenne1);
	float moyenne2 = moyenne(bucket2);
	printf("Second table average = %f\n", moyenne2);
	float resultat_nouveau;
	resultat_nouveau = (resultat / (moyenne1*moyenne2));
	printf("Final estimation = %f\n", resultat_nouveau);
	free (bucket1);

	free (bucket2);
	return (0);
}
