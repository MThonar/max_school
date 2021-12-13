#include <stdio.h>
#include <stdlib.h>
#define LENGTH 12

int		a[2] = {5, 10};
float	histogram[LENGTH] = {0, 30, 7.5, 6, 9, 1.67, 2.33, 0.83, 1.17, 1.5};
// ranges = ( (0, 14), (2, 9), (7, 15), (19, 27), (22, 30) )
// histogram[0] = 0;		v_min
// histogram[1] = 30;		v_max
// histogram[2] = 45;		surface_tot
// histogram[3] = 5;		bin_range
// histogram[4] = 9;		average_range
// histogram[5-10] = upp;	donnees singlehisto.c

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

float	ft_H_SB2(int a_left_bin_num, float a_left_bin_proportion, int b_left_bin_num)
{
	float h = histogram[b_left_bin_num+5];
	int i = 0;
	// we calculate the minimum value in B
	for (i = b_left_bin_num; i < a_left_bin_num; i++)
	{
		//printf("\nREPROUTE (valeur de i = %d)\n", i);
		if (histogram[i+5] < h)
			h = histogram[i+5];
	}
	//  we verify if S_B2 overlaps on a_left_bin. If yes, we verifiy one more time the minimum value of B
	if (a_left_bin_proportion < 1)
	{
		if (histogram[a_left_bin_num+5] < h)
			h = histogram[i+5];
	}
	return h;
}

float	ft_H_SC2(int a_right_bin_num, float a_right_bin_proportion, int c_right_bin_num)
{
	printf("H_SC2\n");
	printf("a_right_bin_num : %i\n", a_right_bin_num);
	printf("a_right_bin_proportion : %f\n", a_right_bin_proportion);
	printf("c_right_bin_num : %i\n", c_right_bin_num);
	float h = histogram[c_right_bin_num+5];
	int i = 0;
	// we calculate the minimum value in C
	for (i = c_right_bin_num; i > a_right_bin_num; i--)
	{
		if (histogram[i+5] < h)
			h = histogram[i+5];
	}
	//  we verify if S_C2 overlaps on a_right_bin. If yes, we verifiy one more time the minimum value of C
	if (a_right_bin_proportion < 1)
	{
		if (histogram[a_right_bin_num+5] < h)
			h = histogram[i+5];
	}
	printf("h : %f\n", h);
	return h;
}

float	ft_surface_A(int a_left_bin_num, float a_left_bin_proportion, int a_right_bin_num, float a_right_bin_proportion) //surface_prime not initialized
{
	float surface_A = 0;
	// we calculate surface_A
	for (int i = a_left_bin_num + 1; i < a_right_bin_num; i++)
		surface_A += histogram[i+5];
		printf("rentre pas\n");
	surface_A += histogram[a_left_bin_num+5] * a_left_bin_proportion;
	surface_A += histogram[a_right_bin_num+5] * a_right_bin_proportion;
	return surface_A;
}

float	*ft_histogram_s_B_ignore(int a_left_bin_num, int b_left_bin_num, int length_B)
{
	float	*histogram_s_B_ignore;
	histogram_s_B_ignore = malloc(sizeof(float) * length_B + 1);
	if (!histogram_s_B_ignore)
		return NULL;
	float current_h_S_B_ignore = histogram[b_left_bin_num+5];
	for (int i = b_left_bin_num; i <= a_left_bin_num; i++)
	{
		if (current_h_S_B_ignore > histogram[i+5])
			current_h_S_B_ignore = histogram[i+5];
		histogram_s_B_ignore[i-b_left_bin_num] = current_h_S_B_ignore;
	}
	histogram_s_B_ignore[length_B] = '\0';
	return histogram_s_B_ignore;
}

float	*ft_histogram_s_C_ignore(int a_right_bin_num, int c_right_bin_num, int length_B)
{
	float	*histogram_s_C_ignore;
	histogram_s_C_ignore = malloc(sizeof(float) * length_B + 1);
	if (!histogram_s_C_ignore)
		return NULL;
	float current_h_S_C_ignore = histogram[c_right_bin_num+5];
	for (int i = c_right_bin_num; i >= a_right_bin_num; i--)
	{
		if (current_h_S_C_ignore > histogram[i+5])
			current_h_S_C_ignore = histogram[i+5];
		histogram_s_C_ignore[i-a_right_bin_num] = current_h_S_C_ignore;
	}
	histogram_s_C_ignore[length_B] = '\0';
	return histogram_s_C_ignore;
}

