#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <getopt.h>

static void do_head(FILE *fp, uint64_t nlines);

#define DEFAULT_N_LINES 10

static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}};
static void do_head(FILE *fp, uint64_t nlines)
{
    int c;
    if (nlines <= 0)
        return;
    while ((c = getc(fp)) != EOF)
    {
        if (putchar(c) < 0)
            exit(1);
        if (c == '\n')
        {
            nlines--;
            if (nlines == 0)
                return;
        }
    }
}
int main(int argc, char **argv)
{
    int opt;
    uint64_t nlines;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s n [file file...]\n", argv[0]);
        exit(1);
    }

    while ((opt = getopt_long(argc, argv, "n:", longopts, NULL)) != -1)
    {
        switch (opt)
        {
        case 'n':
            nlines = atol(optarg);
            break;
        case 'h':
            fprintf(stdout, "Usage: %s [-n LINES] [FILE...]\n", argv[0]);
            exit(0);
        case '?':
            fprintf(stdout, "Usage: %s [-n LINES] [FILE...]\n", argv[0]);
            exit(1);
        }
    }

    if (optind == argc)
    {
        do_head(stdin, nlines);
    }
    else
    {
        for (int i = 2; i < argc; i++)
        {
            FILE *fp;
            fp = fopen(argv[i], "r");
            if (!fp) //fp==NULL
            {
                perror(argv[i]);
                exit(1);
            }
            do_head(fp, nlines);
            fclose(fp);
        }
    }

    exit(0);
}
