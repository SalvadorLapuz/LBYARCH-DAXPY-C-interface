#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

// reference ASM function
extern void daxpyAsm(double* X, double* Y, int Ysize);

void daxpyC(double* X, double* Y, int Ysize);

void userPrompt(int* sizeOfArray);
int checkSanity(double* Y_Asm, double* Y_C, int size);

void generateCsv(const double asmTime[], const double cTime[], int testRun, int size);
double getAverage(double* times, int size);

int main() {
    int sizeOfVector;
    userPrompt(&sizeOfVector);
    int Ysize = sizeOfVector - 6;

    double* X = malloc(sizeOfVector * sizeof(double));
    double* Y = malloc(Ysize * sizeof(double));
    double* X_C = malloc(sizeOfVector * sizeof(double));
    double* Y_C = malloc(Ysize * sizeof(double));

    int check;
    int yPrintLimit = 10;
    int testRun = 30;

    double asmTime[30];
    double cTime[30];

    clock_t start;
    clock_t end;

    if (X == NULL || Y == NULL) {
        printf("Memory not allocated!\n");
        free(X);
        free(Y);
        exit(0);
    }
    else {
        printf("Memory allocated successfully!\n");
    }

    // populate vectors
    for (int i = 0; i < sizeOfVector; i++) {
        X[i] = i;
    }

    for (int j = 0; j < sizeOfVector; j++) {
        X_C[j] = X[j];
    }

    printf("Executing C and ASM Functions...\nPrinting first 10 elements of Vector Y for checking...\n\n");
    daxpyAsm(X, Y, Ysize);
    daxpyC(X_C, Y_C, Ysize);

    check = checkSanity(Y, Y_C, Ysize);

    if (!check) {
        printf("Return values from ASM and C functions don't match!");
        free(X);
        free(Y);
        exit(0);
    }
    else {
        printf("Passed sanity check!\n\nExecuting test...\n");
    }

    printf("Running ASM Implementation 30 times...\n");
    for (int i = 0; i < testRun; i++) {
        start = clock();
        daxpyAsm(X, Y, Ysize);
        end = clock();
        asmTime[i] = (double)(end - start) / CLOCKS_PER_SEC;
    }

    printf("Running C Implementation 30 times...\n");
    for (int i = 0; i < testRun; i++) {
        start = clock();
        daxpyC(X_C, Y_C, Ysize);
        end = clock();
        cTime[i] = (double)(end - start) / CLOCKS_PER_SEC;
    }

    printf("Saving results to CSV file...\n");
    generateCsv(asmTime, cTime, testRun, sizeOfVector);
    return 0;
}

void daxpyC(double* X, double* Y, int iteration) {
    int stencilSum;
    int offset = 0;
    for (int i = 0; i < iteration; i++) {
        stencilSum = 0;
        for (int j = 0; j < 7; j++) {
            stencilSum += X[j + offset];
        }
        Y[i] = stencilSum;
        offset++;
    }
}

void userPrompt(int* sizeOfVector) {
    int good;
    do {
        printf("Input size of vector X: ");
        scanf_s("%d", &good);
        if (good < 7) {
            printf("Size too small! Please retry.\n");
        }
    } while (good < 7);
    *sizeOfVector = good;
}

int checkSanity(double* Y_Asm, double* Y_C, int size) {
    for (int i = 0; i < size; i++) {
        if (Y_Asm[i] != Y_C[i]) {
            return 0;
        }
        // output first 10 values
        if (i < 10) {
            printf("x86-64 implementation Y[%d]: %lf\n", i, Y_Asm[i]);
            printf("C Implementation Y[%d]:      %lf\n", i, Y_C[i]);
        }
    }
    return 1;
}

double getAverage(double* times, int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += times[i];
    }
    return sum / size;

}

void generateCsv(const double asmTime[], const double cTime[], int testRun, int size) {
    FILE* file = fopen("result2.csv", "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(file, "Vector Size,Iteration,Assembly Time (s), C Time (s)\n");

    for (int i = 0; i < testRun; ++i) {
        if (i == 0) {
            fprintf(file, "%d,", size);
        }
        else {
            fprintf(file, ",");
        }
        fprintf(file, "%d,%f,%f\n", i + 1, asmTime[i], cTime[i]);
    }

    double asmAverage = getAverage(asmTime, testRun);
    double cAverage = getAverage(cTime, testRun);
    fprintf(file, "\n, , Average Time (s): %f, Average Time (s): %f\n", asmAverage, cAverage);

    fclose(file);
}