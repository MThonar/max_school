#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 5
#define STATISTIC_TARGET 4

int array_lower1[ARRAY_LENGTH] = {0, 2, 7, 19, 22};
int array_upper1[ARRAY_LENGTH] = {14, 9, 15, 27, 30};
int array_lower_tri1[ARRAY_LENGTH] = {0, 2, 7, 19, 22};
int array_upper_tri1[ARRAY_LENGTH] = {9, 14, 15, 27, 30};
int	a[2] = {5, 10};

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

float ft_average_range()
{
	int i;
	float res = 0;
	for(i = 0; i < ARRAY_LENGTH; i++)
	{
		res += array_upper1[i] - array_lower1[i];
	}
	res = res / ARRAY_LENGTH;
	return res;
}

float *ft_build_histo()
{
	int i;
	float surface_tot = 0;
	float *res;
	float *equiwidth_freq;
	res = malloc(sizeof(float) * (STATISTIC_TARGET + 5));
	equiwidth_freq = malloc(sizeof(float) * STATISTIC_TARGET);
	if (!equiwidth_freq)
		return NULL;

	equiwidth_freq = ft_equiwidth_freq(array_lower1, array_upper1, array_lower_tri1, array_upper_tri1);
	for(i = 0; i < STATISTIC_TARGET; i++)
	{
		surface_tot += equiwidth_freq[i];
		res[i] = equiwidth_freq[i];
	}
	res[STATISTIC_TARGET] = array_lower_tri1[0];
	res[STATISTIC_TARGET + 1] = array_upper_tri1[ARRAY_LENGTH - 1];
	res[STATISTIC_TARGET + 2] = surface_tot;
	res[STATISTIC_TARGET + 3] = (res[STATISTIC_TARGET + 1] - res[STATISTIC_TARGET]) / STATISTIC_TARGET;
	res[STATISTIC_TARGET + 4] = ft_average_range();
	free(equiwidth_freq);
	return res;
}

int	ft_num_bin(float value, float bin_range, float v_min, float v_max)
{
	int i = 0;
	int num_bin = 0;
	float res1 = i*bin_range;
	float res2 = value-v_min;
	float res3 = v_max-v_min;

	for (i = 0; (i * bin_range < value - v_min) && (i * bin_range < v_max - v_min); i++)
	{
		num_bin = i;
	}
	return num_bin;
}

float	ft_bin_proportion(float value, float bin_range, int bin_num, float v_min)
{
	// range in bin number bin_num that is not overlapsed
	float range = value - (bin_num * bin_range + v_min);
	float bin_proportion;
	if (range <= 0)
		bin_proportion = 1;
	else if (range >= bin_range)
		bin_proportion = 1;
	else
		bin_proportion = 1 - (range / bin_range);
	return bin_proportion;
}

float	ft_H_SB2(int a_left_bin_num, float a_left_bin_proportion, int b_left_bin_num, float *histogram)
{
	float h = histogram[b_left_bin_num];
	int i = 0;
	// we calculate the minimum value in B
	for (i = b_left_bin_num; i < a_left_bin_num; i++)
	{
		if (histogram[i] < h)
			h = histogram[i];
	}
	//  we verify if S_B2 overlaps on a_left_bin. If yes, we verifiy one more time the minimum value of B
	if (a_left_bin_proportion < 1)
	{
		if (histogram[a_left_bin_num] < h)
			h = histogram[i];
	}
	return h;
}

float	ft_H_SC2(int a_right_bin_num, float a_right_bin_proportion, int c_right_bin_num, float *histogram)
{
	float h = histogram[c_right_bin_num];
	int i = 0;
	// we calculate the minimum value in C
	for (i = c_right_bin_num; i > a_right_bin_num; i--)
	{
		if (histogram[i] < h)
			h = histogram[i];
	}
	//  we verify if S_C2 overlaps on a_right_bin. If yes, we verifiy one more time the minimum value of C
	if (a_right_bin_proportion < 1)
	{
		if (histogram[a_right_bin_num] < h)
			h = histogram[i];
	}
	return h;
}

float	ft_surface_A(int a_left_bin_num, float a_left_bin_proportion, int a_right_bin_num, float a_right_bin_proportion, float *histogram)
{
	float surface_A = 0;
	// we calculate surface_A
	for (int i = a_left_bin_num + 1; i < a_right_bin_num; i++)
		surface_A += histogram[i];
	surface_A += histogram[a_left_bin_num] * a_left_bin_proportion;
	surface_A += histogram[a_right_bin_num] * a_right_bin_proportion;
	return surface_A;
}

