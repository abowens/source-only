#include <iostream>
#include <stdlib.h>	// atoi
#include <vector>
#include <random>		
#include <limits>

#ifdef _WIN32
    #include <execution>
#endif

#include <algorithm>	// std::sort
#include <chrono>

int cmp(const void* a, const void* b)
{
	if (*(int*)a < *(int*)b) {
		return -1;
	}
	else if (*(int*)a > *(int*)b)	{
		return 1;
	}
	else {
		return 0;
	}
}

int main(int argc, char** argv)
{
	if (argc != 3) {
		std::cout << "Usage: sorttime lim [qps]" << std::endl;
		return argc;
	}

	auto lim = atoi(argv[1]);

	std::vector<int> vec;
	vec.reserve(lim);

	std::default_random_engine generator;

	std::uniform_int_distribution<int> 
		distribution(
			std::numeric_limits<int>::min(), 
			std::numeric_limits<int>::max()
		);

	while (lim--) {
		vec.push_back(distribution(generator));
	}

	using namespace std::chrono;

	steady_clock::time_point t1 = steady_clock::now();

	if (*argv[2] == 'q') {
		qsort(&vec[0], vec.size(), sizeof(int), cmp);
	}
    else if (*argv[2] == 'p')	{
#ifdef _WIN32
		std::sort(std::execution::par, vec.begin(), vec.end());
#else
        std::cout << "parallel sort not supported!" << std::endl;
        return -1;
#endif
	}
	else if (*argv[2] == 's') {
		std::sort(vec.begin(), vec.end());
	}	

	steady_clock::time_point t2 = steady_clock::now();

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    std::cout << time_span.count() << " seconds" << std::endl;

	return 0;
}
