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

char *portname = "0";
char *Cpin_num = "0";
char *reboot_prompt = "0";
char buf[] = "0";

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

	//return 0;
}


// ------ Main program


int main (void) {

	// time information
        //time_t t;
        //time_t t_trigger;

	//float reboot_counter = 0;

	//printf("Number of arguments = %d\n", argc);

/*
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
		found_string = strcmp(argv[counter], "-p");
		if (found_string==0) {
			counter++;
			portname=argv[counter];
			//printf("%s",portname);
		}

		found_string = -1;
		found_string = strcmp(argv[counter], "-r");
		if (found_string==0) {
			counter++;
			Cpin_num=argv[counter];
			pin_num = atoi(Cpin_num);
			//printf("\n>>>\nPIN_NUM = %d\n<<<\n",pin_num);
		}

		found_string = -1;
		found_string = strcmp(argv[counter], "-s");
		if (found_string==0) {
			counter++;
			reboot_prompt=argv[counter];
			printf("\e]P0Looking for the string \"%s\" before rebooting.\n", reboot_prompt);
		}

		counter++;
	}



	if (pin_num==-1) {
		printf("Defaulting the relay channel to mains socket 1\n");
		pin_num=0;
	}
	else {
		printf("Relay channel set to mains socket %d\n", pin_num);
		pin_num--;	//relay channel 1 = 0
	}

*/

	wiringPiSetup ();
	
	// --- Setup the pins to be use on in the program
	for (pin_counter=0; pin_counter<8; pin_counter++) {
		pinMode (relay[pin_counter], OUTPUT);
	}


	// --- Initialise the relays to off
	all_relays_off();
	delay (1000);

	printf ("\nRelay bank initialised\n");

  	return 0 ;
}
