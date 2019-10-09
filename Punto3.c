#include <stdio.h>
#include <stdlib.h>

void tail(FILE*, int);

void main(int argc, char* argv[]){
//Estructura para el programa: mytail -n file
  if(argc != 3){
    printf("Asegurece de poner los tres parametros necesarios.\n");
    exit(1);
  }
  int numeroFilas = 0;
  if((*argv[1]) == '-'){
    numeroFilas = atoi(argv[1]+1);
  }else{
    printf("Ingrese los parametros de forma adecuada.\n");
    exit(1);
  }
  FILE* archivo;
  archivo = fopen(argv[2], "rb");
  if(archivo == NULL){
    printf("No se ha podido abrir el archivo\n");
    exit(1);
  }
  tail(archivo, numeroFilas);
  fclose(archivo); //cerrar el buffer y que no se pierda la información recien guardada.
}

void tail(FILE* archivo, int numeroFilas){
    int contador = 0;
    unsigned long long posicion;
    char lineasFinales[2*100];
    
    if (fseek(archivo, 0, SEEK_END))
        perror("fseek() Error.");
    else{
        posicion = ftell(archivo);
        while (posicion){

            if (numeroFilas==0)
            {
                printf("Por favor ingrese un número mayor a 0.");
                break;
            }

            if (fseek(archivo, --posicion, SEEK_SET) != -1){
                if (fgetc(archivo) == '\n'){
                    if (contador++ == numeroFilas-1)
                        break;
                }
            }else
                perror("fseek() Error.");
        }
        if(posicion == 0)
            rewind(archivo);
            while (fgets(lineasFinales, sizeof(lineasFinales), archivo)){
                printf("%s", lineasFinales);                
            }   
            printf("\n");
    }
}