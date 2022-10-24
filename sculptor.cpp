#include<iostream>
#include"sculptor.h"
#include<fstream>
#include<cmath>

using namespace std;
//Construtor da classe Sculptor
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    //std::cout << "Iniciando o construtor" << endl;
    nx = _nx;
    ny = _ny;
    nz = _nz;
    r = 0.0;
    g = 0.0;
    b = 0.0;
    a = 0.0;

    v = new Voxel **[_nx];

    for(int i = 0; i < _nx; i++ ){
        v[i] = new Voxel *[_ny];
        for(int j = 0; j < _ny; j++){
            v[i][j] = new Voxel [_nz];
            for(int k = 0; k < _nz; k++){
              v[i][j][k].r = 0.0;
              v[i][j][k].g = 0.0;
              v[i][j][k].b = 0.0;
              v[i][j][k].a = 0.0;
              v[i][j][k].isOn = false;

            }
        }
    }
}

//Destrutor da classe Sculptor
Sculptor::~Sculptor(){
    for(int i = 0; i < nx; i++ ){
        for(int j = 0; j < ny; j++){
           delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v;
}
//Métodos
void Sculptor::setColor(float r, float g, float b, float a){
    this -> r = r;
    this -> g = g;
    this -> b = b;
    this -> a = a;
}
void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}
void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k< z1; k++){
                putVoxel(i,j,k);
            }
        }
    }
}
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k< z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    int x0 = (xcenter - radius < 0) ? 0 : xcenter - radius;
    int x1 = (xcenter + radius > this->nx) ? this->nx : xcenter + radius;
    int y0 = (ycenter - radius < 0) ? 0 : ycenter - radius;
    int y1 = (ycenter + radius > this->ny) ? this->ny : ycenter + radius;
    int z0 = (zcenter - radius < 0) ? 0 : zcenter - radius;
    int z1 = (zcenter + radius > this->nz) ? this->nz : zcenter + radius;

    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k< z1; k++){
                if(pow(i - xcenter, 2) / pow(radius, 2) + pow(j - ycenter, 2) / pow(radius, 2) + pow(k - zcenter, 2) / pow(radius, 2) < 1){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    int x0 = (xcenter - radius < 0) ? 0 : xcenter - radius;
    int x1 = (xcenter + radius > this->nx) ? this->nx : xcenter + radius;
    int y0 = (ycenter - radius < 0) ? 0 : ycenter - radius;
    int y1 = (ycenter + radius > this->ny) ? this->ny : ycenter + radius;
    int z0 = (zcenter - radius < 0) ? 0 : zcenter - radius;
    int z1 = (zcenter + radius > this->nz) ? this->nz : zcenter + radius;

     for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k< z1; k++){
                if(pow(i - xcenter, 2) / pow(radius, 2) + pow(j - ycenter, 2) / pow(radius, 2) + pow(k - zcenter, 2) / pow(radius, 2) < 1 ){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int x0 = (xcenter - rx < 0) ? 0 : xcenter - rx;
    int x1 = (xcenter + rx > this->nx) ? this->nx : xcenter + rx;
    int y0 = (ycenter - ry < 0) ? 0 : ycenter - ry;
    int y1 = (ycenter + ry > this->ny) ? this->ny : ycenter + ry;
    int z0 = (zcenter - rz < 0) ? 0 : zcenter - rz;
    int z1 = (zcenter + rz > this->nz) ? this->nz : zcenter + rz;

     for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k< z1; k++){
                if(pow(i - xcenter, 2) / pow(rx, 2) + pow(j - ycenter, 2) / pow(ry, 2) + pow(k - zcenter, 2) / pow(rz, 2) < 1){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    int x0 = (xcenter - rx < 0) ? 0 : xcenter - rx;
    int x1 = (xcenter + rx > this->nx) ? this->nx : xcenter + rx;
    int y0 = (ycenter - ry < 0) ? 0 : ycenter - ry;
    int y1 = (ycenter + ry > this->ny) ? this->ny : ycenter + ry;
    int z0 = (zcenter - rz < 0) ? 0 : zcenter - rz;
    int z1 = (zcenter + rz > this->nz) ? this->nz : zcenter + rz;

     for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k< z1; k++){
                if(pow(i - xcenter, 2) / pow(rx, 2) + pow(j - ycenter, 2) / pow(ry, 2) + pow(k - zcenter, 2) / pow(rz, 2) < 1 ){
                    cutVoxel(i,j,k);
                }
            }
        }
    }

}
// Formato OFF
void Sculptor::writeOFF(const char *filename){
    ofstream arquivo(filename);
    int total = 0, i, j, k;
    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (v[i][j][k].isOn){
                    total++;
                }
            }
        }
    }
    arquivo << "OFF" << endl;
    // 8 vértices e 6 faces
    arquivo << 8 * total << " " << 6 * total << " 0" << endl;
    for (i = 0; i < nx; i++){
        for (j = 0; j < ny; j++){
            for (k = 0; k < nz; k++){
                if (v[i][j][k].isOn){
                    arquivo << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    arquivo << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    arquivo << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    arquivo << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    arquivo << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    arquivo << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    arquivo << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    arquivo << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }
            }
        }
    }
    int contador = 0;
        for (i = 0; i < nx; i++){
            for (j = 0; j < ny; j++){
                for (k = 0; k < nz; k++){
                    if (v[i][j][k].isOn){
                     arquivo << "4 " << contador * 8 + 0 << " " << contador * 8 + 3 << " " << contador * 8 + 2 << " " << contador * 8 + 1 << " " << v[i][j][k].r << ".0 " << v[i][j][k].g << ".0 " << v[i][j][k].b << ".0 " << v[i][j][k].a << ".0" << endl;
                     arquivo << "4 " << contador * 8 + 4 << " " << contador * 8 + 5 << " " << contador * 8 + 6 << " " << contador * 8 + 7 << " " << v[i][j][k].r << ".0 " << v[i][j][k].g << ".0 " << v[i][j][k].b << ".0 " << v[i][j][k].a << ".0" << endl;
                     arquivo << "4 " << contador * 8 + 0 << " " << contador * 8 + 1 << " " << contador * 8 + 5 << " " << contador * 8 + 4 << " " << v[i][j][k].r << ".0 " << v[i][j][k].g << ".0 " << v[i][j][k].b << ".0 " << v[i][j][k].a << ".0" << endl;
                     arquivo << "4 " << contador * 8 + 0 << " " << contador * 8 + 4 << " " << contador * 8 + 7 << " " << contador * 8 + 3 << " " << v[i][j][k].r << ".0 " << v[i][j][k].g << ".0 " << v[i][j][k].b << ".0 " << v[i][j][k].a << ".0" << endl;
                     arquivo << "4 " << contador * 8 + 3 << " " << contador * 8 + 7 << " " << contador * 8 + 6 << " " << contador * 8 + 2 << " " << v[i][j][k].r << ".0 " << v[i][j][k].g << ".0 " << v[i][j][k].b << ".0 " << v[i][j][k].a << ".0" << endl;
                     arquivo << "4 " << contador * 8 + 1 << " " << contador * 8 + 2 << " " << contador * 8 + 6 << " " << contador * 8 + 5 << " " << v[i][j][k].r << ".0 " << v[i][j][k].g << ".0 " << v[i][j][k].b << ".0 " << v[i][j][k].a << ".0" << endl;

                    contador++;
                    }
                }
            }
        }
    arquivo.close();
}
