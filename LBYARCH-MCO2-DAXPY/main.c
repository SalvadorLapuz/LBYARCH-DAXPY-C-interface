#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// A->xmm0, X -> RDX, Y -> R8, Z -> R9
extern void daxpyAsm(double A, double* X, double* Y, double* Z);

void daxpyC(double A, double* X2, double* Y2, double* Z2, int n) {
    for (int i = 0; i < n; i++) {
        Z2[i] = A * X2[i] + Y2[i];
    }
}

int main() {
    int n = 10;
    double A = 2.0;
    double X[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    double Y[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0 };
    double Z[10];

    double X2[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0 };
    double Y2[] = { 11.0, 12.0, 13.0, 14.0, 15.0, 16.0, 17.0, 18.0, 19.0, 20.0 };
    double Z2[10];

    daxpyAsm(A, X, Y, Z);

    printf("Using assembly:\n");
    for (int i = 0; i < n; i++) {
        printf("Z[%d] = %.1f\n", i, Z[i]);
    }

    daxpyC(A, X2, Y2, Z2, n);

    printf("Using C:\n");
    for (int i = 0; i < n; i++) {
        printf("Z[%d] = %.1f\n", i, Z2[i]);
    }

    return 0;
}