float	ft_surfaceB1(int a_left_bin_num  , int b_left_bin_num , float b_left_bin_proportion, float b_right_bin_proportion)
{

	float surfaceB1 = 0;
	int length_B = a_left_bin_num - b_left_bin_num + 1;
	// We create a histogram that represent surface to  ignore from the surface above S_B2
	float *histogram_s_B_ignore = ft_histogram_s_B_ignore(a_left_bin_num, b_left_bin_num, length_B);

	for (int i = 0; i < length_B; i++)
	{
		if (i == length_B - 1)
			surfaceB1 += (histogram[b_left_bin_num + i + 5] - histogram_s_B_ignore[i]) * b_right_bin_proportion;
		else if (i == 0)
			surfaceB1 += (histogram[b_left_bin_num + i + 5] - histogram_s_B_ignore[i]) * b_left_bin_proportion;
		else
			surfaceB1 += (histogram[b_left_bin_num + i + 5] - histogram_s_B_ignore[i]);
	}
	return surfaceB1;
}

float	ft_surfaceC1(int a_right_bin_num, int c_right_bin_num, float c_right_bin_proportion, float c_left_bin_proportion) //add length_B in parameters
{

	float surfaceC1 = 0;
	int i;
	int length_C = c_right_bin_num - a_right_bin_num + 1;
	// We create a histogram that represent surface to  ignore from the surface above S_C2
	float *histogram_s_C_ignore = ft_histogram_s_C_ignore(a_right_bin_num, c_right_bin_num, length_C);
	for (i = 0; i < length_C; i++){
	printf("histogram_s_C_ignore = %f\n", histogram_s_C_ignore[i]);}
	for (i = 0; i < length_C; i++)
	{
		if (i == 0){
			surfaceC1 += (histogram[i + a_right_bin_num+5] - histogram_s_C_ignore[i]) * c_left_bin_proportion;
			printf("i = %i\n", i);
			printf("c_right_bin_num = %i\n", i);
			printf("histogram[i + c_right_bin_num] = %f\n", histogram[i + c_right_bin_num+5]);
			printf("histogram_s_C_ignore[i] = %f\n", histogram_s_C_ignore[i]);
			printf("c_left_bin_proportion = %f\n", c_left_bin_proportion);}
		else if (i == length_C-1){
			surfaceC1 += (histogram[i + a_right_bin_num+5] - histogram_s_C_ignore[i]) * c_right_bin_proportion;
			printf("histogram[i + c_right_bin_num] = %f\n", histogram[i + c_right_bin_num+5]);
			printf("histogram_s_C_ignore[i] = %f\n", histogram_s_C_ignore[i]);
			printf("c_right_bin_proportion = %f\n", c_right_bin_proportion);}
		else{
			surfaceC1 += (histogram[i + a_right_bin_num+5] - histogram_s_C_ignore[i]);
			printf("histogram[i + c_right_bin_num] = %f\n", histogram[i + c_right_bin_num+5]);
			printf("histogram_s_C_ignore = %f\n", histogram_s_C_ignore[i]);
	}}
	return surfaceC1;
}

