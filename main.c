#include <stdio.h>

void read_matrix_from_file(char filename[], int rows, int columns, int matrix[rows][columns]) {
    int elem;
    int count = 0;
    FILE *file_matrix;
    file_matrix = fopen(filename, "r");
    while (!feof(file_matrix)) {
        fscanf(file_matrix, "%d", &elem);
        matrix[count / columns][count % columns] = elem;
        count++;
    }
}

void transpose_matrix(int rows, int columns, int original[rows][columns], int transposed[columns][rows]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            transposed[j][i] = original[i][j];
        }
    }
}

void matrix_product(int rowsA, int columnsA, int rowsB, int columnsB, int A[rowsA][columnsA], int B[rowsB][columnsB],
                    int res[rowsA][columnsB]) {
    if (rowsB == columnsA) { //Check if the operation can be done
        for (int i = 0; i < columnsB; i++){
            for (int j = 0; j< rowsA; j++){
                res[j][i] = 0;
                for (int k = 0; k < columnsA; k++){
                    res[j][i] += A[j][k] * B[k][i];
                }
            }
        }
    }
}

void opposite_matrix(int rows, int columns, int matrix[rows][columns], int res[rows][columns]){
    for (int i = 0; i < rows; i++){
        for (int j = 0; i < columns; j++){
            res[i][j] = - matrix[i][j];
        }
    }
}

//Check if matrix is equal

void print_matrix(int rows, int columns, int matrix[rows][columns]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc == 3) {
        int a_matrix[10][3];
        int b_matrix[3][15];
        int at_matrix[3][10];
        int bt_matrix[15][3];
        int ab_matrix[10][15];
        int abt_matrix[15][10];
        int atbt_matrix[15][10];
        read_matrix_from_file(argv[1], 10, 3, a_matrix);
        read_matrix_from_file(argv[2], 3, 15, b_matrix);
        transpose_matrix(10, 3, a_matrix, at_matrix);
        transpose_matrix(3, 15, b_matrix, bt_matrix);
        matrix_product(10, 3, 3, 15, a_matrix, b_matrix, ab_matrix);
        transpose_matrix(10, 15, ab_matrix, abt_matrix);
        printf("Matrix A:\n");
        print_matrix(10, 3, a_matrix);
        printf("Matrix B:\n");
        print_matrix(3, 15, b_matrix);
        printf("Matrix A transposed:\n");
        print_matrix(3, 10, at_matrix);
        printf("Matrix B transposed:\n");
        print_matrix(15, 3, bt_matrix);
    } else {
        printf("Incorrect Number of parameters");
    }
}
