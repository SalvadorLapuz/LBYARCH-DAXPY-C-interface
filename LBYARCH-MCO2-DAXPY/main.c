// LBYARCH S13 | x86-to-C Interface Programming Project
// LAPUZ, Mari Salvador
// TABADERO, Audrea Arjaemi T.

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>

#define SIZE 1048576 // 2^20
//#define SIZE 16777216// 2^24
//#define SIZE 536870912// 2^29
//#define SIZE 1073741824// 2^30

int sanityCheck();
void daxpyC(double* Z, double* X, double* Y, double A, int size);
extern void daxpyAsm(double* Z, double* X, double* Y, double A, int size);
void displayArray(double* Z, int size);
void rando(double* array, int size, int seed);
void saveToCSV(double* cData, double* asmData, int size, double cAvg, double asmAvg);

int main() {
	int check;

	double* cZ = (double*)malloc(SIZE * sizeof(double));
	double* asmZ = (double*)malloc(SIZE * sizeof(double));
	double* X = (double*)malloc(SIZE * sizeof(double));
	double* Y = (double*)malloc(SIZE * sizeof(double));
	double A = 2.00;

	double c_time_spent = 0;
	double asm_time_spent = 0;
	double total_c_time_spent = 0;
	double total_asm_time_spent = 0;
	double asmTime[30];
	double cTime[30];

	printf("Vector Size = 2^%d\n", 29);
	printf("Executing C and ASM Functions...\n\n");
	check = sanityCheck();
	if (check == 0) {
		printf("Return values from ASM and C functions don't match!\n");
		exit(0);
	}
	else if (check == 1) {
		printf("Passed sanity check!\n\nExecuting tests...\n\n");
	}

	for (int i = 0; i < 30; i++) {
		rando(X, SIZE, 1);
		rando(Y, SIZE, 3);

		clock_t begin = clock();
		daxpyC(cZ, X, Y, A, SIZE);
		clock_t end = clock();
		c_time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
		cTime[i] = c_time_spent;

		clock_t begin_asm = clock();
		daxpyAsm(asmZ, X, Y, A, SIZE);
		clock_t end_asm = clock();
		asm_time_spent = (double)(end_asm - begin_asm) / CLOCKS_PER_SEC;
		asmTime[i] = asm_time_spent;

		total_c_time_spent += c_time_spent;
		total_asm_time_spent += asm_time_spent;

		printf("Iteration %d", i + 1);
		printf("\nC: %.4lfs\n", c_time_spent);
		printf("Assembly: %.4lfs\n\n", asm_time_spent);

	}

	printf("---------------------------------------\n");
	printf("\nAverage Execution time in C: %.4lfs\n", total_c_time_spent / 30);
	printf("Average Execution time in Assembly: %.4lfs\n\n", total_asm_time_spent / 30);

	printf("Saving results to CSV file...\n");
	saveToCSV(cTime, asmTime, 30, total_c_time_spent / 30, total_asm_time_spent / 30);

	free(cZ);
	free(asmZ);
	free(X);
	free(Y);

	return 0;
}

int sanityCheck() {
	double cZ[3] = { 0.00 };
	double asmZ[3] = { 0.00 };
	double X[3] = { 1.00, 2.00, 3.00 };
	double Y[3] = { 11.00, 12.00, 13.00 };
	double A = 4.00;

	daxpyC(cZ, X, Y, A, 3);
	daxpyAsm(asmZ, X, Y, A, 3);

	printf("C results: ");
	displayArray(cZ, 3);

	printf("x86-64 results: ");
	displayArray(asmZ, 3);

	for (int i = 0; i < 3; i++) {
		if (cZ[i] != asmZ[i]) {
			return 0;
		}
	}
	return 1;
	printf("\n\n");
}

void daxpyC(double* Z, double* X, double* Y, double A, int size) {
	for (int i = 0; i < size; i++) {
		Z[i] = A * X[i] + Y[i];
	}
}

void displayArray(double* Z, int size) {
	for (int i = 0; i < size; i++) {
		if (i == size - 1)
			printf("%.2f ", Z[i]);
		else
			printf("%.2f, ", Z[i]);
	}
	printf("\n");
}

void rando(double* array, int size, int seed) {
	srand(((unsigned int)time(NULL)) / seed);
	for (int i = 0; i < size; i++) {
		array[i] = (double)(rand() % 10000 + 1) / 100;
	}
}

void saveToCSV(double* cData, double* asmData, int size, double cAvg, double asmAvg) {
	FILE* file = fopen("results.csv", "w");
	if (file == NULL) {
		printf("Error opening file %s for writing.\n", "results.csv");
		return;
	}

	fprintf(file, "Iteration,C Execution Time (s),Assembly Execution Time (s)\n");

	for (int i = 0; i < size; i++) {
		fprintf(file, "%d,%.4lfs,%.4lfs\n", i + 1, cData[i], asmData[i]);
	}

	fprintf(file, "Average,%.4lfs,%.4lfs\n", cAvg, asmAvg);

	fclose(file);
}