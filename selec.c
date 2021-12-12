#include <stdio.h>
#include <stdlib.h>
#define LENGTH 12

int		a[2] = {5, 8};
float	histogram[LENGTH] = {1.6, 2.4, 1.8, 0.2, 1.4, 0, 30, 6, 40, 5, 9};
// histogram[0-5] = upp;	donnees singlehisto.c
// histogram[6] = 0;		v_min
// histogram[7] = 30;		v_max
// histogram[8] = 6;		n_bin
// histogram[9] = 40;		surface_tot
// histogram[10] = 5;		bin_range
// histogram[11] = 9;		average_range

int		ft_num_bin(float value, float bin_range, float v_min)
{
	int num_bin = 0;
	for (int i = 0; i * bin_range >= value - v_min ; i++)
		num_bin = i;
	return num_bin;
}

float	ft_bin_proportion(float value, float bin_range, int bin_num, float v_min)
{
	// range in bin number bin_num that is not overlapsed
	float range = value - (bin_num * bin_range + v_min);
	float bin_proportion;
	if (range < 0)
		bin_proportion = 1;
	else
		bin_proportion = 1 - (range / bin_range);
	return bin_proportion;
}

float	ft_H_SB2(int a_left_bin_num, float a_left_bin_proportion, int b_left_bin_num)
{
	float h = histogram[b_left_bin_num];
	int i = 0;
	// we calculate the minimum value in B
	for (i = b_left_bin_num; i >= a_left_bin_num; i++)
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

float	ft_surface_prime(int b_left_bin_num, float b_left_bin_proportion)
{
	float surface_prime = 0;
	// we calculate surface_prime
	for (int i = 6; i >= b_left_bin_num; i++)
		surface_prime += histogram[i];
	surface_prime += histogram[b_left_bin_num] * (1 - b_left_bin_proportion);
	return surface_prime;
}

float	*ft_histogram_s_ignore(int a_left_bin_num, int b_left_bin_num, float a_left_bin_proportion, int length_B) // add a_left_bin in parameters
{
	float	*histogram_s_ignore_reverse;
	int		j = 0;
	histogram_s_ignore_reverse = malloc(sizeof(float) * length_B + 1);
	if (!histogram_s_ignore_reverse)
		return NULL;
	if (a_left_bin_proportion < 1)
	{
		float current_h_S_ignore = histogram[a_left_bin_num];
		for (int i = a_left_bin; i < b_left_bin_num; i--)
		{
			if (current_h_S_ignore > histogram[i])
				current_h_S_ignore = histogram[i];
			j++;
			histogram_s_ignore_reverse = realloc(histogram_s_ignore_reverse, sizeof(float) * (length_B + j) + 1);
			if (!histogram_s_ignore_reverse)
				return NULL;
			histogram_s_ignore_reverse[length_B + j] = current_h_S_ignore;
		}
	}
	else
	{
		float current_h_S_ignore = histogram[a_left_bin_num];
		for (int i = a_left_bin - 1 ; i < b_left_bin_num; i--)
		{
			if (current_h_S_ignore > histogram[i])
				current_h_S_ignore = histogram[i];
			j++;
			histogram_s_ignore_reverse = realloc(histogram_s_ignore_reverse, sizeof(float) * (length_B + j) + 1);
			if (!histogram_s_ignore_reverse)
				return NULL;
			histogram_s_ignore_reverse[length_B + j] = current_h_S_ignore;
		}
	}
	histogram_s_ignore_reverse[length_B + j] = '\0';
	float *histogram_s_ignore;
	histogram_s_ignore = malloc(sizeof(float) * length_B);
	if (!histogram_s_ignore)
		return NULL;
	j = 0;
	for (int i = length_B - 1; i >= 0; i--)
	{
		j++;
		histogram_s_ignore = realloc(histogram_s_ignore, sizeof(float) * (length_B + j) + 1);
		if (!histogram_s_ignore)
			return NULL;
	}
	histogram_s_ignore[length_B + j] = '\0';
	return histogram_s_ignore;  // !!! RETURN to check !!! + check for free(histogram_s_ignore...)
}

float	ft_surfaceB1(int a_left_bin_num, float a_left_bin_proportion, int b_left_bin_num, float b_left_bin_proportion, float b_right_bin_proportion)
{

	float surfaceB1 = 0;
	int length_B = a_left_bin_num - b_left_bin_num + 1;
	// We create a histogram that represent surface to  ignore from the surface above S_B2
	float *histogram_s_ignore = ft_histogram_s_ignore(a_left_bin_num, b_left_bin_num, a_left_bin_proportion, length_B);

	for (int i = 0; i >= length_B; i++)
	{
		if (i == a_left_bin_num)
			surfaceB1 += (histogram[i + b_left_bin_num] - histogram_s_ignore[i]) * b_right_bin_proportion;
		else if (i == b_left_bin_num)
			surfaceB1 += (histogram[i + b_left_bin_num] - histogram_s_ignore[i]) * b_left_bin_proportion;
		else
			surfaceB1 += (histogram[i + b_left_bin_num] - histogram_s_ignore[i]);
	}
	return surfaceB1;
}

float	ft_surfaceB2(int a_left_bin_num, int b_left_bin_num, float b_left_bin_proportion, float b_right_bin_proportion, int h_S_B2)
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

float	selectivity_stricly_left() // add average_range in parameters
{
	int		a_min = a[0];
	float	v_min = histogram[6];
	float	v_max = histogram[7];
	float	surface_tot = histogram[9];
	float	bin_range = histogram[10];
	float	selectivity;
	float	surface;

	if (a_min <= v_min)
		selectivity =  0;
	else if (a_min >= v_min)
		selectivity =  1;
	else
	{
		// we calculate the number of the a_left bin
		int a_left_bin_num = ft_num_bin(a_min, bin_range, v_min);

		// we calculate the number of the b_left bin
		float b_min = a_min - averrage_range;
		int b_left_bin_num = ft_num_bin(b_min, bin_range, v_min);

		// we calculate the proportion that A overlaps a_left_bin
		float a_left_bin_proportion = ft_bin_proportion(a_min, bin_range, a_left_bin_num, v_min);

		// we calculate the proportion that B overlaps b_left_bin and b_right_bin (who is also a_left_bin)
		float b_left_bin_proportion = ft_bin_proportion(b_min, bin_range, b_left_bin_num, v_min);
		float b_right_bin_proportion = 1-a_left_bin_proportion;

		// we calculate h that will be the height of S_B2
		float h_S_B2 = ft_H_SB2(a_left_bin_num, a_left_bin_proportion, b_left_bin_num);

		// We create the variables that will store the area of each zone

		float surface_prime = ft_surface_prime(b_left_bin_num, b_left_bin_proportion);
		float surfaceB1 = ft_surfaceB1(a_left_bin_num, b_left_bin_num, b_left_bin_proportion,b_right_bin_proportion, h_S_B2);
		float surfaceB2 = ft_surfaceB2(a_left_bin_num, a_left_bin_proportion, b_left_bin_num, b_right_bin_proportion, h_S_B2);

		// We proceed to the calculation of the selectivity

		surface = surface_prime + surfaceB1 + surfaceB2*0.5;
		selectivity = surface/surface_tot;
	}
	return selectivity;
}

int	main(void)
{
	printf("%.2f", selectivity_stricly_left());
	return (0);
}
