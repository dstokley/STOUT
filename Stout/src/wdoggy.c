#include <stdlib.h>
#include <stdio.h>

int main(void){
	printf("UDOO Watchdog trigger example running ...");
	system("echo out > /sys/class/gpio/gpio351/direction");
	
	for(;;){
		system("sudo echo 0 > /sys/class/gpio/gpio351/value");
		usleep(100000);
		system("sudo echo 1 > /sys/class/gpio/gpio351/value");
		usleep(100000);
	}
}
