#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <gpio.h>
  
typedef struct {
    gpio_id_t positive;  // GPIO pin controlling the positive 
    gpio_id_t negative;  // GPIO pin controlling the negative 
} gpio_pair_t;

typedef struct {
    gpio_pair_t x_axis;
    gpio_pair_t y_axis;
    gpio_pair_t z_axis;
} motor_axes_t;

typedef struct {
    gpio_id_t limit_switch_1;
    gpio_id_t limit_switch_2;
    gpio_id_t limit_switch_3;
    gpio_id_t limit_switch_4;
} limit_switches_t;

extern const limit_switches_t limit_switches;
extern const motor_axes_t motor;


void say_hello(const char *name);
void test_motor();
void test_motor_rev();
void test_read_button(); 

int read_button(); 
void joy_motor_x();
void joy_motor_z();
void grab();


#endif
