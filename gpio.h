#pragma once

/* For GPIO */
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* GPIO */
#define IN 0
#define OUT 1

#define LOW 0
#define HIGH 1

#define LED1_PIN 21
#define SW1_PIN 23

class GPIO
{
private:
	//
public:
	// Default constructor
	GPIO();	

	// Common methods
	int gpio_export(int pin);
	int gpio_set_direction(int pin, int dir);
	int gpio_read(int pin);
	int gpio_write(int pin, int value);
};


class LED : public GPIO
{
private:
	//
public:
	LED(int pin);	// Constructor
	
	int LED_PIN;
	
	void ON();
	void OFF();
	void TOGGLE();
	void BLINK_MS(int micro_second);
	void BLINK_S(int second);
	void BLINK_MS_NTIMES(int micro_second, int ntimes);
	void BLINK_S_NTIMES(int second, int ntimes);
};

class BUTTON : public GPIO
{
private:
	//
public:
	BUTTON(int pin); // Constructor

	int BUTTON_PIN;
	int READ_STATUS();
	bool IS_PRESSED();
	bool IS_RELEASED();	
};