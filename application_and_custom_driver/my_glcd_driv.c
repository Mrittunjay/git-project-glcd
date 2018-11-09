#include "M0564.h"
#include "glcd_font.h"
#include "myglcd.h"

void my_delay(unsigned int del) {
		int i, j;
		for(i=0;i<del;i++) 
				for(j=0;j<150;j++);
}

void glcd_command(unsigned char command) {
		RS = 0;
		outpb(PB, command<<3);
		E = 1;
		my_delay(5);
		E = 0;
}

void glcd_data(unsigned char data) {
		RS = 0;
		outpb(PB, (data<<3));
		E=1;
		my_delay(5);
		E=0;
}
void glcd_initilization(void) {
		int i;
		//setting the pins 0 to 15 to output mode
		for(i=0; i<15; i++) {
			GPIO_SetMode(PC, 1<<i, GPIO_MODE_OUTPUT);
		}
		RST = 1;
		CS2 = 1;
		CS1 = 1;
		my_delay(30);
		glcd_command(0x3E);
		glcd_command(0x40);
		glcd_command(0xB8);
		glcd_command(0xC0);
		glcd_command(0x3F);
}

void glcd_clean(void) {
		int i, j;
		for(i=0;i<8;i++) {
				CS2 = 1;
				CS1 = 0;
				glcd_command(0xB8 + i);
				for(j=0;j<64;j++)
						glcd_data(0);

				CS1 = 1;
				CS2 = 0;
				glcd_command(0xB8 + i);
				for(j=0;j<64;j++)
						glcd_data(0);
		}
		glcd_command(0x40);
		glcd_data(0xB8);
}

void glcd_print_string(unsigned char page_no, char *string_to_print) {
		//int char_to_print_1, char_to_print_2, char_to_print_3;
		unsigned int i,column,Page=((0xB8)+page_no),Y_address=0;	
		float Page_inc=0.5;													
	
		CS2 = 1; 
		CS1 = 0;	/* Select Left half of display */
	
		glcd_command(Page);
		
		for(i=0;string_to_print[i]!='\0';i++) {	/* Print char in string till null */
				if (Y_address>(1024-(((page_no)*128)+5)))
						break;
				
				if (string_to_print[i]!=32) {
						for (column=1;column<=5;column++) {
								if ((Y_address+column)==(128*((int)(Page_inc+0.5)))) {
										if (column==5)
												break;
          
										glcd_command(0x40);
										Y_address = Y_address+column;
										if(CS1 != 0)
											CS1 = 0;
										else
											CS1 = 1;
										if(CS2 == 0)
											CS2 = 1;
										else
											CS2 = 0;
										
										glcd_command((Page+Page_inc));
										Page_inc=Page_inc+0.5;
								}
						}
				}
        
				if (Y_address>(1024-(((page_no)*128)+5)))
						break;
				
				//char_to_print_1 = (((string_to_print[i]-32)*5)+4);
				//if((int)(*(code_page[1]+char_to_print_1)) == 0 || (((int)string_to_print[i])==32)) {
				if((FONT[((string_to_print[i]-32)*5)+4]) == 0 || (string_to_print[i]==32)) {
						for(column=0;column<=5;column++) {
								//char_to_print_2 = ((string_to_print[i])*column);
								//glcd_data(*(code_page[1] + char_to_print_2));	
								glcd_data(FONT[string_to_print[i]-32][column]);
								if((Y_address+1)%64==0) {
										if(CS1 != 0)
											CS1 = 0;
										else
											CS1 = 1;
										if(CS2 == 0)
											CS2 = 1;
										else
											CS2 = 0;
										
										glcd_command((Page+Page_inc));
										Page_inc=Page_inc+0.5;
								}
								
								Y_address++;
						}
				}
				else {
						for(column=0;column<=5;column++) {
								//char_to_print_3 = ((string_to_print[i])*column);
								//glcd_data(*(code_page[1] + char_to_print_3));	
								glcd_data(FONT[string_to_print[i]-32][column]);
								if((Y_address+1)%64==0) {
											if(CS1 != 0)
												CS1 = 0;
											else
												CS1 = 1;
											if(CS2 == 0)
												CS2 = 1;
											else
												CS2 = 0;
											
											glcd_command((Page+Page_inc));
											Page_inc=Page_inc+0.5;
								}
								Y_address++;
						}

						glcd_data(0);
						Y_address++;
						
						if((Y_address)%64==0) {
								if(CS1 != 0)
									CS1 = 0;
								else
									CS1 = 1;
								if(CS2 == 0)
									CS2 = 1;
								else
									CS2 = 0;
								
								glcd_command((Page+Page_inc));
								Page_inc=Page_inc+0.5;
						}
						
						
				}
  }
	glcd_command(0x40);
}

void glcd_print_image(const unsigned char *pic) {
		int column, page, page_add = 0xB8, k = 0;
		float page_inc = 0.5;
		CS2 = 1;
		CS1 = 0;
		for(page=0;page<16;page++) {
			for(column=0;column<64;column++) {
				glcd_data(pic[column+k]);
			}
			
			if(CS1 != 0)
				CS1 = 0;
			else
				CS1 = 1;
			if(CS2 == 0)
				CS2 = 1;
			else
				CS2 = 0;

			glcd_command((page_add+page_inc));
			page_inc = page_inc+0.5;
			k=k+64;
		}
		glcd_command(0x40);
		glcd_command(0xB8);
}
