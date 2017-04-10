#include <stdio.h>

// for the relay
#include "/usr/include/wiringPi.h"

// for the com port section
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
//#include <termios.h>
#include <unistd.h>
#include <time.h>

/*	PIN INFO
			
	Number	| Relay
	0	! 1
	2	| 2
	3	| 3
	4	| 4
	20	| 5
	19	| 6
	6	| 7
	5	| 8
*/
#define debug_time 10		// displays the reboot counter and search string every <debug_time> seconds

// ----- Variables
unsigned int relay[8] = {0,2,3,4,20,19,6,5};
unsigned int exit_loop = 0;
unsigned int char_counter = 0;
unsigned int rb_prmt_len = 0;
unsigned int rb_prmt_trig = 0;
unsigned int counter = 0;
unsigned int pin_counter = 0;

signed int pin_num = -1;
signed int relay_num = -1;
signed int found_string = -1;

//static const char portname[] = "-1";
//unsigned char buf[80];
//unsigned char rb_prmt_str[256];
int fd;
int wlen;
int rdlen;
//char *time_now;
//char *disp_time;


void relay_on(relay_num) {
	digitalWrite (relay[relay_num], LOW);
	printf("Relay %d is on\n", (pin_num+1));
}

void relay_off(relay_num) {
	digitalWrite (relay[pin_num],  HIGH);
	printf("Relay %d is off\n", (pin_num+1));
}


void all_relays_off() {
	printf("Setting all relays to off\n");

	for (pin_counter=0; pin_counter<8; pin_counter++) {
		digitalWrite (relay[pin_counter],  HIGH);
	}
}



void help(void) {
	printf("\nMains switching applicaton\n");
	printf("By D L Goodman - 23rd November 2016\n\n");
	printf("\nThis help file needs to be updated....\n\n");
	/*
	printf("sudo ./gemini_mains <switches> -s \"<String>\"\n\n");
	printf("This application reboots a set top box when a particular string is detected on a debug port.\n\n");
	printf("Switches\t\t-\tDescription\n");
	printf("-h\t\t\t-\tDisplays this information\n");
	printf("--help\t\t\t-\tDisplays this information\n");
	printf("-r <relay>\t\t-\tSpecifies a relay channel to turn on/off\n");
	printf("-p <com port>\t\t-\tSpecify a communications port to listen read from\n");
	printf("\t\t\t\ti.e -p /dev/ttyUSB0 or -p /dev/ttyUSB1 etc.\n");
	printf("\t\t\t\tType 'ls /dev/ttyUSB*' to get a list of available ports\n");
	printf("-s <string>\t\t-\tEnter the string to reboot the set top box with\n\n");
	printf("Not selecting a relay channel (-r) or com port (-p) will result in these values:\n");
	printf("Default values for relay is channel 1\n");
	printf("Default values for com port is /dev/ttyUSB0\n\n");
	*/
	//return 0;
}


// ------ Main program


int main (int argc, char *argv[]) {

	char relay_state = 0x0;
	//char cpin_num = 0x0;

	// time information

	//printf("Number of arguments = %d\n", argc);

        if (argc<2) {
                printf("Type -h or --help to list all options\n");
                return -1;
        }

	counter=1;
	while (counter<argc) {
		printf("%s\n", argv[counter]);

		found_string=-1;
		found_string = strcmp(argv[counter], "-h");
		if (found_string==0) {
			help();
			return -1;
		}

		found_string=-1;
		found_string = strcmp(argv[counter], "--help");
		if (found_string==0) {
			help();
			return -1;
		}

		found_string = -1;
		found_string = strcmp(argv[counter], "-r");
		if (found_string==0) {
			counter++;
			pin_num=atoi(argv[counter]);
			//pin_num = atoi(Cpin_num);
			//printf("\n>>>\nPIN_NUM = %d\n<<<\n",pin_num);
		}

		found_string = -1;
		found_string = strcmp(argv[counter], "-on");
		if (found_string==0) {
			relay_state = 0x1;
		}

		found_string = -1;
		found_string = strcmp(argv[counter], "-off");
		if (found_string==0) {
			relay_state = 0x0;
		}

		counter++;
	}

	wiringPiSetup ();


	if (pin_num==-1) {
		printf("Defaulting the relay channel to mains socket 1\n");
		pin_num=0;
	}
	else {
		printf("Relay channel set to mains socket %d\n", pin_num);
		pin_num--;	//relay channel 1 = 0
	}


	if (relay_state == 0x1) {
		relay_on(pin_num);
	}

	if (relay_state == 0x0) {
		relay_off(pin_num);
	}

  	return 0 ;
}
