#include <at89c5131.h>
#include "serial.c"	

char init=1;
char final=99;
unsigned int cnt;
unsigned char str[3]={0,0,'\0'};


void lcd_test(void){
	lcd_cmd(0x01);
	cnt=init;
	int_to_string(cnt,str);
	lcd_cmd(0x01);
	lcd_cmd(0x83);
	lcd_write_string("Token:  ");
	lcd_cmd(0x8B);
	lcd_write_string(str);
	msdelay(2000);
	init=init+1;
}	

void main(void)
{
	unsigned char ch=0;

	lcd_init();
	uart_init();
	transmit_string("Press t for token number\r\n");
	
	while(1)
	{
  	ch = receive_char();
		switch(ch)
			{
				case 't':lcd_test();
				break;
	  	}
	}
	
}
