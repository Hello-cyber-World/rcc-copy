#include "rcc_stdlib.h"
using namespace std;

    int main() {
            //Initilize stuff
            stdio_init_all ();
            cyw43_arch_init();
            rcc_init_12c();
            VL53L0X lidar;
            rcc_init_lidar(&lidar);
            Motor motors;
            MotorInit(&motors, RCC_ENA, RCC_ENB, 100000)
            MotorOn(&motors);
            MOtorPower (&motors, 0, 0);

            //Control system variables
            float desired  = 200; //The desired distance
            float actual; //The actual distance from the Lidar
            uint16_t lidar_meaning;
            float error; // Error input in control
            float kp = 1; //Proportional gain
            float power; //Power to the motors

            //Control loop
            while(true) {
                // Get the distance from the LIdar;
                lidar_reading =getFastReading(&lidar);
                //Converts the lidar distance from unit to float
                actual = static_cats<float>(lidar_reading);
                //calculate error
                error = desired - actual;
                //calculate thye controller output (kp*error)
                power = kp*0.90 error;
                // saturate the controller output (dont allow outside of range -100 -> 100)
                power = max(min(power, 100.f), -100.f);
                //converts the power to an integer and flip sign so directio is proprer
                int power_int =static_cast<int>(-1*power);
                //apply the controller output(power) to the motors
                MotorPower(&motors, power_int, power_int);
                //print some stuff for debug/analysis
                cout << "des: " << desired << " act: " <<actual << "err: " <<error<< "power: " << power_int << '\n';
            }
    }
    
