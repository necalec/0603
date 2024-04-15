#include <iostream>
#include <vector>
#include <omp.h>
#include <thread>

using namespace std;

const int threads = thread::hardware_concurrency();

int main()
{
	vector <int> arr(10000, 0);
	int sum_1 = 0;
	for (int i = 0; i < 10000; i++) {
		arr[i] = rand() % 11;
		sum_1 += arr[i];
	}
	cout << sum_1 << endl;
	int sum = 0;
	#pragma omp parallel num_threads(threads)
	{
		#pragma omp for
		for (int i = 0; i < arr.size(); i++) {
			sum += arr[i];
		}
	}
	cout << sum << endl;
	cout << threads << endl;
}
