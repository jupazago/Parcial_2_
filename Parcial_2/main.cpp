#include <iostream>
#include <canion.h>
#include <math.h>
#define G 9.81
#define pi 3.141617

using namespace std;

Canion llenar_datos(int opcion);

void ImprimirResultados(int anglulo,int velocidad, float x, float y, float t);

void DisparoOfensivo(Canion OFENSIVO, Canion DEFENSIVO, int seleccion);
void DisparoDefensivo(Canion OFENSIVO, Canion DEFENSIVO, float Limite_tiempo);
void DisparoNeutral(Canion OFENSIVO, Canion DEFENSIVO, float Limite_tiempo);

int main()
{
    cout << "       Sistema de simulacion       " << endl;
    cout << "-----------------------------------" << endl;

    Canion OFENSIVO = llenar_datos(1);
    Canion DEFENSIVO = llenar_datos(2);

    cout << "                     X  Y"<<endl;
    cout << "Canion #1 : ( "<<OFENSIVO.getPosx() << "   , "<< OFENSIVO.getPosy()<<" )"<<endl;
    cout << "Canion #2 : ( "<<DEFENSIVO.getPosx() << " , "<< DEFENSIVO.getPosy()<<" )"<<endl;

    //Decide de donde a donde se dispara, ubicandolos en el plano cartesiano
    if(OFENSIVO.getPosx() < DEFENSIVO.getPosx()){
        DisparoOfensivo(OFENSIVO, DEFENSIVO, 1);
    }else{
        DisparoOfensivo(OFENSIVO, DEFENSIVO, 2);
    }

    cout << endl<< endl;
    return 0;
}


