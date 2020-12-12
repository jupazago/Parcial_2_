#include "canion.h"

double Canion::getPosx() const
{
    return posx;
}

void Canion::setPosx(double value)
{
    posx = value;
}

double Canion::getPosy() const
{
    return posy;
}

void Canion::setPosy(double value)
{
    posy = value;
}

double Canion::getVel() const
{
    return vel;
}

void Canion::setVel(double value)
{
    vel = value;
}

double Canion::getAng() const
{
    return ang;
}

void Canion::setAng(double value)
{
    ang = value;
}

double Canion::getVelx() const
{
    return velx;
}

void Canion::setVelx(double value)
{
    velx = value;
}

double Canion::getVely() const
{
    return vely;
}

void Canion::setVely(double value)
{
    vely = value;
}

int Canion::getR() const
{
    return r;
}

void Canion::setR(int value)
{
    r = value;
}

Canion::Canion()
{

}

Canion::Canion(double x, double y)
{
    posx= x;
    posy= y;
}
