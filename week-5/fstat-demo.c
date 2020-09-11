#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h> // open
#include <err.h> // warn
#include <stdlib.h>
#include <unistd.h> // close
#include <sys/types.h> // fstat

/*!
    \brief Main entrance of open-demo script
    \param argc int value of arguments passed to script
    \param argv vector of C strings
    \return exitstatus of script 0 if successful
*/
int main() {
    struct stat statbuf;
    // file we are attempting to open
    const char* filename = "./test-files/THE_PRINCE";
    // value to hold file discriptor
    int fd = open(filename, O_RDONLY);

    // determine if there was an error opening file
    if (fd == -1) {
        warn("%s", filename);
        exit(EXIT_FAILURE);
    }

    fstat(fd, &statbuf);

    printf("File Size: %ld\n", statbuf.st_size);

    close(fd);

    return EXIT_SUCCESS;
}
