#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#define EXP_SZ 11
#define FRAC_SZ 52

int main(int argc, char *argv[]) {

    // SETUP

    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return 0;
    }

    // first, read the number
    double value;
    fscanf(fp, "%lf", &value);
    if (value == 0.0) {
        if (1 / value > 0) { // +infinity which implies 0.0
            printf("0_00000000000_0000000000000000000000000000000000000000000000000000");
            exit(0);
        } else { // -infinity which implies -0.0
            printf("1_00000000000_0000000000000000000000000000000000000000000000000000");
            exit(0);
        }
    }
    // the reference solution ('the easy way')
    // you are not allowed to print from this casted 'ref_bits' variable below
    // but, it is helpful for validating your solution
    unsigned long int ref_bits = *(unsigned long int*) &value;

    // THE SIGN BIT
    bool sign = value<0.0;
    printf("%d_",sign);
    assert (sign == (1&ref_bits>>(EXP_SZ+FRAC_SZ))); // validate your result against the reference

    // THE EXP FIELD
    // find the exponent E such that the fraction will be a canonical fraction:
    // 1.0 <= fraction < 2.0
    double fraction = sign ? -value : value;

    signed short trial_exp=(1<<(EXP_SZ-1))-1; // start by assuming largest possible exp (before infinity)
    // do trial division until the proper exponent E is found
    for (int i = trial_exp; i >= -trial_exp; i--) {
        fraction = abs(value / (pow(2, i)));
        if (fraction >= 1.0 && fraction < 2) {
            trial_exp = i;
            break;
        }
    }
    unsigned short bias = (1<<(EXP_SZ-1))-1; //1023
    signed short exp = trial_exp + bias;

    for ( int exp_index=EXP_SZ-1; 0<=exp_index; exp_index-- ) {
        bool exp_bit = 1&exp>>exp_index;
        printf("%d",exp_bit);
        // assert (exp_bit == (1&ref_bits>>(exp_index+FRAC_SZ))); // validate your result against the reference
    }
    printf("_");
    // you get partial credit by getting the exp field correct
    // even if you print zeros for the frac field next
    // you should be able to pass test cases 0, 1, 2, 3

    // THE FRAC FIELD
    // prepare the canonical fraction such that:
    // 1.0 <= fraction < 2.0
    fraction = sign ? -value : value;
    while (fraction < 1) {
        fraction *=2;
    }
    while (fraction >= 2) {
        fraction /=2;
    }
    fraction -= 1;
    bool frac_array[FRAC_SZ+1]; // one extra LSB bit for rounding
    for ( int frac_index=FRAC_SZ; 0<=frac_index; frac_index-- ) {
        // frac_array[frac_index] = false; // frac set to zero to enable partial credit
        /* ... */
        fraction *=2;
        if (fraction >= 1) {
            frac_array[frac_index] = 1;
            fraction -= 1;
        }
        else {
            frac_array[frac_index] = 0;
        }
    }

    // rounding
    if (frac_array[0] == 1) {
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

}