float	ft_surfaceB2(int a_left_bin_num, int b_left_bin_num, float b_left_bin_proportion, float b_right_bin_proportion, float h_S_B2)
{
	float surfaceB2 = 0;
	printf("h = %f\n", h_S_B2);
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
	printf("h = %f\n", h_S_C2);
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

float	selectivity_overlaps()
{
	int	a_min = a[0];
	int	a_max = a[1];
	float	v_min = histogram[0];
	float	v_max = histogram[1];
	float	surface_tot = histogram[2];
	float	bin_range = histogram[3];
	float	average_range = histogram[4];
	float	selectivity;
	float	surface;

	if (a_max <= v_min)
	{
		selectivity =  0;
		printf("\ncoucou\n");
	}
	else if (a_min >= v_max)
	{
		selectivity =  0;
		printf("\nrecoucou\n");
	}
	else
	{
		// we calculate the number of the a_left bin
		int a_left_bin_num = ft_num_bin(a_min, bin_range, v_min, v_max);
		printf("\n1\n");

		// we calculate the number of the a_right bin
		int a_right_bin_num = ft_num_bin(a_max, bin_range, v_min, v_max);
		printf("\n2\n");

		// we calculate the number of the b_left bin
		float b_min = a_min - average_range;
		int b_left_bin_num = ft_num_bin(b_min, bin_range, v_min, v_max);
		printf("\n3\n");

		// we calculate the number of the c_right bin
		float c_max = a_max + average_range;
		int c_right_bin_num = ft_num_bin(c_max, bin_range, v_min, v_max);
		printf("\n4\n");

		// we calculate the proportion that A overlaps a_left_bin
		float a_left_bin_proportion = ft_bin_proportion(a_min, bin_range, a_left_bin_num, v_min);
				printf("a_left_bin_proportion = %f\n", a_left_bin_proportion);
		printf("\n5\n");

		// we calculate the proportion that A overlaps a_right_bin
		float a_right_bin_proportion = 1-ft_bin_proportion(a_max, bin_range, a_right_bin_num, v_min);
						printf("a_right_bin_proportion = %f\n", a_right_bin_proportion);
		printf("\n6\n");

		// we calculate the proportion that B overlaps b_left_bin and b_right_bin (who is also a_left_bin)
		float b_left_bin_proportion = ft_bin_proportion(b_min, bin_range, b_left_bin_num, v_min);
		printf("b_left_bin_proportion = %f\n", b_left_bin_proportion);
		printf("\n7\n");
		float b_right_bin_proportion = 1-a_left_bin_proportion;
				printf("b_right_bin_proportion = %f\n", b_right_bin_proportion);

		// we calculate the proportion that C overlaps c_right_bin and c_left_bin (who is also a_left_bin)
		float c_right_bin_proportion = 1-ft_bin_proportion(c_max, bin_range, c_right_bin_num, v_min);
		printf("\n8\n");
		float c_left_bin_proportion = 1-a_right_bin_proportion;

		// we calculate h that will be the height of S_B2
		float h_S_B2 = ft_H_SB2(a_left_bin_num, a_left_bin_proportion, b_left_bin_num);
		printf("\n9\n");

		// we calculate h that will be the height of S_C2
		float h_S_C2 = ft_H_SC2(a_right_bin_num, a_right_bin_proportion, c_right_bin_num);
		printf("\n10\n");

		// We create the variables that will store the area of each zone

		float surface_A = ft_surface_A(a_left_bin_num, a_left_bin_proportion, a_right_bin_num, a_right_bin_proportion);
		printf("surface_A : %f/n", surface_A);
		printf("\nsurface_A = %f\n", surface_A);
		float surfaceB1 = ft_surfaceB1(a_left_bin_num  , b_left_bin_num , b_left_bin_proportion, b_right_bin_proportion);
		printf("\nsurfaceB1 = %f\n", surfaceB1);
		float surfaceB2 = ft_surfaceB2(a_left_bin_num, a_left_bin_proportion, b_left_bin_num, b_right_bin_proportion, h_S_B2);
		printf("\nsurfaceB2 = %f\n", surfaceB2);
		float surfaceC1 = ft_surfaceC1(a_right_bin_num, c_right_bin_num, c_right_bin_proportion, c_left_bin_proportion);
		printf("\nsurfaceC1 = %f\n", surfaceC1);
		float surfaceC2 = ft_surfaceC2(a_right_bin_num, c_right_bin_num, c_left_bin_proportion, c_right_bin_proportion, h_S_C2);
		printf("\nsurfaceC2 = %f\n", surfaceC2);

		// We proceed to the calculation of the selectivity

		surface = surface_A + surfaceB1 + surfaceB2*0.5 + surfaceC1 + surfaceC2*0.5;
		selectivity = surface/surface_tot;
	}
	return selectivity;
}

int	main(void)
{
	printf("\n%f\n", selectivity_overlaps());
	return (0);
}
