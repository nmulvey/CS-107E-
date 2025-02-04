#include "motor_control.h"
#include "printf.h"
#include "assert.h"
#include "uart.h"
#include "mcp3008.h"
#include "strings.h"
#include "timer.h"

const limit_switches_t limit_switches = {
    .limit_switch_1 = GPIO_PB7,  //limit switch on left side
    .limit_switch_2 = GPIO_PD17, //limit switch on right side <-- working
    .limit_switch_3 = GPIO_PD15, //limit switch on motor
    .limit_switch_4 = GPIO_PE16
};


const motor_axes_t motor = {
    .x_axis = { .positive = GPIO_PC0, .negative = GPIO_PB2 },
    .y_axis = { .positive = GPIO_PD21, .negative = GPIO_PD22 },
    .z_axis = { .positive = GPIO_PC1, .negative = GPIO_PD14 }
};

void test_motor() {
    gpio_set_output(GPIO_PC0);
    gpio_set_output(GPIO_PB2);
    gpio_write(GPIO_PC0, 0);
    gpio_write(GPIO_PB2, 1);
    timer_delay_ms(1500);
    gpio_write(GPIO_PB2, 0);
}


void test_motor_rev() {
    gpio_set_output(GPIO_PC0);
    gpio_set_output(GPIO_PB2);
    gpio_write(GPIO_PC0, 1);
    gpio_write(GPIO_PB2, 0);
    timer_delay_ms(1500);
    gpio_write(GPIO_PC0, 0);
}

/* Left: x < 12 && 300 < y < 900
 * Right: x > 1020 && 300 < y < 900
 * Up: 300 < x < 900 && y < 12
 * Down: 300 < x < 900 && y > 1020
 * */


/*red and green cables control motor along x axis
 * red is defined as +, green as -*/
void joy_motor_x(){

    gpio_set_output(motor.x_axis.positive);
    gpio_set_output(motor.x_axis.negative);

    int joy_x = mcp3008_read(1);
    int joy_y = mcp3008_read(2);

    if (joy_x < 30 && (300 < joy_y && joy_y < 900)){ //Move left
        printf("moving left\n");
        gpio_write(motor.x_axis.positive, 1);
        gpio_write(motor.x_axis.negative, 0);
        timer_delay_ms(100);

    } else if (joy_x > 1020 && (300 < joy_y && joy_y < 900)){ //Move right
        gpio_write(motor.x_axis.positive, 0);
        gpio_write(motor.x_axis.negative, 1);
        timer_delay_ms(100);
    }
    
    //0,0 state, turn motor off
    gpio_write(motor.x_axis.positive, 0);
    gpio_write(motor.x_axis.negative, 0);
}


void joy_motor_z(){

    gpio_set_output(motor.z_axis.positive);
    gpio_set_output(motor.z_axis.negative);

    int joy_x = mcp3008_read(1);
    int joy_y = mcp3008_read(2);
    
    printf("x : %d, y: %d\n", joy_x, joy_y);
    if (joy_y < 30 && (300 < joy_x && joy_x < 900) ){ //Move left
   //     printf("moving left\n");
        gpio_write(motor.z_axis.positive, 1);
        gpio_write(motor.z_axis.negative, 0);
        timer_delay_ms(100);

    } else if (joy_y > 1020 && (300 < joy_x && joy_x < 900)){ //Move right
    //    printf("moving right\n");
        gpio_write(motor.z_axis.positive, 0);
        gpio_write(motor.z_axis.negative, 1);
        timer_delay_ms(100);
    }
    
    //0,0 state, turn motor off
    gpio_write(motor.z_axis.positive, 0);
    gpio_write(motor.z_axis.negative, 0);
}

void grab() {
    gpio_set_output(motor.y_axis.positive);
    gpio_set_output(motor.y_axis.negative);

    //time the claw descent 
    gpio_write(motor.y_axis.positive, 1);
    gpio_write(motor.y_axis.negative, 0);
    timer_delay_ms(1500);

    //return to start position with grabbed object
    gpio_write(motor.y_axis.positive, 0);
    gpio_write(motor.y_axis.negative, 1);
    timer_delay_ms(1500);

    //turn motors off
    gpio_write(motor.y_axis.positive, 0);
    gpio_write(motor.y_axis.negative, 0);
}

void test_read_button() {
    gpio_set_input(GPIO_PB7);
    int button_press = gpio_read(GPIO_PB7); 
    printf("Button : %d \n", button_press);
    timer_delay_ms(50);
}

int read_button() {
    int analog_read = mcp3008_read(0); 
    int button = 0; 
    printf ("Analog Read: %d\n", analog_read);
    if (analog_read < 900) { //current that I read on comp
      button = 1;
    }
    return button;
}

void say_hello(const char *name) {
    printf("Hello, %s!\n", name);
}

