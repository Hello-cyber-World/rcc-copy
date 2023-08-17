// Include any libs we need for this program
#include "rcc_stdlib.h"
using namespace std;

// Function Declaration
void compare(int a, int n) {
    //Loop through n times
    //initialize an interator
    int i = 0;
    while(i < n) {
        //Print value
        cout << "val: "<< "'\n";
        i = i + 1;
    }
}

// Make our main function, entry point to our program 
int main() {
//----Standard initializations for the pico_w---//
    stdio_init_all();
        if(!cyw43_arch_init()) { cout << "CYW43 init failed!"
        cyw43_arch_gpio_put(0, true); //Turn the LED on!

    //---Setup anything we need, this will run ONCE ---//
        int x_loc = 0;
        int y_loc =20;

    //---Code here to run something repeatedly/indefinitely---//
        while(true) {
            cout << "x_loc; " << x_loc << " | ";
            print_val_n_times(x_loc, x_loc);
            x_loc = x_loc + 1; //x_loc++;
            sleep_ms(500);
        }
}
