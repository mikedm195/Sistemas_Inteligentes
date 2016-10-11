#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

float ut[4];  //De tamaño 4 porque son 4 estados.
float utmas1[4];

//Arreglo para la acción optima;
int accionoptima[4];

//Arreglo de recompensas:
float r[4] = {100, 1000, 10000, 50000};

//Arreglo de probabilidades;
float p[4][5][3];

int main(int argc, char const *argv[]) {
    //Arreglos para las utilidades en el tiempo t y en el tiempo t+1

    p[0][1][0] = .9; //responder bien
    p[0][0][1] =  .99999; //quedarse ahi
    p[0][1][2] =  .45; //pasar automaticamente

    p[1][2][0] =.75;
    p[1][1][1] =  .99999;
    p[1][2][2] =  .375;

    p[2][3][0] = .1;
    p[2][2][1] =  .99999;
    p[2][3][2] =  .25;

    p[3][4][0] = .1;
    p[3][3][1] =  .99999;
    p[3][4][2] =  .05;

    //Variable para indicar el error menor:
    float error = 0.001;

    //Variable para determinar cuando se detiene:
    bool repetir = true;

    //Inicializar
    for(int i=0; i<4; i++)
    ut[i] = utmas1[i] = r[i];

    while(repetir == true)
    {
        for(int edo = 0; edo<4; edo++)
        {
            ut[edo] = utmas1[edo];
        }

        for(int edoi= 0; edoi<4; edoi++)
        {
            float maximo = -999999; //Un numero muy pequeño
            float valor;
            for(int accion=0; accion<3; accion++)
            {
                valor = 0;

                for(int edoj=0; edoj<4; edoj++)
                {
                    if(accion == 0)
                        valor = valor + p[edoj][edoi][accion]*ut[edoj];                    
                    else if(accion == 2)
                        valor = (valor + p[edoj][edoi][accion]*ut[edoj])/2;
                }
                if(valor > maximo)
                {
                    maximo = valor;
                    utmas1[edoi] = valor;
                    accionoptima[edoi] = accion;
                }
            }//cierra for accion

        }//cierra for edoi

        //Revision de error
        int cont = 0;
        for(int i=0; i<4; i++)
        {
            //printf("%f + ", ut[i]);
            //printf("%f = ",utmas1[i]);
            //printf("%f\n",fabs(ut[i] - utmas1[i]) );
            if( fabs(ut[i] - utmas1[i]) < error)
                cont++;
        }

        if (cont == 4)
        repetir = false;
    } //cierra while

    for(int i = 0; i<4;i++){
        printf("%d ",accionoptima[i]);
    }
    printf("\n" );
    return 0;
}
