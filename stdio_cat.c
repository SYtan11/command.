#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        FILE *fp;
        int c;

        fp = fopen(argv[i], "r");

        if (!fp)
        {
            perror(argv[i]);
            exit(1);
        }

        while ((c = fgetc(fp)) != EOF)
        {
            if (putchar(c) < 0)
                exit(1);
        }
        
        fclose(fp);
    }
    exit(0);
}