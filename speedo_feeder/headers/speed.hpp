#ifndef SPEED_HPP
# define SPEED_HPP


#include <iostream>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <cstdint>

//for can
#include <linux/can.h>
#include <linux/can/raw.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>


typedef struct CANMessage 
{
	uint32_t id;
	uint8_t data_length;
	uint8_t data[8];
} t_can;

class Speed
{
    private:
		int _input;
		int_least16_t _speed;
    public:
		Speed();
		// Speed(int input);
		~Speed();
		void forward();
		void reverse();
		void bbreak();
		void errorHandling();
		void wrongInput();
		
		//getters
		int getInput();
		int getSpeed();

		//for can
		t_can convSpedCAN() const;
};

#endif