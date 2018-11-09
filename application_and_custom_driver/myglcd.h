#ifndef MY_GLCD_H
#define MY_GLCD_H

#define FONT fontRENEW
//#define FONT fontBOLOK
//#define FONT fontACME

#define RS PB1
#define E PB2
//3 TO 10 LCD PINS
#define RST PB13
#define CS2 PB14
#define CS1 PB15

void my_delay(unsigned int );
void glcd_command(unsigned char );
void glcd_data(unsigned char );
void glcd_initilization(void);
void glcd_clean(void);
void glcd_print_string(unsigned char, char *);
void glcd_print_image(const unsigned char *);

#endif
