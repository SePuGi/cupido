#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <stdlib.h>

#define MODE_CHUCK_NORRIS 99
#define MAX_INTENTS 10
#define FINAL 'n'

//Comprobaci� de que les dues persones no cauen en la mateixa casella: Linia 50
//Controlar entrada usuari: Linia 72
//Mode Chuck Norris: Linia 90

int cont_intents, fila, columna, victoria;  //variable per a l'usuari
int x_rng_CB, y_rng_CB, x_rng_CN, y_rng_CN; //Dades aleatori
char reiniciar, objectes_creats = 0, chuck = 0;

void mygotoxy(int x,int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon,dwPos);
}

int final_seq(){
    return (reiniciar == FINAL);
}
int segon_final(){
    return (cont_intents == MAX_INTENTS || victoria == 2);
}

void obtenir_primer(){
    //Obtenir objectius
    reiniciar = '\0';
    if(!objectes_creats){
        do{
            //clrscr();
            system("cls");
            srand(time(NULL));
            x_rng_CB = rand() % 79 + 1;
            y_rng_CB = rand() % 23 + 1;

            x_rng_CN = rand() % 79 + 1;
            y_rng_CN = rand() % 23 + 1;


            if(x_rng_CB != x_rng_CN && y_rng_CB != y_rng_CN){    //Comprobaci� aleatoritzacio de les cares
                mygotoxy(x_rng_CB,y_rng_CB);
                printf("%c",1); //CARA BLANCA
                mygotoxy(x_rng_CN,y_rng_CN);
                printf("%c",2); //CARA NEGRA
                objectes_creats = 1;
            }else{
                x_rng_CB = 0;
                x_rng_CN = 0;
                y_rng_CB = 0;
                y_rng_CN = 0;
            }
        }while(!objectes_creats);
    }


    //clrscr();
}
void obtenir_seguent(){
    if((fila==y_rng_CB && columna == x_rng_CB) || (fila==y_rng_CN && columna == x_rng_CN)){
        victoria++; //comprobar punts
    }
    if((fila <= 24 && fila >=0) && (columna <= 80 && columna >= 0)){  //Comprobaci� entrada usuari
        mygotoxy(columna,fila);
        printf("%c",3);
    }else{
        mygotoxy(52,0);
        printf("ERROR");
        mygotoxy(35,0);
        printf("ERROR");

        getch();
        cont_intents--;
    }

}
void tractar_element(){
    mygotoxy(0,0);
    if(!chuck){
        printf("Fletxes restants: %.2d",MAX_INTENTS - cont_intents);
    }else{
        printf("***MODE CHUCK NORRIS*** ");      //activar MODE CHUCK NORRIS
        cont_intents = MAX_INTENTS*2;
    }
    mygotoxy(30,0);
    printf("Fila:        Columna:            ");
    mygotoxy(35,0);
    scanf("%d",&fila);fflush(stdin);          //Obtenim valors X Y

    if(fila == MODE_CHUCK_NORRIS)
        chuck = 1;

    mygotoxy(52,0);
    scanf("%d",&columna);fflush(stdin);
    cont_intents++;
}

void fi_programa(){
    if(victoria == 2){
        //CARTEL VICTORIA
        mygotoxy(15,6);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3);
        mygotoxy(15,7);
        printf("%c%c %c  VICTORIA  %c %c%c\n",221,206,1,2,206,221);
        mygotoxy(15,8);
        printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3);
    }else if(cont_intents == MAX_INTENTS){
        // CARTEL GAME OVER
        mygotoxy(16,9);
        printf("****GAME OVER****");
    }

    mygotoxy(16,10);
    printf("Tornar a intentar?");
    mygotoxy(18, 11);
    printf("  SI      NO");
    reiniciar = getch(); fflush(stdin);
    cont_intents = 0;
    victoria = 0;
    x_rng_CB = 0;
    x_rng_CN = 0;
    y_rng_CB = 0;
    y_rng_CN = 0;
    objectes_creats = 0;
    chuck = 0;
}

int main (void){
    while(!final_seq()){        // Millor un do{}while;??
        while(!segon_final()){
            obtenir_primer();
            tractar_element();
            obtenir_seguent();
        }
        fi_programa();
    }
}
