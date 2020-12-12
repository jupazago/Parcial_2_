#include <iostream>
#include <canion.h>
#include <math.h>
#define G 9.81
#define pi 3.141617

using namespace std;

Canion llenar_datos(int opcion);

void ImprimirResultados(int anglulo,int velocidad, float x, float y, float t);

void DisparoOfensivo(Canion OFENSIVO, Canion DEFENSIVO);
bool DisparoDefensivo(Canion OFENSIVO, Canion DEFENSIVO);

int main()
{
    cout << "       Sistema de simulacion       " << endl;
    cout << "-----------------------------------" << endl;

    Canion OFENSIVO = llenar_datos(1);

    Canion DEFENSIVO = llenar_datos(2);


    cout << "Canion Ofensivo: ( "<<OFENSIVO.getPosx() << " , "<< OFENSIVO.getPosy()<<" )"<<endl;
    cout << "Canion Ofensivo: ( "<<DEFENSIVO.getPosx() << " , "<< DEFENSIVO.getPosy()<<" )"<<endl;
    cout << "-------------------------"<<endl;
    cout << "-------------------------"<<endl<<endl;

    DisparoOfensivo(OFENSIVO, DEFENSIVO);



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
        /*
        cout <<"El canion DEFENSIVO: "<<endl<<endl;
        cout <<"Ingrese coordenada en X"<<endl<<endl;
        cin >> posx;
        cout <<"Ingrese coordenada en Y"<<endl<<endl;
        cin >> posy;
        */

        //Canion canio(posx, posy);
        Canion canio(500, 50);
        return  canio;

    }

    //Si falla
    cout << "Hubo error"<<endl;
    Canion canio(0, 0);
    return canio;
}

void ImprimirResultados(int anglulo,int velocidad, float x, float y, float t)
{
    cout << "Impacto con un angulo de " << anglulo << " grados" << endl;
    cout << "Impacto con velocidad incial " << velocidad << endl;
    cout << "Impacto con posicion x: " << x << endl;
    cout << "Impacto con posicion y: " << y << endl;
    cout << "Con tiempo: " << t << endl;
    cout << endl;
}

void DisparoOfensivo(Canion OFENSIVO, Canion DEFENSIVO){
    int flag = 0;
    float x = 0.0;
    float y = 0.0;

    for(int angulo = 1; angulo < 90 ; angulo++){
        OFENSIVO.setAng(angulo);
        for(float velocidad = 10; velocidad < 100 ; velocidad += 5){
            OFENSIVO.setVel(velocidad); //Angulo
            OFENSIVO.setVelx(velocidad*cos(OFENSIVO.getAng()*pi/180));  //Vellocidad X
            OFENSIVO.setVely(velocidad*sin(OFENSIVO.getAng()*pi/180));  //Vellocidad Y
            OFENSIVO.setR(0.05*(DEFENSIVO.getPosx())); //0.05*d __ distancia entre caniones
            x = 0.0;
            y = 0.0;
            for(float t = 0; ; t+= 0.05){
                x = OFENSIVO.getVelx()*t;
                y = OFENSIVO.getPosy()+ OFENSIVO.getVely()*t -(0.5*G*t*t);
                //Verificar impacto
                //comprobar que este en el radio de impacto
                //distancia entre dos puntos (bala y DEFENSIVO) < radio de explosion
                if(sqrt(pow((DEFENSIVO.getPosx() - x),2)+pow((DEFENSIVO.getPosy() - y),2)) < OFENSIVO.getR()){
                    if(y<0) y = 0;
                    cout << endl<<endl<<endl;
                    cout << "--------------------------------------"<<endl;
                    cout << "Lanzamiento Ofensivo #"<<flag+1<<endl;
                    cout << "--------------------------------------"<<endl;
                    ImprimirResultados(OFENSIVO.getAng(), OFENSIVO.getVel(), x, y, t);

                    //Creamos la reaccion DEFENSIVA
                    if(t>2){
                        //3 disparos defensivos
                        DisparoDefensivo(OFENSIVO, DEFENSIVO);

                    }
                    flag++;
                    angulo += 5;
                    velocidad += 10;
                    break;
                }
                if(y < 0){
                    break;
                }
            }
            if(flag == 3) break;
        }
        if(flag == 3) break;
    }
    if(flag != 3){
        cout << "No impacto en los disparos esperados"<< endl;
    }
}


bool DisparoDefensivo(Canion OFENSIVO, Canion DEFENSIVO){

    float xo = 0.0;
    float yo = 0.0;
    float xd = 0.0;
    float yd = 0.0;
    int flag = 0;

    //Generar disparo defensivo
    for(int angulo = 0; angulo < 90 ; angulo++){
        DEFENSIVO.setAng(angulo+90);
        for(float velocidad = 1; velocidad < 300 ; velocidad += 5){
            DEFENSIVO.setVel(velocidad); //Angulo
            DEFENSIVO.setVelx(velocidad*cos(DEFENSIVO.getAng()*pi/180));  //Vellocidad X
            DEFENSIVO.setVely(velocidad*sin(DEFENSIVO.getAng()*pi/180));  //Vellocidad Y
            DEFENSIVO.setR(0.025*(DEFENSIVO.getPosx())); //0.025*d __ distancia entre caniones

            for(float t2 = 0; ; t2 += 0.05){
                xd = -DEFENSIVO.getVelx()*t2;
                yd = DEFENSIVO.getPosy() + DEFENSIVO.getVely()*t2 - (0.5*G*t2*t2);
                float t = t2;
                xo = OFENSIVO.getVelx()*t;
                yo = OFENSIVO.getPosy() + OFENSIVO.getVely()*t - (0.5*G*t*t);





                //Verificar impacto
                //comprobar que este en el radio de impacto
                //distancia entre dos puntos (bala y DEFENSIVO) < radio de explosion
                if(sqrt(pow((xo - xd),2)+pow((yo - yd),2)) < OFENSIVO.getR()){
                    if(yd<0) yd = 0;
                    cout << "Lanzamiento Defensivo #"<<flag+1<<endl;
                    ImprimirResultados(DEFENSIVO.getAng(), DEFENSIVO.getVel(), xd, yd, t2);
                    ImprimirResultados(OFENSIVO.getAng(), OFENSIVO.getVel(), xo, yo, t);

                    flag++;
                    angulo += 5;
                    velocidad += 10;
                    break;
                }
                if(yd < 0){
                    break;
                }
            }
            if(flag == 3) break;
        }
        if(flag == 3) break;
    }
    return true;

}




