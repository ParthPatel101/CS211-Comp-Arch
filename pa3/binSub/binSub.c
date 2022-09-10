#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    // first, read the minuend (number to be subtracted from)
    char buff;
    bool minuend[8];
    // suggested that you store bits as array of bools; minuend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);

        minuend[i] = (buff == '1');
    }
    // notice that you are reading two different lines; caution with reading
    fscanf(fp, "%c", &buff);
    
    // second, read the subtrahend (number to subtract)
    bool subtrahend[8] = {}; // suggested that you store bits as array of bools; subtrahend[0] is the LSB
    for (int i=7; 0<=i; i--) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);
        subtrahend[i] = (buff == '1');
    }

    // WE WILL DO SUBTRACTION BY NEGATING THE SUBTRAHEND AND ADD THAT TO THE MINUEND

    // Negate the subtrahend
    // flip all bits
    for (int i = 7; 0 <= i; i--) {
        if (subtrahend[i]) {
            subtrahend[i] = 0;
        }
        else {
            subtrahend[i] = 1;
        }
    }

    // add one
    bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
    for (int i=0; i<8; i++) { // iterate from LSB to MSB
        if (subtrahend[i] == 0 && carry) {
                subtrahend[i] = 1;
                carry = false;
        }
        else {
            if (carry) {
                subtrahend[i] = 0;
                carry = true;
            }
        }

    }

    // Add the minuend and the negated subtrahend
    bool difference[8] = {};
    carry = false;
    for (int i=0; i<8; i++) {
        if (subtrahend[i] && minuend[i]) {
            if (carry) {
                carry = true;
                difference[i] = 1;
            }
            else {
                carry = true;
                difference[i] = 0;
            }
        }
        else if (subtrahend[i] || minuend[i]) {
            if (carry) {
                carry = true;
                difference[i] = 0;
            }
            else {
                carry = false;
                difference[i] = 1;
            }
        }
        else {
            if (carry) {
                carry = false;
                 difference[i] = 1;
            }
            else {
                carry = false;
                difference[i] = 0;
            }
        }
    }

    // print the difference bit string
    for (int i=7; 0<=i; i--) {
        printf("%d",difference[i]);
    }
    printf("\n");
    return EXIT_SUCCESS;

}
