#include <at89c5131.h>
#include "lcd.h"		
#include <stdio.h>

bit tx_complete = 0,rx_complete = 0;

void uart_init(void){
	TMOD=0x20;		
	TH1=0xCC;				
	SCON=0x50;			 
	TR1=1;             
	EA=1;									
	ES=1;	}

void transmit_char(unsigned char ch){
	SBUF=ch;				
	while(!tx_complete); 			
	tx_complete = 0;}

void transmit_string(unsigned char *s){
	while(*s != 0)	{
			transmit_char(*s++);}
}

unsigned char str0[3]={0,0,'\0'};
unsigned char str1[3]={0,0,'\0'};
unsigned char str2[3]={0,0,'\0'};
unsigned char str3[3]={0,0,'\0'};

char y=' ';	


void test0(void){
		lcd_cmd(0x01);
	lcd_cmd(0x82);
	lcd_write_string("A: ");
	int_to_string(y,str0);
	lcd_cmd(0x85);
	lcd_write_string(str0);
}

void test1(void){
		
	lcd_cmd(0x89);
	lcd_write_string("B: ");
	int_to_string(y,str1);
	lcd_cmd(0x8C);
	lcd_write_string(str1);
}

void test2(void){
		
	lcd_cmd(0xC2);
	lcd_write_string("C: ");
	int_to_string(y,str2);
	lcd_cmd(0xC5);
	lcd_write_string(str2);
}

void test3(void){

	lcd_cmd(0xC9);
	lcd_write_string("D: ");
	int_to_string(y,str3);
	lcd_cmd(0xCC);
	lcd_write_string(str3);
}

unsigned char receive_char(void)
{
	unsigned char ch = 0;
	
sbit sw0= P1^0;
sbit sw1=P1^1;
sbit sw2 = P1^2;
sbit sw3=P1^3;
sbit r0;
sbit r1;
	sbit r2;
	sbit r3;
	
test0();
	test1();
	test2();
	test3();

	
	while(!rx_complete){
		    sbit s0=P1^0;
				sbit s1=P1^1;
				sbit s2=P1^2;
				sbit s3=P1^3;
	    	y=1;
				r0=s0^sw0;
		
				if(r0==1){sw0=s0; test0(); y++;
					break;}
				r1=s1^sw1;
				if(r1==1){sw0=s0; test1(); y++;
					break;}
				r2=s2^sw2;
				if(r2==1){sw2=s2; test2(); y++;
					break;}
				r3=s3^sw3;
					if(r3==1){sw3=s3; test3(); y++;
					break;}	
	}
	
	rx_complete = 0;
	ch = SBUF;				
	return ch;					
}

void serial_ISR(void) interrupt 4

{

		if(TI==1)			//check whether TI is set

		{

			TI = 0;			//Clear TI flag

			tx_complete = 1;	//Set tx_complete flag indicating interrupt completion

		}

		else if(RI==1)			//check whether RI is set

		{

			RI = 0;			//Clear RI flag

			rx_complete = 1;	//Set rx_complete flag indicating interrupt completion

		}

}
