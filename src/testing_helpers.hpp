#pragma once

#include <cstdlib>
#include <cuda.h>
#include <cuda_runtime.h>


template<typename T>
int cmpArrays(int n, T *a, T *b) {
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            printf("    a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
            return 1;
        }
    }
    return 0;
}

void printDesc(const char *desc) {
    printf("==== %s ====\n", desc);
}

template<typename T>
void printCmpResult(int n, T *a, T *b) {
    printf("    %s \n",
            cmpArrays(n, a, b) ? "FAIL VALUE" : "passed");
}

template<typename T>
void printCmpLenResult(int n, int expN, T *a, T *b) {
    if (n != expN) {
        printf("    expected %d elements, got %d\n", expN, n);
    }
    printf("    %s \n",
            (n == -1 || n != expN) ? "FAIL COUNT" :
            cmpArrays(n, a, b) ? "FAIL VALUE" : "passed");
}

void zeroArray(int n, int *a) {
    for (int i = 0; i < n; i++) {
        a[i] = 0;
    }
}

void genArray(int n, int *a, int maxval) {
    srand(0);

    for (int i = 0; i < n; i++) {
        a[i] = rand() % maxval;
    }
}

void printArray(int n, int *a, bool abridged = false) {
    printf("    [ ");
    for (int i = 0; i < n; i++) {
        if (abridged && i + 2 == 15 && n > 16) {
            i = n - 2;
            printf("... ");
        }
        printf("%3d ", a[i]);
    }
    printf("]\n");
}

template <class T>
void testSorted(int n, const T *data, bool lessThan = true)
{
	if (n <= 0 || !data)
	{
		printf("    testSorted: Error: Invalid argument(s)\n");
		return;
	}

	for (int i = 0; i < n - 1; ++i)
	{
		if ((lessThan && (data[i] > data[i + 1])) ||
			(!lessThan && (data[i] < data[i + 1])))
		{
			printf("    Failed: Element %d %s Element %d\n", i, lessThan ? ">" : "<", i + 1);
			return;
		}
	}

	printf("    passed\n");
}

void printGPUInfo(int device)
{
	cudaDeviceProp deviceProp;

	cudaGetDeviceProperties(&deviceProp, device);

	std::cout << '\n'
		<< deviceProp.name << " [sm_" << deviceProp.major << deviceProp.minor << "]\n";
}
