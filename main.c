#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define SIZE 10
int main(int argc, char **argv) {
    int c;
    int fd1 = -1;
    int fd2 = -1;
    while ((c = getopt(argc, argv, "f:g:")) != -1) {
        switch (c) {
            case 'f':
                fd1 = open(optarg, O_RDONLY);
                if (fd1 == -1){
                    perror("Error opening file for reading");
                    exit(EXIT_FAILURE);
                }
                printf("File '%s' opened for reading\n", optarg);
                break;
            case 'g':
                fd2 = open(optarg, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
                if (fd2 == -1){
                    perror("Error opening file for ariting");
                    exit(EXIT_FAILURE);
                }
                printf("File '%s' opened for ariting\n", optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -f <input_file> -g <output_file>\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    if (fd1 == -1 || fd2 == -1) {
        fprintf(stderr, "Both input and output files must be specified.\n");
        exit(EXIT_FAILURE);
    }
    char buf[SIZE];
    int n;
    while ((n = read(fd1, buf, SIZE))>0){
        int n2 = write(fd2, buf, n);
        if (n2<0) {
            perror ("Error writing to output file");
            break;
        }
    }
    if(n < 0){
        perror("Error reading from from input file");
    }
    close(fd1);
    close(fd2);
    return 0;
}