#ifndef __PUNTO_H__
#define __PUNTO_H__


class Punto{
    public:
        Punto(float x, float y) { this->x = x; this->y = y; }
        float X() { return x; }
        float Y() { return y; }

    private:
        float x;
        float y;
};

#endif // __PUNTO_H__