Canion llenar_datos(int opcion){

    //float posx, posy;
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
        Canion canio(800, 50);
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

void DisparoOfensivo(Canion OFENSIVO, Canion DEFENSIVO, int seleccion){
    int flag = 0;
    float x = 0.0;
    float y = 0.0;

    if(seleccion == 1){

        for(int angulo = 1; angulo < 90 ; angulo++){
            OFENSIVO.setAng(angulo);//Angulo
            for(float velocidad = 50; velocidad < 100 ; velocidad += 5){
                OFENSIVO.setVel(velocidad);
                OFENSIVO.setVelx(velocidad*cos(OFENSIVO.getAng()*pi/180));  //Vellocidad X
                OFENSIVO.setVely(velocidad*sin(OFENSIVO.getAng()*pi/180));  //Vellocidad Y
                OFENSIVO.setR(0.05*(DEFENSIVO.getPosx())); //0.05*d __ distancia entre caniones
                x = 0.0;
                y = 0.0;
                for(float t = 0; ; t+= 0.05){
                    x = OFENSIVO.getVelx()*t;
                    y = OFENSIVO.getPosy()+ OFENSIVO.getVely()*t -(0.5*G*t*t);
                    //y += DEFENSIVO.getPosy();
                    //Verificar impacto
                    //comprobar que este en el radio de impacto
                    //distancia entre dos puntos (bala y DEFENSIVO) < radio de explosion
                    if(sqrt(pow((DEFENSIVO.getPosx() - x),2)+pow((DEFENSIVO.getPosy() - y),2)) < OFENSIVO.getR()){
                        if(y<0) y = 0;
                        cout << endl<<endl<<endl;
                        cout << "--------------------------------------"<<endl;
                        cout << "Lanzamiento Ofensivo #"<<flag+1<<endl;
                        cout << "--------------------------------------"<<endl;
                        cout << "-------Prediccion de lanzamiento------"<<endl;
                        cout << "--------------------------------------"<<endl;
                        ImprimirResultados(OFENSIVO.getAng(), OFENSIVO.getVel(), x, y, t);
                        cout << "--------------------------------------"<<endl;
                        //Creamos la reaccion DEFENSIVA
                        if(t>2){
                            //3 disparos defensivos
                            DisparoDefensivo(OFENSIVO, DEFENSIVO, t);

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
    }else if (seleccion == 2) {
        Canion OFENSIVO1(OFENSIVO.getPosx(), DEFENSIVO.getPosy());
        Canion DEFENSIVO1(DEFENSIVO.getPosx(), OFENSIVO.getPosy());

        for(int angulo = 1; angulo < 90 ; angulo++){
            OFENSIVO1.setAng(angulo);//Angulo
            for(float velocidad = 50; velocidad < 100 ; velocidad += 5){
                OFENSIVO1.setVel(velocidad);
                OFENSIVO1.setVelx(velocidad*cos(OFENSIVO1.getAng()*pi/180));  //Vellocidad X
                OFENSIVO1.setVely(velocidad*sin(OFENSIVO1.getAng()*pi/180));  //Vellocidad Y
                OFENSIVO1.setR(0.05*(DEFENSIVO.getPosx())); //0.05*d __ distancia entre caniones
                x = 0.0;
                y = 0.0;
                for(float t = 0; ; t+= 0.05){
                    x = OFENSIVO1.getVelx()*t;
                    y = OFENSIVO1.getPosy()+ OFENSIVO1.getVely()*t -(0.5*G*t*t);
                    //y += DEFENSIVO1.getPosy();
                    //Verificar impacto
                    //comprobar que este en el radio de impacto
                    //distancia entre dos puntos (bala y DEFENSIVO) < radio de explosion
                    if(sqrt(pow((DEFENSIVO1.getPosx() - x),2)+pow((DEFENSIVO1.getPosy() - y),2)) < OFENSIVO1.getR()){
                        if(y<0) y = 0;
                        cout << endl<<endl<<endl;
                        cout << "--------------------------------------"<<endl;
                        cout << "Lanzamiento Ofensivo #"<<flag+1<<endl;
                        cout << "--------------------------------------"<<endl;
                        cout << "-------Prediccion de lanzamiento------"<<endl;
                        cout << "--------------------------------------"<<endl;
                        ImprimirResultados(OFENSIVO1.getAng(), OFENSIVO1.getVel(), x, y, t);
                        cout << "--------------------------------------"<<endl;

                        //Creamos la reaccion DEFENSIVA
                        if(t>2){
                            //3 disparos defensivos
                            DisparoDefensivo(OFENSIVO1, DEFENSIVO1, t);
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
}

void DisparoDefensivo(Canion OFENSIVO, Canion DEFENSIVO, float Limite_tiempo){

    float xo = 0.0;
    float yo = 0.0;
    float xd = 0.0;
    float yd = 0.0;
    int flag = 0;

    //Generar disparo defensivo
    for(int angulo = 180; angulo > 90 ; angulo--){
        DEFENSIVO.setAng(angulo); //Angulo
        for(float velocidad = 50; velocidad < 100 ; velocidad += 5){
            DEFENSIVO.setVel(velocidad);
            DEFENSIVO.setVelx(velocidad*cos(DEFENSIVO.getAng()*pi/180));  //Vellocidad X
            DEFENSIVO.setVely(velocidad*sin(DEFENSIVO.getAng()*pi/180));  //Vellocidad Y
            DEFENSIVO.setR(0.025*(DEFENSIVO.getPosx())); //0.025*d __ distancia entre caniones

            for(float t2 = 0; t2<Limite_tiempo ; t2 += 0.05){
                xd = (DEFENSIVO.getVelx()*t2)+DEFENSIVO.getPosx();
                yd = DEFENSIVO.getPosy() + DEFENSIVO.getVely()*t2 - (0.5*G*t2*t2);
                float t = t2+2;
                xo = OFENSIVO.getVelx()*t;
                yo = OFENSIVO.getPosy() + OFENSIVO.getVely()*t - (0.5*G*t*t);
                //Verificar impacto
                //comprobar que este en el radio de impacto
                //distancia entre dos puntos (bala y DEFENSIVO) < radio de explosion
                if(sqrt(pow((xo - xd),2)+pow((yo - yd),2)) <= OFENSIVO.getR()){
                    if(yd<0) yd = 0;
                    cout <<endl<< "***Lanzamiento Defensivo #"<<flag+1 ;
                    cout << "  - Datos prediccion de explosion entre caniones "<<endl<<endl;
                    cout << "Canion Defensivo:"<<endl;
                    ImprimirResultados(DEFENSIVO.getAng(), DEFENSIVO.getVel(), xd, yd, t2);
                    cout <<endl;
                    cout << "Canion Ofensivo:"<<endl;
                    ImprimirResultados(OFENSIVO.getAng(), OFENSIVO.getVel(), xo, yo, t);
                    cout << "--------------------------------------"<<endl;
                    cout << "--------------------------------------"<<endl;
                    cout << "--------------------------------------"<<endl;

                    //Creamos la reaccion NEUTRALIZAR
                    if(t>1){
                        //3 disparos NEUTRALES
                        DisparoNeutral(OFENSIVO, DEFENSIVO, t2);

                    }

                    flag++;
                    angulo -= 5;
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

}

void DisparoNeutral(Canion OFENSIVO, Canion DEFENSIVO, float Limite_tiempo){

    float xo = 0.0;
    float yo = 0.0;
    float xd = 0.0;
    float yd = 0.0;
    int flag = 0;



    //Generar disparo NEUTRAL
    for(float angulo = 1; angulo < 90 ; angulo+=0.5){
        OFENSIVO.setAng(angulo);
        for(float velocidad = 600; velocidad < 1200 ; velocidad += 1){
            OFENSIVO.setVel(velocidad); //Angulo
            OFENSIVO.setVelx(velocidad*cos(OFENSIVO.getAng()*pi/180));  //Vellocidad X
            OFENSIVO.setVely(velocidad*sin(OFENSIVO.getAng()*pi/180));  //Vellocidad Y
            OFENSIVO.setR(0.005*(DEFENSIVO.getPosx())); //0.005*d __ distancia entre caniones

            for(float t2 = 0; t2<Limite_tiempo ; t2 += 0.025){
                xo = OFENSIVO.getVelx()*t2;
                yo = OFENSIVO.getPosy() + OFENSIVO.getVely()*t2 - (0.5*G*t2*t2);
                float t = t2+1;
                xd = (DEFENSIVO.getVelx()*t)+DEFENSIVO.getPosx();
                yd = DEFENSIVO.getPosy() + DEFENSIVO.getVely()*t - (0.5*G*t*t);
                //Verificar impacto
                //comprobar que este en el radio de impacto
                //distancia entre dos puntos (Neutralizador y DEFENSIVO) < radio de explosion
                if(sqrt(pow((xo - xd),2)+pow((yo - yd),2)) <= OFENSIVO.getR()){
                    if(yd<0) yd = 0;
                    cout <<endl<< "***Impacto Neutralizador VS Defensa"<<endl<<endl;
                    cout << "Canion Defensivo:"<<endl;
                    ImprimirResultados(DEFENSIVO.getAng(), DEFENSIVO.getVel(), xd, yd, t);
                    cout <<endl;
                    cout << "Canion Neutralizador:"<<endl;
                    ImprimirResultados(OFENSIVO.getAng(), OFENSIVO.getVel(), xo, yo, t2);
                    cout << "--------------------------------------"<<endl;
                    cout << "--------------------------------------"<<endl;
                    cout << "--------------------------------------"<<endl;
                    flag++;
                    angulo += 5;
                    velocidad += 10;
                    break;
                }
                if(yd < 0) break;
            }
            if(flag == 3) break;
        }
        if(flag == 3) break;
    }
}








