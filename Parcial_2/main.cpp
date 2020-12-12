#include <iostream>
#include <canion.h>
#include <math.h>
#define G 9.81
#define pi 3.141617

using namespace std;

Canion llenar_datos(int opcion);

int main()
{
    cout << "       Sistema de simulacion       " << endl;
    cout << "-----------------------------------" << endl;

    Canion OFENSIVO = llenar_datos(1);

    Canion DEFENSIVO = llenar_datos(2);









    cout << endl<< endl;
    return 0;
}


Canion llenar_datos(int opcion){

    float posx, posy;
    if(opcion == 1){
        cout <<"El canion OFENSIVO se encuentra en coordenadas (0 , 0)"<<endl<<endl;
        Canion canio(0, 0);
        return  canio;

    }else if(opcion == 2){
        cout <<"El canion DEFENSIVO: "<<endl<<endl;
        cout <<"Ingrese coordenada en X"<<endl<<endl;
        cin >> posx;
        cout <<"Ingrese coordenada en Y"<<endl<<endl;
        cin >> posy;
        Canion canio(posx, posy);
        return  canio;

    }

    //Si falla
    cout << "Hubo error"<<endl;
    Canion canio(0, 0);
    return canio;
}









