#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <math.h>
#include "omp.h"

using namespace std;

int main(int argc, char* argv[])
{
	double start = 0, finish = 0;

	const int N = 500; //L2 = 2 * 256 KB;  
	const int K = 250;

	const int SIZE = N * N;

	int* A = new int[SIZE];
	int* B = new int[SIZE];
	int* C = new int[SIZE];


	for (int i = 0; i < SIZE; i++)
	{
		A[i] = rand() % 100;
		B[i] = rand() % 100;
		C[i] = 0;
	}

	if (argv[1][0] == '0')
	{
		start = omp_get_wtime();

		for (int time = 0; time < 15; time++)
			for (int i = 0; i < N; i++)
				for (int k = 0; k < N; k++)
					for (int j = 0; j < N; j++)
						C[i*N + j] += A[i*N + k] * B[k*N + j];

		finish = omp_get_wtime();
	}
	else if (argv[1][0] == '1')
	{
		start = omp_get_wtime();

		for (int time = 0; time < 15; time++)
			for (int j = 0; j < N; j++)
				for (int k = 0; k < N; k++)
					for (int i = 0; i < N; i++)
						C[i*N + j] += A[i*N + k] * B[k*N + j];

		finish = omp_get_wtime();
	}
	else
	{
		start = omp_get_wtime();

		for (int time = 0; time < 15; time++)
	 #pragma omp parallel for
			for (int jj = 0; jj < N; jj += K)
				for (int kk = 0; kk < N; kk += K)
				{
					for (int i = 0; i < N; i++)
					{
						for (int j = jj; j < min(jj + K, N); j++)
						{
							float sum = 0.0;
							for (int k = kk; k < min(kk + K, N); k++)
								sum += A[i*N + k] * B[k*N + j];
							C[i*N + j] += sum;
						}
					}
				}

		finish = omp_get_wtime();
	}

	cout << "Time: " << (finish - start);
}