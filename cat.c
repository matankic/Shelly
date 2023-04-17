#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    FILE * f = NULL;
    char c;

    f = fopen(argv[1], "r");
    if (f == NULL)
        exit(1);
   
    while ((c = fgetc(f)) != EOF) {
        putchar(c);
    }
    
    fclose(f);
    return 0;
}
