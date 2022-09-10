#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    signed int input;
    fscanf(fp, "%d", &input);
    char fourbits[5];
    long int counter = 0;
    char x;
    // print bits; you will see this kind of for loop often in this assignment
    for ( int bit=sizeof(signed int)*4-1; 0<=bit; bit-- ) {
        size_t bit_val = ((1<<1)-1) & input>>bit*1; // shift and mask
        char character = bit_val ? '1' : '0';
        fourbits[counter] = character;
        counter = counter + 1;
        if (counter == 4) {
            x = strtol(fourbits, NULL, 2);
            printf("%X", x);
            counter = 0;
        }
    }
    printf("\n");

    return EXIT_SUCCESS;

}
