#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Selection sort based approach to sorting jobs

int main(int argc, char* argv[]) {

    // First peek at how many jobs and timeslots there are
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        exit(EXIT_FAILURE);
    }

    char buf[256];

    // Read the number of jobs to be scheduled
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of jobs failed");
        exit(EXIT_FAILURE);
    }
    int jobcount = atoi(buf);

    // Next read the maximum number of timeslots
    if (!fscanf(fp, "%s\n", buf)) {
        perror("reading the number of timeslots failed");
        exit(EXIT_FAILURE);
    }
    int timeslots = atoi(buf);
    int last_end = 0;
    // We've read the number of timeslots so close the file and start over
    fclose(fp);
    char last_job = 0;
    
    for (unsigned int slot=0; slot<timeslots; slot++) {
        int last_start = timeslots;

        FILE* fp = fopen(argv[1], "r");
        if (!fp) {
            perror("fopen failed");
            exit(EXIT_FAILURE);
        }

        char buf[256];

        // First read the number of jobs to be scheduled
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of jobs failed");
            exit(EXIT_FAILURE);
        }

        // Next read the maximum number of timeslots
        if (!fscanf(fp, "%s\n", buf)) {
            perror("reading the number of timeslots failed");
            exit(EXIT_FAILURE);
        }

        // Now read the rest of the file
        for ( int line = 0; line < jobcount; line++ ) {

            if (!fgets(buf, 256, fp)) {
                perror("reading a line for a job failed");
                exit(EXIT_FAILURE);
            }

            char job;
            unsigned int start;
            unsigned int end;
            if (!sscanf(buf, "%c %d %d", &job, &start, &end)) {
                perror("parsing a line for a job failed");
                exit(EXIT_FAILURE);
            }

            if (slot != 0 && start > last_end && end == slot) {
                if (start <= last_start) {
                    last_job = job;
                    last_start = start;
                }
            }
            if (slot != 0 && line  == jobcount - 1 && last_job != 0) {
                printf("%c\n", last_job);
                last_end = slot;
            }
            
        }
        
        last_job = 0;

        fclose(fp);

    }
    exit(EXIT_SUCCESS);
}
