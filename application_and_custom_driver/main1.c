//SAMPLE CODE FOR THE DRIVER 
#include "bmp_image.h"
#include "myglcd.h"

char *buff = "I ! HATE ipl, ipl IS A DISGRACE TO THE CRICTET GAME. Some timers i want to throw the tv when ipl is running live. They gamble and we waste our time";

int main() {
		glcd_initilization();
		glcd_print_string(0, buff);
		my_delay(10000);
		glcd_clean();
		glcd_print_image(IPL_Logo);
		my_delay(10000);
		glcd_clean();
		for(;;);
}
