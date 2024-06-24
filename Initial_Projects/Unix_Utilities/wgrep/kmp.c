#include <stdio.h>
#include <stdlib.h>

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
            return i;
        }
    }
    
    return -1;
}

int size(const char* str){
    int count = 0;
    while (str[count] != '\0')
    {
        count++;
    }
    return count;
}

int main(int argc, char const *argv[])
{
    const char *pattern = "ababac";
    const char *str = "aabaababacabc";
    int* next_v = next_val(pattern, 6);
    printf("%d\n", kmp_match(str, pattern, next_v));
    free(next_v);
    // printf("%d\n", size(pattern));
    return 0;
}

