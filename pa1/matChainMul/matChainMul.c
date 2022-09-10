#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

unsigned int cost (unsigned int matrixCount, unsigned int* rowSizes, unsigned int* colSizes);
int** recMult(int*** all,int** matMulProduct, int x, unsigned int matrixCount, unsigned int* rowSizes, unsigned int* colSizes);
void matMul(unsigned int l, unsigned int m, unsigned int n, int** matrix_a, int** matrix_b, int** matMulProduct);

int main(int argc, char* argv[]) {

    unsigned int matrixCount;
    unsigned int* rowSizes;
    unsigned int* colSizes;
    int*** All;
    

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    if (!fscanf(fp, "%d\n", &matrixCount)) {
        perror("reading the number of matrices failed");
        exit(EXIT_FAILURE);
    }
    All = malloc(matrixCount*sizeof(int**));

    rowSizes = malloc( matrixCount*sizeof(int) );
    colSizes = malloc( matrixCount*sizeof(int) );
    
    for (unsigned int matIndex=0; matIndex<matrixCount; matIndex++) {
        unsigned int len, wid;
        if (!fscanf(fp, "%d %d\n", &len, &wid)) {
            perror("reading the dimensions of matrix failed");
            exit(EXIT_FAILURE);
        }
        rowSizes[matIndex] = len;
        colSizes[matIndex] = wid;

        All[matIndex] = malloc(len*sizeof(int*)); //creates array of int* which store the rows
        for (unsigned int i = 0; i < len; i++) {
            All[matIndex][i] = malloc(wid*sizeof(int)); //creates array of int which store the columns
            for ( unsigned int j=0; j< wid; j++ ) {
                int element;
                if (!fscanf(fp, "%d", &element)) {
                    perror("reading the elements of a matrix failed");
                    exit(EXIT_FAILURE);
                }
                All[matIndex][i][j] = element;
            }
            fscanf(fp, "\n"); //DONT KNOW IF THIS NECESSARY OR NOT
        }
    }
    printf("%d\n", cost(matrixCount, rowSizes, colSizes));

    unsigned int l = rowSizes[0];
    unsigned int m = colSizes[0];
    unsigned int n = colSizes[matrixCount - 1];

    int** matMulProduct = malloc(l*sizeof(int*));
    for (int i = 0; i < l; i++) {
        matMulProduct[i] = malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            matMulProduct[i][j] = All[0][i][j];
        }
    }

    int** product = recMult(All, matMulProduct, 0, matrixCount, rowSizes, colSizes);

    //PRINT PRODUCT
    for (int row = 0; row < l; row++) {
        for (int col = 0; col < n; col++) {
            printf("%d ", product[row][col]);
        }
        printf("\n");
    }

    //FREE MATMULPRODUCT
    for (int i = 0; i < l; i++) {
        free(matMulProduct[i]);
    }
    free(matMulProduct);

    //FREE PRODUCT
    for (int i = 0; i < l; i++) {
        free(product[i]);
    }
    free(product);
    
    //FREE ALL
    for (int matrix = 0; matrix < matrixCount; matrix++) {
        for (int r = 0; r < rowSizes[matrix]; r++) {
            free(All[matrix][r]);
        }
        free(All[matrix]);
    }
    free(All);
    free(rowSizes);
    free(colSizes);
    
    fclose(fp);
    exit(EXIT_SUCCESS);
}

unsigned int cost (unsigned int matrixCount, unsigned int* rowSizes, unsigned int* colSizes) {
    if ( matrixCount==1 ) { // Base case.
        return 0; // No multplication to be done.
    } else {

        unsigned int numPossibleSplits = matrixCount-1; // Think: if there are two matrices to multiply, there is one way to split.
        // AB: (A)(B)
        // ABC: (A)(BC) and (AB)(C)
        // ABCD: (A)(BCD), (AB)(CD), (ABC)(D)
        unsigned int costs[numPossibleSplits]; //creates an array for each cost
        for ( unsigned int split=0; split<numPossibleSplits; split++ ) {

            unsigned int l = rowSizes[0];
            assert ( colSizes[split] == rowSizes[split+1] );
            unsigned int m = colSizes[split];
            unsigned int n = colSizes[matrixCount-1];

            costs[split] =
                cost( split+1, rowSizes, colSizes ) + // cost of left subchain
                l * m * n + // cost of multiplying the two chains
                cost( matrixCount-split-1, rowSizes+split+1, colSizes+split+1 ); // cost of right subchain
        }

        unsigned int minCost = costs[0];
        for ( unsigned int split=1; split<numPossibleSplits; split++ ) { //iterates to find the minCost
            if ( costs[split]<minCost ) {
                minCost = costs[split];
            }
        }

        return minCost;
    }
}

int** recMult(int*** all,int** matMulProduct, int x, unsigned int matrixCount, unsigned int* rowSizes, unsigned int* colSizes) {
    if (x == matrixCount - 1) {
        return matMulProduct;
    }
    unsigned int l = rowSizes[0];
    unsigned int m = rowSizes[x+1];
    unsigned int n = colSizes[x+1];

    int** temp = malloc(l*sizeof(int*));
    for (int i = 0; i < l; i++) {
        temp[i] = malloc(n*sizeof(int));
    }

    // temp = matMulProduct;

    matMul(l, m, n, matMulProduct, all[x+1], temp);

    x++;

    int** product = recMult(all, temp, x, matrixCount, rowSizes, colSizes);
    
    if (x < matrixCount - 1) {
        for (unsigned int i = 0; i < l; i++) {
            free(temp[i]);
        }
        free(temp);
    }

    return product;
}

void matMul(unsigned int l, unsigned int m, unsigned int n, int** matrix_a, int** matrix_b, int** matMulProduct) {
    for ( unsigned int i=0; i<l; i++ ) {
        for ( unsigned int k=0; k<n; k++ ) {
            matMulProduct[i][k] = 0;
            for ( unsigned int j=0; j<m; j++ ) {
                matMulProduct[i][k] += matrix_a[i][j] * matrix_b[j][k];
            }
        }
    }
}