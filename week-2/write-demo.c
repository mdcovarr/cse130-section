#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h> // open
#include <err.h> // warn
#include <stdlib.h>
#include <unistd.h> // for close
#include <string.h> // strlen

/*!
    \brief Main entrance of open-demo script
    \param argc int value of arguments passed to script
    \param argv vector of C strings 
    \return exitstatus of script 0 if successful
*/
int main(int argc, char** argv) {
    // file we want to write to
    const char* filename = "./write-file.txt";
    // open file with writing permissions only
    int fd = open(filename, O_WRONLY);
    ssize_t nbytes;
    char* buffer = "Hello World\n";
    size_t len = strlen(buffer);

    // determine if there was an error opening file
    if (fd == -1) {
        warn("%s", filename);
        exit(EXIT_FAILURE);
    }

    nbytes = write(fd, buffer, len);

    // detemine if there was an error writing to file
    if (nbytes == -1) {
        warn("%s", filename);
        exit(EXIT_FAILURE);
    }

    close(fd);

    return EXIT_SUCCESS;
}

