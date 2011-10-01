#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BUFFER_SIZE 100

int main(int argc, char *argv[])
{
    if (argc < 2) {
        perror ("Error arguments");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    
    if (file == NULL) {
        perror ("Error opening file");
        return 1;
    }

    int i = 0;

    char line[BUFFER_SIZE];

    printf("# /bin/bash \n");

    while (!feof(file)) {
        if (fgets(line, BUFFER_SIZE, file) == NULL) {
            return 0;
        }
        

        char *begpath = strstr(line, "<link>");
        if (begpath == NULL) {
            continue;
        }
        
        begpath += 6; // strlen("<link>");

        
        char *endpath = strstr(begpath, "</link>");
        if (endpath == NULL) {
            continue;
        }
        
        endpath[0] = '\0';
        
        
        printf("wget %s\n", begpath);
    }
    
    fclose(file);
    
    return 0;
}

