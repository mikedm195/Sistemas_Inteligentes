#include <stdio.h>
#include <string.h>

using namespace std;

int mat [20][6] = {
    {1,1,1,1,2,1},
    {1,2,1,1,2,2},
    {1,3,1,2,1,3},
    {1,1,1,2,1,2},
    {1,2,2,1,2,3},
    {1,3,2,1,2,3},
    {1,2,2,2,2,3},
    {2,1,1,1,2,1},
    {2,2,1,1,2,1},
    {2,3,1,2,1,3},
    {2,1,1,2,1,1},
    {2,2,2,1,2,3},
    {2,3,2,1,2,3},
    {3,1,1,1,2,1},
    {3,2,1,1,2,1},
    {3,3,1,2,1,2},
    {3,1,1,2,1,1},
    {3,2,2,2,1,2},
    {3,3,2,1,2,3},
    {3,2,2,2,2,2}
};

double totalGanar = 0.0;
double totalEmpatar = 0.0;
double totalPerder = 0.0;

void imprimir(){
    for(int i = 0;i<20;i++){
        for(int j = 0;j<6;j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void calcProbs(){
    for(int i = 0; i<20;i++){
        if(mat[i][5] == 1)
            totalGanar++;
        else if(mat[i][5] == 2)
            totalEmpatar++;
        else if(mat[i][5] == 3)
            totalPerder++;
    }
}

double probGanar(int x, int val, int ganar){
    int veces = 0.0;
    for(int i = 0;i<20;i++){
        if(mat[i][x] == val && mat[i][5] == ganar){
            veces++;
        }
    }

    if(ganar==1)
        return veces/totalGanar;
    if(ganar==2)
        return veces/totalEmpatar;
    if(ganar==3)
        return veces/totalPerder;

}

int main(){
    bool seguir = true;
    calcProbs();
    int op = 0;
    while (seguir) {
        double probabilidadGanar = 1.0;
        double probabilidadEmpatar = 1.0;
        double probabilidadPerder = 1.0;
        printf("Equipo rival\n1)Fuerte\n2)Normal\n3)Debil\n");
        scanf("%d",&op);
        probabilidadGanar *= probGanar(0,op,1);
        probabilidadEmpatar *= probGanar(0,op,2);
        probabilidadPerder *= probGanar(0,op,3);

        printf("Mi equipo   \n1)Fuerte\n2)Normal\n3)Debil\n");
        scanf("%d",&op);
        probabilidadGanar *= probGanar(1,op,1);
        probabilidadEmpatar *= probGanar(1,op,2);
        probabilidadPerder *= probGanar(1,op,3);

        printf("Juegan en equipo\n1)Si\n2)No\n");
        scanf("%d",&op);
        probabilidadGanar *= probGanar(2,op,1);
        probabilidadEmpatar *= probGanar(2,op,2);
        probabilidadPerder *= probGanar(2,op,3);

        printf("Motivados\n1)Si\n2)No\n");
        scanf("%d",&op);
        probabilidadGanar *= probGanar(3,op,1);
        probabilidadEmpatar *= probGanar(3,op,2);
        probabilidadPerder *= probGanar(3,op,3);

        printf("Cansados\n1)Si\n2)No\n");
        scanf("%d",&op);
        probabilidadGanar *= probGanar(4,op,1);
        probabilidadEmpatar *= probGanar(4,op,2);
        probabilidadPerder *= probGanar(4,op,3);

        if(probabilidadGanar>probabilidadPerder && probabilidadGanar>probabilidadEmpatar){
            printf("\nEquipo va a ganar con probabilidad de %f\n\n", probabilidadGanar);
        }else{
            if(probabilidadPerder>probabilidadEmpatar){
                printf("\nEquipo va a perder con probabilidad de %f\n\n", probabilidadPerder);
            }else{
                printf("\nLos equipos van a empatar con probabilidad de %f\n\n", probabilidadEmpatar);
            }
        }

        printf("Seguir?\n1)Si\n2)No\n");
        scanf("%d",&op);
        if(op == 2)
            seguir = false;

    }
    return 0;
}
