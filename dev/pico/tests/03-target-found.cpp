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
    ServoOn(&s3); //Servo motor (line 4-15)

    Motor motors;
    MotorInit(&motors, RCC_ENB, RCC_ENA, 1000);
    MotorsOn(&motors);

    rcc_init_i2c(); //sensor operating info (lidar sensor)

    Left_Odom left; //class=c
    Right_Odom right;

    VL53L0X lidar; //c
    rcc_init_lidar(&lidar); //setup lidar (i2c1)

    int positions[100]; //array for servo positions

    for (int i = 0; i < 100; ++i) {
        positions[i] = i;  //filling array 0-99
    }

    int i = 0; 
    uint16_t distance1; 
    uint16_t distance2;
    bool searching = false;
    bool stop = false;

    while(true) {   

        if(!gpio_get(RCC_PUSHBUTTON))
        {
            searching = true;
        }

        distance1 = getFastReading(&lidar); //want to always check
        distance2 = getFastReading(&lidar); 

        if(searching){
            if(distance1 >= 200){
                ServoPosition(&s3, positions[i]);
                sleep_ms(100);
                i++;
                if (i >= 100){
                    i = 0; //reset counter
                }
            }
            else{ //distance1 less than 200

                if (i <= 50){  //object was on left
                    ServoPosition(&s3, 50); //forwards
                    MotorPower(&motors, 50, -50); //turn left
                    if (distance2 <= 200){
                        stop = true;
                        cout<<"leffft\n";
                    }
                }
                else{ //object was on right
                    ServoPosition(&s3, 50);
                    MotorPower(&motors, -50, 50); //turn right
                    if (distance2 <= 200){
                        stop = true;
                        cout<<"righttt\n";
                        /*
                        
                        line 60-81 motor sensing and turning
                        
                        */
                    }
                }

            }
        }
        
        if(stop){
            MotorPower(&motors, 0,0); //permanently stop
            cout<<"stop\n";
        }
    }

}