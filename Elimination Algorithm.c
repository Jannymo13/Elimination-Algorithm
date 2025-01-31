#include <stdio.h>

// Given an n x k matrix, prints out the matrix into the terminal
// (Not really used since I'm mainly printing Augmented Matrices)
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

// Given an n x k Augmented Matrix, prints it out into the terminal
void printAMatrix(int n, int k, float matrix[n][k]) {
    for (int r = 0; r < n; r++) {

        // Add the brackets before the matrix
        if (r == 0) {
            printf("⎡ ");
        } else if (r == n - 1) {
            printf("⎣ ");
        } else {
            printf("⎢ ");
        }

        for (int c = 0; c < k; c++) {

            // Print the bar for the last column
            if (c == k - 1) {
                printf("⎥ %3g ", matrix[r][c]);
            } else {
                printf("%3g  ", matrix[r][c]);
            }
        }

        // Add brackets after Matrix
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

// Performs the add operation, scales row2 and adds it to row 1.
void addRows(int n, int k, float matrix[n][k], int row1, int row2,
             float scale) {
 
    //Don't allow adding a row to itself
    if (row1 == row2)
        return;

    for (int c = 0; c < k; c++) {
        matrix[row1][c] += scale * matrix[row2][c];
    }
}

// Scales a row by the scale factor
void scaleRow(int n, int k, float matrix[n][k], int row, float scale) {

    //Don't scale by 0
    if (scale == 0)
        return;

    for (int c = 0; c < k; c++) {
        matrix[row][c] *= scale;
    }
}

// Swap the values in two rows
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

// Returns the index of the first row at or below startRow that has a nonZero entry. 
// Also sets the value at targetColumn to the column that non-zero value is
// Returns -1 if no non-zero rows were found
int findNonZeroRow(int n, int k, float matrix[n][k], int startRow, int *targetColumn) {
    int row = -1;
    int column = k + 1;

    for (int r = startRow; r < n; r++) {
        for (int c = 0; c < k; c++) {

            if (matrix[r][c] != 0) {
                if (c < column) {
                    row = r;
                    column = c;
                }
            }
        }
    }
    *(targetColumn) = column;
    return row;
}

// Given the row "i" and column "j" of a row with a leading term of 1,
// sets the value of all other entries in the same column to zero using 
// row operations.
void zeroColumn(int n, int k, float matrix[n][k], int i, int j) {
    float scale;
    for (int r = 0; r < n; r++) {
        scale = matrix[r][j];
        addRows(n, k, matrix, r, i, -scale);
    }
}

// Performs the elimination algorithm
void eliminate(int n, int k, float matrix[n][k]) {
    int leadRow;
    int j;

    //loop through each row
    for (int i = 0; i < n; i++) {

        // find the row with a non-zero entry
        leadRow = findNonZeroRow(n, k, matrix, i, &j);
        if (leadRow == -1) //end algorithm if remaining rows are 0
            return;

        //scale the row so that the leading term is 1
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

    //populate matrix with input
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