float	*ft_histogram_s_B_ignore(int a_left_bin_num, int b_left_bin_num, int length_B, float *histogram)
{
	float	*histogram_s_B_ignore;
	histogram_s_B_ignore = malloc(sizeof(float) * length_B + 1);
	if (!histogram_s_B_ignore)
		return NULL;
	float current_h_S_B_ignore = histogram[b_left_bin_num];
	for (int i = b_left_bin_num; i <= a_left_bin_num; i++)
	{
		if (current_h_S_B_ignore > histogram[i])
			current_h_S_B_ignore = histogram[i];
		histogram_s_B_ignore[i-b_left_bin_num] = current_h_S_B_ignore;
	}
	histogram_s_B_ignore[length_B] = '\0';
	return histogram_s_B_ignore;
}

float	*ft_histogram_s_C_ignore(int a_right_bin_num, int c_right_bin_num, int length_B, float *histogram)
{
	float	*histogram_s_C_ignore;
	histogram_s_C_ignore = malloc(sizeof(float) * length_B + 1);
	if (!histogram_s_C_ignore)
		return NULL;
	float current_h_S_C_ignore = histogram[c_right_bin_num];
	for (int i = c_right_bin_num; i >= a_right_bin_num; i--)
	{
		if (current_h_S_C_ignore > histogram[i])
			current_h_S_C_ignore = histogram[i];
		histogram_s_C_ignore[i-a_right_bin_num] = current_h_S_C_ignore;
	}
	histogram_s_C_ignore[length_B] = '\0';
	return histogram_s_C_ignore;
}

float	ft_surfaceB1(int a_left_bin_num  , int b_left_bin_num , float b_left_bin_proportion, float b_right_bin_proportion, float *histogram)
{

	float surfaceB1 = 0;
	int length_B = a_left_bin_num - b_left_bin_num + 1;
	// We create a histogram that represent surface to  ignore from the surface above S_B2
	float *histogram_s_B_ignore = ft_histogram_s_B_ignore(a_left_bin_num, b_left_bin_num, length_B, histogram);

	for (int i = 0; i < length_B; i++)
	{
		if (i == length_B - 1)
			surfaceB1 += (histogram[b_left_bin_num + i] - histogram_s_B_ignore[i]) * b_right_bin_proportion;
		else if (i == 0)
			surfaceB1 += (histogram[b_left_bin_num + i] - histogram_s_B_ignore[i]) * b_left_bin_proportion;
		else
			surfaceB1 += (histogram[b_left_bin_num + i] - histogram_s_B_ignore[i]);
	}
	return surfaceB1;
}

float	ft_surfaceC1(int a_right_bin_num, int c_right_bin_num, float c_right_bin_proportion, float c_left_bin_proportion, float *histogram)
{

	float surfaceC1 = 0;
	int i;
	int length_C = c_right_bin_num - a_right_bin_num + 1;
	// We create a histogram that represent surface to  ignore from the surface above S_C2
	float *histogram_s_C_ignore = ft_histogram_s_C_ignore(a_right_bin_num, c_right_bin_num, length_C, histogram);
	for (i = 0; i < length_C; i++)
	{
		if (i == 0)
			surfaceC1 += (histogram[i + a_right_bin_num] - histogram_s_C_ignore[i]) * c_left_bin_proportion;
		else if (i == length_C-1)
			surfaceC1 += (histogram[i + a_right_bin_num] - histogram_s_C_ignore[i]) * c_right_bin_proportion;
		else
			surfaceC1 += (histogram[i + a_right_bin_num] - histogram_s_C_ignore[i]);
	}
	return surfaceC1;
}

float	ft_surfaceB2(int a_left_bin_num, int b_left_bin_num, float b_left_bin_proportion, float b_right_bin_proportion, float h_S_B2)
{
	float surfaceB2 = 0;
	// we calculate surfaceB2+
	if(a_left_bin_num == b_left_bin_num)
		surfaceB2 += h_S_B2 * (b_right_bin_proportion);
	else
	{
		surfaceB2 += h_S_B2 * (b_left_bin_proportion);
		surfaceB2 += h_S_B2 * (a_left_bin_num - b_left_bin_num -1);
		surfaceB2 += h_S_B2 * (b_right_bin_proportion);
	}
	return surfaceB2;
}

