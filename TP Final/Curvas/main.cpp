#include <iostream>
#include "TestBaseBSpline.h"
#include "TestBSpline.h"
#include "TestBaseBerstein.h"
#include "TestBezier.h"
#include <glm/glm.hpp>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    TestBaseBSpline testBase;
    TestBSpline testCurva;
    TestBaseBerstein testBBerstein;
    TestBezier testCurvaBezier;

    testBase.iniciar();
    testCurva.iniciar();

    testBBerstein.iniciar();
    testCurvaBezier.iniciar();

	int i; cin >> i;

    return 0;
}
