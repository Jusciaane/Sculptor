#include<iostream>
#include"sculptor.h"
using namespace std;
int main(){
    Sculptor desenho(500,500,500);
    //Caixa
    desenho.setColor(1,0,0,1.0);
    desenho.putBox(1,10,1,10,1,10);
    // Caixa vazada
    desenho.cutBox(1,6,2,6,2,6);
    //Caixa
    desenho.setColor(0.6,0.5,0.9,0.5);
    desenho.putBox(52,60,52,60,52,60);

    //Esfera
    desenho.setColor(1, 1, 0, 1);
    desenho.putSphere(35, 35, 35, 10);
    desenho.setColor(1, 1, 1, 1);
    desenho.putSphere(50, 50, 50, 10);

    //Elipsoide
    desenho.setColor(1,0,1,1.0);
    desenho.putEllipsoid(15, 15, 28, 7, 7, 14);

    //Voxel
    desenho.setColor(0, 0, 0, 1);
    desenho.putVoxel(13,30,20);
    desenho.putVoxel(17,45,30);
    desenho.putVoxel(13,30,50);
    desenho.putVoxel(17,15,30);

    //Salva arquivo .off
    desenho.writeOFF("desenhoteste1.off");

    return 0;
}
