#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

int main() {

    char* tablero[8][8] = {{"Jail","+75","-50","-50","+75","+75","Back 3","     Free"},
                        {"-25"," "," "," "," "," ","                    ","Forward 3"},
                        {"+50"," "," "," "," "," ","                        ","+50"},
                        {"Back 2"," "," "," "," "," MONOPOLY","            ","Back 4"},
                        {"-25"," "," "," "," "," ","                        ","+50"},
                        {"+50"," "," "," "," "," ","                        ","-50"},
                        {"+50"," "," "," "," "," ","                        ","-25"},
                        {"Start","-75","-25","Back 4","+75","Forward 5","+75","Jail"}};

    int columns,rows;
    int flag = 1;
    int fd[2];
    int dinero = 100;
    int pos = 0;
    int dado;
    int dadohijo, poshijo, dinerohijo;
    int cont = 0;

    while (flag == 1)
    { 
        for (int jugador = 0; jugador < 3; jugador++)
        {
            int child;
            pipe(fd);
            child = fork();

            if (child == 0) // es hijo
            {
                srand(getpid()); // generador de semillas distintas para cada jugador
                dado = ((rand() % 6) + 1);
                pos = pos + dado;
                dinero = dinero + dado;

                write(fd[1], &dado, sizeof(int));
                write(fd[1], &pos, sizeof(int));
                write(fd[1], &dinero, sizeof(int));
                sleep(1);
                exit(0);
            }

            else // es padre
            {
                sleep(1);
                read(fd[0], &dadohijo, sizeof(int));
                read(fd[0], &poshijo, sizeof(int));
                read(fd[0], &dinerohijo, sizeof(int));
                printf("el dado del jugador %d fue %d\n", jugador+1, dadohijo);
                printf("la posicion del jugador %d es %d\n", jugador+1, poshijo);
                printf("el jugador %d que tiene %d dinero\n", jugador+1, dinerohijo);
                printf("*************************************************\n");
                write(fd[1], &poshijo, sizeof(int));
                write(fd[1], &dinerohijo, sizeof(int));
            }
        }

        sleep(1);
        for(columns = 0; columns <= 7; columns++){

            for(rows = 0; rows <= 7; rows++){
                printf(" %s" , tablero[columns][rows]);
            }

            printf("\n");
            printf("\n");
        }

        printf("Quieres seguir jugando?? \n1: si \ncualquier otro: no:\n");
        scanf("%d", &flag);
        cont++;
    }

    return 0;
} 