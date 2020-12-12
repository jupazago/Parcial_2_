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
    int r;

public:
    //Constructores
    Canion();
    Canion(double x, double y);

    double getPosx() const;
    void setPosx(double value);
    double getPosy() const;
    void setPosy(double value);
    double getVel() const;
    void setVel(double value);
    double getAng() const;
    void setAng(double value);
    double getVelx() const;
    void setVelx(double value);
    double getVely() const;
    void setVely(double value);
    int getR() const;
    void setR(int value);
};

#endif // CANION_H
