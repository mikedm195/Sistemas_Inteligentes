#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <time.h>

#define N 21

using namespace std;

int x = 0;
int y = 0;
int mapa[N][N];
bool llaveTomada = false;
bool ganar = false;

struct Personaje{
    int x = 1;
    int y = 1;
    int direccion = 0;
} personaje, malo;

struct Objeto{
    int x = 1;
    int y = 1;
} llave, salida;

void cargaMapa(string archivo);
void imprime();
void muevePersonaje();
void mueveMalo();
bool girar();
void ponerLlave();
void ponerSalida();
void ponerMalo();
void ponerPersonaje();
void checaAtrapa();

int main(){
    srand (time(NULL));

    cargaMapa("map1.txt");

    ponerMalo();
    ponerLlave();
    ponerSalida();

    while(!ganar){
        muevePersonaje();
        mueveMalo();
        imprime();
        usleep(100000);
    }
    printf("¡¡¡¡ganaste!!!!");
    return 0;
}

void muevePersonaje(){
    //bool g = girar();
    while (!girar()) {
        if(personaje.direccion == 3)
            personaje.direccion = 0;
        else
            personaje.direccion++;
        //g = girar();
    }
    switch (personaje.direccion) {
        case 0: personaje.y--;
        break;
        case 1: personaje.x++;
        break;
        case 2: personaje.y++;
        break;
        case 3: personaje.x--;
        break;
    }
    if(personaje.x == llave.x && personaje.y == llave.y){
        llaveTomada = true;
        llave.x = -1;
        llave.y = -1;
    }
    if(personaje.x == salida.x && personaje.y == salida.y && llaveTomada){
        ganar = true;
    }
}

bool girar(){
    bool libre = false;
    if(personaje.direccion == 0){
        if(mapa[personaje.y][personaje.x-1] != 1){
            personaje.direccion = 3;
            libre = true;
        }else{
            if(mapa[personaje.y-1][personaje.x] != 1)
                libre = true;
        }
    }else{
        if(personaje.direccion == 1){
            if(mapa[personaje.y-1][personaje.x] != 1){
                personaje.direccion--;
                libre = true;
            }else{
                if(mapa[personaje.y][personaje.x+1] != 1)
                    libre = true;
            }
        }else{
            if(personaje.direccion == 2){
                if(mapa[personaje.y][personaje.x+1] != 1){
                    personaje.direccion--;
                    libre = true;
                }else{
                    if(mapa[personaje.y+1][personaje.x] != 1)
                        libre = true;
                }
            }else{
                if(personaje.direccion == 3){
                    if(mapa[personaje.y+1][personaje.x] != 1){
                        personaje.direccion--;
                        libre = true;
                    }else{
                        if(mapa[personaje.y][personaje.x-1] != 1)
                            libre = true;
                    }
                }
            }
        }
    }
    return libre;
}

void nuevaDireccion(){
    int direccionesDisponibles = 0;
    int dirs[3] = {0,0,0};
    if(mapa[malo.y-1][malo.x] != 1 && malo.direccion != 2)
        dirs[direccionesDisponibles++] = 0;
    if(mapa[malo.y+1][malo.x] != 1 && malo.direccion != 0)
        dirs[direccionesDisponibles++] = 2;
    if(mapa[malo.y][malo.x-1] != 1 && malo.direccion != 1)
        dirs[direccionesDisponibles++] = 3;
    if(mapa[malo.y][malo.x+1] != 1 && malo.direccion != 3)
        dirs[direccionesDisponibles++] = 1;

    if(direccionesDisponibles == 0){
        switch (malo.direccion) {
            case 0: malo.direccion = 2; break;
            case 1: malo.direccion = 3; break;
            case 2: malo.direccion = 0; break;
            case 3: malo.direccion = 1; break;
        }
    }else{
        malo.direccion = dirs[rand()%direccionesDisponibles];
    }
    switch (malo.direccion) {
        case 0: malo.y--; break;
        case 1: malo.x++; break;
        case 2: malo.y++; break;
        case 3: malo.x--; break;
    }
}

void mueveMalo(){
    checaAtrapa();
    mapa[malo.y][malo.x] = 0;
    nuevaDireccion();
    checaAtrapa();
    mapa[malo.y][malo.x] = 3;
}

void checaAtrapa(){
    if (malo.x == personaje.x && malo.y == personaje.y){
        if(llaveTomada){
            ponerLlave();
            llaveTomada = false;
        }
        ponerPersonaje();
    }
}

void ponerLlave(){
    bool puesta = false;
    while(!puesta){
        int x = rand() % 20 + 1;
        int y = rand() % 20 + 1;
        if(mapa[y][x] != 1){
            mapa[y][x] = 5;
            llave.x = x;
            llave.y = y;
            puesta = true;
        }
    }
}

void ponerSalida(){
    bool puesta = false;
    while(!puesta){
        int x = rand() % 20 + 1;
        int y = rand() % 20 + 1;
        if(mapa[y][x] != 1){
            mapa[y][x] = 4;
            salida.x = x;
            salida.y = y;
            puesta = true;
        }
    }
}

void ponerPersonaje(){
    bool puesta = false;
    while(!puesta){
        int x = rand() % 20 + 1;
        int y = rand() % 20 + 1;
        if(mapa[y][x] != 1){
            personaje.x = x;
            personaje.y = y;
            puesta = true;
        }
    }
}

void ponerMalo(){
    bool puesta = false;
    while(!puesta){
        int x = rand() % 20 + 1;
        int y = rand() % 20 + 1;
        if(mapa[y][x] != 1){
            mapa[y][x] = 3;
            malo.x = x;
            malo.y = y;
            malo.direccion = rand() % 4;
            puesta = true;
        }
    }
}

void cargaMapa(string archivo) {
    string line;
    ifstream myfile (archivo.c_str());
    if (myfile.is_open()){
        int j = 0;
        while ( getline (myfile,line) ){
            for(int i = 0;i<line.length();i++){
                mapa[j][i] = line[i] - '0';
            }
            j++;
        }
        myfile.close();
    }
}

void imprime(){
    int color;
    mapa[personaje.y][personaje.x] = 2;
    for(int i = 0;i<N;i++){
        for(int j = 0;j<N;j++){
            //temp = mapa[i][j];
            switch (mapa[i][j]) {
                case 0: printf("\033[1;37m0");
                break;
                case 1: printf("\033[1;30m0");
                break;
                case 2:
                if(llaveTomada) printf("\033[1;33mO");
                else            printf("\033[1;34mO");
                break;
                case 3: printf("\033[1;31mM");
                break;
                case 4: printf("\033[1;32mS");
                break;
                case 5: printf("\033[1;33mX");
                break;
            }
        }
        printf("\n");
    }
    mapa[personaje.y][personaje.x] = 0;
    mapa[llave.y][llave.x] = 5;
    mapa[salida.y][salida.x] = 4;
}
