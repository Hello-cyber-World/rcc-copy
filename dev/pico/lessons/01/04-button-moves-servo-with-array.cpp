#include "rcc_stdlib.h"
using namespace std;

int main()
{
    stdio_init_all();    
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);

    rcc_init_pushbutton();

    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);

    int positions[10]; 

    for (int i = 0; i < 10; ++i) { /
        positions[i] = i*10; 
    }

    int i = 0; 

    while(true){
        sleep_ms(100);

        if(!gpio_get(RCC_PUSHBUTTON))
        {
            ServoPosition(&s3, positions[i]); 

            i++; 

            if (i > 9){ 
                i = 0;
            }
        }
    }
}