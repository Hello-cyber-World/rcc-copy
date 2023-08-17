#include "rcc_stdlib.h"
using namespace std;

int state;
uint32_t cur;
uint32_t s0enter, s1enter, s2enter, sFWDenter, sRightenter, sLeftenter; //Timing variables
uint32_t dt0=10000000; //1 second duration
uint32_t dt1=30000000; //3 second duration


int main() {

stdio_init_all();    
sleep_ms(1500);
cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);

    rcc_init_pushbutton();

    Motor motors;
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000);
    MotorsOn(&motors);
    printf("AFTER MOTORS");

    Left_Odom left;
    Right_Odom right;
    printf("AFTER ODOM");

    int left_count = 0;
int right_count = 0;
float scale_factor = 1.2; 
int base_power = 50;

    //Initializations

    //might be important... stdio_init_all();

    //initialize our timing variable
    cur = time_us_32();
    s0enter = s1enter = s2enter = cur;
    while(true) {
        //update current time
        cur = time_us_32();
        //State 0
        if(state == 0) { 
            if(cur - s0enter >= dt0) { state = 1; s1enter = cur; }
        }
        //State 1
        if(state == 1) {
            cout << "Calculate control\n";

            if(cur - s1enter >= dt1){ state = 2; s2enter = cur; }
        }
        //State 2
        if(state == 2) {
            cout <<"SPIN CCW\n";
            if(cur - s2enter >= dt1) { state = 1; s1enter = cur;}
        }
    }




while(true) {
        //update current time
        cur = time_us_32();
        //State FWD
        if(state == FWD) { 

        if(!gpio_get(RCC_PUSHBUTTON))
        {
            MotorPower(&motors, static_cast<int>(base_power*scale_factor), base_power);
            cout << "Messi\n";
        }

        if(left_count >= 200 && right_count >= 200){
            MotorPower(&motors, 0, 0); 
            cout << "Messi is the goat\n";
        }
            if(cur - sFWDenter >= dt0) { state = Right; sRightenter = cur; }
        }


        //State Right
        if(state == Right) {
            cout << "SPIN CW\n";
        
            if(cur - s1enter >= dt1){ state = 2; s2enter = cur; }
        }


        //State Left
        if(state == Left) {
            cout <<"SPIN CCW\n";
            if(cur - s2enter >= dt1) { state = 1; s1enter = cur;}
        }
    }
}


int main()
{
/*    stdio_init_all();    
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0,1);

    rcc_init_pushbutton();                   */

    Servo s3;
    ServoInit(&s3, 18, false, 50);
    ServoOn(&s3);

    Motor motors;
    MotorInit(&motors, RCC_ENB, RCC_ENA, 1000);
    MotorsOn(&motors);

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

    state_t state = WAIT;

    while(true) {   
        print_state(state); 

        if(!gpio_get(RCC_PUSHBUTTON))
        {
            state = SEARCHING;
        }

        distance = getFastReading(&lidar); 

        switch(state){
            case WAIT:
                MotorPower(&motors, 0, 0); //stop
                if(distance > 200){
                    state = SEARCHING;
                }
            break;

            case SEARCHING:
                ServoPosition(&s3, positions[i]);
                sleep_ms(100);
                i++;
                if (i >= 100){
                    i = 0; //reset counter
                }
                //transition condition
                if(distance <= 200){
                    state = FOUND;
                }
                break;

            case FOUND:
                ServoPosition(&s3, 50);
                if (i <= 50){  //object was on left
                    state = ROTATING_L;
                }
                else{ //object was on right
                    state = ROTATING_R;
                }
                break;

            case ROTATING_L:
                MotorPower(&motors, -50, 50); //rotate left
                if(distance <= 200){
                    state = APPROACHING;
                }
                break;

            case ROTATING_R:
                MotorPower(&motors, 50, -50); //rotate right
                if(distance <= 200){
                    state = APPROACHING;
                }
                break;

            case APPROACHING:
                MotorPower(&motors, 50, 50); //forwards
                if(distance <= 100){
                    state = WAIT;
                }
                break;

        }


    }

}