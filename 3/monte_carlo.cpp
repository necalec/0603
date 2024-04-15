#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

int main()
{
    int num_points = 10000000;
    int count_inside = 0;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(0.0, 1.0);

#pragma omp parallel for reduction(+:count_inside)
    for (int i = 0; i < num_points; ++i) {
        double x = dis(gen);
        double y = dis(gen);

        if (x * x + y * y <= 1) {
            count_inside++;
        }
    }

    double pi_approx = static_cast<double>(count_inside) / num_points * 4;

    cout << "pi: " << pi_approx << endl;

    return 0;
}
