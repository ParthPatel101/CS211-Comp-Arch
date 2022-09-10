#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 8
#define FRAC_SZ 23

int main(int argc, char *argv[]) {

    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    // SETUP

    char buff;

    bool multiplier[EXP_SZ + FRAC_SZ + 1];
    // first, read the binary number representation of multiplier
    /* ... */
    for (int i=EXP_SZ + FRAC_SZ; 0<=i; i--) {
        fscanf(fp, "%c", &buff);

        multiplier[i] = (buff == '1');
    }
    // notice that you are reading two different lines; caution with reading
    /* ... */
    fscanf(fp, "%c", &buff);

    bool multiplicand[EXP_SZ + FRAC_SZ  + 1];
    // first, read the binary number representation of multiplcand
    /* ... */
    for (int i=EXP_SZ + FRAC_SZ; 0<=i; i--) { // read MSB first as that is what comes first in the file
        fscanf(fp, "%c", &buff);

        multiplicand[i] = (buff == '1');
    }


    // float product = *(float *) &multiplier * *(float *) &multiplicand; // you are not allowed to print from this.
    // unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.

    // SIGN
    /* ... */
    if (multiplicand[31] && multiplier[31]) {
        bool sign = 0;
        printf("%d_",sign);
    }
    else if (multiplicand[31] | multiplier[31]) {
        bool sign = 1;
        printf("%d_",sign);
    }
    else {
        bool sign = 0;
        printf("%d_",sign);
    }
    
    // assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ )));

    // EXP
    // get the exp field of the multiplier and multiplicand
    /* ... */
    int multiplier_exp = 0;
    for (int i = 30; i > 22; i--) {
        if (multiplier[i]) {
            multiplier_exp += pow(2, abs(i - 23));
        }
    }

    int multiplicand_exp = 0;
    for (int i = 30; i > 22; i--) {
        if (multiplicand[i]) {
            multiplicand_exp += pow(2, abs(i - 23));
        }
    }
    // add the two exp together
    /* ... */
    int exp = multiplicand_exp + multiplier_exp;
    // subtract bias
    /* ... */
    exp -= 127;

    // FRAC
    // get the frac field of the multiplier and multiplicand
    /* ... */
    double multiplier_frac = 0;
    for (int i = 22; i >= 0; i--) {
        if (multiplier[i] == 1) {
            multiplier_frac += 1/(pow(2, 23 - i));
        }
    }

    double multiplicand_frac = 0;
    for (int i = 22; i >= 0; i--) {
        if (multiplicand[i] == 1) {
            multiplicand_frac += 1/(pow(2, 23 - i));
        }
    }
    
    // assuming that the input numbers are normalized floating point numbers, add back the implied leading 1 in the mantissa
    /* ... */
    multiplier_frac += 1;
    multiplicand_frac += 1;
    // multiply the mantissas
    /* ... */
    double frac;
    frac = multiplier_frac * multiplicand_frac;
    // overflow and normalize
    /* ... */
    while (frac >= 2) {
        frac /= 2;
        exp += 1;
    }
    // rounding
    /* ... */
    
    // move decimal point
    /* ... */
    frac -= 1;
    // PRINTING
    // print exp
    for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&exp>>bit_index;
        printf("%d",trial_bit);
        // assert (trial_bit == (1&ref_bits>>(bit_index+FRAC_SZ)));
    }
    printf("_");

    // // print frac
    // for ( int bit_index=FRAC_SZ-1; 0<=bit_index; bit_index-- ) {
    //     bool trial_bit = 1&frac>>bit_index;
    //     printf("%d",trial_bit);
    //     // assert (trial_bit == (1&ref_bits>>(bit_index)));
    // }
    bool frac_array[FRAC_SZ+1]; // one extra LSB bit for rounding
    for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {
        // frac_array[frac_index] = false; // frac set to zero to enable partial credit
        /* ... */
        frac *=2;
        if (frac >= 1) {
            frac_array[frac_index] = 1;
            frac -= 1;
        }
        else {
            frac_array[frac_index] = 0;
        }
    }

    if (frac_array[0] == true) {
        bool carry = true; // to implement the 'add one' logic, we do binary addition logic with carry set to true at the beginning
        for (int i=0; i<FRAC_SZ; i++) { // iterate from LSB to MSB
            if (frac_array[i] == 0 && carry) {
                    frac_array[i] = 1;
                    carry = false;
            }
            else {
                if (carry) {
                    frac_array[i] = 0;
                    carry = true;
                }
            }

        }
    }
    for ( int frac_index=FRAC_SZ-1; 0<=frac_index; frac_index-- ) {
        bool frac_bit = frac_array[frac_index+1]; // skipping the extra LSB bit for rounding
        printf("%d", frac_bit);
        // assert (frac_bit == (1&ref_bits>>frac_index)); // validate your result against the reference
    }
    return(EXIT_SUCCESS);

}