float	ft_surfaceC2(int a_right_bin_num, int c_right_bin_num, float c_left_bin_proportion, float c_right_bin_proportion, float h_S_C2)
{
	float surfaceC2 = 0;
	// we calculate surfaceB2+
	if(a_right_bin_num == c_right_bin_num)
		surfaceC2 += h_S_C2 * (c_left_bin_proportion);
	else
	{
		surfaceC2 += h_S_C2 * (c_left_bin_proportion);
		surfaceC2 += h_S_C2 * (c_right_bin_num - a_right_bin_num -1);
		surfaceC2 += h_S_C2 * (c_right_bin_proportion);
	}
	return surfaceC2;
}

float	selectivity_overlaps(float *histogram)
{
	int	a_min = a[0];
	int	a_max = a[1];
	float	v_min = histogram[STATISTIC_TARGET];
	float	v_max = histogram[STATISTIC_TARGET + 1];
	float	surface_tot = histogram[STATISTIC_TARGET + 2];
	float	bin_range = histogram[STATISTIC_TARGET + 3];
	float	average_range = histogram[STATISTIC_TARGET + 4];
	float	selectivity;
	float	surface;

	if (a_max <= v_min)
	{
		selectivity =  0;
	}
	else if (a_min >= v_max)
	{
		selectivity =  0;
	}
	else
	{
		// we calculate the number of the a_left bin
		int a_left_bin_num = ft_num_bin(a_min, bin_range, v_min, v_max);

		// we calculate the number of the a_right bin
		int a_right_bin_num = ft_num_bin(a_max, bin_range, v_min, v_max);

		// we calculate the number of the b_left bin
		float b_min = a_min - average_range;
		int b_left_bin_num = ft_num_bin(b_min, bin_range, v_min, v_max);

		// we calculate the number of the c_right bin
		float c_max = a_max + average_range;
		int c_right_bin_num = ft_num_bin(c_max, bin_range, v_min, v_max);

		// we calculate the proportion that A overlaps a_left_bin
		float a_left_bin_proportion = ft_bin_proportion(a_min, bin_range, a_left_bin_num, v_min);

		// we calculate the proportion that A overlaps a_right_bin
		float a_right_bin_proportion = 1-ft_bin_proportion(a_max, bin_range, a_right_bin_num, v_min);

		// we calculate the proportion that B overlaps b_left_bin and b_right_bin (who is also a_left_bin)
		float b_left_bin_proportion = ft_bin_proportion(b_min, bin_range, b_left_bin_num, v_min);
		float b_right_bin_proportion = 1-a_left_bin_proportion;

		// we calculate the proportion that C overlaps c_right_bin and c_left_bin (who is also a_left_bin)
		float c_right_bin_proportion = 1-ft_bin_proportion(c_max, bin_range, c_right_bin_num, v_min);
		float c_left_bin_proportion = 1-a_right_bin_proportion;

		// we calculate h that will be the height of S_B2
		float h_S_B2 = ft_H_SB2(a_left_bin_num, a_left_bin_proportion, b_left_bin_num, histogram);

		// we calculate h that will be the height of S_C2
		float h_S_C2 = ft_H_SC2(a_right_bin_num, a_right_bin_proportion, c_right_bin_num, histogram);

		// We create the variables that will store the area of each zone

		float surface_A = ft_surface_A(a_left_bin_num, a_left_bin_proportion, a_right_bin_num, a_right_bin_proportion, histogram);
		float surfaceB1 = ft_surfaceB1(a_left_bin_num  , b_left_bin_num , b_left_bin_proportion, b_right_bin_proportion, histogram);
		float surfaceB2 = ft_surfaceB2(a_left_bin_num, a_left_bin_proportion, b_left_bin_num, b_right_bin_proportion, h_S_B2);
		float surfaceC1 = ft_surfaceC1(a_right_bin_num, c_right_bin_num, c_right_bin_proportion, c_left_bin_proportion, histogram);
		float surfaceC2 = ft_surfaceC2(a_right_bin_num, c_right_bin_num, c_left_bin_proportion, c_right_bin_proportion, h_S_C2);

		// We proceed to the calculation of the selectivity

		surface = surface_A + surfaceB1 + surfaceB2*0.5 + surfaceC1 + surfaceC2*0.5;
		selectivity = surface/surface_tot;
	}
	return selectivity;
}

int	main(void)
{
	int i;
	float selectivity;
	float *histogram;
	histogram = ft_build_histo();
	selectivity = selectivity_overlaps(histogram);
	printf("\nSelectivity overlaps estimation = %f\n", selectivity);
	free(histogram);
	return (0);
}
