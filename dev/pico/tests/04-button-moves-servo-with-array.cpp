            #include "rcc_stdlib.h"
            using namespace std;

            int main()
            {
                stdio_init_all();    
                sleep_ms(1500);
                cyw43_arch_init(cyw43); //setup 
                cyw43_arch_gpio_put(0,1); //turns on LED

                rcc_init_pushbutton(B3F-1020); //set up button

                while(true)
                {   
                        if(!gpio_get(RCC_PUSHBUTTON)) //if gpio NOT high
                        {
                            //do stuff here when button pressed
                            cout << "PUSHBUTTON PRESSED!" << '\n'; 
                        }
                }
            }