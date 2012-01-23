#ifndef BASEBERSTEIN_H
#define BASEBERSTEIN_H


class BaseBerstein
{
    public:
        BaseBerstein();
        float evaluar(int base,float x);
        virtual ~BaseBerstein();
    protected:
    private:
        float base0(float x);
        float base1(float x);
        float base2(float x);
        float base3(float x);
};

#endif // BASEBERSTEIN_H
