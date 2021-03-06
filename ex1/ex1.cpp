// ex1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <process.h>
#include <vector>

using namespace std;

const int k = 3;
const int m = 3;
const int l = 3;

double **a = new double *[k];
double **b = new double *[m];
double **res = new double *[k];



unsigned __stdcall mult(void *param) {
	int inum = (int)param;

		for (int n = 0; n < l; n++) {
			res[inum][n] = 0;
			for (int p = 0; p < m; p++) {
				res[inum][n] += a[inum][p] * b[p][n];
			}
		}
	
	return 0;
}


int main()
{
	for (int i = 0; i < k; i++)
	{
		a[i] = new double [m];
	}
	for (int i = 0; i < m; i++)
	{
		b[i] = new double[l];
	}
	for (int i = 0; i < k; i++)
	{
		res[i] = new double[l];
	}

	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			a[i][j]=1;
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			 b[i][j]=2;
		}
		
	}
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	int numCPU = sysinfo.dwNumberOfProcessors; // кол-во ядер
	const int n = 3; //  кол-во потоков
	int num[n];
	unsigned int id;
	HANDLE threads[n];
	for (int i = 0; i < n; i++) {
		threads[i] = (HANDLE)_beginthreadex(NULL, 0, mult, (void*)(i), 0, &id);
	}
	WaitForMultipleObjects(n, threads, TRUE, INFINITE);
	for (int i = 0; i < n; i++)
	{
		CloseHandle(threads[i]);
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cout << " " << a[i][j];
		}
		cout << endl;
	}
	cout << "____________________________" << endl;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cout << " " << b[i][j];
		}
		cout << endl;
	}
	cout << "____________________________" << endl;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			cout << " " << res[i][j];
		}
		cout << endl;
	}
	for (int i = 0; i < k; i++)
	{
		delete [] a[i] ;
	}
	for (int i = 0; i < m; i++)
	{
		delete [] b[i];
	}
	for (int i = 0; i < k; i++)
	{
		delete [] res[i];
	}
	delete[] a;
	delete[] b;
	delete[] res;
	return 0;
}