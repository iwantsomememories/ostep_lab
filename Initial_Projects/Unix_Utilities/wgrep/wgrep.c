#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE

int* next_val(const char *, int);
int kmp_match(const char *, const char *, const int*);

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char *line = NULL;
    size_t len = 0;
    __ssize_t read;
    const char* pattern = argv[1];
    int pattern_size = 0;
    while(pattern[pattern_size] != '\0') pattern_size++;

    if (pattern_size == 0)
    {
        exit(0);
    }
    int* next_v = next_val(pattern, pattern_size);
    
    if(argc == 2){
        while ((read = getline(&line, &len, stdin)) != -1)
        {
            if(kmp_match(line, pattern, next_v) == 1){
                printf("%s", line);
            }
        }
        free(next_v);
    } else
    {
        int i;
        FILE *fp;

        for ( i = 2; i < argc; i++)
        {
            fp = fopen(argv[i], "r");
            if(fp == NULL){
                printf("wgrep: cannot open file\n");
                free(next_v);
                exit(1);
            }
            while ((read = getline(&line, &len, fp)) != -1)
            {
                if(kmp_match(line, pattern, next_v) == 1)
                {
                    printf("%s", line);
                }
            }
            free(next_v);
        }
        
    }

    free(line);
    
    return 0;
}

int kmp_match(const char *str, const char *pattern, const int* next_v){
    int i = 0, j = 0;

    while (str[i] != '\n')
    {
        if (str[i] == pattern[j])
        {
            i++;
            j++;
        } else {
            if (next_v[j] == -1)
            {
                j = 0;
                i++;
            } else
                j = next_v[j];
        }
        if (pattern[j] == '\0')
        {
            return 1;
        }
    }
    
    return 0;
}

int* next_val(const char *str, int size){
    int* next_arr = (int *) malloc(sizeof(int)*size);
    int i;
    char newChar;
    int cur;

    next_arr[0] = -1;
    for(i = 1; i < size; i++){
        newChar = str[i-1];
        cur = next_arr[i-1];
        while (cur != -1)
        {
            if(newChar == str[cur]){
                break;
            }
            cur = next_arr[cur];
        }
        next_arr[i] = cur+1;  
    }

    for(i = 1; i < size; i++){
        if (str[i] == str[next_arr[i]])
        {
            next_arr[i] = next_arr[next_arr[i]];
        }
    }

    return next_arr;
}


