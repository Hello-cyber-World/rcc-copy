#include "rcc_stdlib.h"
using namespace std;
int addition(int a, int b)
{
    return (a + b);
}
//return (c+d) function(007) (find_hypotenuse_){
// +=
// 



int main(void)
{
    stdio_init_all();

    if(cyw43_arch_init())
    {
        cout << "CYW43 init failed!" << "\n";
    }

    cyw43_arch_gpio_put(0, 1);
    for(int i= 0; i<100; i++)
    {
    	printf("Hello World\n");    
    	sleep_ms(100);
    }
}
