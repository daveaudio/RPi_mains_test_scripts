#include <stdio.h>
#include <time.h>


int main() {

	time_t t;
	time_t t_trigger;
	time(&t);
	printf("\nCurrent time is %s",ctime(&t));
	//printf("\nCurrent time is %d\n", &t);
	t_trigger = t + 10;
	printf("Trigger will occur at time = %s", ctime(&t_trigger));

	while(1) {
		time(&t);
		//printf("\nCurrent time is %s",ctime(&t));
		if (t >= t_trigger) {
			printf("\nTime trigger found at %s", ctime(&t));
			return 0;
		}
	}
	return 0;
}
