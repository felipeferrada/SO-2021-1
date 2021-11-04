#include <stdio.h>
#include <stdlib.h>



int main() {

    printf("\n");
    printf("\n");

    char* tablero[8][8] = {{"Jail","+75","-50","-50","+75","+75","Back 3","     Free"},
                        {"-25"," "," "," "," "," ","                    ","Forward 3"},
                        {"+50"," "," "," "," "," ","                        ","+50"},
                        {"Back 2"," "," "," "," "," MONOPOLY","            ","Back 4"},
                        {"-25"," "," "," "," "," ","                        ","+50"},
                        {"+50"," "," "," "," "," ","                        ","-50"},
                        {"+50"," "," "," "," "," ","                        ","-25"},
                        {"Start","-75","-25","Back 4","+75","Forward 5","+75","Jail"}};

    int columns,rows;

    for(columns = 0; columns <= 7; columns++){

        for(rows = 0; rows <= 7; rows++){
            printf(" %s" , tablero[columns][rows]);
        }

        printf("\n");
        printf("\n");
    }

    return 0;
}