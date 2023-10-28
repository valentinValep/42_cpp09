#include "PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

#define SSTR( x ) static_cast< std::ostringstream & >( \
		( std::ostringstream() << std::dec << x ) ).str()

int	error(std::string file, unsigned int line, std::string msg)
{
	std::cout << "Error: " << file << ":" << line << ": " << msg << std::endl;
	return (1);
}

unsigned int	get_jacobstal_number(unsigned int n);
std::vector<unsigned int>	get_jacobstal_indexes(unsigned int size);

int	jacobstal_number_tests()
{
	unsigned int	jac_seq_arr[] = {0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 178956971, 357913941, 715827883, 1431655765, 2863311531};
	std::vector<unsigned int>	jac_seq(jac_seq_arr, jac_seq_arr + sizeof(jac_seq_arr) / sizeof(unsigned int));

	for (unsigned int i = 0; i < jac_seq.size(); i++)
		if (get_jacobstal_number(i) != jac_seq[i])
			return (error(__FILE__, __LINE__, SSTR("get_jacobstal_number(" << i << ") != " << jac_seq[i])));
	return (0);
}

size_t	get_jacobstal_indexes_size(unsigned int n)
{
	size_t	size = 0;
	int		i = 0;

	while (size < n)
		size = get_jacobstal_number(i++);
	return (size);
}

int	jacobstal_indexes_tests()
{
	unsigned int	jac_ind_arr[] = {
		// from 0 to 0
		0,
		// from 2 to 1
		2, 1,
		// from 4 to 3
		4, 3,
		// from 10 to 5
		10, 9, 8, 7, 6, 5,
		// from 20 to 11
		20, 19, 18, 17, 16, 15, 14, 13, 12, 11,
		// from 42 to 21
		42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21,
		// from 84 to 43
		84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43,
		// from 170 to 85
		170, 169, 168, 167, 166, 165, 164, 163, 162, 161, 160, 159, 158, 157, 156, 155, 154, 153, 152, 151, 150, 149, 148, 147, 146, 145, 144, 143, 142, 141, 140, 139, 138, 137, 136, 135, 134, 133, 132, 131, 130, 129, 128, 127, 126, 125, 124, 123, 122, 121, 120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85
	};

	std::cout << "testing : " << sizeof(jac_ind_arr) / sizeof(unsigned int) << " indexes" << std::endl;

	std::vector<unsigned int>	jac_ind(jac_ind_arr, jac_ind_arr + sizeof(jac_ind_arr) / sizeof(unsigned int));

	for (unsigned int i = 0; i < jac_ind.size(); i++)
	{
		std::vector<unsigned int>	jac_ind_test = get_jacobstal_indexes(i);
		size_t						size = get_jacobstal_indexes_size(i);
		if (jac_ind_test.size() != size)
			return (error(__FILE__, __LINE__, SSTR("get_jacobstal_indexes(" << i << ").size() != " << size << " (got " << jac_ind_test.size() << ")")));
		for (unsigned int j = 0; j < size; j++)
			if (jac_ind_test[j] != jac_ind[j])
				return (error(__FILE__, __LINE__, SSTR("get_jacobstal_indexes(" << i << ")[" << j << "] != " << jac_ind[j])));
	}
	return (0);
}

