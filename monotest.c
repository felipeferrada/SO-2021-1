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
    int ph1[2]; // para crear pipe de padre a hijo1
    int h1p[2]; // para crear pipe de hijo1 a padre
    int ph2[2]; // para crear pipe de padre a hijo2
    int h2p[2]; // para crear pipe de hijo2 a padre
    int ph3[2]; // para crear pipe de padre a hijo3
    int h3p[2]; // para crear pipe de hijo3 a padre
    int dinero = 100;
    int pos = 0;
    int dado;
    int dadohijo, poshijo, dinerohijo;
    int cont = 0;

    pipe(ph1);
    pipe(h1p);
    pipe(ph2);
    pipe(h2p);
    pipe(ph3);
    pipe(h3p);


    while (flag == 1)
    { 
        for (int jugador = 0; jugador < 3; jugador++)
        {
            int child;
            child = fork();

            if (child == 0) // es hijo
            {
                switch (jugador)
                {
                case 1:
                    if (cont != 0)
                    {
                        read(ph2[0], &pos, sizeof(int));
                        read(ph2[0], &dinero, sizeof(int));
                    }

                    srand(getpid()); // generador de semillas distintas para cada jugador
                    dado = ((rand() % 6) + 1);
                    pos = pos + dado;
                    dinero = dinero + dado;

                    write(ph2[1], &dado, sizeof(int));
                    write(ph2[1], &pos, sizeof(int));
                    write(ph2[1], &dinero, sizeof(int));
                    sleep(1);
                    exit(0);
                    break;
                case 2:
                    if (cont != 0)
                    {
                        read(ph3[0], &pos, sizeof(int));
                        read(ph3[0], &dinero, sizeof(int));
                    }

                    srand(getpid()); // generador de semillas distintas para cada jugador
                    dado = ((rand() % 6) + 1);
                    pos = pos + dado;
                    dinero = dinero + dado;

                    write(ph3[1], &dado, sizeof(int));
                    write(ph3[1], &pos, sizeof(int));
                    write(ph3[1], &dinero, sizeof(int));
                    sleep(1);
                    exit(0);
                    break;
                default:
                    if (cont != 0)
                    {
                        read(ph1[0], &pos, sizeof(int));
                        read(ph1[0], &dinero, sizeof(int));
                    }

                    srand(getpid()); // generador de semillas distintas para cada jugador
                    dado = ((rand() % 6) + 1);
                    pos = pos + dado;
                    dinero = dinero + dado;

                    write(ph1[1], &dado, sizeof(int));
                    write(ph1[1], &pos, sizeof(int));
                    write(ph1[1], &dinero, sizeof(int));
                    sleep(1);
                    exit(0);
                    break;
                }
            }

            else // es padre
            {
                switch (jugador)
                {
                case 1:
                    sleep(1);
                    read(h2p[0], &dadohijo, sizeof(int));
                    read(h2p[0], &poshijo, sizeof(int));
                    read(h2p[0], &dinerohijo, sizeof(int));
                    printf("el dado del jugador %d fue %d (proceso padre)\n", jugador+1, dadohijo);
                    printf("la posicion del jugador %d es %d (proceso padre)\n", jugador+1, poshijo);
                    printf("el jugador %d que tiene %d dinero (proceso padre)\n", jugador+1, dinerohijo);
                    printf("*************************************************\n");
                    write(h2p[1], &poshijo, sizeof(int));
                    write(h2p[1], &dinerohijo, sizeof(int));
                    break;
                case 2:
                    sleep(1);
                    read(h3p[0], &dadohijo, sizeof(int));
                    read(h3p[0], &poshijo, sizeof(int));
                    read(h3p[0], &dinerohijo, sizeof(int));
                    printf("el dado del jugador %d fue %d (proceso padre)\n", jugador+1, dadohijo);
                    printf("la posicion del jugador %d es %d (proceso padre)\n", jugador+1, poshijo);
                    printf("el jugador %d que tiene %d dinero (proceso padre)\n", jugador+1, dinerohijo);
                    printf("*************************************************\n");
                    write(h3p[1], &poshijo, sizeof(int));
                    write(h3p[1], &dinerohijo, sizeof(int));
                    break;
                
                default:
                    sleep(1);
                    read(h1p[0], &dadohijo, sizeof(int));
                    read(h1p[0], &poshijo, sizeof(int));
                    read(h1p[0], &dinerohijo, sizeof(int));
                    printf("el dado del jugador %d fue %d (proceso padre)\n", jugador+1, dadohijo);
                    printf("la posicion del jugador %d es %d (proceso padre)\n", jugador+1, poshijo);
                    printf("el jugador %d que tiene %d dinero (proceso padre)\n", jugador+1, dinerohijo);
                    printf("*************************************************\n");
                    write(h1p[1], &poshijo, sizeof(int));
                    write(h1p[1], &dinerohijo, sizeof(int));
                    break;
                }
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