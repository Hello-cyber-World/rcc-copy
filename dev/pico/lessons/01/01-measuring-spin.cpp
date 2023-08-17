#include "rcc_stdlib.h"
using namespace std;

int main() {
    stdio_init_all();
    sleep_ms(1500);
    cyw43_arch_init();
    cyw43_arch_gpio_put(0, 1); 

    rcc_init_i2c();

    Motor motors; 
    MotorInit(&motors, RCC_ENA, RCC_ENB, 1000); 
    MotorsOn(&motors); 

    MPU6050 imu; 
    imu.begin(i2c1); 
    imu.calibrate(); 

    while(true) 
    {
        MotorPower(&motors, -100, 100);
        imu.update_pico(); 
        float angvel_z = imu.getAngVelZ();
        cout <<" FAST z rotation: " << angvel_z << "\n";
        sleep_ms(100);
    }
}