#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

int amount = 0;

static void merge(vector<int>& buf, size_t left, size_t right, size_t middle)
{
    if (left >= right || middle < left || middle > right) return;
    if (right == left + 1 && buf[left] > buf[right]) {
        swap(buf[left], buf[right]);
        amount++;
        return;
    }

    vector<int> tmp(&buf[left], &buf[right] + 1);

#pragma omp parallel for
    for (size_t i = left, j = 0, k = middle - left + 1; i <= right; ++i) {
        if (j > middle - left) {
            buf[i] = tmp[k++];
        }
        else if (k > right - left) {
            buf[i] = tmp[j++];
        }
        else {
            buf[i] = (tmp[j] < tmp[k]) ? tmp[j++] : tmp[k++];
        }
    }
}

static void MergeSort(vector<int>& buf, size_t left, size_t right)
{
    if (left >= right) return;

    size_t middle = left + (right - left) / 2;

#pragma omp parallel sections
    {
#pragma omp section
        MergeSort(buf, left, middle);
#pragma omp section
        MergeSort(buf, middle + 1, right);
    }
    merge(buf, left, right, middle);
}

int main()
{
    int n = 100;
    vector<int> A(n);
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100;
        cout << A[i] << " ";
    }
    cout << endl;
    MergeSort(A, 0, n - 1);
    cout << "sort: ";
    for (int i = 0; i < n; i++)
        cout << A[i] << " ";
    return 0;
}
