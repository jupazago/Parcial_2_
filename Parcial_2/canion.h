#ifndef CANION_H
#define CANION_H


class Canion
{
    double posx;
    double posy;
    double vel;
    double ang;
    double velx;
    double vely;
    const double g = 9.8;
    int r;

public:
    Canion();
    Canion(double x, double y,double v, double a);
};

#endif // CANION_H
