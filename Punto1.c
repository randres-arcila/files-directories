#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

char* formatdate(char* str, time_t val)
{
        strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
        return str;
}


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    struct stat test;
    
    stat(argv[1], &test);
    if(stat(argv[1],&test) < 0)        
    return 1;
    printf("File: %s\n", argv[1]);
    printf("Tamaño del archivo: \t\t%d bytes\n",test.st_size);
    printf("Número de bloques: \t\t%d \n",test.st_blocks);
    printf("Contador de referencias: \t%d\n",test.st_nlink);
    printf("Nodo-i: \t\t%d\n",test.st_ino);
    char date[36];
    printf("Permisos del archivo: \t");
    printf( (S_ISDIR(test.st_mode)) ? "d" : "-");
    printf( (test.st_mode & S_IRUSR) ? "r" : "-");
    printf( (test.st_mode & S_IWUSR) ? "w" : "-");
    printf( (test.st_mode & S_IXUSR) ? "x" : "-");
    printf( (test.st_mode & S_IRGRP) ? "r" : "-");
    printf( (test.st_mode & S_IWGRP) ? "w" : "-");-
    printf( (test.st_mode & S_IXGRP) ? "x" : "-");
    printf( (test.st_mode & S_IROTH) ? "r" : "-");
    printf( (test.st_mode & S_IWOTH) ? "w" : "-");
    printf( (test.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");
    printf("Fecha de ultimo acceso: \t\t%s\n",formatdate(date, test.st_atime));
    printf("Fecha de ultima modificación: \t\t%s\n",formatdate(date, test.st_mtime));
    printf("Fecha de ultimo cambio: \t\t%s\n",formatdate(date, test.st_ctime));    
    return 0;
}