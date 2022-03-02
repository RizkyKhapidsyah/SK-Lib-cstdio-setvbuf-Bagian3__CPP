#pragma warning(disable:4996)

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <sys/stat.h>

/*
    Source by CPPReference
    Modified For Learn by RK
    I.D.E : VS2019
*/

int main() {
    std::FILE* fp = std::fopen("/tmp/test.txt", "w+");
    if (!fp) {
        std::perror("fopen"); return EXIT_FAILURE;
    }

    struct stat stats;
    if (fstat(fileno(fp), &stats) == -1) { // POSIX only
        std::perror("fstat"); return EXIT_FAILURE;
    }

    std::cout << "BUFSIZ is " << BUFSIZ << ", but optimal block size is " << stats.st_blksize << '\n';
    if (std::setvbuf(fp, nullptr, _IOFBF, stats.st_blksize) != 0) {
        std::perror("setvbuf failed"); // POSIX version sets errno
        return EXIT_FAILURE;
    }

    // read entire file: use truss/strace
    // to observe the read(2) syscalls used
    for (int ch; (ch = std::fgetc(fp)) != EOF; ) {}

    std::fclose(fp);
    return EXIT_SUCCESS;
}