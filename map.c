#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "map.h"
#include "eventoprueba.h"

#define START_HEALTH 10   /* PROVISORIO !!!! CAMBIAR LUEGO*/

#define HIDDEN   0   
#define REVEALED 1   
#define VISITED  2 

void clear_screen() { printf("\033[H\033[2J\033[3J"); }


int tirar_dado(void){
    return rand()%6 + 1;
}

/* terreno interior segun la Tabla 3 */
char terreno_por_dado(int dado){
    if(dado<=2) return FOREST;   /* 1-2 */
    if(dado==3) return SWAMP;
    if(dado==4) return HILL;
    if(dado==5) return SPRING;
    return PATH;                 /* 6 */
}

/* letra de una casilla visitada*/
char letra_visitada(char terreno){
    if(terreno==PATH) return '=';
    return toupper(terreno);
}

void generar_mapa(char mapa[MAP_SIZE][MAP_SIZE], int visto[MAP_SIZE][MAP_SIZE]){
    int i,j;
    int centro = MAP_SIZE/2;

    for(i=0;i<MAP_SIZE;i++){
        for(j=0;j<MAP_SIZE;j++){
            if(i==0 || i==MAP_SIZE-1 || j==0 || j==MAP_SIZE-1){
                mapa[i][j]=BEACH;                          /* bordes = playa */
            } else {
                mapa[i][j]=terreno_por_dado(tirar_dado()); /* interior = dado */
            }
            visto[i][j]=HIDDEN;                            
        }
    }

    mapa[centro][centro]=CAMP;   /* el campamento siempre en el centro */

    /* Coral Cave: casilla interior a 3 pasos o mas del campamento */
    int f, c;
    do{
        f = rand()%(MAP_SIZE-2) + 1;
        c = rand()%(MAP_SIZE-2) + 1;
    } while(abs(f-centro) + abs(c-centro) < 3);
    mapa[f][c]=CAVE;

    /* Jaguar's Den: casilla interior a 3 pasos o mas del campamento, sin pisar la cueva */
    do{
        f = rand()%(MAP_SIZE-2) + 1;
        c = rand()%(MAP_SIZE-2) + 1;
    } while(abs(f-centro) + abs(c-centro) < 3 || mapa[f][c]==CAVE);
    mapa[f][c]=DEN;
}

/* revela (en cadena) todos los caminos */
void revelar_caminos(char mapa[MAP_SIZE][MAP_SIZE], int visto[MAP_SIZE][MAP_SIZE], int fila, int col){
    int df[4] = {-1, 1, 0, 0};   /* arriba, abajo, -, - */
    int dc[4] = { 0, 0,-1, 1};   /* -, -, izquierda, derecha */
    int k;

    for(k=0;k<4;k++){
        int f = fila + df[k];
        int c = col  + dc[k];

        if(f<0 || f>=MAP_SIZE || c<0 || c>=MAP_SIZE) continue;   /* fuera del mapa */

        if(mapa[f][c]==PATH && visto[f][c]==HIDDEN){
            visto[f][c]=REVEALED;                 /* se ve, pero no se visita */
            revelar_caminos(mapa, visto, f, c);   /* seguir la cadena desde ahi */
        }
    }
}

void mostrar_mapa(char mapa[MAP_SIZE][MAP_SIZE], int visto[MAP_SIZE][MAP_SIZE], int fila, int col, int pasos, int salud, int lente, int llave){
    int i,j;
    clear_screen();

    printf("Prueba mapa island - Day -  | %d/%d Steps  | Castaway - (%d Health) | Lens: %s | Key: %s :\n",
           pasos, MAX_STEPS, salud, lente ? "yes" : "no", llave ? "yes" : "no");

    printf("    ");
    for(j=0;j<MAP_SIZE;j++){
        printf("%d ",j);
    }
    printf("\n");

    for(i=0;i<MAP_SIZE;i++){
        printf("%d   ",i);
        for(j=0;j<MAP_SIZE;j++){
            if(i==fila && j==col){
                printf("%c ",CASTAWAY);
            } else if(visto[i][j]==VISITED){
                printf("%c ",letra_visitada(mapa[i][j]));
            } else if(visto[i][j]==REVEALED){
                printf("%c ",mapa[i][j]);
            } else {
                printf("? ");
            }
        }
        printf("\n");
    }

    printf("\nLegend: # castaway  @ Camp  b/B Beach  f/F Forest  p/P Swamp  c/C Hill\n");
    printf("o/O Spring  -/= Path  r/R Shipwreck  g/G Cave  t/T Den  l/L Lighthouse  ? hidden\n\n");
}


