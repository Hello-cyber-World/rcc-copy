// Include any libs we need for this program
#include "rcc_stdlib.h"
using namespace std;

typedef enum{
    WAIT,
    INCREMENT,
    RESET
} state_t;

int main(){
    stdio_init_all();
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1);
    rcc_init_i2c
    rcc_init_i2c

    int state = 0
    // Timing variables
    state_t state=WAIT;
    uint32_t cur_time = 0;
    uint32_t prev_time = 0;
    int servo_pos = 0;
    uint32_t dt= 1000000;

    while(true)
    //state0
    cur_time = time_us_

    switch(state){
            case wait:
            //do nothing
            cout<< "WAITING!\n";
            //Check transition conditions
            if(cur_time - prev_time >= dt){
                state = INCREMENT ;
            }
            break;
        case INCREMENT:
            //switch state of LED
            servo_pos = servo_pos + 1;
            ServoPosition(&s3, servo_pos);
            //Check transition conditions
            if(servo_pos)

    }
}