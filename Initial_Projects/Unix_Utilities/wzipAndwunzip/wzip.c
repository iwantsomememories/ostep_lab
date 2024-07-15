#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    int i;
    int count = 0;
    FILE *fp;
    char prev[2] = "";
    char cur[2] = "";

    for (i = 1; i < argc; i++)
    {
        const char *fileName = argv[i];
        fp = fopen(fileName, "r");
        if (fp == NULL)
        {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while (fread(cur, 1, 1, fp))
        {
            if(strcmp(cur, prev) == 0)
                count++;
            else {
                if (prev[0] != '\0')
                {
                    fwrite(&count, sizeof(int), 1, stdout);
                    fwrite(prev, sizeof(char), 1, stdout);
                }
                count = 1;
                strcpy(prev, cur);
            }
        }
        fclose(fp);
    }

    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(prev, sizeof(char), 1, stdout);
    return 0;
}
