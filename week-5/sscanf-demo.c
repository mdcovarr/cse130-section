#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h> // open
#include <err.h> // warn
#include <stdlib.h>
#include <unistd.h> // close
#include <sys/types.h> // fstat
#include <stdint.h> // uint8_t
#include <string.h> // strstr

#define CONTENT_LENGTH "Content-Length:"

/*!
    \brief Main entrance of open-demo script
    \param argc int value of arguments passed to script
    \param argv vector of C strings
    \return exitstatus of script 0 if successful
*/
int main() {
    uint8_t buffer[4096];
    ssize_t count;

    // file we are attempting to open
    const char* filename = "test-files/PUT_REQUEST";
    // value to hold file discriptor
    int fd = open(filename, O_RDONLY);

    // determine if there was an error opening file
    if (fd == -1) {
        warn("%s", filename);
        exit(EXIT_FAILURE);
    }

    count = read(fd, buffer, 4096);

    if (count < 0) {
        warn("%s", filename);
        exit(EXIT_FAILURE);
    }

    /*
        get char* beginning at the first occurance
        else NULL if no occurance
    */
    char* cl_location = strstr((char*) &buffer, CONTENT_LENGTH);


    if (cl_location) {
        printf("content length begins at: %s\n", cl_location);
    }

    /*
        Now we  might want to get a cetain part of a string
    */
    ssize_t cl_size;

    /*
        scan for an unsigned int value representing number of bytes
    */
    int nscan = sscanf(cl_location, "Content-Length: %zd", &cl_size);

    if (nscan < 1) {
        printf("Invalid Format!\n");
        exit(EXIT_FAILURE);
    }

    printf("Content-Length Value is %zd\n", cl_size);

    close(fd);

    return EXIT_SUCCESS;
}
