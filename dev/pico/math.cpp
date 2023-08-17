#include "rcc_stdlib.h"
using namespace std;

double addition(double a, double b)
{
    return (a + b);
}

double main(void)
{
    studio_init_all();

    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }

    cyw43_arch_gpio_put(0, 1);
    
    double x=9;
    double y=10;

    double result =divide(x,y)

    while (true) 
    {printf("%d\n", divide)
    sleep_ms(100)}

}
