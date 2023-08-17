#include "rcc_stdlib.h"
using namespace std;

int main()
{
    stdio_init_all();
    sleep_ms(1000);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1); 

    Left_Odom left; 
    Right_Odom right; 
    
    while(true)
    {
        int left_count = left.getCount(); 
        int right_count = right.getCount();

        cout << left_count << " | " << right_count << "\n";
        sleep_ms(100);
    }
}