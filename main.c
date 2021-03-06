#include <stdio.h>

void read_matrix_from_file(char filename[], int rows, int columns, int matrix[rows][columns], FILE *fitxer) {
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

void transpose_matrix(int rows, int columns, int original[rows][columns], int transposed[columns][rows], FILE *fitxer) {
    for (int i = 0; i < rows; i++){
        fprintf(fitxer,"%d %p\n",2,&i); //:)
        for (int j = 0; j < columns; j++) {
            fprintf(fitxer,"%d %p\n",2,&j); //:)
            transposed[j][i] = original[i][j];
            fprintf(fitxer,"%d %p\n",3,&transposed[j][i]); //:)
            fprintf(fitxer,"%d %p\n",2,&original[i][j]); //:)
            fprintf(fitxer,"%d %p\n",3,&j);
        }
        fprintf(fitxer,"%d %p\n",3,&i);
    }
}

void matrix_product(int rowsA, int columnsA, int rowsB, int columnsB, int A[rowsA][columnsA], int B[rowsB][columnsB],
                    int res[rowsA][columnsB], FILE *fitxer) {
    if (rowsB == columnsA) { //Check if the operation can be done
        for (int i = 0; i < columnsB; i++){
            fprintf(fitxer,"%d %p\n",2,&i); //:)
            for (int j = 0; j< rowsA; j++){
                fprintf(fitxer,"%d %p\n",2,&j); //:)
                res[j][i] = 0;
                fprintf(fitxer,"%d %p\n",3, &res[j][i]); //:)

                for (int k = 0; k < columnsA; k++){
                    fprintf(fitxer,"%d %p\n",2,&k); //:)


                    res[j][i] += A[j][k] * B[k][i];
                    fprintf(fitxer,"%d %p\n",2,&A[j][k]); //:)
                    fprintf(fitxer,"%d %p\n",2,&B[k][i]); //:)
                    fprintf(fitxer,"%d %p\n",3,&res[j][i]); //:)


                    fprintf(fitxer,"%d %p\n",3,&k); //:)

                }
                fprintf(fitxer,"%d %p\n",3,&j); //:)

            }
            fprintf(fitxer,"%d %p\n",3,&i); //:)
        }
    }
}

void opposite_matrix(int rows, int columns, int matrix[rows][columns], int res[rows][columns], FILE *fitxer){
    for (int i = 0; i < rows; i++){
        fprintf(fitxer,"%d %p\n",2,&i); //:)
        for (int j = 0; j < columns; j++){
            fprintf(fitxer,"%d %p\n",2,&j); //:)
            res[i][j] = 0 - matrix[i][j];
            fprintf(fitxer,"%d %p\n",2,&matrix[i][j]); //:)
            fprintf(fitxer,"%d %p\n",3,&res[i][j]); //:)

            fprintf(fitxer,"%d %p\n",3,&j); //:)
        }
        fprintf(fitxer,"%d %p\n",3,&i); //:)

    }
}

void check_equals(int rows, int columns, int A[rows][columns], int B[rows][columns], FILE *fitxer){
    int equal = 1;
    for (int i = 0; i < rows; i++){
        fprintf(fitxer,"%d %p\n",2,&i); //:)
        for (int j = 0; j < columns; j++){
            fprintf(fitxer,"%d %p\n",2,&j); //:)
            fprintf(fitxer,"%d %p\n",2,&B[i][j]); //:)
            fprintf(fitxer,"%d %p\n",3,&A[i][j]); //:)
            if (A[i][j] != B[i][j]){
                fprintf(fitxer,"%d %p\n",3,&equal);
                equal = 0;
                break;
            }
            fprintf(fitxer,"%d %p\n",3,&j); //:)
        }
        fprintf(fitxer,"%d %p\n",3,&i); //:)

    }
    fprintf(fitxer,"%d %p\n",2,&equal);
    if (equal == 0){
        printf("No s??n iguals\n");
    } else {
        printf("S??n iguals\n");
    }
}
void print_matrix(int rows, int columns, int matrix[rows][columns], FILE *fitxer) {
    for (int i = 0; i < rows; i++) {
        fprintf(fitxer,"%d %p\n",2,&i); //:)
        for (int j = 0; j < columns; j++) {
            fprintf(fitxer,"%d %p\n",2,&j); //:)
            printf("%i ", matrix[i][j]);

            fprintf(fitxer,"%d %p\n",3,&j); //:)
        }
        printf("\n");
        fprintf(fitxer,"%d %p\n",3,&i); //:)

    }
}

int main(int argc, char *argv[]) {
    FILE *fitxer = fopen("tra??a.txt", "w+");
    if (argc == 3) {
        int a_matrix[10][3];
        int b_matrix[3][15];
        int at_matrix[3][10];
        int bt_matrix[15][3];
        int ab_matrix[10][15];
        int abt_matrix[15][10];
        int btat_matrix[15][10];
        int op_a_matrix[10][3];
        int op_b_matrix[3][15];
        int op_a_op_b_matrix[10][15];
        read_matrix_from_file(argv[1], 10, 3, a_matrix, fitxer);
        read_matrix_from_file(argv[2], 3, 15, b_matrix, fitxer);
        transpose_matrix(10, 3, a_matrix, at_matrix, fitxer);
        transpose_matrix(3, 15, b_matrix, bt_matrix, fitxer);
        matrix_product(10, 3, 3, 15, a_matrix, b_matrix, ab_matrix, fitxer);
        transpose_matrix(10, 15, ab_matrix, abt_matrix, fitxer);
        matrix_product(15, 3, 3, 10, bt_matrix, at_matrix, btat_matrix, fitxer);    // :)
        check_equals(15, 10, abt_matrix, btat_matrix, fitxer); // :)
        opposite_matrix(10, 3, a_matrix, op_a_matrix, fitxer);  // :)
        opposite_matrix(3, 15, b_matrix, op_b_matrix, fitxer);  // :)
        matrix_product(10, 3, 3, 15, op_a_matrix, op_b_matrix, op_a_op_b_matrix, fitxer);    // :)

        printf("Matrix A:\n");
        print_matrix(10, 3, a_matrix, fitxer);
        printf("Matrix B:\n");
        print_matrix(3, 15, b_matrix, fitxer);
        printf("Matrix A transposed:\n");
        print_matrix(3, 10, at_matrix, fitxer);
        printf("Matrix B transposed:\n");
        print_matrix(15, 3, bt_matrix, fitxer);
        printf("Matrix (A * B) transposed:\n"); // :)
        print_matrix(15, 10, abt_matrix, fitxer);   // :)
        printf("Matrix -A:\n"); // :)
        print_matrix(3, 10, op_a_matrix, fitxer);   // :)
        printf("Matrix -B:\n"); // :)
        print_matrix(3, 15, op_b_matrix, fitxer);   // :)
        printf("Matrix -A * Matrix -B:\n"); // :)
        print_matrix(10, 15, op_a_op_b_matrix, fitxer);   // :)

    } else {
        printf("Incorrect Number of parameters");
    }
}