int	PmergeMe_tests()
{
	// test empty array
	PmergeMe<int>	pmergeMe(std::vector<int>(0));
	std::vector<int>	sorted = pmergeMe.merge_insertion_sort();
	if (sorted.size() != 0)
		return (error(__FILE__, __LINE__, SSTR("sorted.size() != 0")));

	// test array of size 1
	pmergeMe = PmergeMe<int>(std::vector<int>(1, 42));
	sorted = pmergeMe.merge_insertion_sort();
	if (sorted.size() != 1 || sorted[0] != 42)
		return (error(__FILE__, __LINE__, SSTR("sorted.size() != 1 || sorted[0] != 42")));

	// test array of size 2
	std::vector<int>	vec(2);
	vec[0] = 42;
	vec[1] = 21;
	pmergeMe = PmergeMe<int>(vec);
	sorted = pmergeMe.merge_insertion_sort();
	if (sorted.size() != 2 || sorted[0] != 21 || sorted[1] != 42)
		return (error(__FILE__, __LINE__, SSTR("sorted.size() != 2 || sorted[0] != 21 || sorted[1] != 42")));

	vec[0] = 21;
	vec[1] = 42;
	pmergeMe = PmergeMe<int>(vec);
	sorted = pmergeMe.merge_insertion_sort();
	if (sorted.size() != 2 || sorted[0] != 21 || sorted[1] != 42)
		return (error(__FILE__, __LINE__, SSTR("sorted.size() != 2 || sorted[0] != 21 || sorted[1] != 42")));

	// test array of size 3
	vec.resize(3);
	for (int i = 0; i < 3; i++)
	{
		vec[i] = 84;
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
				continue ;
			vec[j] = 42;
			for (int k = 0; k < 3; k++)
			{
				if (k == i || k == j)
					continue ;
				vec[k] = 21;
				pmergeMe = PmergeMe<int>(vec);
				sorted = pmergeMe.merge_insertion_sort();
				std::vector<int>	cpy = vec;
				std::sort(cpy.begin(), cpy.end());
				if (cpy != sorted)
					return (error(__FILE__, __LINE__, SSTR("vec(" << vec[0] << ", " << vec[1] << ", " << vec[2] << ") != sorted")));
			}
		}
	}

	// test array of size 4
	vec.resize(4);
	vec[0] = 84;
	vec[1] = 42;
	vec[2] = 10;
	vec[3] = 21;
	pmergeMe = PmergeMe<int>(vec);
	std::sort(vec.begin(), vec.end());
	sorted = pmergeMe.merge_insertion_sort();
	if (vec != sorted)
		return (error(__FILE__, __LINE__, SSTR("vec != sorted")));

	// test array of size 5
	vec.resize(5);
	vec[0] = 84;
	vec[1] = 5;
	vec[2] = 10;
	vec[3] = 21;
	vec[4] = 42;
	pmergeMe = PmergeMe<int>(vec);
	std::sort(vec.begin(), vec.end());
	sorted = pmergeMe.merge_insertion_sort();
	if (vec != sorted)
		return (error(__FILE__, __LINE__, SSTR("vec != sorted")));

	// test array of size 6
	vec.resize(6);
	vec[0] = 84;
	vec[1] = 10;
	vec[2] = 5;
	vec[3] = 42;
	vec[4] = 21;
	vec[5] = 0;
	pmergeMe = PmergeMe<int>(vec);
	std::sort(vec.begin(), vec.end());
	sorted = pmergeMe.merge_insertion_sort();
	if (vec != sorted)
		return (error(__FILE__, __LINE__, SSTR("vec != sorted")));

	// test array of size 10
	int arr[] = {84, 10, 5, 42, 21, 0, 1, 2, 3, 4};
	vec = std::vector<int>(arr, arr + sizeof(arr) / sizeof(int));
	pmergeMe = PmergeMe<int>(vec);
	std::sort(vec.begin(), vec.end());
	sorted = pmergeMe.merge_insertion_sort();
	if (vec != sorted)
		return (error(__FILE__, __LINE__, SSTR("vec != sorted")));

	// test array of size 20
	int arr2[] = {0, 10, 5, 42, 21, 84, 1, 2, 100, 9, 12, 17, 3, 32, 31, 7, 4, 11, 6, 13};
	vec = std::vector<int>(arr2, arr2 + sizeof(arr2) / sizeof(int));
	pmergeMe = PmergeMe<int>(vec);
	std::sort(vec.begin(), vec.end());
	sorted = pmergeMe.merge_insertion_sort();
	if (vec != sorted)
		return (error(__FILE__, __LINE__, SSTR("vec != sorted")));

	// test array of size 42
	int	arr3[] = {38, 26, 4, 0, 5, 15, 18, 37, 20, 9, 7, 1, 36, 25, 16, 28, 35, 24, 6, 12, 22, 27, 23, 21, 14, 40, 8, 34, 3, 41, 29, 17, 19, 13, 31, 2, 10, 11, 39, 30, 33, 32};
	vec = std::vector<int>(arr3, arr3 + sizeof(arr3) / sizeof(int));
	pmergeMe = PmergeMe<int>(vec);
	std::sort(vec.begin(), vec.end());
	sorted = pmergeMe.merge_insertion_sort();
	if (vec != sorted)
		return (error(__FILE__, __LINE__, SSTR("vec != sorted")));

	// test array of size 1000
	int	arr4[] = {235,352,113,880,367,985,395,508,830,898,997,720,460,26,68,521,34,455,167,845,224,835,707,619,318,574,630,165,730,225,315,429,402,457,394,659,438,765,219,844,475,840,200,795,131,339,0,803,37,577,822,554,364,967,726,443,812,624,781,202,127,973,297,175,512,926,114,666,984,687,587,177,956,278,280,412,740,230,646,243,163,982,358,754,391,375,775,863,288,95,673,380,247,338,385,934,94,477,258,92,974,653,71,70,589,757,310,448,216,255,161,672,696,537,572,818,5,511,872,586,893,441,62,910,140,362,145,21,20,848,655,489,396,970,100,529,403,633,348,921,622,662,456,603,860,820,873,647,923,240,514,451,713,286,579,369,940,75,580,346,53,4,116,119,16,319,523,478,374,268,183,379,902,802,935,502,838,946,35,643,933,181,831,553,613,335,569,147,10,505,804,920,932,829,981,668,515,223,510,721,918,735,86,188,850,807,134,608,552,424,870,663,842,905,942,895,883,462,585,620,471,543,220,530,185,852,919,979,312,480,63,908,816,345,253,410,425,172,38,24,636,354,54,45,708,482,745,897,121,242,211,615,678,983,187,193,598,488,821,493,929,576,755,293,19,894,968,203,833,171,837,826,195,638,144,153,660,215,729,43,65,516,612,307,481,274,486,889,671,526,868,877,594,504,858,711,769,557,865,329,413,519,593,231,724,692,287,915,78,142,209,555,311,640,874,760,864,420,960,927,229,778,899,327,295,388,890,42,648,568,853,472,254,205,650,218,234,350,115,992,250,566,876,164,931,439,162,67,282,355,682,73,688,152,697,500,652,814,158,101,88,393,458,141,168,48,701,780,432,61,128,561,285,996,621,766,154,676,129,11,28,558,896,641,418,349,463,846,937,332,245,204,272,904,46,686,246,8,847,805,469,947,436,986,739,178,376,706,189,106,520,513,279,344,958,764,347,491,719,750,326,742,548,855,751,427,123,450,169,93,590,703,221,281,540,201,825,878,733,768,148,738,400,485,132,337,583,176,473,925,296,772,517,541,944,96,248,190,617,651,405,77,773,97,907,823,356,901,437,283,999,109,308,685,966,597,271,199,30,361,404,675,817,373,611,851,867,69,497,370,544,22,581,813,483,324,302,565,166,276,52,879,665,563,522,906,753,149,792,614,582,811,186,409,866,442,179,806,856,322,912,681,430,971,789,550,284,717,645,606,667,194,539,1,656,952,465,66,301,39,9,49,47,415,994,299,903,786,313,232,683,334,151,570,605,208,452,690,416,644,377,244,698,991,191,524,669,664,993,60,470,401,710,368,882,767,351,635,91,962,871,270,827,836,381,291,251,949,849,808,762,567,269,716,298,159,774,105,793,610,217,292,484,728,117,107,736,631,832,398,12,249,433,704,854,479,365,758,689,571,386,684,888,798,939,961,546,103,654,869,7,801,266,501,336,213,227,787,17,110,725,534,487,528,800,796,945,453,137,426,761,779,122,104,382,749,731,525,680,304,305,360,892,446,909,466,226,980,146,90,259,674,743,277,459,303,957,799,84,309,112,978,924,535,943,23,506,936,80,366,212,559,723,573,531,928,542,922,25,41,490,990,810,387,699,911,330,82,262,133,776,538,954,843,885,592,323,320,748,214,72,428,518,712,440,661,784,887,236,419,884,267,83,839,560,632,498,390,953,496,314,359,445,417,507,454,136,691,467,289,679,261,474,977,642,788,499,917,975,941,596,556,695,875,340,435,584,741,241,616,495,785,273,602,342,702,634,938,732,252,601,809,99,228,294,995,591,637,492,56,81,58,331,118,372,791,170,629,102,770,182,476,2,468,233,197,744,900,815,59,509,363,44,494,14,434,734,989,206,834,13,782,431,237,627,714,859,125,160,275,771,797,819,987,57,964,157,143,700,988,422,588,18,74,406,397,913,551,532,333,533,461,180,55,353,87,998,32,527,618,138,196,722,64,399,126,120,384,184,29,76,15,210,959,447,886,383,607,192,98,198,862,40,783,260,881,50,421,408,626,389,411,562,378,265,256,891,955,300,257,264,625,449,972,639,604,763,173,317,759,705,407,85,677,316,124,135,824,464,737,715,930,914,595,111,306,392,976,263,414,709,916,33,658,89,599,623,6,549,36,547,290,139,328,536,575,156,174,321,727,207,3,239,503,777,150,27,155,694,950,649,965,794,343,341,325,130,609,564,752,357,600,841,238,718,790,857,969,222,747,657,31,371,578,693,756,628,746,670,951,79,545,828,948,861,108,423,51,444,963};
	vec = std::vector<int>(arr4, arr4 + sizeof(arr4) / sizeof(int));
	pmergeMe = PmergeMe<int>(vec);
	std::sort(vec.begin(), vec.end());
	sorted = pmergeMe.merge_insertion_sort();
	if (vec != sorted)
		return (error(__FILE__, __LINE__, SSTR("vec != sorted")));

	// test array of size 5000
	int	arr5[] = {1217,4018,2429,4621,1053,1024,3665,4253,221,4662,4112,3438,3294,2127,4699,2927,3007,4967,51,4200,4905,2380,1584,2452,2235,1810,719,1740,2823,4733,4824,1658,4818,1916,4469,359,3661,4361,2716,3058,3083,3644,2131,144,551,202,2580,744,1202,708,4896,483,234,4801,4115,3055,1332,990,819,3734,671,1659,879,2844,4826,3107,3130,2692,2753,2742,1419,3611,3910,911,3354,1957,3712,2561,1519,386,4055,1749,963,4768,4645,2906,2966,2988,2433,3830,4565,3214,3596,2455,3410,3743,3701,97,2873,3645,4571,4737,3123,1426,3825,224,590,4122,575,809,3078,2678,3121,4810,3769,993,4844,649,4403,3496,219,3607,4817,4238,1240,2001,3086,3913,3466,4097,1136,3313,347,3176,873,2704,584,1573,4965,2851,996,4900,3243,507,3605,3020,1843,1505,890,4437,2458,1908,183,2238,4726,1119,185,299,2396,3798,1816,3357,116,764,690,3919,3492,755,4296,343,4103,2077,4615,4626,4046,1974,2909,1973,1233,4267,2245,3493,539,2555,1814,2217,3706,3142,2516,3528,1960,945,2781,1358,18,1940,975,1758,2313,3548,3883,603,232,4345,4248,936,529,4327,3340,2389,476,101,3937,480,905,1346,4113,4232,2874,2637,4504,1597,3245,3626,477,3699,4305,721,607,3367,762,4832,485,4490,1125,4364,3507,2316,2647,4303,3973,287,1128,3509,4926,2321,4090,3953,3198,160,402,3733,1357,4596,949,914,2124,865,1352,4325,3171,1694,2869,752,3915,404,370,3249,3079,4167,4344,4974,3495,2901,3336,215,919,530,3523,3470,4962,1149,2468,2159,111,4368,1567,3224,4802,3375,1601,2955,3233,4411,2486,4275,4291,2801,3707,390,2121,4945,1076,332,2852,3467,591,1949,2491,726,2757,528,4033,3399,2470,3580,4874,1162,4507,3124,159,4171,1718,3650,3338,4960,2679,4398,4242,918,780,1443,4816,2614,4650,2338,1599,1490,3739,1652,284,4406,1982,2223,4774,2890,182,4659,1356,14,1107,3996,2392,1773,4842,2143,4578,512,1395,4756,4454,4550,955,3433,1153,2197,508,4441,2613,1750,387,1617,3030,2227,1132,807,1105,2932,1839,2865,3748,3930,2856,3291,1272,2744,4042,3658,270,4174,1777,392,3101,1820,3381,4255,2150,1331,4924,365,4564,98,235,4143,421,1582,2758,2116,67,4272,457,2566,4909,4311,4451,2889,4982,2752,3680,4952,901,2970,2552,123,42,4913,927,4134,3981,3787,3584,4608,4688,4280,2892,610,1958,4976,4666,3766,1142,1580,910,3068,1218,930,2759,4681,1798,4786,2527,3761,3541,2391,4460,798,3773,626,3651,961,681,4461,1998,1725,4172,3491,771,1029,4646,4290,1455,1171,1340,4822,2078,1767,1631,3365,175,4850,16,1651,536,3066,913,27,553,2866,2253,2208,305,2830,3873,4371,976,2084,4263,4702,1109,1634,522,333,3648,3921,127,4141,1436,1518,1929,1322,4495,4227,4278,218,1323,4140,4420,3431,3934,825,2989,3568,4362,354,4023,2683,1891,606,344,4683,4474,3165,3871,2308,3246,1587,4124,2542,465,2665,1074,1822,459,3503,2161,2035,4994,4966,348,2450,3459,3300,3186,2094,4617,863,3414,4553,1068,4724,2590,2576,820,4073,2834,1183,1382,1823,748,2707,523,339,1211,2628,4079,3725,3885,3164,4402,2306,1596,4836,2195,4218,4040,1877,644,4812,304,1177,4043,563,331,2153,5,2987,1959,4697,4918,758,3592,2301,3904,4753,983,4628,2629,2913,1607,3075,3552,2686,4086,4835,3413,3111,1472,3571,613,854,1092,1415,2249,3663,3630,3407,1508,4522,1627,646,2691,4234,41,4466,723,1007,3439,4394,1894,4351,4777,2122,310,4388,2406,4690,3432,1944,1530,830,4424,3471,34,1431,3662,77,3332,4005,954,4536,145,3616,1259,3875,1215,2358,194,1844,3705,3458,1261,3486,4482,1910,4950,647,3821,4219,2315,1946,488,4526,229,4769,2024,2791,2749,1268,21,4417,398,2553,3390,2037,1714,4561,4562,670,249,2975,1895,3983,1234,3346,4347,321,2439,4903,4377,2485,2702,678,3129,3550,4386,1796,2069,1251,894,1683,4182,2796,4473,3374,4025,4907,212,4587,106,3637,2888,1097,612,426,782,3670,1970,3692,1543,112,3309,1537,3694,4175,4342,675,2810,1495,3211,4829,1641,4823,533,1521,1143,2949,986,1392,88,3586,2267,100,2921,1435,3341,1899,2726,2819,2277,599,3003,2461,4604,3168,4353,2107,4310,4056,4443,898,4813,1157,4846,138,2142,4209,4409,135,3145,3537,965,838,1075,1722,1210,1344,707,4693,3708,246,1275,792,4317,908,2500,1277,2776,3927,4102,4963,2216,3898,1558,302,4871,1525,4491,1481,1541,256,4062,4820,3693,1854,3222,2674,906,4014,1800,341,3946,4804,399,1977,2302,4011,953,1152,2482,243,4314,289,652,2100,4916,4707,466,1903,2912,931,841,3629,4382,2241,937,2164,2896,2700,656,1411,3226,1950,1333,3385,1464,3697,2359,2264,2003,4009,197,1857,3027,1413,1398,1945,2539,2581,4521,68,560,2582,2910,4197,1220,1019,4757,2712,1315,1148,2467,3154,4754,2266,3148,4780,3956,184,871,3943,720,655,795,3840,3926,545,4508,1225,4412,4431,2177,1246,3046,694,2972,2534,225,3469,1429,4876,230,1776,4837,3094,858,899,3666,992,672,4173,3617,3522,1325,66,2985,2732,2797,519,3252,3851,2663,2734,734,3757,4207,253,3393,788,1458,4221,1447,1011,4869,3146,94,479,3254,4910,2049,2041,57,765,4630,3292,1258,4993,4566,3034,4619,444,3024,2718,3339,2393,3115,2408,1203,3511,3558,1475,2635,2370,1066,1198,2586,999,2403,1920,4664,3316,583,500,1016,3135,3092,525,178,546,4425,3143,1354,3364,4749,1835,3203,4307,3782,1087,2600,168,1513,1645,4983,1439,4026,3732,435,472,1552,2849,2944,625,2174,2848,4771,2795,2247,4614,1370,15,3102,4904,4468,4887,1741,2136,733,3918,1371,58,1205,1733,1297,938,4130,455,103,2123,1997,1479,3655,136,4016,4531,1621,1939,3891,3120,2845,113,3848,831,315,4831,3792,4148,3318,1061,4233,509,2981,532,453,732,505,869,2703,3618,301,1768,1476,2652,4767,367,689,1223,4849,4539,430,3805,4032,4399,2088,504,3814,2309,4358,3879,260,760,1168,324,4179,1438,4072,2212,4579,2366,3816,3350,176,3510,4282,2021,2231,1036,1892,2805,503,4895,1409,3936,3352,1904,1880,3004,747,988,3720,604,1540,82,351,3113,4669,1111,4281,4590,790,839,3505,4932,3351,2598,1578,456,3358,4638,429,1803,537,3852,56,2398,2368,2185,3643,2360,2694,3237,1654,4959,3334,4000,916,3005,162,4163,4300,888,1808,2544,4828,960,4189,47,1650,2156,213,2352,2328,1253,349,1603,154,2862,2427,3970,1925,3159,3668,754,948,2102,3892,1572,4928,3640,1919,3283,2762,2775,2760,2418,1731,628,1158,1388,3219,2495,3856,669,4906,2026,1140,1794,4609,2426,3758,3628,2496,2723,1139,3314,1090,578,4254,3370,1227,3376,845,1782,1600,2836,2394,1921,1909,3071,4640,280,39,619,1743,4555,3709,3265,4109,3227,2129,1689,1793,3306,1293,360,2905,4520,4581,2846,1788,3382,3449,3476,951,3108,4295,482,203,1402,143,2344,2276,2361,1978,4545,1309,1936,1339,2095,3474,3262,1536,3544,4301,4770,192,3506,1618,1393,3389,2638,148,1316,3752,463,3366,236,2969,4117,915,1888,4236,99,4413,1336,3425,4205,70,1858,4795,4878,424,4779,3013,806,2575,2416,4934,3524,1935,3815,3660,1167,2179,4567,2806,2312,364,1028,3779,4811,2636,2135,1420,2523,4249,3895,4268,1181,2633,1510,1319,4698,1022,3560,4315,2341,2568,1138,1619,4164,1547,3166,2588,2828,2510,715,2929,1116,2165,4634,4222,3001,1965,2858,4047,947,2538,1191,3319,2867,499,1317,2569,2941,2456,1377,3036,559,502,3218,3886,542,3483,4755,4297,1691,1992,4012,682,4808,1744,1850,880,944,2662,2257,400,2004,155,4396,4560,265,2271,1772,226,883,1091,137,939,3343,4385,4081,33,3259,1012,2573,119,2713,1502,3212,2785,1813,4391,1301,79,2463,4763,1423,4569,1390,982,781,2737,1160,2689,2610,1595,4839,133,2168,470,1728,3435,355,312,1,1669,3762,1305,4328,187,3986,3345,3603,2634,84,2229,2334,2331,3751,710,4725,4215,1096,3333,2721,3654,4948,1084,3217,2746,492,126,4193,2154,4169,1685,4118,4170,3556,3250,1761,4323,4843,3905,3074,2596,4264,3204,2211,1806,117,1348,3664,3740,1753,3428,4151,490,1343,4379,3867,4882,3726,1745,3687,3967,2300,1279,2483,2773,1842,3572,2549,3899,761,1705,2063,2047,64,903,4139,3191,2343,3423,1229,313,4803,1657,3783,3724,3772,2996,2278,4497,1381,2163,1757,527,2193,4002,4108,1807,959,572,4022,573,4700,4623,1557,950,3419,3824,632,2002,3264,4247,2984,1668,570,2108,3363,2583,1811,2222,1433,3517,4166,3054,3513,1779,3652,2777,4885,3406,2133,3080,2991,2838,1260,3497,4605,4276,4376,800,3746,4847,269,4156,1987,3903,3235,657,3464,4554,569,4407,1605,405,4257,4322,1969,1616,4381,3042,247,2503,2766,2053,3776,1928,2525,3502,3514,4191,582,2294,4198,2365,4937,2140,3320,1342,3063,3170,2693,4572,1050,1216,3615,850,4339,1870,773,3747,45,2644,4527,1707,4884,3601,1666,410,3238,2914,1129,1422,3323,661,3929,3606,1859,1412,4889,4898,3880,1663,1993,4306,384,1292,3569,3297,1424,171,3337,3602,3531,3188,3691,4622,3756,4035,3302,3261,677,1984,4448,473,835,2333,2536,2784,3032,4252,4925,2770,4060,4436,3841,2048,2337,2871,2128,933,1047,968,3424,3157,3853,3312,2325,4334,3391,3310,4147,784,3011,4586,635,2020,2478,1242,853,1882,4873,4408,966,1701,93,2205,3553,2272,4627,1932,3359,1667,1727,1262,3436,3185,1881,1590,1624,589,4610,803,3870,1841,1889,2591,180,1697,211,2863,2977,922,1006,3809,4593,107,1905,1207,1553,668,2209,4682,3512,2917,3396,1724,2747,1271,170,2148,702,4050,1361,660,3215,1918,338,1355,4861,3118,4136,4692,3700,2860,1795,3508,4483,3878,962,4228,2761,4739,1244,2401,3207,3103,1711,2937,3278,4265,2728,1550,2099,2675,3355,4547,4121,2509,1059,4003,1736,4129,849,1503,4093,1213,4378,520,3954,4237,521,11,3150,4687,1649,2489,2519,2381,2671,4416,4573,3952,1126,3636,991,1265,4038,2696,4430,2443,2220,4366,4341,1819,1836,3621,1106,2011,2632,524,767,881,340,3494,909,85,3008,1110,779,1449,852,2593,1067,2175,946,3315,1732,2221,498,3085,4332,2546,72,1922,4709,1739,4373,3189,3197,149,791,1655,2270,240,3860,593,4498,1900,957,2511,2465,3059,538,285,2032,598,4877,1866,2255,3902,4349,1783,2171,2303,972,3447,3961,3276,2661,3978,2097,2466,4731,1048,1937,2915,1752,2907,618,2653,2748,4500,4958,4672,1069,1296,2015,1911,1700,1432,3175,1534,3836,55,141,1031,2230,3771,1086,3125,2724,834,3960,383,19,1642,222,3682,1120,1713,210,4935,1328,2900,1174,2537,3279,4463,3775,239,1840,4653,4995,4616,2550,8,793,1042,2204,2893,4800,2460,369,3384,9,897,3087,576,319,3608,373,2793,1349,3022,979,3304,2710,3258,3182,4989,2042,2682,969,3100,4516,268,2252,2809,2571,50,3823,1450,3923,3301,2289,3897,3768,3715,1112,4711,725,692,676,75,2882,4158,3581,3105,2756,2059,3849,2878,4745,4176,870,1326,1175,4455,3326,1516,2601,775,3578,1446,2564,1829,208,2940,2184,1989,201,1345,827,1696,4274,4583,290,1235,2947,4734,3038,2998,3128,2234,3441,3684,912,3920,3674,1856,4740,1442,995,2397,662,2517,4192,1636,1670,4797,3801,2219,1828,4338,3133,634,4594,3785,2173,738,4712,2719,3156,2968,3480,2930,414,1804,2022,3737,3451,4487,2740,3126,3240,3408,4010,4750,3696,1098,2735,122,3632,3799,1626,1058,882,4941,1791,3675,2854,1885,3284,4337,4123,1875,4085,2400,306,2973,1403,3369,2558,4477,1963,1681,776,1695,4186,2346,4949,2395,1575,4421,1648,3177,2046,4743,877,4478,3416,3755,449,2611,4599,3427,1287,1837,4809,3210,1716,3190,327,2387,1514,152,181,1593,4428,2639,264,1304,2574,3822,703,964,4784,4883,4760,1467,375,815,4641,1923,2224,1454,1864,3147,3846,3595,3741,1671,2741,3119,2254,1418,389,3220,3842,1017,1437,4930,4766,3422,3289,4776,1729,4530,1927,3442,4384,4107,3460,2188,1000,884,4165,130,2908,580,4041,4696,3163,206,3928,29,1208,295,735,443,2891,73,2086,63,1913,3457,2709,1665,722,4080,271,1376,2354,1397,3807,621,822,4127,4875,3180,2513,577,3090,411,3263,3268,4230,2964,4943,4661,2986,1204,4625,3935,2883,3901,4100,3837,4395,31,4738,4321,501,2117,1613,1546,547,4220,2621,4223,2826,96,1135,4348,4912,2817,2091,124,325,4246,303,2833,191,4685,1088,594,2604,2772,3671,4790,4017,3622,186,893,3290,169,2113,4629,753,2166,3440,1687,3417,926,4313,3482,3649,491,2743,362,2881,2178,4854,4633,4155,1990,2612,3567,469,1509,2279,2946,4030,2832,4195,2357,2928,3563,4783,104,4206,2362,2446,3446,1588,4471,4981,2350,1237,516,3397,1938,917,3236,1917,1320,2769,4432,4439,1099,3959,4168,1416,1350,4077,419,4203,3947,4422,1080,1682,4848,3999,1879,263,1568,1637,3368,3533,2431,3251,376,2196,3847,2911,2831,382,3141,3379,4575,2918,2789,3009,2685,2339,2659,4979,3735,1876,4954,4261,2040,615,4864,4576,4106,4369,3138,1089,134,4986,250,2137,638,2440,3949,4224,2960,518,4607,2442,2711,1539,2788,1559,697,4775,1077,2886,4270,1254,1023,4133,896,2648,1719,770,4138,3089,193,565,541,3052,1486,1614,3922,3728,2292,3285,895,772,1494,1797,4363,1407,3275,1604,2384,2206,1131,4529,7,4111,46,4860,2645,2864,511,2815,3900,688,2043,1931,3477,2172,2213,4494,1269,4678,3722,4161,4695,1245,2282,1886,4084,309,1549,2967,2480,1299,981,1504,4289,3209,925,3269,1282,2895,4654,2377,816,3695,2378,3835,3656,812,2976,4671,531,1137,3866,3635,4541,4902,425,1562,4465,1173,2899,3833,3968,320,3647,1581,4751,3299,2170,2202,4486,3266,3088,561,3963,836,2481,1620,166,4942,3679,1247,2012,4410,3778,4078,1612,1027,4807,2451,2158,1967,2880,1585,2923,4798,2640,2073,1463,840,2242,1321,718,3472,2484,238,1121,415,1123,3938,35,2695,3924,1185,2162,4036,3889,3811,3293,3817,3714,3039,3829,4188,74,1861,4433,2152,2715,1532,2356,4037,2369,2814,2529,2070,3065,2191,3888,3273,1566,471,1860,3392,3429,1698,2701,245,3057,416,1564,4480,3914,2974,2304,623,1039,2650,833,1186,3966,2373,1252,2916,4415,4606,4868,1026,2778,4742,2965,3882,4074,4019,4390,2275,1400,1952,4066,2622,558,1221,1491,2902,2794,1071,4484,1243,4717,3114,4706,3984,3260,393,552,3247,2926,1868,4636,4686,3916,4150,1453,3985,2376,3642,3865,233,385,2609,2578,1555,1146,2803,3911,3579,4283,1095,158,2045,2961,4031,2570,272,4806,4370,4277,1473,4094,394,2792,3225,1324,3896,4637,297,4202,847,4984,1896,1485,300,357,4479,4720,3763,645,4013,1427,335,4799,673,814,2120,1662,4142,3371,4580,1712,4357,1306,2595,1586,350,4029,32,2738,345,4591,658,1049,2771,4251,3789,861,3132,4256,4380,2379,353,746,1414,4485,458,2997,3342,855,2813,4972,1384,778,4549,1688,3917,329,2824,2092,3137,328,3073,1197,3091,3527,1035,4383,4190,2112,3023,4819,3639,1598,4154,3874,2925,2347,813,4359,3992,4071,4447,2324,2051,2706,2618,622,4789,731,91,4099,1832,3461,1827,3232,4723,1867,2273,3402,3667,3330,4845,3002,2971,1318,2008,1303,2931,4293,3229,2508,2956,2708,361,3112,1278,2104,1988,1684,1404,1523,131,1778,1072,2547,1715,4120,4577,1298,3545,650,568,3303,1971,1187,3587,920,535,1030,4956,4863,2681,932,4544,4509,4331,3061,3802,2942,1902,2286,1898,24,110,2157,4152,2071,4052,2548,2228,4470,156,2954,4788,4,2850,2190,3192,2943,3348,1563,1369,1465,1708,3881,2520,3031,3386,2825,3838,2090,4506,1941,4235,4971,1893,2551,693,1295,1180,617,4970,2545,4444,2619,3627,4008,3676,4716,2922,3311,1192,2579,1592,4329,2087,2780,1365,3982,684,4214,1362,4434,1995,2565,1385,2169,1302,1441,2904,2730,1489,3160,2428,2745,4535,3043,1078,4713,1653,61,4426,4791,1372,2274,3328,121,1206,2531,2487,1471,3430,2979,115,4069,4968,0,3255,4728,1005,1434,228,4467,3796,195,1848,3863,3612,2307,4975,2083,406,2076,4643,1638,1622,1226,3228,4330,2050,4985,1300,1452,60,1051,4814,2330,478,2952,4595,1606,3060,2690,4135,2877,4216,928,1677,3535,200,4679,1897,1821,1924,1818,4159,292,2318,3784,436,2476,4899,2898,2672,1379,95,2521,1591,597,2098,3631,1994,1734,52,4911,413,1133,1289,447,4462,2141,147,1812,2203,199,4045,1506,2342,1980,4764,1239,4212,4762,1103,3484,1855,1672,3047,2559,1248,1101,3634,1270,2664,2934,2526,2597,636,1169,4923,4044,3721,2764,3296,2957,3753,2490,4589,3274,1286,371,4533,366,3131,4825,1623,3659,766,1366,4387,2382,2438,1817,1884,934,3893,140,2512,401,2623,3010,2280,4705,4778,3136,3945,3018,1676,2488,712,2953,4940,128,2504,4592,704,4997,3463,4350,3962,174,2585,2870,1515,2194,794,1656,4110,2699,797,846,3534,214,4243,1313,1212,4908,4400,1789,1118,3481,4316,2829,2013,2291,2802,1507,4701,3109,474,3711,1124,1594,3818,4939,467,273,4676,4585,2385,261,4213,495,1845,1159,1104,3909,3099,4128,1528,4841,62,4603,1009,2717,1232,454,4540,2506,2297,196,4689,2959,3448,4157,3657,83,633,549,1644,2999,2868,1040,2149,1469,4978,1184,832,4258,902,2250,1646,1872,125,4446,2787,1730,2160,3134,4260,857,2688,4890,2811,1762,2285,1406,4552,3583,2669,1720,1954,1964,4787,1337,4858,1002,4857,3925,3971,161,1524,2200,818,1308,1359,3401,4340,1826,3828,777,3420,2945,2763,2054,3857,4481,643,4453,3152,4859,4660,4990,4598,139,4893,223,4881,4657,2657,2725,1673,2879,4304,2464,2705,4298,2351,4558,695,3453,1533,2768,4998,2494,4920,2479,2462,2919,2554,1018,2666,4064,4034,1425,997,1883,2025,1428,1224,275,1849,1738,4584,875,38,177,89,1520,4039,3906,4528,994,3539,4299,1468,907,3738,2295,1056,4288,1194,2236,3562,3710,4821,3070,3173,3069,1193,1968,2263,2528,409,163,2938,4001,1004,1577,3551,2584,4006,4559,4244,2144,1499,728,1488,1640,1981,4092,1529,4721,891,4827,4067,4999,2935,3912,4557,4374,2114,2106,4855,2857,3764,484,642,2036,4499,2560,3487,1241,974,3843,3979,3887,1754,4063,2290,3529,4741,4162,36,4204,4028,876,4658,2132,3485,2642,2332,1930,2125,3169,514,4101,248,1948,3864,3383,1195,2422,3797,3019,1934,4752,4346,866,4352,142,4054,601,3669,3570,2515,441,3234,4886,1526,3140,468,2293,4185,4438,3174,1551,4969,1947,3894,856,4312,592,2475,2472,3179,378,1602,4083,3454,2402,4442,1679,3404,768,1704,4525,1976,713,188,2096,3465,1196,323,3117,358,1457,4496,2624,1445,2774,3151,886,1628,423,2722,842,2540,4655,2029,3555,3155,2239,1901,3742,1556,1474,3286,4488,330,1228,4996,3208,1710,3808,336,251,627,3582,3017,3161,984,900,278,2014,3730,407,3813,3056,3325,4534,3940,3452,53,2119,3281,418,3295,25,317,3026,4951,4980,874,3890,1200,267,1512,3803,3646,3468,4511,10,2765,2499,48,4922,3280,3609,3767,510,4955,1127,2841,3810,663,12,2056,637,2677,3231,2625,1674,198,3200,1873,2225,2668,4286,3127,2005,4600,1943,417,2676,2111,114,2417,1401,3321,2750,69,3515,4838,2269,2311,3908,1496,2298,3589,4210,1647,120,2192,3149,4266,4927,1678,4355,1266,602,4318,4919,4194,3158,4931,605,648,153,3199,1338,3759,1755,2233,2243,3272,368,4262,745,4131,4727,4815,1288,2425,1190,817,2454,2064,3536,4089,1522,2210,4694,929,3426,3678,1871,1001,2180,714,2697,3834,978,237,1914,2299,2167,1915,1643,1311,653,1037,3760,2435,2859,2018,2924,293,4075,1906,973,4180,3547,1130,4336,581,427,600,4524,1347,3844,2646,1122,1831,3950,4178,2903,4294,860,2259,37,3744,3184,2673,1085,2028,683,1046,71,481,179,4397,1330,1264,4888,3861,4551,1639,2214,2414,751,274,432,1500,78,4365,3221,3557,4319,4250,740,4269,3015,1219,1610,6,1257,1531,2436,388,1517,3067,1003,759,3610,1456,4856,2000,1405,3241,3703,2109,1535,1375,129,334,4644,2950,4673,2827,4851,2493,2447,291,2134,3064,1583,1869,4796,2656,3827,3242,487,699,2182,774,2835,1851,1408,1102,2441,1170,3532,4126,1747,2818,1093,2755,4360,2101,397,2603,3600,2502,1511,1781,821,2982,2061,3791,1387,4746,2861,4862,924,4057,2314,2727,1574,3455,805,2371,2016,1380,4938,3689,3717,564,4729,3327,4612,3356,804,2980,2375,2994,1629,4722,3475,2434,789,2594,2962,1501,4285,1394,59,3806,2281,3850,544,3253,620,3322,244,1784,2103,2265,769,420,3025,729,4867,3400,2714,1440,674,3256,2654,3178,2010,4987,4601,1199,2062,2448,4119,3565,1015,2089,1280,2176,548,1021,4639,2804,3347,1410,1155,1062,1291,3049,189,460,608,4245,4125,4061,3317,1448,4144,2261,680,3690,442,440,1034,1721,1675,372,87,3812,4505,4356,4105,1975,3980,3804,204,1497,4375,1571,2992,3718,105,3239,4546,1735,3479,1025,1545,4830,4389,1396,4792,1386,4459,2410,1255,2363,1231,3372,2820,868,783,2533,970,2033,1108,3205,971,2631,1373,1460,614,3213,3095,4177,3462,2812,231,1250,2782,1417,4199,2067,2822,4058,4582,288,1459,4719,3223,4287,132,1966,526,889,705,3361,2840,2413,4452,4059,2232,826,2251,4137,3826,750,4024,2374,2800,1769,2240,1865,1953,2226,2453,3790,92,4021,1466,164,3331,431,3770,2105,3931,878,1399,3202,4503,4476,1363,1709,2390,26,1686,3518,4225,2034,2386,4747,3599,3593,2729,4953,437,2507,1775,450,108,2085,4489,3613,2335,4677,4872,1790,3104,3016,2038,3062,2557,395,4302,2058,4091,2248,4292,2283,494,3248,4027,49,2733,4096,2556,2246,1561,4652,1230,2608,4680,3298,294,967,1310,4418,1117,3349,810,1055,2602,977,102,2320,3944,279,4631,4404,2698,4691,4785,4240,2626,1633,4153,4891,1863,13,2471,3053,4183,2655,3360,86,517,3884,2412,342,4076,3786,314,2181,4053,2936,242,2837,1032,308,3277,4704,3543,3257,4977,540,1334,1274,4543,2767,2505,4563,258,4642,3434,4229,3540,2348,665,2126,4068,1717,596,298,2687,4226,3623,787,3591,445,3040,1070,4936,2589,1222,1478,438,3564,3378,4333,709,43,1483,2843,4095,3488,2660,2680,844,3957,2605,3077,2186,3588,3677,2983,151,3604,1846,2541,862,4782,3969,3727,3577,4512,412,4736,4429,1693,2288,4273,3181,4475,3394,1759,4393,513,1589,2383,4458,3958,799,2079,1660,4343,3443,3794,2617,3990,3576,4651,4181,624,586,3729,3713,1312,1765,2807,3380,4852,3964,1702,217,1538,3872,1961,4618,4781,3868,4714,1276,737,1726,1878,2658,3988,2319,1933,3172,346,4513,3489,4196,2670,1723,2457,4515,667,3624,286,616,4537,1742,666,4149,3041,2039,2887,363,2146,3196,2075,4457,3719,403,461,2407,3793,3620,3021,1010,1360,1256,3194,4915,1134,2872,2027,4556,3096,1664,318,2215,887,227,3499,4070,3093,4320,1484,4104,2939,1285,1054,998,259,1144,2019,1847,3633,4440,3122,631,2260,3519,4715,2532,823,739,3287,4957,3976,2437,2535,3736,989,3498,1746,2055,2145,4602,1284,567,4834,3977,1801,3832,2799,1560,451,1188,700,4668,1045,1329,664,1165,1166,4710,859,2364,904,4392,2643,1764,716,1341,940,2138,2498,1327,205,1073,1852,1912,3050,2933,2667,1294,796,1064,4087,3854,685,1972,4519,1834,4988,2990,4914,4944,1951,464,4866,2322,22,1374,462,1548,1985,3362,824,3450,3530,4542,4015,493,1389,1802,724,1955,2894,1249,4570,2421,3716,2118,2739,54,1979,1041,3641,4435,2256,4184,4568,2839,2198,2060,3800,2030,4517,515,4718,4472,4372,4647,2409,892,3044,4961,3839,711,1189,2323,4098,2367,3162,4992,2790,1060,1956,2875,4611,4933,3672,4523,4367,1201,3749,3437,1115,2885,1209,2052,4632,3994,381,422,3590,4211,3445,3995,534,1609,921,2736,2897,1874,3907,4445,4217,3859,4730,2477,1991,3998,1862,1554,828,736,2372,2353,1699,1833,322,2066,1838,2326,4597,2424,543,958,579,4324,757,786,118,3201,1766,216,3167,3444,2958,3538,3780,2081,595,1824,2287,3702,651,4146,3388,3076,1044,4271,452,1290,3781,2821,3000,3965,2201,3594,4309,433,2031,1335,554,2522,1267,1625,985,3955,3521,4048,2155,4973,3051,872,2296,2599,3415,3045,4794,2562,2514,851,2641,3418,641,556,587,3520,3230,2606,1082,3862,496,167,1163,942,2110,1114,3987,1792,3206,3072,2349,3554,2649,1014,1150,90,1771,4991,3788,3933,980,706,1926,172,4160,3307,281,173,3033,3516,3395,785,1907,1635,2151,1353,654,2951,23,1470,741,4514,4684,1164,941,4748,756,4675,1314,4574,550,2783,1094,1527,2139,255,3688,3193,1815,30,4892,4082,1081,4419,4502,3566,1579,207,434,2497,811,2189,2627,1364,3329,4259,4870,1182,2651,1154,2786,241,391,4735,1608,2779,2432,257,446,1065,1661,1786,2006,3685,3216,1281,2751,4703,2080,2684,3153,4663,2798,4088,557,4773,4674,4284,3082,2068,659,2592,109,3,2754,3932,283,1825,4354,1615,2336,1492,1760,1799,3585,3683,1498,3619,3116,1079,640,3035,3681,2074,763,374,1145,629,3575,3139,3098,2847,2415,254,3106,1887,630,4335,379,3723,3097,17,3048,4538,1770,1063,679,3795,4840,3373,2044,1351,4532,4744,2473,2007,609,1996,1462,1391,2183,3411,1421,209,44,3501,3698,150,1830,2530,4865,3948,4772,1033,2017,2327,2876,2199,475,1482,4518,1141,4308,1378,252,1176,311,2237,2808,1805,2920,4004,686,3271,687,3686,3731,2411,2620,3084,3187,4414,3110,165,3504,2072,3456,1487,2404,337,574,262,3412,2469,3398,742,4588,3244,4667,396,935,801,4208,1703,2577,1983,3993,3573,1576,4114,4656,1630,377,3997,4833,639,3006,1570,4921,4649,3195,1179,4964,76,4620,1569,2399,3405,3500,3282,380,4492,2630,2567,843,1632,3765,352,952,4450,2474,1151,2009,2187,4132,2262,2449,808,2065,408,2310,4880,3344,3028,2057,2317,1147,4201,3972,4449,4423,80,4759,2444,157,4501,2345,3939,2615,2082,4635,3403,2329,1430,3037,4326,3387,4020,4732,4187,701,2023,555,1083,20,1236,3597,848,1692,1774,4793,4624,4510,3183,3081,1383,1680,4805,3353,2884,2340,2268,1748,4401,3625,588,3014,3750,3598,3855,3831,727,3478,3704,277,356,2115,956,1890,2855,2524,4947,4758,730,3991,1013,3490,3574,3614,3942,3653,3549,2388,2978,3305,2305,4049,1161,4917,566,3308,1156,3858,1809,2258,1052,2420,1542,4405,562,4231,3526,1113,1368,3270,2218,1787,3845,4648,2616,1020,2,489,2816,4708,146,864,3774,571,2543,3144,3473,3754,266,1283,4761,1043,220,1853,1172,2948,326,2130,4116,2720,1706,307,4879,829,1737,506,4665,585,3951,3421,4464,1057,1544,2563,4145,2093,1008,2284,1451,3559,28,987,1962,1751,3777,611,3525,837,3324,2459,943,4051,1273,1367,2993,2445,2207,439,2853,4897,3877,1942,1480,1690,923,190,4239,1763,486,717,4670,65,2419,296,4929,1611,276,3819,3542,1214,3975,2607,3561,282,3876,4456,2430,2405,4548,743,4853,3012,1100,4427,3335,885,1785,2963,4241,2995,2518,4901,40,3869,497,1986,2492,867,1178,3941,3638,4279,4065,1263,4007,428,4765,1461,1038,802,81,3673,3029,2731,2244,3745,4613,4946,2355,4894,2501,1238,1307,691,3267,3820,3409,1999,3377,2587,1756,749,696,3288,2572,3989,1780,3974,1444,3546,1493,1565,1477,448,4493,2842,698,2147,316,2423};
	vec = std::vector<int>(arr5, arr5 + sizeof(arr5) / sizeof(int));
	pmergeMe = PmergeMe<int>(vec);
	std::sort(vec.begin(), vec.end());
	sorted = pmergeMe.merge_insertion_sort();
	if (vec != sorted)
		return (error(__FILE__, __LINE__, SSTR("vec != sorted")));

	return (0);
}

int	main(void)
{
	int	ret;
	int	ret_total = 0;

	// jacobstal number tests
	std::cout << "Starting jacobstal number tests" << std::endl;
	if (!(ret = jacobstal_number_tests()))
		std::cout << "Jacobstal numbers tests: ✅" << std::endl;
	else
		std::cout << "Jacobstal numbers tests: ❌" << std::endl;
	ret_total += ret;

	// jacobstal indexes tests
	std::cout << std::endl << "Starting jacobstal indexes tests" << std::endl;
	if (!(ret = jacobstal_indexes_tests()))
		std::cout << "Jacobstal indexes tests: ✅" << std::endl;
	else
		std::cout << "Jacobstal indexes tests: ❌" << std::endl;
	ret_total += ret;

	// PmergeMe tests
	std::cout << std::endl << "Starting PmergeMe tests" << std::endl;
	if (!(ret = PmergeMe_tests()))
		std::cout << "PmergeMe tests: ✅" << std::endl;
	else
		std::cout << "PmergeMe tests: ❌" << std::endl;
	ret_total += ret;

	std::cout << std::endl << "Total: " << ret_total << " errors " << (ret_total == 0 ? "✅" : "❌") << std::endl;
	return (0);
}
