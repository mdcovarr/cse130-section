#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h> // open
#include <err.h> // warn
#include <stdlib.h>
#include <unistd.h> // for close

/*!
    \brief Main entrance of open-demo script
    \param argc int value of arguments passed to script
    \param argv vector of C strings 
    \return exitstatus of script 0 if successful
*/
int main(int argc, char** argv) {
    const char* filename = "./text-file.txt";
    int fd = open(filename, O_RDONLY);

    // arbitrary  buffer length
    int MAX_LEN = 500;
    // keey track of how many bytes were read in
    ssize_t count;
    // our buffer
    unsigned char buffer[MAX_LEN];

    // determine if there was an error opening file
    if (fd == -1) {
        warn("%s", filename);
        exit(EXIT_FAILURE);
    }

    count = read(fd, buffer, MAX_LEN);

    // determine if there was an error reading from file
    if (count == -1) {
        warn("%s", filename);
        exit(EXIT_FAILURE);
    }

    // print contents from file (NOTE: you will not use printf for your assignment)
    printf("%s\n", buffer);

    close(fd);

    return EXIT_SUCCESS;
}

