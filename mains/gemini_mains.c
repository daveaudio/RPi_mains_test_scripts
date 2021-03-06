#include <stdio.h>

// for the relay
#include "/usr/include/wiringPi.h"

// for the com port section
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
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


int set_interface_attribs(int fd, int speed)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error from tcgetattr: %s\n", strerror(errno));
        return -1;
    }

    cfsetospeed(&tty, (speed_t)speed);
    cfsetispeed(&tty, (speed_t)speed);

    tty.c_cflag |= (CLOCAL | CREAD);    /* ignore modem controls */
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;         /* 8-bit characters */
    tty.c_cflag &= ~PARENB;     /* no parity bit */
    tty.c_cflag &= ~CSTOPB;     /* only need 1 stop bit */
    tty.c_cflag &= ~CRTSCTS;    /* no hardware flowcontrol */

    /* setup for non-canonical mode */
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    tty.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    tty.c_oflag &= ~OPOST;

    /* fetch bytes as they become available */
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 1;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        printf("Error from tcsetattr: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

void set_mincount(int fd, int mcount)
{
    struct termios tty;

    if (tcgetattr(fd, &tty) < 0) {
        printf("Error tcgetattr: %s\n", strerror(errno));
        return;
    }

    tty.c_cc[VMIN] = mcount ? 1 : 0;
    tty.c_cc[VTIME] = 5;        /* half second timer */

    if (tcsetattr(fd, TCSANOW, &tty) < 0) {
        printf("Error tcsetattr: %s\n", strerror(errno));
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


int main (int argc, char *argv[]) {

	// time information
        time_t t;
        time_t t_trigger;

	float reboot_counter = 0;

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
	//printf("RPi pin number set to %d\n", pin_num);

	found_string=-1;
	found_string = strcmp(portname, "0");
	//printf("portname = %s\n", portname);
	//printf("String_found = %d\n", found_string);
	if (found_string==0){
		printf("Defaulting the debug port to /dev/ttyUSB0\n");
		portname="/dev/ttyUSB0";
	}

	//printf("Com port name = %s\n", portname);


		// --- Initialising com port
	fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) {
		printf("Error opening %s: %s\n", portname, strerror(errno));
		return -1;
	}
	/*baudrate 115200, 8 bits, no parity, 1 stop bit */
	set_interface_attribs(fd, B115200);
	//set_mincount(fd, 0);                /* set to pure timed read */


	// evaluate the compare string
	rb_prmt_len = strlen(reboot_prompt);

	printf("Looking for '%s' before rebooting\n", reboot_prompt);
	printf("String length of %d\n", rb_prmt_len);


	wiringPiSetup ();
		// --- Setup the pins to be use on in the program
	for (pin_counter=0; pin_counter<8; pin_counter++) {
		pinMode (relay[pin_counter], OUTPUT);
	}



		// --- Initialise the relays to off
	all_relays_off();
	printf("Power on in 5 seconds\n");
	for (counter=5; counter>0; counter--) {
		delay(1000);
		printf("%d\n", (counter-1));
	}
	//printf("\n");

	//pin_num = 0;		// relay number


	// Reboot counter screen refresh
	time(&t);
	t_trigger = t + debug_time;

	//time_now = time(null);

	printf("\n\n\nCurrent time = %s\n", ctime(&t));
	printf("Next info update to be trigger on %s\n", ctime(&t_trigger));

	//return 0;



	//	disp_time = mytime + 

	relay_on(pin_num);
	printf("\nWaiting for %s...\n", reboot_prompt);

	while (exit_loop==0) {

		time(&t);	//get the time

		// this section displays information when the screen is full of debug
		if (t >= t_trigger){
			printf("\n\n\e]PA\t\t >>> COUNTER = %0.0f <<< \n", reboot_counter);
			printf("Waiting for '%s' ...\e]PF\n\n", reboot_prompt);
			t_trigger = t + debug_time;
		}

//        	rdlen = read(fd, buf, sizeof(buf) - 1);		// waits for the buffer to get filled
		rdlen = read(fd, buf, 1);	// reads one character in at a time

	        if (rdlen > 0) {
			printf("%s", buf);

			if (*buf==reboot_prompt[char_counter]) {
				char_counter++;
			}
			else {
				char_counter=0;
			}

			if (char_counter==rb_prmt_len) {
				printf("\n\nString found\nRebooting in 10 seconds...\n");
		                relay_off(pin_num);
                		sleep (10);
		                relay_on(pin_num);
				char_counter=0;
				//exit_loop=1;
				reboot_counter++;
				printf("\n\n\e]PA\t\t >>> COUNTER = %0.0f <<< \n", reboot_counter);
				printf("Waiting for '%s' ...\e]PF\n\n", reboot_prompt);
			}
	        }
		else if (rdlen < 0) {
        	    printf("Error from read: %d: %s\n", rdlen, strerror(errno));
	        }
	//usleep(75000);
	}

	// --- pins sequence for reference
/*	for (pin_num=0; pin_num<relays_used; pin_num++) {
		relay_on(pin_num);
    		delay (500);
		relay_off(pin_num);
		delay (500);
  	}
*/


	printf ("\n\nTotal number of reboot cycles = %0.0f\n",reboot_counter);
  	return 0 ;
}
