#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

extern int errno;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        exit(0);
    }

    int i;
    FILE *fp;
    char buffer[1025];

    for(i = 1; i < argc; i++){
        const char* file_name = argv[i];
        fp = fopen(file_name, "r");
        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        while (fgets(buffer, 1024, fp) != NULL)
        {
            printf("%s", buffer);
        }
        
        fclose(fp);
    }
    
    return 0;
}
