#include "rcc_stdlib.h"
using namespace std;

typedef enum{
    SEARCHING,   //0
    FIRE, //1
} state_t;

void print_state(state_t state){
    cout << state << '\n';
}

int main()
{
    stdio_init_all();    
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);
    gpio_init(RCC_ACTUATOR_PIN);
    gpio_set_dir(RCC_ACTUATOR_PIN, true);
   
    rcc_init_pushbutton();
    rcc_init_actuator_gpio();
    gpio_put(RCC_ACTUATOR_PIN, false);
    gpio_put(RCC_ACTUATOR_PIN, true);

    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);

    rcc_init_i2c();

    Left_Odom left;
    Right_Odom right;

    VL53L0X lidar;
    rcc_init_lidar(&lidar);


    int positions[100]; //array for servo positions

    for (int i = 0; i < 100; ++i) {
        positions[i] = i;  //filling array 0-99
    }

    int i = 0;
    uint16_t distance;

    state_t state = SEARCHING;

    while(true) {   
        print_state(state); 
        // gpio_put(RCC_ACTUATOR_PIN, true);

        // if(!gpio_get(RCC_PUSHBUTTON))
        // {
        //     state = SEARCHING;
        // }

        distance = getFastReading(&lidar); 

        switch(state){
            case SEARCHING:
                ServoPosition(&s3, positions[i]);
                sleep_ms(100);
                i++;
                if (i >= 100){
                    i = 0; //reset counter
                }
                //transition condition
                if(distance <= 200){
                    state = FIRE;
                }
                break;

            case FIRE:
                gpio_put(RCC_ACTUATOR_PIN, true);
                if(true){
                    state = SEARCHING;
                } 
                break;
        }


    }

}