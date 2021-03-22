#include "gpio.h"

/***************************** GPIO *******************************************/

/* Default constructor for GPIO
*/
GPIO::GPIO()
{
	// empty constructor
}

/* Export GPIO pin
*/
int GPIO::gpio_export(int pin) {
	int BUFFER_MAX = 3;
	ssize_t bytes_written;
	char buffer[BUFFER_MAX];
	int fd;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open export for writing\n");
		return(-1);
	}

	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}

/* Set direction as "dir" to GPIO "pin"
*  dir=0 -> input
*  dir=1 -> output
*/
int GPIO::gpio_set_direction(int pin, int dir)
{
	static const char s_directions_str[] = "in\0out";
	int BUFFER_MAX = 35;
	char buffer[BUFFER_MAX];
	int fd;
	
	snprintf(buffer, BUFFER_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(buffer, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio direction for writing!\n");
		return(-1);
	}

	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		fprintf(stderr, "Failed to set direction!\n");
		return(-1);
	}
	close(fd);
	return(0);
}


/* Read value of GPIO "pin"
*/
int GPIO::gpio_read(int pin)
{
	int BUFFER_MAX = 35;
	char buff[BUFFER_MAX]; 
	char value_str[3];
	int fd;

	snprintf(buff, BUFFER_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(buff, O_RDONLY);
	if (-1 == fd) {
		fprintf(stderr, "Fail to open gpio value for reading!\n");
		return(-1);
	}

	if (-1 == read(fd, value_str, 3)) {
		fprintf(stderr, "Fail to read gpio value!\n");
		return(-1);
	}

	close(fd);
	return(atoi(value_str));
}

/* Write "value" to GPIO "pin"
*  value=0 -> LOW
*  value=1 -> HIGH
*/
int GPIO::gpio_write(int pin, int value)
{
	static const char s_values_str[] = "01";
	int BUFFER_MAX = 35;
	char buff[BUFFER_MAX];
	int fd;

	snprintf(buff, BUFFER_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(buff, O_WRONLY);
	if (-1 == fd) {
		fprintf(stderr, "Failed to open gpio value for writing!\n");
		return(-1);
	}

	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		fprintf(stderr, "Failed to write value!\n");
		return(-1);
	}
	close(fd);
	return(0);
}

/***************************** LED *******************************************/

/* LED constructor
*  // Export GPIO
*  // Set GPIO as output
*  // Initilize at LOW (LED OFF)
*/
LED::LED(int pin)
{
	LED_PIN = pin;
	GPIO::gpio_export(LED_PIN);
	GPIO::gpio_set_direction(LED_PIN, OUT);
	gpio_write(LED_PIN, LOW);
}

/* Turn LED on
*/
void LED::ON()
{
	gpio_write(LED_PIN, 1);
}

/* Turn LED off
*/
void LED::OFF()
{
	gpio_write(LED_PIN, 0);
}

/* Toggle LED
*/
void LED::TOGGLE()
{
	if (LOW == gpio_read(LED_PIN))
		ON();
	else
		OFF();
}
/* Blink the LED
*  every "ms" micro-second
*/
void LED::BLINK_MS(int micro_second)
{
	TOGGLE();
	usleep(500 * micro_second);
}

/* Blink the LED
*  every "ms" micro-second
*/
void LED::BLINK_S(int second)
{
	TOGGLE();
	sleep(second);
}


/* Blink the LED
*  every "ms" micro-second
*  for "ntimes" times
*/
void LED::BLINK_MS_NTIMES(int micro_second, int ntimes)
{
	for (int i = 0; i < 2*ntimes; i++) {
		TOGGLE();
		usleep(1000 * micro_second);
	}
}

/* Blink the LED
*  every "s" second
*  for "ntimes" times
*/
void LED::BLINK_S_NTIMES(int second, int ntimes)
{
	for (int i = 0; i < 2*ntimes; i++) {
		TOGGLE();
		sleep(second);
	}
}

/***************************** BUTTON *******************************************/

/* BUTTON constructor
*  // Export GPIO
*  // Set GPIO as input
*/
BUTTON::BUTTON(int pin)
{
	BUTTON_PIN = pin;
	GPIO::gpio_export(BUTTON_PIN);
	GPIO::gpio_set_direction(BUTTON_PIN, IN);
}

/* Read status of button
*/
int BUTTON::READ_STATUS()
{
	return(gpio_read(BUTTON_PIN));
}

/* Check if button is pressed (loggeric 0)
*/
bool BUTTON::IS_PRESSED()
{
	return(0 == gpio_read(BUTTON_PIN));
}

/* Check if button is released (loggeric 1)
*/
bool BUTTON::IS_RELEASED()
{
	return(1 == gpio_read(BUTTON_PIN));
}

