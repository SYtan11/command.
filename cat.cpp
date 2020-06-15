#include <sys/types.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 2048

static void concatenate(const char *path)
{
    uint8_t buf[BUF_SIZE];
    ssize_t nread;
    int fd = STDIN_FILENO;

    fd = open(path, O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "cannnot open %s: %s\n", path, strerror(errno));
        exit(1);
    }

    while (1)
    {
        nread = read(fd, buf, sizeof(buf));
        if (nread < 0)
        {
            fprintf(stderr, "cannnot read %s: %s\n", path, strerror(errno));
            exit(1);
        }
        if (nread == 0)
            break;
        if ((write(STDOUT_FILENO, buf, nread) < 0))
        {
            fprintf(stderr, "cannnot write %s: %s\n", path, strerror(errno));
            exit(1);
        }
    }
    if (close(fd) < 0)
    {
        fprintf(stderr, "cannnot close %s: %s\n", path, strerror(errno));
        exit(1);
    }
}
int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "%s: file name not given\n", argv[0]);
        exit(1);
    }
    for (int i = 1; i < argc; i++)
    {
        concatenate(argv[i]);
    }
    exit(0);
}
