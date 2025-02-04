#ifndef ADC_DEMO_H
#define ADC_DEMO_H

#include "assert.h"
#include "uart.h"
#include "mcp3008.h"
#include "printf.h"
#include "strings.h"
#include "timer.h"


static const int MAX_VALUE = 1024;

#define STRINGIFY_IMPL(x) #x
#define AS_STRING(x) STRINGIFY_IMPL(x)
#define ANSI_ESC(n) "\e[" AS_STRING(n) "m"

#define RED     ANSI_ESC(41)
#define GREEN   ANSI_ESC(42)
#define YELLOW  ANSI_ESC(43)
#define BLUE    ANSI_ESC(44)
#define MAGENTA ANSI_ESC(45)
#define CYAN    ANSI_ESC(46)
#define WHITE   ANSI_ESC(47)
#define NORMAL  ANSI_ESC(0)


static void print_analog_scale(int val, const char *label, const char *color);
static void print_dashboard(int vert, int horiz);
void joy_demo(void);

#endif
