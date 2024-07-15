#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    int i, j;
    int count;
    char cur;
    FILE *fp;
    char buffer[1025];

    for (i = 1; i < argc; i++)
    {
        const char *fileName = argv[i];
        fp = fopen(fileName, "r");
        if (fp == NULL)
        {
            printf("wzip: cannot open file\n");
            exit(1);
        }

        while (fgets(buffer, 1024, fp) != NULL)
        {
            j = 0;
            while (j < 1024 && buffer[j] != '\n' && buffer[j] != '\0')
            {
                cur = buffer[j];
                count = 1;
                while(buffer[j+1] == buffer[j]){
                    count++;
                    j++;
                }
                // fwrite(&count, sizeof(int), 1, stdout);
                // fwrite(&cur, sizeof(char), 1, stdout);
                printf("%d %c", count, cur);
                j++;
            }
            // if (j != 0 && buffer[j] == '\n')
            // {
            //     printf("\n");
            // }
        }

        fclose(fp);
    }
    
    return 0;
}