int main(void){
    char mapa[MAP_SIZE][MAP_SIZE];
    int visto[MAP_SIZE][MAP_SIZE];
    int fila=MAP_SIZE/2, col=MAP_SIZE/2;   
    int pasos=0;
    int salud=START_HEALTH;
    int lente=0;   /* 1 cuando se consigue la lente del faro */
    int llave=0;   /* 1 cuando se consigue la llave del faro (Jaguar's Den) */
    char tecla;

    srand(time(NULL));   /* mapa distinto en cada partida */

    generar_mapa(mapa, visto);

    visto[fila][col]=VISITED;   /* el campamento ya esta visitado */

    mostrar_mapa(mapa, visto, fila, col, pasos, salud, lente, llave);

    while(1){
        printf("Move (w=up s=down a=left d=right q=quit): ");
        scanf(" %c", &tecla);

        if(tecla=='q') break;

        int nf=fila, nc=col;
        char *mensaje = "";
    

        if(tecla=='w') nf--;
        else if(tecla=='s') nf++;
        else if(tecla=='a') nc--;
        else if(tecla=='d') nc++;
        else mensaje = "Invalid key";

        if(mensaje[0]=='\0'){
            if(nf<0 || nf>=MAP_SIZE || nc<0 || nc>=MAP_SIZE){
                mensaje = "You can't go that way";
            } else {
                fila=nf;
                col=nc;
                pasos++;

                if(visto[fila][col]!=VISITED){          /* evento sin resolver */
                    if(mapa[fila][col]==CAVE){
                        mostrar_mapa(mapa, visto, fila, col, pasos, salud, lente, llave);
                        if(evento_cueva()){
                            lente=1;
                            visto[fila][col]=VISITED;   /* resuelto */
                            mensaje = "Correct! You got the Lighthouse Lens.";
                        } else {
                            salud -= CAVE_DAMAGE;
                            visto[fila][col]=REVEALED;  /* reintentar en otra visita */
                            mensaje = "Wrong! The cave partially collapses: -3 health. Try again later.";
                        }
                    } else if(mapa[fila][col]==DEN){
                   
                        visto[fila][col]=REVEALED;
                        mensaje = "Jaguar (combat not implemented yet)";

                        /* Cuando juntemos la funcion nuestra unir su codigo con el de el

                        mostrar_mapa(mapa, visto, fila, col, pasos, salud, lente, llave);
                        if(NOMBRE_FUNCION(&salud)){
                            llave=1;
                            // comida += JAGUAR_FOOD;   (cuando exista la variable comida)
                            visto[fila][col]=VISITED;   // resuelto
                            mensaje = "You defeated the jaguar! You got the Lighthouse Key and +4 Food.";
                        } else {
                            visto[fila][col]=REVEALED;  // sigue pendiente
                            mensaje = "The jaguar wins this time...";
                        }
                        */
                    } else {
                        visto[fila][col]=VISITED;
                        if(mapa[fila][col]==PATH){
                            revelar_caminos(mapa, visto, fila, col);
                        }
                    }
                }
            }
        }

        mostrar_mapa(mapa, visto, fila, col, pasos, salud, lente, llave);
        printf("%s\n", mensaje);
        if(pasos>=MAX_STEPS){
            printf("No more steps left!!!\n");
            break; /* romper limite de pasos*/
        }
    }

    return 0;
}
