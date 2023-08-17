#include "rcc_stdlib.h"
using namespace std;

void blink_led(int time)
{  
sleep_ms(1500);
cyw43_arch_gpio_put(0,!cyw43_arch_gpio_get(0));
sleep_ms(time);
}

int main()
{
    stdio_init_all();
    sleep_ms(100);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1);
    sleep_ms(1000);

    while(true)
    {
        blink_led(300);
        cout << "Messi is not the goat\n";
    }
}