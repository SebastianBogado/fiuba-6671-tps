#ifndef BASEBERSTEIN_H
#define BASEBERSTEIN_H


class BaseBerstein
{
    public:
        BaseBerstein();
        float evaluar(int base,float x);
		float evaluarDerivada(int base, float x);
        virtual ~BaseBerstein();
    protected:
    private:
        float base0(float x);
        float base1(float x);
        float base2(float x);
        float base3(float x);

		float baseDer0(float x);
		float baseDer1(float x);
		float baseDer2(float x);
		float baseDer3(float x);
};

#endif // BASEBERSTEIN_H
