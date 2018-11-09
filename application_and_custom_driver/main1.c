//SAMPLE CODE FOR THE DRIVER 
#include "bmp_image.h"
#include "myglcd.h"

#define PLL_CLOCK       72000000

char *buff = "I ! HATE ipl, ipl IS A DISGRACE TO THE CRICTET GAME. \
	Some timers i want to throw the tv when ipl is running live. They gamble and we waste our time";

void SYS_Init(void) {
    	/* Enable HIRC clock */
    	CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    	/* Waiting for HIRC clock ready */
    	CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    	/* Switch HCLK clock source to HIRC */
    	CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    	/* Enable HXT */
    	CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    	/* Waiting for clock ready */
    	CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    	/* Set core clock as PLL_CLOCK from PLL and SysTick source to HCLK/2*/
    	CLK_SetCoreClock(PLL_CLOCK);
    	CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLKSEL_HCLK_DIV2);
}


int main() {
	SYS_Init();
	glcd_initilization();
	glcd_print_string(0, buff);
	my_delay(10000);
	glcd_clean();
	glcd_print_image(IPL_Logo);
	my_delay(10000);
	glcd_clean();
	for(;;);
}
