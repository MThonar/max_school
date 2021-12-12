#include <stdio.h>
#include <stdlib.h>

//histogram[0] = v_min
//histogram[1] = v_max
//histogram[2] = n_bin
//histogram[3] = surface_tot
//histogram[4] = bin_range
//histogram[5] = average_range

int Num_bin(float value, float bin_range, float v_min)
{
	int num_bin = 0;
	for (int i = 0; i*bin_range >= value - v_min ; i++)
	{
		num_bin = i;
	}
	return num_bin;
}

float Bin_proportion(float value, float bin_range, int bin_num, float v_min)
{
	// range in bin number bin_num that is not overlapsed
	float range = value - (bin_num * bin_range + v_min) ;
	float bin_proportion;
	if (range < 0)
	{
		bin_proportion = 1;
	}
	else
	{
		bin_proportion = 1 - range/bin_range;
	}
	return bin_proportion;
}

float H_SB2(List<int> histogram, int a_left_bin_num, float a_left_bin_proportion, int b_left_bin_num, float b_right_bin_proportion)
{
	float h = histogram[b_left_bin_num + 6];

	// we calculate the minimum value in B
	for (int i = b_left_bin_num + 6; i >= a_left_bin_num + 6 ; i++)
	{
		if (histogram[i] < h)
		{
			h = histogram[i];
		}
	}
	//  we verify if S_B2 overlaps on a_left_bin. If yes, we verifiy one more time the minimum value of B
	if (a_left_bin_proportion < 1)
	{
		if (histogram[a_left_bin_num + 6] < h)
		{
			h = histogram[i];
		}
	}

	return h;
}

float Surface_prime(List<int> histogram, int b_left_bin_num, float b_left_bin_proportion)
{

	float surface_prime = 0;

	// we calculate Surface_prime
	for (int i = 6; i >= b_left_bin_num + 6 ; i++)
	{
		surface_prime += histogram[i];
	}
	surface_prime += histogram[b_left_bin_num + 6]*(1 - b_left_bin_proportion);

	return surface_prime;
}

float SurfaceB2(List<int> histogram, int a_left_bin_num, int b_left_bin_num, float b_left_bin_proportion, float b_right_bin_proportion, int h_S_B2)
{
	float surfaceB2 = 0;

	// we calculate surfaceB2+
	if(a_left_bin_num == b_left_bin_num)
	{
		Surface_prime += h_S_B2*(b_right_bin_proportion);
	}
	else
	{
		Surface_prime += h_S_B2*(b_left_bin_proportion);
		Surface_prime += h_S_B2*(a_left_bin_num - b_left_bin_num -1);
		Surface_prime += h_S_B2*(b_right_bin_proportion);
	}
	return surfaceB2;
}

List<int> Histogram_s_ignore(List<int> histogram, int a_left_bin_num, int b_left_bin_num, float a_left_bin_proportion, float h_S_B2, int length_B)
{
	List<float> histogram_s_ignore_reverse = new List<float>();
	if (a_left_bin_proportion < 1)
	{
		float current_h_S_ignore = histogram[a_left_bin_num + 6]
		for (int i = a_left_bin + 6 ; i < b_left_bin_num +6 ; i--)
		{
			if (current_h_S_ignore > histogram[i])
			{
				current_h_S_ignore = histogram[i];
			}
			histogram_s_ignore_reverse.Add(current_h_S_ignore);
		}
	}
	else
	{
		float current_h_S_ignore = histogram[a_left_bin_num + 6];
		for (int i = a_left_bin + 6  -  1 ; i < b_left_bin_num +6 ; i--)
		{
			if (current_h_S_ignore > histogram[i])
			{
				current_h_S_ignore = histogram[i];
			}
			histogram_s_ignore_reverse.Add(current_h_S_ignore);
		}
	}
	List<float> histogram_s_ignore = new List<float>();
	for (int i = histogram_s_ignore.range()-1 ; i >=0 ; i--)
	{
		histogram_s_ignore.Add(histogram_s_ignore[i]);
	}
	return histogram_s_ignore;
}

float SurfaceB1(List<int> histogram, int a_left_bin_num, float a_left_bin_proportion, int b_left_bin_num, float b_left_bin_proportion, float b_right_bin_proportion)
{

	float surfaceB1 = 0;

	int length_B = a_left_bin_num - b_left_bin_num  +1;

	// We create a histogram that represent surface to  ignore from the surface above S_B2
	List<int> histogram_s_ignore = Histogram_s_ignore(histogram, a_left_bin_num, b_left_bin_num, a_left_bin_proportion, h_S_B2, length_B);

	for (int i = 0 ; i >= length_B ; i++)
	{
		if(i == a_left_bin_num)
		{
			surfaceB1 += (histogram[i + b_left_bin_num + 6] - histogram_s_ignore[i])*b_right_bin_proportion;
		}
		elseif(i == b_left_bin_num)
		{
			surfaceB1 += (histogram[i + b_left_bin_num + 6] - histogram_s_ignore[i])*b_left_bin_proportion;
		}
		else{
			surfaceB1 += (histogram[i + b_left_bin_num + 6] - histogram_s_ignore[i]);
		}
	}

	return surfaceB1;
}

float selectivity_stricly_left(List<int> histogram, rangetype a)
{
	float v_min = histogram[0];
	float v_max = histogram[1];
	float surface_tot = histogram[3];
	float bin_range = histogram[4];
	float selectivity;

	if(a.minimum() <= v_min)
	{
		selectivity =  0;
	}
	elseif(a.minimum() >= v_min)
	{
		selectivity =  1;
	}
	else()
	{
		// we calculate the number of the a_left bin
		int a_left_bin_num = Num_bin(a.minimum(), bin_range, v_min);

		// we calculate the number of the b_left bin
		float b_min = a.minimum() - averrage_range;
		int b_left_bin_num = Num_bin(b_min, bin_range, v_min);

		// we calculate the proportion that A overlaps a_left_bin
		float a_left_bin_proportion = Bin_proportion(a.minimum(), bin_range, a_left_bin_num, v_min);

		// we calculate the proportion that B overlaps b_left_bin and b_right_bin (who is also a_left_bin)
		float b_left_bin_proportion = Bin_proportion(b_min, bin_range, b_left_bin_num, v_min);
		float b_right_bin_proportion = 1-a_left_bin_proportion;

		// we calculate h that will be the height of S_B2
		float h_S_B2 = H_SB2(List<int> histogram, a_left_bin_num, a_left_bin_proportion, b_left_bin_num, b_right_bin_proportion);

		// We create the variables that will store the area of each zone

		float surface_prime = Surface_prime(histogram, a, b_left_bin_num, b_left_bin_proportion);
		float surfaceB1 = SurfaceB1(histogram, a_left_bin_num, b_left_bin_num, b_left_bin_proportion,b_right_bin_proportion, h_S_B2);
		float surfaceB2 = SurfaceB2(histogram, a_left_bin_num, a_left_bin_proportion, b_left_bin_num, b_right_bin_proportion);

		// We proceed to the calculation of the selectivity

		surface = surface_prime + surfaceB1 + surfaceB2*0.5;
		selectivity = surface/surface_tot;
	}
	return selectivity;
}