#include <stdio.h>
#include "/usr/include/wiringPi.h"


// ------ USER SETTINGS ----------------------------------------------

// Only change these values don't play with anything else MOFO!

#define relays_used 2		// Always starts from relay channel 1








// -------------------------------------------------------------------



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


// ----- Variables
unsigned int pin_num = 0;
unsigned int relay[8]={0,2,3,4,20,19,6,5};


// ------ Main program
int main (void) {
	wiringPiSetup ();

	// --- Setup the pins to be use on in the program
	for (pin_num=0; pin_num<8; pin_num++) {
		pinMode (relay[pin_num], OUTPUT);
	}

	// --- Initialise the relays to off
	for (pin_num=0; pin_num<8; pin_num++) {
		pinMode (relay[pin_num], OUTPUT);
	}

	for (pin_num=0; pin_num<relays_used; pin_num++) {
		printf("PIN : %d\n",pin_num);
		digitalWrite (relay[pin_num], LOW);
    		delay (2000);
    		digitalWrite (relay[pin_num],  HIGH);
		delay (2000);
  	}
  	return 0 ;
}
