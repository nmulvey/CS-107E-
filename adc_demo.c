/* File: adc_demo.c
 * ---------------
 * SPI + MCP3008 adc test
 *
 * Breadboard configured for analog inputs:
 * 2-axis joystick channels 0/1
 * Photoresistor channel 6
 * Force sensor channel 7
 */
#include "adc_demo.h"

static void print_analog_scale(int val, const char *label, const char *color) {
    assert(val <= MAX_VALUE);
    int quanta = 30;
    int on_quantized = val/quanta;
    int off_quantized = MAX_VALUE/quanta - on_quantized;
    char buf_on[on_quantized+1];
    char buf_off[off_quantized+1];
    memset(buf_off, ' ', sizeof(buf_off));
    memset(buf_on, '-', sizeof(buf_on));
    buf_on[sizeof(buf_on)-1] = '\0';
    buf_off[sizeof(buf_off)-1] = '\0';
    printf("%12s [%s%s%s%s]", label, color, buf_on, NORMAL, buf_off);
}

static void print_dashboard(int vert, int horiz){
    printf("\f\n     mcp3008 Readings  \n\n");
    printf("x : %d, y : %d\n", horiz, vert);
  //  print_analog_scale(vert, "Joy vert", CYAN);
  //  print_analog_scale(horiz, "Joy horiz", GREEN);
}

void joy_demo(void)  {
    gpio_init();
    uart_init();
    mcp3008_init();
    printf("Starting program %s\n\n", __FILE__);

    while (1) {
        int joy_x = mcp3008_read(0);
        int joy_y = mcp3008_read(1);
        print_dashboard(joy_x, joy_y);

        timer_delay_ms(100);
    }
}
