#include "uart.h"
#include "motor_control.h"
#include "adc_demo.h"

void main(void) {
//    uart_init();
   // say_hello("CS107e");
 //   test_motor();
    // joy_demo();
  gpio_init();
  uart_init();
  mcp3008_init();
    gpio_set_input(limit_switches.limit_switch_1);
    gpio_set_input(limit_switches.limit_switch_2);
    gpio_set_input(limit_switches.limit_switch_3);
    gpio_set_input(limit_switches.limit_switch_4);

  //gpio_set_input(GPIO_PB7);

  while(1) {
    //int button = gpio_read(GPIO_PB7); 
    // joy_motor_x();
    // joy_motor_z();
    // int button = read_button();
    // // if (button == 1){
    // //   grab();

    // //   break;
    // // }

        int state1 = gpio_read(limit_switches.limit_switch_1);
        int state2 = gpio_read(limit_switches.limit_switch_2);
        int state3 = gpio_read(limit_switches.limit_switch_3);
        int state4 = gpio_read(limit_switches.limit_switch_4);

        // Print out the states
        printf("Limit Switch 1: %d\n", state1);
        printf("Limit Switch 2: %d\n", state2);
        printf("Limit Switch 3: %d\n", state3);
        printf("Limit Switch 4: %d\n", state4);
    
  }
}
