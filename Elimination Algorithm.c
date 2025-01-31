#include <stdio.h>

void printMatrix(int n, int k, float matrix[n][k]) {
    for (int r = 0; r < n; r++) {

        if (r == 0) {
            printf("⎡ ");
        } else if (r == n - 1) {
            printf("⎣ ");
        } else {
            printf("⎢ ");
        }

        for (int c = 0; c < k; c++) {
            if (c == k - 1) {
                printf("%2g ", matrix[r][c]);
            } else {
                printf("%2g   ", matrix[r][c]);
            }
        }

        if (r == 0) {
            printf("⎤");
        } else if (r == n - 1) {
            printf("⎦");
        } else {
            printf("⎥");
        }

        printf("\n");
    }
}

void printAMatrix(int n, int k, float matrix[n][k]) {
    for (int r = 0; r < n; r++) {

        if (r == 0) {
            printf("⎡ ");
        } else if (r == n - 1) {
            printf("⎣ ");
        } else {
            printf("⎢ ");
        }

        for (int c = 0; c < k; c++) {
            if (c == k - 1) {
                printf("| %3g ", matrix[r][c]);
            } else {
                printf("%3g  ", matrix[r][c]);
            }
        }

        if (r == 0) {
            printf("⎤");
        } else if (r == n - 1) {
            printf("⎦");
        } else {
            printf("⎥");
        }

        printf("\n");
    }
}

void addRows(int n, int k, float matrix[n][k], int row1, int row2,
             float scale) {
    if (row1 == row2)
        return;

    for (int c = 0; c < k; c++) {
        matrix[row1][c] += scale * matrix[row2][c];
    }
}

void scaleRow(int n, int k, float matrix[n][k], int row, float scale) {
    if (scale == 0)
        return;

    for (int c = 0; c < k; c++) {
        matrix[row][c] *= scale;
    }
}

void swapRows(int n, int k, float matrix[n][k], int row1, int row2) {
    float temp;
    if (row1 == row2)
        return;
    for (int c = 0; c < k; c++) {
        temp = matrix[row1][c];
        matrix[row1][c] = matrix[row2][c];
        matrix[row2][c] = temp;
    }
}

int findNonZeroRow(int n, int k, float matrix[n][k], int i, int *j) {
    int row = -1;
    int column = k + 1;

    for (int r = i; r < n; r++) {
        for (int c = 0; c < k; c++) {
            if (matrix[r][c] != 0) {
                if (c < column) {
                    row = r;
                    column = c;
                }
            }
        }
    }
    *(j) = column;
    return row;
}

void zeroColumn(int n, int k, float matrix[n][k], int i, int j) {
    float scale;
    for (int r = 0; r < n; r++) {
        scale = matrix[r][j];
        addRows(n, k, matrix, r, i, -scale);
    }
}

void eliminate(int n, int k, float matrix[n][k]) {
    int leadRow;
    int j;

    for (int i = 0; i < n; i++) {

        leadRow = findNonZeroRow(n, k, matrix, i, &j);
        if (leadRow == -1)
            return;

        scaleRow(n, k, matrix, leadRow, ((double)1 / (matrix[leadRow][j])));

        swapRows(n, k, matrix, i, leadRow);

        zeroColumn(n, k, matrix, i, j);
    }
}

int main() {
    int n = 2;
    int k = 3;

    printf("Enter number of equations followed by number of variables:\n");
    scanf("%d %d", &n, &k);
    k++;

    float matrix[n][k];

    for (int r = 0; r < n; r++) {

        printf("Row %d: ", r);

        for (int c = 0; c < k; c++) {
            scanf("%f", &matrix[r][c]);
        }
    }

    printf("\n");

    printAMatrix(n, k, matrix);

    eliminate(n, k, matrix);

    printf("\n");
    printAMatrix(n, k, matrix);
}
