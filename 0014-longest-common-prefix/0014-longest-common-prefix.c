#include <string.h>
#include <stdlib.h>

char* longestCommonPrefix(char** strs, int strsSize){
    char *prefix= malloc(sizeof(char) * 201);
    char tempPrefix = '\0';
    int i = 0, end=0;

    while (!end) {
        if (strs[0][i] != '\0') tempPrefix = strs[0][i];
        else {
            prefix[i] = '\0';
            return prefix;
        }
        for (int j=1; j < strsSize; j++) {
            if (strs[j][i] == '\0' || strs[j][i] != tempPrefix) {
                prefix[i] = '\0';
                return prefix;
            }
        }
        prefix[i] = tempPrefix;
        i++;
    }
    return prefix;
}