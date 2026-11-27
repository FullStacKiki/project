#include <stdio.h>
#include <stdlib.h>
#include "eventoprueba.h"

int es_tribonacci(int n){
    int a=0, b=0, c=1;   

    while(a<n){         
        int siguiente = a+b+c;
        a=b;
        b=c;
        c=siguiente;
    }

    return a==n;
}


int evento_cueva(void){
    int numero = rand()%500 + 1;   
    int correcta = es_tribonacci(numero);
    char respuesta;

    printf("=== Coral Cave ===\n");
    printf("An inscription shows the number %d.\n", numero);
    printf("Does it belong to the Tribonacci sequence (0, 0, 1, 1, 2, 4, 7, 13, 24, ...)?\n");

    do{
        printf("Answer [y/n]: ");
        scanf(" %c", &respuesta);
    } while(respuesta!='y' && respuesta!='Y' && respuesta!='n' && respuesta!='N');

    int dijo_si = (respuesta=='y' || respuesta=='Y');

    return dijo_si==correcta;
}


/* esto solamente es un evento de prueba para ir probando y validando lo que fui haciendo, despues reemplazar con lo de ale
 */