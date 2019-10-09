#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#define _POSIX_SOURCE
#include <unistd.h>
#undef _POSIX_SOURCE
#include <time.h>

char* formatdate(char* str, time_t val)
{
        strftime(str, 36, "%d.%m.%Y %H:%M:%S", localtime(&val));
        return str;
}

int main(int argc, char *argv[])
{
    
    if (argc == 1)
    {
        DIR *carpeta = opendir(".");
        struct dirent *nombre;
        if (carpeta == NULL)
        {
            printf("No se pudo abrir la carpeta");
        }
        while ((nombre = readdir(carpeta)) != NULL)
        {
            printf("%s\n", nombre->d_name);
        }
        closedir(carpeta);
    }
    
    if (argc == 2 && strcmp(argv[1], "-l") == 0)
    {
        DIR *carpeta = opendir(".");
        struct dirent *nombre;
        if (carpeta == NULL)
        {
            printf("No se pudo abrir la carpeta");
        }
        while ((nombre = readdir(carpeta)) != NULL)
        {
            printf("%s\n", nombre->d_name);
            procesoArchivo(nombre->d_name);
        }
        closedir(carpeta);
    }
    if (argc == 3 && strcmp(argv[1], "-l") == 0)
    {
        char cwd[256];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {

            const size_t tam1 = strlen(cwd);
            const size_t tam2 = strlen(argv[2]);
            char *resultado = malloc(tam1 + tam2 + 1);

            memcpy(resultado, argv[2], tam2 + 1);
                     
            printf("El directorio de trabajo actual es: %s\n", resultado);

            DIR *carpeta = opendir(resultado);
            struct dirent *nombre;
            if (carpeta == NULL)
            {
                printf("No se puede abrir el directorio");
            }
            while ((nombre = readdir(carpeta)) != NULL)
            {
                printf("\n\n");
                procesoArchivo(nombre->d_name);
            }
            closedir(carpeta);
        }
        else
        {
            perror("getcwd() error");
        }
    }

    return 0;
}

void procesoArchivo(char *archivo)
{

    struct stat test;
    printf("File: %s\n", archivo);
    stat(archivo, &test);
    if (stat(archivo, &test) < 0)
    return 1;

    printf("Tamaño del archivo: \t\t%d bytes\n",test.st_size);
    printf("Número de bloques: \t\t%d \n",test.st_blocks);
    printf("Contador de referencias: \t%d\n",test.st_nlink);
    printf("Nodo-i: \t\t%d\n",test.st_ino);
    char date[36];
    printf("Permisos de archivo: \t");
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
}