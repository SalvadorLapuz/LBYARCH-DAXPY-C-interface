#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// A->xmm0, X -> RDX, Y -> R8, Z -> R9
extern void daxpyAsm(double A, double* X, double* Y, double* Z);
void generateCsv(const double asmTime[], const double cTime[], int testRun, int size);
double getAverage(double* times, int size);
int sanityCheck(double* Z_asm, double* Z_c, int size);
void userPrompt(int* sizeOfVector);


void daxpyC(double A, double* X2, double* Y2, double* Z2, int n) {
    for (int i = 0; i < n; i++) {
        Z2[i] = A * X2[i] + Y2[i];
    }
}

int main() {
    double asmTime[30];
    double cTime[30];

    clock_t start;
    clock_t end;

    int testRun = 30;

    int check;

    srand(time(NULL));

    double A=0;
    int sizeOfVector=0;
    userPrompt(&sizeOfVector, &A);
    sizeOfVector = pow(2, sizeOfVector);

    double* X = malloc(sizeOfVector * sizeof(double));
    double* X2 = malloc(sizeOfVector * sizeof(double));

    double* Y = malloc(sizeOfVector * sizeof(double));
    double* Y2 = malloc(sizeOfVector * sizeof(double));

    double* Z = malloc(sizeOfVector * sizeof(double));
    double* Z2 = malloc(sizeOfVector * sizeof(double));

    if (X == NULL || Y == NULL) {
        printf("Memory not allocated!\n");
        free(X);
        free(Y);
        exit(0);
    }
    else {
        printf("Memory allocated successfully!\n");
    }

    for (int i = 0; i < sizeOfVector; i++) {
        X[i] = rand();
        Y[i] = rand();
    }

    for (int j = 0; j < sizeOfVector; j++) {
        X2[j] = X[j];
        Y2[j] = Y[j];
    }

    printf("Executing C and ASM Functions...\nPrinting first 10 elements for checking...\n\n");
    daxpyAsm(A, X, Y, Z);
    daxpyC(A, X2, Y2, Z2, sizeOfVector);

    check = sanityCheck(Z, Z2, sizeOfVector);

    if (check==0) {
        printf("Return values from ASM and C functions don't match!\n");
        exit(0);
    }
    else if(check==1) {
        printf("Passed sanity check!\n\nExecuting test...\n");
    }

    printf("Running ASM Implementation 30 times...\n");
    for (int i = 0; i < testRun; i++) {
        start = clock();
        daxpyAsm(A, X, Y, Z);
        end = clock();
        asmTime[i] = (double)(end - start) / CLOCKS_PER_SEC;
    }

    printf("Running C Implementation 30 times...\n");
    for (int i = 0; i < testRun; i++) {
        start = clock();
        daxpyC(A, X2, Y2, Z2, sizeOfVector);
        end = clock();
        cTime[i] = (double)(end - start) / CLOCKS_PER_SEC;
    }

    printf("Saving results to CSV file...\n");
    generateCsv(asmTime, cTime, testRun, sizeOfVector);

    return 0;
}


void userPrompt(int* sizeOfVector, double* A) {
    int good;
    do {
        printf("Input size of vector: ");
        scanf_s("%d", &good);
        if (good < 0) {
            printf("Invalid size! Please retry.\n");
        }
    } while (good < 0);
    *sizeOfVector = good;
    printf("Input A: ");
    scanf_s("%lf", &A);
}

int sanityCheck(double* Z, double* Z2, int size) {
    for (int i = 0; i < size; i++) {
        if (Z[i] != Z2[i]) {
            printf("index = %d", i);
            printf("z = %f\n", Z[i]);
            printf("z2 = %f\n", Z2[i]);
            return 0;
        }
        if (i < 10) {
            printf("x86-64 implementation Y[%d]: %.1f\n", i, Z[i]);
            printf("C Implementation Y[%d]:      %.1f\n", i, Z2[i]);
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

    for (int i = 0; i < testRun; i++) {
        if (i == 0) {
            fprintf(file, "%d,", size);
        }
        else {
            fprintf(file, ",");
        }
        printf("asm: %f\n c: %f\n\n", asmTime[i], cTime[1]);
        fprintf(file, "%d,%f,%f\n", i + 1, asmTime[i], cTime[i]);
    }

    double asmAverage = getAverage(asmTime, testRun);
    double cAverage = getAverage(cTime, testRun);
    fprintf(file, "\n, , Average Time (s): %f, Average Time (s): %f\n", asmAverage, cAverage);

    fclose(file);
}