#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>

int main(int argc, char** argv) {
    int aflag = 0;
    int bflag = 0;
    char* cvalue = NULL;
    int index;
    int c;

    opterr = 0;

    while ((c = getopt(argc, argv, "abc:")) != -1) {
        switch (c) {
            case 'a':
                aflag = 1;
                break;
            case 'b':
                bflag = 1;
                break;
            case 'c':
                cvalue = optarg;
                break;
            case '?':
                if (optopt == 'c') {
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                } else if (isprint (optopt)) {
                    fprintf(stderr, "Unknown option -%c.\n", optopt);
                } else {
                    fprintf(stderr, "Unknown option character \\x%x'.\n", optopt);
                }
            
                return EXIT_FAILURE;
            default:
                abort();
        }
    }

    printf("aflag: %d\nbflag: %d\ncvalue: %s\n", aflag, bflag, cvalue);

    for (index = optind; index < argc; index++) {
        printf("Non-option argument: %s\n", argv[index]);
    }

    return EXIT_SUCCESS;
}
