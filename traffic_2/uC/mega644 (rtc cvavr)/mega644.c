/*****************************************************
This program was produced by the
CodeWizardAVR V1.25.9 Standard
Automatic Program Generator
� Copyright 1998-2008 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 10/9/2013
Author  : F4CG                            
Company : F4CG                            
Comments: 


Chip type           : ATmega644
Program type        : Application
Clock frequency     : 1.000000 MHz
Memory model        : Small
External SRAM size  : 0
Data Stack size     : 1024
*****************************************************/

#include <mega644.h> 
#include <lcd4x20.h>
#include <delay.h>
#include <string.h>

// I2C Bus functions
#asm
   .equ __i2c_port=0x05 ;PORTB
   .equ __sda_bit=1
   .equ __scl_bit=0
#endasm
#include <i2c.h>

// PCF8583 Real Time Clock functions
#include <pcf8583.h>

//------------------ Module Connections -------------
// Keypad
#define RowA PORTA.0	//RowA
#define RowB PORTA.1	//RowB
#define RowC PORTA.2	//RowC
#define RowD PORTA.3	//RowD
#define C1   PINA.4	//Column1
#define C2   PINA.5	//Column2
#define C3   PINA.6	//Column3
#define C4   PINA.7	//Column4

#define COR 	'/'
#define MEN 	'x'
#define UP 	'-'
#define DOWN 	'+'
#define CAN 	'm'
#define ENT 	'='

void StartUp();				// 1
void Idle();				// 2
void InputSetting();			// 3
void Monitor();				// 4
void InputKeypad();			// 5
void InputKompSer();			// 6
void InputKompInt();			// 7
void SetHoliday();			// 8
void SetTanggal();			// 9
void SetWaktu();			// 10
void SetPlan();				// 11
void SetPlanPilih();			// 12
void SetProgramHarian();		// 13
void SetProgramHarianPilih();	        // 14
void SetStartUp();			// 15
void UpdateProgramHarian();		// 16
void UpdatePlan();			// 17
void UpdateLampu();			// 18
char READ_SWITCHES(void);		// 19
char get_key(void);			// 20

// Declare your global variables here
char key='n';                   // keypad
char str[4][22];                // char tampil LCD utk > 4 brs
char st1[3];                    // char tampil LCD utk variabel
char temp=61;
char baris=0;
char stateset=0;                // jmlh karakter yg mau diedit
char progharpilihan;            // temp utk proghar yg akan diedit
char planpilihan;               // temp utk plan yg akan diedit      					
int i;

unsigned char jam = 23, mnt = 59, dtk = 55, hdtk = 0, bln = 2, tgl = 28, hr = 1;       // RTC, EEPROM
unsigned thn = 2012;
char dtkstartup = 2;						                // EEPROM
int holiday[25] = {202,1202,304,412,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char jmlholiday = 4;
char listplan1[16] = {23,56,110,130,0,156,200,222,103,119,43,104,89,139,43,76};
char listplan2[16] = {8,49,15,60,132,180,93,100,4,15,0,43,20,139,33,40};
/*char listplan3[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan4[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan5[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan6[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan7[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan8[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan9[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan10[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan11[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan12[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan13[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan14[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan15[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan16[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};*/
long int listproghar1[20] = {71502,74510,84502,102506,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
long int listproghar2[20] = {70013,92514,121513,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
/*int listproghar3[20] = {101,202,304,412,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int listproghar4[20] = {101,202,304,412,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int listproghar5[20] = {101,202,304,412,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int listproghar6[20] = {101,202,304,412,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int listproghar7[20] = {101,202,304,412,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int listproghar8[20] = {101,202,304,412,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};*/
char jmllistproghar[8] = {4,3,0,0,0,0,0,0};

char proghar = 1;		// RAM
char plan = 1;
char lampu = 240;
char tempo=123;
long int dtktempo=45;
int wktmulai=0;

void main(void)
{
        st1[2] = 0;
        DDRC=0xFF;      // PORT C output 
	PORTA=0xF0;
        DDRA=0x0F;
	                     
        // I2C Bus initialization
        i2c_init();

        // PCF8583 Real Time Clock initialization
        rtc_init(0,0);

	Lcd4_Init();  
        
        //rtc_set_time(0,jam,mnt,dtk,hdtk);
        //rtc_set_date(0,tgl,bln,thn);
	
	StartUp();
	
	while (1){
                Idle();
	};
}

void StartUp(){		
	temp = dtkstartup;
	
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("TRAFFIC TLPCO-08 SG");	 
	
	while (temp > 0){ 	
		Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("START UP:");
		st1[0] = 48 + (temp / 10); st1[1] = 48 + (temp % 10);
		Lcd4_Set_Cursor(2,10);Lcd4_Write_String(st1);
		
		temp--;
		delay_ms(1000);
	} 
	delay_ms(1000);
	Lcd4_Clear();delay_ms(50);
} 

void Idle(){
	temp=61;
	Lcd4_Clear();delay_ms(50);
	
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("TELEPICO TLPCO-08 SG");	 		// baris 1
	
	Lcd4_Set_Cursor(2,4); Lcd4_Write_Flash(",");									// baris 2
	
	Lcd4_Set_Cursor(3,2);Lcd4_Write_Flash(":");
	Lcd4_Set_Cursor(3,5);Lcd4_Write_Flash(":");
	Lcd4_Set_Cursor(3,9); Lcd4_Write_Flash("S:");									// baris 3
	Lcd4_Set_Cursor(3,14); Lcd4_Write_Flash("P:");
	
   	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[1] Set [2] Monitor");			// baris 4
	
	while((key != '1') && (key != '2')){
		rtc_get_time(0,&jam,&mnt,&dtk,&hdtk);
                rtc_get_date(0,&tgl,&bln,&thn);
	        if(temp != dtk){
			temp=dtk;
			UpdateProgramHarian();UpdatePlan();UpdateLampu();
			
			switch (hr){																	// baris 2
				case 1:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_Flash("MGG");  break;
				case 2:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_Flash("SNN");  break;
				case 3:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_Flash("SLS");  break;
				case 4:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_Flash("RAB");  break;
				case 5:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_Flash("KMS");  break;
				case 6:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_Flash("JMT");  break;
				case 7:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_Flash("SBT");  break;
			}
			st1[0] = 48 + (tgl / 10); st1[1] = 48 + (tgl % 10);
			Lcd4_Set_Cursor(2,6);Lcd4_Write_String(st1);
			switch (bln){
				case 1:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("JAN");  break;
				case 2:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("FEB");  break;
				case 3:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("MAR");  break;
				case 4:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("APR");  break;
				case 5:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("MEI");  break;
				case 6:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("JUN");  break;
				case 7:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("JUL");  break;
				case 8:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("AGS");  break;
				case 9:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("SEP");  break;
				case 10:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("OKT");  break;
				case 11:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("NOV");  break;
				case 12:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_Flash("DES");  break;
			}
			st1[0] = 48 + (thn / 1000); st1[1] = 48 + ((thn % 1000)/100);
			Lcd4_Set_Cursor(2,13);Lcd4_Write_String(st1);
			st1[0] = 48 + ((thn %100)/10); st1[1] = 48 + (thn %10);
			Lcd4_Set_Cursor(2,15);Lcd4_Write_String(st1);
			
			st1[0] =  48 + (jam / 10);	 st1[1] = 48 + (jam % 10);							// baris 3
			Lcd4_Set_Cursor(3,0);Lcd4_Write_String(st1);
			st1[0] =  48 + (mnt / 10);	 st1[1] = 48 + (mnt % 10);
			Lcd4_Set_Cursor(3,3);Lcd4_Write_String(st1);
			st1[0] =  48 + (dtk / 10);	 st1[1] = 48 + (dtk % 10);
			Lcd4_Set_Cursor(3,6);Lcd4_Write_String(st1);
			st1[0] =  48 + (proghar/ 10);st1[1] = 48 + (proghar % 10);
			Lcd4_Set_Cursor(3,11);Lcd4_Write_String(st1);
			st1[0] =  48 + (plan/ 10);st1[1] = 48 + (plan % 10);
			Lcd4_Set_Cursor(3,16);Lcd4_Write_String(st1);
		}
		key = READ_SWITCHES();
	}
	switch (key){
		case '1':	while(key=='1'){key=get_key();}InputSetting(); break;
		case '2':	while(key=='2'){key=get_key();}Monitor(); break;
	}
}

void InputSetting(){	
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Input Setting");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[1] Keypad");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[2] Komputer (ser)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[3] Komputer (int)");
	
	while (key != CAN){
		key = get_key();
		
		switch (key){
			case '1': while(key=='1'){key=get_key();}InputKeypad(); break;
			case '2': while(key=='2'){key=get_key();}InputKompSer(); break;
			case '3': while(key=='3'){key=get_key();}InputKompInt(); break;
		} 
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();delay_ms(50);
}

void Monitor(){					
	temp = 61;
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Monitor (L1 - L8)");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("RED");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("GRE"); 
	
	while (key != CAN){
		if(temp != dtk){
			temp = dtk;
			UpdateProgramHarian();UpdatePlan();UpdateLampu();
			
			if (((lampu >> 0) & 1) == 1){
				Lcd4_Set_Cursor(2,4); Lcd4_Write_Char(' ');
				Lcd4_Set_Cursor(3,4); Lcd4_Write_Char('*');}
			else if (((lampu >> 0) & 1) == 0){
				Lcd4_Set_Cursor(2,4); Lcd4_Write_Char('*');
				Lcd4_Set_Cursor(3,4); Lcd4_Write_Char(' ');}	
													
			if (((lampu >> 1) & 1) == 1){
				Lcd4_Set_Cursor(2,5); Lcd4_Write_Char(' ');
				Lcd4_Set_Cursor(3,5); Lcd4_Write_Char('*');}
			else if (((lampu >> 1) & 1) == 0){
				Lcd4_Set_Cursor(2,5); Lcd4_Write_Char('*');
				Lcd4_Set_Cursor(3,5); Lcd4_Write_Char(' ');}
	
			if (((lampu >> 2) & 1) == 1){
				Lcd4_Set_Cursor(2,6); Lcd4_Write_Char(' ');
				Lcd4_Set_Cursor(3,6); Lcd4_Write_Char('*');}
			else if (((lampu >> 2) & 1) == 0){
				Lcd4_Set_Cursor(2,6); Lcd4_Write_Char('*');
				Lcd4_Set_Cursor(3,6); Lcd4_Write_Char(' ');}

			if (((lampu >> 3) & 1) == 1){
				Lcd4_Set_Cursor(2,7); Lcd4_Write_Char(' ');
				Lcd4_Set_Cursor(3,7); Lcd4_Write_Char('*');}
			else if (((lampu >> 3) & 1) == 0){
				Lcd4_Set_Cursor(2,7); Lcd4_Write_Char('*');
				Lcd4_Set_Cursor(3,7); Lcd4_Write_Char(' ');}

			if (((lampu >> 4) & 1) == 1){
				Lcd4_Set_Cursor(2,8); Lcd4_Write_Char(' ');
				Lcd4_Set_Cursor(3,8); Lcd4_Write_Char('*');}
			else if (((lampu >> 4) & 1) == 0){
				Lcd4_Set_Cursor(2,8); Lcd4_Write_Char('*');
				Lcd4_Set_Cursor(3,8); Lcd4_Write_Char(' ');}

			if (((lampu >> 5) & 1) == 1){
				Lcd4_Set_Cursor(2,9); Lcd4_Write_Char(' ');
				Lcd4_Set_Cursor(3,9); Lcd4_Write_Char('*');}
			else if (((lampu >> 5) & 1) == 0){
				Lcd4_Set_Cursor(2,9); Lcd4_Write_Char('*');
				Lcd4_Set_Cursor(3,9); Lcd4_Write_Char(' ');}

			if (((lampu >> 6) & 1) == 1){
				Lcd4_Set_Cursor(2,10); Lcd4_Write_Char(' ');
				Lcd4_Set_Cursor(3,10); Lcd4_Write_Char('*');}
			else if (((lampu >> 6) & 1) == 0){
				Lcd4_Set_Cursor(2,10); Lcd4_Write_Char('*');
				Lcd4_Set_Cursor(3,10); Lcd4_Write_Char(' ');}

			if (((lampu >> 7) & 1) == 1){
				Lcd4_Set_Cursor(2,11); Lcd4_Write_Char(' ');
				Lcd4_Set_Cursor(3,11); Lcd4_Write_Char('*');}
			else if (((lampu >> 7) & 1) == 0){
				Lcd4_Set_Cursor(2,11); Lcd4_Write_Char('*');
				Lcd4_Set_Cursor(3,11); Lcd4_Write_Char(' ');}
		
                        st1[0]=dtktempo/100 + '0'; st1[1]=(dtktempo%100)/10 + '0';
                        Lcd4_Set_Cursor(2,15);Lcd4_Write_String(st1);             
                        st1[0]=dtktempo%10 + '0'; st1[1]=0;                    
                        Lcd4_Set_Cursor(2,17);Lcd4_Write_String(st1);
                        st1[0]=tempo/100 + '0'; st1[1]=(tempo%100)/10 + '0';
                        Lcd4_Set_Cursor(3,15);Lcd4_Write_String(st1);       
                        st1[0]=tempo%10 + '0'; st1[1]=0;                             
                        Lcd4_Set_Cursor(3,17);Lcd4_Write_String(st1);       
                }
		key = get_key();
	} 
	while(key==CAN){key=get_key();}
	Lcd4_Clear();delay_ms(50);
}

void InputKeypad(){				
	baris = 0;
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[2] Set tanggal     ");
	
	while (key != CAN){
		key = get_key();
		
		if((key==UP) ||(key==DOWN)){
			if(key==UP){ 
                                while(key==UP){key=get_key();}
				if(baris>0)
					baris--;
			}
			if(key==DOWN){
                                while(key==DOWN){key=get_key();}
				if(baris<4)
					baris++;
			}
			
			if((baris>=0) && (baris<=0))				    
				strcpy(str[0 - baris],"MAIN MENU [1]-[6]   ");
			if((baris>=0) && (baris<=1))
				strcpy(str[1 - baris],"[CAN]EXIT           ");
			if((baris>=0) && (baris<=2))
				strcpy(str[2 - baris],"[1] Set waktu       ");
			if((baris>=0) && (baris<=3))
				strcpy(str[3 - baris],"[2] Set tanggal     ");
			if((baris>=1) && (baris<=4))
				strcpy(str[4 - baris],"[3] Set hari libur  ");
			if((baris>=2) && (baris<=4))
				strcpy(str[5 - baris],"[4] Set startup     ");
			if((baris>=3) && (baris<=4))
				strcpy(str[6 - baris],"[5] Set PLAN        ");
			if((baris>=4) && (baris<=4))
				strcpy(str[7 - baris],"[6] Set prog harian ");
			
			Lcd4_Set_Cursor(1,0);Lcd4_Write_String(str[0]);
			Lcd4_Set_Cursor(2,0);Lcd4_Write_String(str[1]);
			Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
			Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
		}
		
		switch (key){
			case '1': while(key=='1'){key = get_key();}baris = 0;SetWaktu(); break;
			case '2': while(key=='2'){key = get_key();}baris = 0;SetTanggal(); break;
			case '3': while(key=='3'){key = get_key();}baris = 0;SetHoliday(); break;
			case '4': while(key=='4'){key = get_key();}baris = 0;SetStartUp(); break;
			case '5': while(key=='5'){key = get_key();}baris = 0;SetPlan(); break;
			case '6': while(key=='6'){key = get_key();}baris = 0;SetProgramHarian(); break;
		}  
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Input Setting");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[1] Keypad");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[2] Komputer (ser)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[3] Komputer (int)");
}

void InputKompSer(){
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Komputer (serial)");
	
	while (key != CAN){
		key = get_key();  
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Input Setting");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[1] Keypad");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[2] Komputer (ser)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[3] Komputer (int)");
}

void InputKompInt(){
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Komputer (internet)");
	
	while (key != CAN){
		key = get_key();  
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Input Setting");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[1] Keypad");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[2] Komputer (ser)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[3] Komputer (int)");
}

void SetWaktu(){				// 1. SetWaktu					
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,3);Lcd4_Write_Flash("SET WAKTU");
	Lcd4_Set_Cursor(2,2);Lcd4_Write_Flash(":  :");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[COR]EDIT/SAVE");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[CAN]EXIT");
	
	while(key != CAN){		
		st1[0]= '0'+ jam/10;st1[1]= '0'+ jam%10;
		Lcd4_Set_Cursor(2,0);Lcd4_Write_String(st1);
		st1[0]= '0'+ mnt/10;st1[1]= '0'+ mnt%10;
		Lcd4_Set_Cursor(2,3);Lcd4_Write_String(st1);
		st1[0]= '0'+ dtk/10;st1[1]= '0'+ dtk%10;
		Lcd4_Set_Cursor(2,6);Lcd4_Write_String(st1);
		
		key = get_key();	 //cuma scanning keypad		

		if(key == COR){
			while(key==COR){key=get_key();}
			while(key != COR){								
				st1[0]= '0'+ jam/10;st1[1]= '0'+ jam%10;
				Lcd4_Set_Cursor(2,0);Lcd4_Write_String(st1);
				st1[0]= '0'+ mnt/10;st1[1]= '0'+ mnt%10;
				Lcd4_Set_Cursor(2,3);Lcd4_Write_String(st1);
				st1[0]= '0'+ dtk/10;st1[1]= '0'+ dtk%10;
				Lcd4_Set_Cursor(2,6);Lcd4_Write_String(st1);
				delay_ms(50);
				key = get_key();
				
				switch(stateset){
					case 0:	
						Lcd4_Set_Cursor(2,0);
						if ((key>='0') && (key<='1')){
							jam = (jam % 10) + ((key-'0') *10);							
							temp= key;
							while(key==temp){key=get_key();}
							stateset=1;
						}								
						else if (key == '2') {
							if ((jam%10 >= 0) && (jam%10 <= 3)){
								jam = (jam % 10) + ((key-'0') *10);							
								temp= key;
								while(key==temp){key=get_key();}
								stateset=1;
							}
						}					
						break;
					case 1:	
						Lcd4_Set_Cursor(2,1);
						if(((jam/10)==0) || ((jam/10)==1)){
							if((key>='0') && (key<='9')){	
							        jam = (jam - (jam % 10)) + (key-'0');							
								temp= key;
								while(key==temp){key=get_key();}
								stateset=2;
							}
						}
						else if((jam/10)==2){
							if((key>='0') && (key<='3')){	
								jam = (jam - (jam % 10)) + (key-'0');							
								temp= key;
								while(key==temp){key=get_key();}
								stateset=2;
							}
						}
						break;
					case 2:	
						Lcd4_Set_Cursor(2,3);
						if((key>='0') && (key<='5')){			
							mnt = (mnt % 10) + ((key-'0') *10);						
							temp= key;
							while(key==temp){key=get_key();}
							stateset=3;
						}
						break;
					case 3:
						Lcd4_Set_Cursor(2,4);
						if((key>='0') && (key<='9')){						
							mnt = (mnt - (mnt % 10)) + (key-'0');					
							temp= key;
							while(key==temp){key=get_key();}
							stateset=4;
						}
						break;
					case 4:
						Lcd4_Set_Cursor(2,6);
						if((key>='0') && (key<='5')){			
							dtk = (dtk % 10) + ((key-'0') *10);							
							temp= key;
							while(key==temp){key=get_key();}
							stateset=5;
						}
						break;
					case 5:	
						Lcd4_Set_Cursor(2,7);
						if((key>='0') && (key<='9')){							
							dtk = (dtk - (dtk % 10)) + (key-'0');				
							temp= key;
							while(key==temp){key=get_key();}
							stateset=0;								
						}
						break;
				}
				Lcd4_Write_Char('_');delay_ms(50); 
                                
                                if(key==UP){           
			                while(key==UP){key=get_key();}
                                        if(stateset==0)
                                                stateset=5;
                                        else
                                                stateset--;
                                }
                                if(key==DOWN){           
			                while(key==DOWN){key=get_key();}
                                        if(stateset==5)
                                                stateset=0;
                                        else
                                                stateset++;
                                }
			}	
			while(key==COR){key=get_key();}
			stateset=0;		
		}																		
	}
	while(key==CAN){key = get_key();}	
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[2] Set tanggal     ");
}

void SetTanggal(){				// 2. SetTanggal				
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,3);Lcd4_Write_Flash("SET TANGGAL");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash(" ,   /  /");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[COR]EDIT/SAVE");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[CAN]EXIT");
	
	while(key != CAN){		
		Lcd4_Set_Cursor(2,0);Lcd4_Write_Char(hr+'0');
		st1[0]= '0'+ tgl/10;st1[1]= '0'+ tgl%10;
		Lcd4_Set_Cursor(2,3);Lcd4_Write_String(st1);
		st1[0]= '0'+ bln/10;st1[1]= '0'+ bln%10;
		Lcd4_Set_Cursor(2,6);Lcd4_Write_String(st1);
		st1[0]= '0'+ thn/1000;st1[1]= '0'+ (thn%1000)/100;
		Lcd4_Set_Cursor(2,9);Lcd4_Write_String(st1);
		st1[0]= '0'+ (thn%100)/10;st1[1]= '0'+ thn%10;
		Lcd4_Set_Cursor(2,11);Lcd4_Write_String(st1);
		
		key = get_key();	 //cuma scanning keypad		

		if(key == COR){
			while(key==COR){key=get_key();}
			while(key != COR){								
				Lcd4_Set_Cursor(2,0);Lcd4_Write_Char(hr+'0');
				st1[0]= '0'+ tgl/10;st1[1]= '0'+ tgl%10;
				Lcd4_Set_Cursor(2,3);Lcd4_Write_String(st1);
				st1[0]= '0'+ bln/10;st1[1]= '0'+ bln%10;
				Lcd4_Set_Cursor(2,6);Lcd4_Write_String(st1);
				st1[0]= '0'+ thn/1000;st1[1]= '0'+ (thn%1000)/100;
				Lcd4_Set_Cursor(2,9);Lcd4_Write_String(st1);
				st1[0]= '0'+ (thn%100)/10;st1[1]= '0'+ thn%10;
				Lcd4_Set_Cursor(2,11);Lcd4_Write_String(st1);
				delay_ms(50);
				key = get_key();
				
				switch(stateset){
					case 0:	
						Lcd4_Set_Cursor(2,0);						
						if((key>='1') && (key<='7')){	
							hr = key-'0';							
							temp= key;
							while(key==temp){key=get_key();}
							stateset=1;
						}								
						break;
					case 1: // tanggal puluhan
						Lcd4_Set_Cursor(2,3);
						if (bln == 2){
							if((tgl%10) == 0){
								if ((key >= '1') && (key <= '2')){
									tgl = (tgl % 10) + ((key-'0') *10);					
									temp= key;
									while(key==temp){key=get_key();}
									stateset=2;
								}
							}
							else{
								if((thn%400 == 0) || ((thn%100!=0) && (thn%4==0))){
									if((key>='0') && (key<='2')){
										tgl = (tgl % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=2;
									}
								}
								else{
									if(((tgl%10)>=1) && ((tgl%10)<=8)){
										if((key>='0') && (key<='2')){
											tgl = (tgl % 10) + ((key-'0') *10);							
											temp= key;
											while(key==temp){key=get_key();}
											stateset=2;
										}
									}
									else if((tgl%10)==9){
										if((key>='0') && (key<='1')){
											tgl = (tgl % 10) + ((key-'0') *10);							
											temp= key;
											while(key==temp){key=get_key();}
											stateset=2;
										}
									}
								}
							}
						}
						else if ((bln==1) || (bln==3) || (bln==5) || (bln==7) || (bln==8) || (bln==10) || (bln==12)){
							if((tgl%10) == 0){
								if ((key >= '1') && (key <= '3')){
									tgl = (tgl % 10) + ((key-'0') *10);					
									temp= key;
									while(key==temp){key=get_key();}
									stateset=2;
								}
							}
							else if((tgl%10)==1){
								if((key>='0') && (key<='3')){
									tgl = (tgl % 10) + ((key-'0') *10);							
									temp= key;
									while(key==temp){key=get_key();}
									stateset=2;
								}
							}
							else if(((tgl%10)>=2) && ((tgl%10)<=9)){
								if((key>='0') && (key<='2')){
									tgl = (tgl % 10) + ((key-'0') *10);							
									temp= key;
									while(key==temp){key=get_key();}
									stateset=2;
								}
							}
						}
						else if ((bln==4) || (bln==6) || (bln==9) || (bln==11)){
							if((tgl%10)==0){
								if((key>='1') && (key<='3')){
									tgl = (tgl % 10) + ((key-'0') *10);							
									temp= key;
									while(key==temp){key=get_key();}
									stateset=2;
								}
							}
							else if(((tgl%10)>=1) && ((tgl%10)<=9)){
								if((key>='0') && (key<='2')){
									tgl = (tgl % 10) + ((key-'0') *10);							
									temp= key;
									while(key==temp){key=get_key();}
									stateset=2;
								}
							}
						}
						break;
					case 2:	//tanggal satuan
						Lcd4_Set_Cursor(2,4);
						if (bln == 2){
							if((tgl/10) == 0){
								if ((key >= '1') && (key <= '9')){
									tgl = (tgl - (tgl % 10)) + (key-'0');					
									temp= key;
									while(key==temp){key=get_key();}
									stateset=3;
								}
							}
							else{
								if((thn%400 == 0) || ((thn%100!=0) && (thn%4==0))){
									if((key>='0') && (key<='9')){
										tgl = (tgl - (tgl % 10)) + (key-'0');							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=3;
									}
								}
								else{
									if((tgl/10) == 1){
										if((key>='0') && (key<='9')){
											tgl = (tgl - (tgl % 10)) + (key-'0');
											temp= key;
											while(key==temp){key=get_key();}
											stateset=3;
										}
									}
									else if((tgl/10) == 2){
										if((key>='0') && (key<='8')){
											tgl = (tgl - (tgl % 10)) + (key-'0');
											temp= key;
											while(key==temp){key=get_key();}
											stateset=3;
										}
									}
								}
							}
						}
						else if ((bln==1) || (bln==3) || (bln==5) || (bln==7) || (bln==8) || (bln==10) || (bln==12)){
							if((tgl/10) == 0){
								if ((key >= '1') && (key <= '9')){
									tgl = (tgl - (tgl % 10)) + (key-'0');					
									temp= key;
									while(key==temp){key=get_key();}
									stateset=3;
								}
							}
							else if(((tgl/10) == 1) || ((tgl/10) == 2)){
								if ((key >= '0') && (key <= '9')){
									tgl = (tgl - (tgl % 10)) + (key-'0');					
									temp= key;
									while(key==temp){key=get_key();}
									stateset=3;
								}
							}
							else if((tgl/10) == 3){
								if ((key >= '0') && (key <= '1')){
									tgl = (tgl - (tgl % 10)) + (key-'0');					
									temp= key;
									while(key==temp){key=get_key();}
									stateset=3;
								}
							}
						}
						else if ((bln==4) || (bln==6) || (bln==9) || (bln==11)){
							if((tgl/10) == 0){
								if ((key >= '1') && (key <= '9')){
									tgl = (tgl - (tgl % 10)) + (key-'0');					
									temp= key;
									while(key==temp){key=get_key();}
									stateset=3;
								}
							}
							else if(((tgl/10) == 1) || ((tgl/10) == 2)){
								if ((key >= '0') && (key <= '9')){
									tgl = (tgl - (tgl % 10)) + (key-'0');					
									temp= key;
									while(key==temp){key=get_key();}
									stateset=3;
								}
							}
							else if((tgl/10) == 3){
								if (key == '0'){
									tgl = (tgl - (tgl % 10)) + (key-'0');					
									temp= key;
									while(key==temp){key=get_key();}
									stateset=3;
								}
							}
						}
						break;
					case 3: //bulan puluhan
						Lcd4_Set_Cursor(2,6);
						if((thn%400 == 0) || ((thn%100!=0) && (thn%4==0))){
							if((tgl>=1) && (tgl<=29)){
								if((bln%10)==0){
									if(key=='1'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if(((bln%10)>=1) && ((bln%10)<=2)){
									if((key>='0') && (key<='1')){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if(((bln%10)>=3) && ((bln%10)<=9)){
									if(key=='0'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
							}
							else if(tgl==30){
								if(((bln%10)==0) || ((bln%10)==2)){
									if(key=='1'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if((bln%10)==1){
									if((key>='0') && (key<='1')){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if(((bln%10)>=3) && ((bln%10)<=9)){
									if(key=='0'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
							}
							else if(tgl==31){
								if(((bln%10)==0) || ((bln%10)==2)){
									if(key=='1'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if(((bln%10)==1) || ((bln%10)==3) || ((bln%10)==5) || ((bln%10)==7) || ((bln%10)==8)){
									if(key=='0'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
							}
						}
						else{
							if((tgl>=1) && (tgl<=28)){
								if((bln%10)==0){
									if(key=='1'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if(((bln%10)>=1) && ((bln%10)<=2)){
									if((key>='0') && (key<='1')){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if(((bln%10)>=3) && ((bln%10)<=9)){
									if(key=='0'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
							}
							else if((tgl>=29) && (tgl<=30)){
								if(((bln%10)==0) || ((bln%10)==2)){
									if(key=='1'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if((bln%10)==1){
									if((key>='0') && (key<='1')){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if(((bln%10)>=3) && ((bln%10)<=9)){
									if(key=='0'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
							}
							else if(tgl==31){
								if(((bln%10)==0) || ((bln%10)==2)){
									if(key=='1'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
								else if(((bln%10)==1) || ((bln%10)==3) || ((bln%10)==5) || ((bln%10)==7) || ((bln%10)==8)){
									if(key=='0'){						
										bln = (bln % 10) + ((key-'0') *10);							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=4;
									}
								}
							}
						}
						break;
					case 4: // satuan bulan
						Lcd4_Set_Cursor(2,7);
						if((thn%400 == 0) || ((thn%100!=0) && (thn%4==0))){
							if((tgl>=1) && (tgl<=29)){
								if((bln/10)==0){
									if((key>='1') && (key<='9')){						
										bln = (bln - (bln % 10)) + (key-'0');							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
								else if((bln/10)==1){
									if((key>='0') && (key<='2')){				
										bln = (bln - (bln % 10)) + (key-'0');							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
							}
							else if(tgl==30){
								if((bln/10)==0){
									if((key=='1') || ((key>='3') && (key<='9'))){		
										bln = (bln - (bln % 10)) + (key-'0');					
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
								else if((bln/10)==1){
									if((key>='0') && (key<='2')){				
										bln = (bln - (bln % 10)) + (key-'0');							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
							}
							else if(tgl==31){
								if((bln/10)==0){
									if((key=='1') || (key=='3') || (key=='5') || (key=='7') || (key=='8')){		
										bln = (bln - (bln % 10)) + (key-'0');	
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
								else if((bln/10)==1){
									if((key=='0') || (key=='2')){									
										bln = (bln - (bln % 10)) + (key-'0');		
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
							}
						}
						else{
							if((tgl>=1) && (tgl<=28)){
								if((bln/10)==0){
									if((key>='1') && (key<='9')){						
										bln = (bln - (bln % 10)) + (key-'0');							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
								else if((bln/10)==1){
									if((key>='0') && (key<='2')){				
										bln = (bln - (bln % 10)) + (key-'0');							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
							}
							else if((tgl==29) || (tgl==30)){
								if((bln/10)==0){
									if((key=='1') || ((key>='3') && (key<='9'))){		
										bln = (bln - (bln % 10)) + (key-'0');					
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
								else if((bln/10)==1){
									if((key>='0') && (key<='2')){				
										bln = (bln - (bln % 10)) + (key-'0');							
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
							}
							else if(tgl==31){
								if((bln/10)==0){
									if((key=='1') || (key=='3') || (key=='5') || (key=='7') || (key=='8')){		
										bln = (bln - (bln % 10)) + (key-'0');	
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
								else if((bln/10)==1){
									if((key=='0') || (key=='2')){									
										bln = (bln - (bln % 10)) + (key-'0');		
										temp= key;
										while(key==temp){key=get_key();}
										stateset=5;
									}
								}
							}
						}
						break;
					case 5:	
						Lcd4_Set_Cursor(2,9);
						if((tgl==29) && (bln==2)){
							if (((((int)(key-'0')*1000) + (thn%1000)) %400 == 0) || (((((int)(key-'0')*1000) + (thn%1000)) %100 != 0) && ((((int)(key-'0')*1000) + (thn%1000)) %4 == 0))){
								if((key>='0') && (key<='9')){							
									thn = (thn % 1000) + ((int)(key-'0')*1000);				
									temp= key;
									while(key==temp){key=get_key();} stateset = 6;
								}
							}
						}
						else{
							if((key>='0') && (key<='9')){							
								thn = (thn % 1000) + ((int)(key-'0')*1000);				
								temp= key;
								while(key==temp){key=get_key();} stateset = 6;
							}
						}
						break;
					case 6:	
						Lcd4_Set_Cursor(2,10);
						if((tgl==29) && (bln==2)){
							if (((((thn/1000)*1000) + ((int)(key-'0')*100) + (thn%100)) %400 == 0) || (((((thn/1000)*1000) + ((int)(key-'0')*100) + (thn%100)) %100 != 0) && ((((thn/1000)*1000) + ((int)(key-'0')*100) + (thn%100)) %4 == 0))){
								if((key>='0') && (key<='9')){							
									thn = (((thn/1000)*1000) + ((int)(key-'0')*100) + (thn%100));				
									temp= key;
									while(key==temp){key=get_key();} stateset = 7;
								}
							}
						}
						else{
							if((key>='0') && (key<='9')){							
								thn = (((thn/1000)*1000) + ((int)(key-'0')*100) + (thn%100));				
								temp= key;
								while(key==temp){key=get_key();} stateset = 7;
							}
						}
						break;
					case 7:	
						Lcd4_Set_Cursor(2,11);
						if((tgl==29) && (bln==2)){
							if ((((thn-(thn%100))+((int)(key-'0')*10)+(thn%10)) %400 == 0) || ((((thn-(thn%100))+((int)(key-'0')*10)+(thn%10)) %100 != 0) && (((thn-(thn%100))+((int)(key-'0')*10)+(thn%10)) %4 == 0))){
								if((key>='0') && (key<='9')){							
									thn = ((thn-(thn % 100))+((int)(key-'0')*10)+(thn%10));				
									temp= key;
									while(key==temp){key=get_key();} stateset = 8;
								}
							}
						}
						else{
							if((key>='0') && (key<='9')){							
								thn = ((thn-(thn%100))+((int)(key-'0')*10)+(thn%10));				
								temp= key;
								while(key==temp){key=get_key();} stateset = 8;
							}
						}
						break;
					case 8:	
						Lcd4_Set_Cursor(2,12);
						if((tgl==29) && (bln==2)){
							if ((((thn-(thn%10))+(key-'0')) %400 == 0) || ((((thn-(thn%10))+(key-'0')) %100 != 0) && (((thn-(thn%10))+(key-'0')) %4 == 0))){
								if((key>='0') && (key<='9')){							
									thn = (thn-(thn%10))+(key-'0');
									temp= key;
									while(key==temp){key=get_key();} stateset = 0;
								}
							}
						}
						else{
							if((key>='0') && (key<='9')){							
								thn = (thn-(thn%10))+(key-'0');				
								temp= key;
								while(key==temp){key=get_key();} stateset = 0;
							}
						}
						break;
				}
				Lcd4_Write_Char('_');delay_ms(50);         
                                if(key==UP){           
			                while(key==UP){key=get_key();}
                                        if(stateset==0)
                                                stateset=8;
                                        else
                                                stateset--;
                                }
                                if(key==DOWN){           
			                while(key==DOWN){key=get_key();}
                                        if(stateset==8)
                                                stateset=0;
                                        else
                                                stateset++;
                                }        
			}	
			while(key==COR){key=get_key();}
			stateset=0;		
		}																		
	}
	while(key==CAN){key = get_key();}	
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[2] Set tanggal     ");
}

void SetHoliday(){				// 3. SetHoliday	
        char a=0;
        baris = 0;
	Lcd4_Clear();delay_ms(50);
	
        Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("SET HARI LBR (dd/mm)");
	
        Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[COR]EDT/SV [ENT]DEL");
        
        strcpy(str[2],"1.   /              ");
        str[2][3] = '0'+ holiday[0]/1000;
        str[2][4] = '0'+ (holiday[0]%1000)/100;
        str[2][6] = '0'+ (holiday[0]%100)/10;
        str[2][7] = '0'+ holiday[0]%10;
        Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
        
        if(jmlholiday==0){
                Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[CAN]EXIT           ");
        }
        else{
                strcpy(str[3],"2.   /              ");
                str[3][3] = '0'+ holiday[1]/1000;
                str[3][4] = '0'+ (holiday[1]%1000)/100;
                str[3][6] = '0'+ (holiday[1]%100)/10;
                str[3][7] = '0'+ holiday[1]%10;
                Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
        }
                
	while(key != CAN){				
		key=get_key();
                Lcd4_Set_Cursor(3,0);Lcd4_Write_Char('_');
                delay_ms(50);  
                if((key==UP) ||(key==DOWN)){
			if(key==UP){
                                while(key==UP){key=get_key();}
				if(baris>0)
					{Lcd4_Clear();delay_ms(50);baris--;}
			}
			if(key==DOWN){          
                                while(key==DOWN){key=get_key();}
				if(baris<jmlholiday)
					{Lcd4_Clear();delay_ms(50);baris++;}
			}
			
			if(baris==0){				    
				strcpy(str[0],"SET HARI LBR (dd/mm)");
			}
                        if((baris>=0) && (baris<=1)){
				strcpy(str[1 - baris],"[COR]EDT/SV [ENT]DEL");
			}
			for(i=0;i<=jmlholiday;i++){  
                                if(((i + 2 - baris) >= 0) && ((i + 2 - baris) <=3)){
                                        strcpy(str[i + 2 - baris]," .   /              ");
                                        str[i + 2 - baris][0] = i + '1';
                                        str[i + 2 - baris][3] = '0'+ holiday[i]/1000;
                                        str[i + 2 - baris][4] = '0'+ (holiday[i]%1000)/100;
                                        str[i + 2 - baris][6] = '0'+ (holiday[i]%100)/10;
                                        str[i + 2 - baris][7] = '0'+ holiday[i]%10;
                                }
                        }
			if(baris==jmlholiday){
				strcpy(str[3],"[CAN]EXIT           ");
			} 
			Lcd4_Set_Cursor(1,0);Lcd4_Write_String(str[0]);
			Lcd4_Set_Cursor(2,0);Lcd4_Write_String(str[1]);
			Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
			Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
		}	
	        
                Lcd4_Set_Cursor(3,0);Lcd4_Write_Char(str[2][0]);
                delay_ms(50);
		
                if(key==COR){     
                        while(key==COR){key=get_key();}   
                        while(key != COR){ 
                                st1[0] = '0'+ holiday[baris]/1000;st1[1] = '0'+ (holiday[baris]%1000)/100;
                                Lcd4_Set_Cursor(3,3);Lcd4_Write_String(st1);			
                                st1[0] = '0'+ (holiday[baris]%100)/10;st1[1] = '0'+ holiday[baris]%10;
                                Lcd4_Set_Cursor(3,6);Lcd4_Write_String(st1);
                                delay_ms(50);							
                                key=get_key();
                                
                                switch(stateset){
					case 0:	
						Lcd4_Set_Cursor(3,3);
						if ((holiday[baris]%100) == 2){
							if(((holiday[baris]/100)%10) == 0){
								if ((key >= '1') && (key <= '2')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((int)(key-'0')*1000) + (holiday[baris]%1000)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((int)(key-'0') *1000) + (holiday[baris]%1000);
										stateset=1;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if((((holiday[baris]/100)%10)>=1) && (((holiday[baris]/100)%10)<=9)){
								if((key>='0') && (key<='2')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((int)(key-'0')*1000) + (holiday[baris]%1000)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((int)(key-'0') *1000) + (holiday[baris]%1000);
										stateset=1;
									}			
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						}
						else if (((holiday[baris]%100)==1)||((holiday[baris]%100)==3)||((holiday[baris]%100)==5)||((holiday[baris]%100)==7)||((holiday[baris]%100)==8)||((holiday[baris]%100)==10)||((holiday[baris]%100)==12)){
							if(((holiday[baris]/100)%10) == 0){
								if ((key >= '1') && (key <= '3')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((int)(key-'0')*1000) + (holiday[baris]%1000)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((int)(key-'0') *1000) + (holiday[baris]%1000);
										stateset=1;
									}			
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if(((holiday[baris]/100)%10)==1){
								if((key>='0') && (key<='3')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((int)(key-'0')*1000) + (holiday[baris]%1000)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((int)(key-'0') *1000) + (holiday[baris]%1000);
										stateset=1;
									}			
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if((((holiday[baris]/100)%10)>=2) && (((holiday[baris]/100)%10)<=9)){
								if((key>='0') && (key<='2')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((int)(key-'0')*1000) + (holiday[baris]%1000)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((int)(key-'0') *1000) + (holiday[baris]%1000);
										stateset=1;
									}			
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						}
						else if (((holiday[baris]%100)==4)||((holiday[baris]%100)==6)||((holiday[baris]%100)==9)||((holiday[baris]%100)==11)){
							if(((holiday[baris]/100)%10)==0){
								if((key>='1') && (key<='3')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((int)(key-'0')*1000) + (holiday[baris]%1000)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((int)(key-'0') *1000) + (holiday[baris]%1000);
										stateset=1;
									}			
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if((((holiday[baris]/100)%10)>=1) && (((holiday[baris]/100)%10)<=9)){
								if((key>='0') && (key<='2')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((int)(key-'0')*1000) + (holiday[baris]%1000)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((int)(key-'0') *1000) + (holiday[baris]%1000);
										stateset=1;
									}			
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						}
						break;
					case 1:	
						Lcd4_Set_Cursor(3,4);
						if ((holiday[baris]%100) == 2){
							if((holiday[baris]/1000) == 0){
								if ((key >= '1') && (key <= '9')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100);
										stateset=2;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if(((holiday[baris]/1000)>=1) && ((holiday[baris]/1000)<=2)){
								if((key>='0') && (key<='9')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100);
										stateset=2;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						}
						else if (((holiday[baris]%100)==1)||((holiday[baris]%100)==3)||((holiday[baris]%100)==5)||((holiday[baris]%100)==7)||((holiday[baris]%100)==8)||((holiday[baris]%100)==10)||((holiday[baris]%100)==12)){
							if((holiday[baris]/1000) == 0){
								if ((key >= '1') && (key <= '9')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100);
										stateset=2;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if(((holiday[baris]/1000)>=1) && ((holiday[baris]/1000)<=2)){
								if((key>='0') && (key<='9')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100);
										stateset=2;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if((holiday[baris]/1000)==3){
								if((key>='0') && (key<='1')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100);
										stateset=2;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						}
						else if (((holiday[baris]%100)==4)||((holiday[baris]%100)==6)||((holiday[baris]%100)==9)||((holiday[baris]%100)==11)){
							if((holiday[baris]/1000)==0){
								if((key>='1') && (key<='9')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100);
										stateset=2;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if(((holiday[baris]/1000)>=1) && ((holiday[baris]/1000)<=2)){
								if((key>='0') && (key<='9')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100);
										stateset=2;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						        else if((holiday[baris]/1000)==3){
								if(key=='0'){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/1000)*1000) + ((int)(key-'0')*100) + (holiday[baris]%100);
										stateset=2;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
                                                }
						break;
					case 2:	
						Lcd4_Set_Cursor(3,6);
						if (((holiday[baris]/100) >= 1) && ((holiday[baris]/100) <= 29)){
							if((holiday[baris]%10) == 0){
								if (key == '1'){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10);
										stateset=3;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if(((holiday[baris]%10)>=1) && ((holiday[baris]%10)<=2)){
								if((key>='0') && (key<='1')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10);
										stateset=3;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						        else if(((holiday[baris]%10)>=3) && ((holiday[baris]%10)<=9)){
								if(key=='0'){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10);
										stateset=3;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
                                                }
						else if ((holiday[baris]/100) == 30){
							if(((holiday[baris]%10) == 0) || ((holiday[baris]%10) == 2)){
								if(key == '1'){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10);
										stateset=3;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if((holiday[baris]%10)==1){
								if((key>='0') && (key<='1')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10);
										stateset=3;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if(((holiday[baris]%10)>=3) && ((holiday[baris]%10)<=9)){
								if(key=='0'){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10);
										stateset=3;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						}
						else if ((holiday[baris]/100) == 31){
							if(((holiday[baris]%10)==0) || ((holiday[baris]%10)==2)){
								if(key=='1'){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10);
										stateset=3;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
							else if(((holiday[baris]%10)==1) || ((holiday[baris]%10)==3) || ((holiday[baris]%10)==5) || ((holiday[baris]%10)==7) || ((holiday[baris]%10)==8)){
								if(key=='0'){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10)) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/100)*100) + ((int)(key-'0')*10) + (holiday[baris]%10);
										stateset=3;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						}
						break;
					case 3:
						Lcd4_Set_Cursor(3,7);
						if (((holiday[baris]/100) >= 1) && ((holiday[baris]/100) <= 29)){
							if(((holiday[baris]%100)/10) == 0){
								if ((key >= '1') && (key <= '9')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/10)*10) + (key-'0')) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/10)*10) + (key-'0');
										stateset=0;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						        else if(((holiday[baris]%100)/10)==1){
								if((key >= '0') && (key <= '2')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/10)*10) + (key-'0')) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/10)*10) + (key-'0');
										stateset=0;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
                                                }
						else if ((holiday[baris]/100) == 30){
							if(((holiday[baris]%100)/10) == 0){
								if ((key == '1') || ((key >= '3') && (key <= '9'))){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/10)*10) + (key-'0')) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/10)*10) + (key-'0');
										stateset=0;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						        else if(((holiday[baris]%100)/10)==1){
								if((key >= '0') && (key <= '2')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/10)*10) + (key-'0')) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/10)*10) + (key-'0');
										stateset=0;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						}
						else if ((holiday[baris]/100) == 31){
							if(((holiday[baris]%100)/10) == 0){
								if ((key == '1') || (key == '3') || (key == '5') || (key == '7') || (key == '8')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/10)*10) + (key-'0')) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/10)*10) + (key-'0');
										stateset=0;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						        else if(((holiday[baris]%100)/10)==1){
								if((key=='0') || (key == '2')){
									for(i=0;i<jmlholiday;i++){
										if(i!=baris){
											if((((holiday[baris]/10)*10) + (key-'0')) == holiday[i])
												a=1;
										}
									}
									if(a==0){
										holiday[baris] = ((holiday[baris]/10)*10) + (key-'0');
										stateset=0;
									}
									temp= key;
									while(key==temp){key=get_key();}
									a=0;
								}
							}
						}
						break;
				}
				Lcd4_Write_Char('_');delay_ms(50);
                                if(key==UP){           
			                while(key==UP){key=get_key();}
                                        if(stateset==0)
                                                stateset=3;
                                        else
                                                stateset--;
                                }
                                if(key==DOWN){           
			                while(key==DOWN){key=get_key();}
                                        if(stateset==3)
                                                stateset=0;
                                        else
                                                stateset++;
                                }
		     
			}                            
                        while(key==COR){key=get_key();}    
                        st1[0] = '0'+ holiday[baris]/1000;st1[1] = '0'+ (holiday[baris]%1000)/100;
                        Lcd4_Set_Cursor(3,3);Lcd4_Write_String(st1);			
                        st1[0] = '0'+ (holiday[baris]%100)/10;st1[1] = '0'+ holiday[baris]%10;
                        Lcd4_Set_Cursor(3,6);Lcd4_Write_String(st1);  
                        
                        if((baris==jmlholiday) && (holiday[baris]!=0) && (jmlholiday<25)){
                                jmlholiday++;                          
                                strcpy(str[3]," . 00/00            ");
                                str[3][0] = jmlholiday + '1';
                                Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
                        }
                        stateset=0;
                }
                 
                if(key==ENT){     
                        while(key==ENT){key=get_key();} 
                        if(baris!=jmlholiday){
                                if(jmlholiday<25){
                                        for(i=baris;i<jmlholiday;i++){
                                                holiday[i] = holiday[i+1];
                                        }                          
                                        jmlholiday--;   
                                        strcpy(str[2]," .   /              ");
                                } 
                                else{    
                                        for(i=baris;i<24;i++){
                                                holiday[i] = holiday[i+1];
                                        }                
                                        holiday[24]=0; 
                                        jmlholiday--;      
                                        strcpy(str[2]," .   /              ");
                                }
                        }
                        
                        str[2][0] = baris + '1'; 
                        str[2][3] = '0'+ holiday[baris]/1000;
                        str[2][4] = '0'+ (holiday[baris]%1000)/100;
                        str[2][6] = '0'+ (holiday[baris]%100)/10;
                        str[2][7] = '0'+ holiday[baris]%10;
                        Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
                        
                        if(baris<jmlholiday){              
                                strcpy(str[3]," .   /              ");
                                str[3][0] = baris + '2';        
                                str[3][3] = '0'+ holiday[(int)baris+1]/1000;
                                str[3][4] = '0'+ (holiday[(int)baris+1]%1000)/100;
                                str[3][6] = '0'+ (holiday[(int)baris+1]%100)/10;
                                str[3][7] = '0'+ holiday[(int)baris+1]%10;       
                                Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
                        }                               
                        else{                                                        
                                strcpy(str[3],"[CAN]EXIT           ");
                                Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
                        }
                }
                
        }
	while(key==CAN){key=get_key();}
	baris=0;
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[2] Set tanggal     ");
}

void SetStartUp(){				// 4. SetStartUp				
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,2);Lcd4_Write_Flash("SET STARTUP");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("Waktu Start Up:");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[COR]EDIT/SAVE");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[CAN]EXIT");
	
	while(key != CAN){		
		st1[0]= '0'+ dtkstartup/10;st1[1]= '0'+ dtkstartup%10;
		Lcd4_Set_Cursor(2,16);Lcd4_Write_String(st1);
		
		key = get_key();
		
		if(key == COR){
			while(key==COR){key=get_key();}
			while (key != COR){									
				key = get_key();
				st1[0]= '0'+ dtkstartup/10;st1[1]= '0'+ dtkstartup%10;
				Lcd4_Set_Cursor(2,16);Lcd4_Write_String(st1);delay_ms(50);
				
				switch(stateset){
					case 0:
						Lcd4_Set_Cursor(2,16);	
						if((key>='0') && (key<='9')){
							dtkstartup = (dtkstartup % 10) + ((key-'0') *10);
							temp=key;
							while(key==temp){key=get_key();}
							stateset=1;		
						}
						break;
					case 1:
						Lcd4_Set_Cursor(2,17);							
						if((key>='0') && (key<='9')){
							dtkstartup = (dtkstartup - (dtkstartup % 10)) + (key-'0');
							temp=key;
							while(key==temp){key=get_key();}
							stateset=0;
						}
						break;
				}
				Lcd4_Write_Char('_');delay_ms(50);
			}
			while(key==COR){key=get_key();} 
			stateset=0;
		}			
	}
	while(key==CAN){key = get_key();}	
	Lcd4_Clear();delay_ms(50);	
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[2] Set tanggal     ");
}

void SetPlan(){					// 5. SetPlan							
	planpilihan=1;
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Pilih Plan");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("Plan:");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[COR]EDIT  [CAN]EXIT");
	
	while(key != CAN){		
		key = get_key();
		st1[0]= '0'+ planpilihan/10;st1[1]= '0'+ planpilihan%10;
		Lcd4_Set_Cursor(2,6);Lcd4_Write_String(st1);delay_ms(50);
				
		switch(stateset){
			case 0:
				Lcd4_Set_Cursor(2,6);	
				if((key>='0') && (key<='9')){
					planpilihan = (planpilihan % 10) + ((key-'0') *10);
					temp=key;
					while(key==temp){key=get_key();}
					stateset=1;		
				}
				break;
			case 1:
				Lcd4_Set_Cursor(2,7);							
				if((key>='0') && (key<='9')){
					planpilihan = (planpilihan - (planpilihan % 10)) + (key-'0');
					temp=key;
					while(key==temp){key=get_key();}
					stateset=0;
				}
				break;
		}
		Lcd4_Write_Char('_');delay_ms(50);
		
		if(key==COR){
			while(key==COR){key=get_key();} 
			stateset=0;
			SetPlanPilih();
		}
	}		
	stateset=0;
	while(key==CAN){key=get_key();}
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[2] Set tanggal     ");
}

void SetPlanPilih(){			// 5.a. SetPlanPilih
	char tlist[16];
	baris=0;
	
	switch(planpilihan){
		case 1:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan1[temp];
		break;
		case 2:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan2[temp];
		break;
		/*case 3:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan3[temp];
		break;
		case 4:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan4[temp];
		break;
		case 5:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan5[temp];
		break;
		case 6:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan6[temp];
		break;
		case 7:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan7[temp];
		break;
		case 8:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan8[temp];
		break;
		case 9:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan9[temp];
		break;
		case 10:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan10[temp];
		break;
		case 11:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan11[temp];
		break;
		case 12:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan12[temp];
		break;
		case 13:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan13[temp];
		break;
		case 14:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan14[temp];
		break;
		case 15:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan15[temp];
		break;
		case 16:
			for(temp=0;temp<16;temp++)
				tlist[temp] = listplan16[temp];
		break;*/
	}
	
	Lcd4_Clear();delay_ms(50);
	
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Plan-");			// baris 1
	st1[0]= '0'+ planpilihan/10;st1[1]= '0'+ planpilihan%10;
	Lcd4_Set_Cursor(1,5);Lcd4_Write_String(st1);
	
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[COR] EDIT/SAVE");	// baris 2
	
	//Lcd4_Set_Cursor(3,0);
	strcpy(str[2],"1. L1 =    -   ");	// baris 3
	str[2][8] = (tlist[0]/100) + '0'; str[2][9] = ((tlist[0]%100)/10) + '0';str[2][10] = (tlist[0]%10) + '0';
	str[2][12] = (tlist[1]/100) + '0'; str[2][13] = ((tlist[1]%100)/10) + '0'; str[2][14] = (tlist[1]%10) + '0';
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
	
	//Lcd4_Set_Cursor(4,0);
	strcpy(str[3],"2. L2 =    -   ");	// baris 4
	str[3][8] = (tlist[2]/100) + '0'; str[3][9] = ((tlist[2]%100)/10) + '0';str[3][10] = (tlist[2]%10) + '0';
	str[3][12] = (tlist[3]/100) + '0'; str[3][13] = ((tlist[3]%100)/10) + '0'; str[3][14] = (tlist[3]%10) + '0';
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
	
	while (key != CAN){
		key = get_key();
		Lcd4_Set_Cursor(3,0); Lcd4_Write_Char('_'); delay_ms(50); 
		if((key==UP) ||(key==DOWN)){
			if(key==UP){   
                                while(key==UP){key=get_key();}
				if(baris>0)
					{Lcd4_Clear();delay_ms(50);baris--;}
			}
			if(key==DOWN){  
                                while(key==DOWN){key=get_key();}
				if(baris<7)
					{Lcd4_Clear();delay_ms(50);baris++;}
			}
			
			if((baris>=0) && (baris<=0)){				    
				strcpy(str[0 - baris],"Plan-   ");
				str[0 - baris][5]= '0'+ planpilihan/10;str[0 - baris][6]= '0'+ planpilihan%10;
			}
                        if((baris>=0) && (baris<=1)){
				strcpy(str[1 - baris],"[COR] EDIT/SAVE");
			}
                        if((baris>=0) && (baris<=2)){
				strcpy(str[2-baris],"1. L1 =    -   ");
				str[2-baris][8]=(tlist[0]/100)+'0';str[2-baris][9]=((tlist[0]%100)/10)+'0';str[2-baris][10]=(tlist[0]%10)+'0';
				str[2-baris][12]=(tlist[1]/100)+'0';str[2-baris][13]=((tlist[1]%100)/10)+'0';str[2-baris][14]=(tlist[1]%10)+'0';
			}	
			if((baris>=0) && (baris<=3)){
				strcpy(str[3-baris],"2. L2 =    -   ");
				str[3-baris][8]=(tlist[2]/100)+'0';str[3-baris][9]=((tlist[2]%100)/10)+'0';str[3-baris][10]=(tlist[2]%10)+'0';
				str[3-baris][12]=(tlist[3]/100)+'0';str[3-baris][13]=((tlist[3]%100)/10)+'0';str[3-baris][14]=(tlist[3]%10)+'0';
			}	
			if((baris>=1) && (baris<=4)){
				strcpy(str[4-baris],"3. L3 =    -   ");
				str[4-baris][8]=(tlist[4]/100)+'0';str[4-baris][9]=((tlist[4]%100)/10)+'0';str[4-baris][10]=(tlist[4]%10)+'0';
				str[4-baris][12]=(tlist[5]/100)+'0';str[4-baris][13]=((tlist[5]%100)/10)+'0';str[4-baris][14]=(tlist[5]%10)+'0';
			}	 
			if((baris>=2) && (baris<=5)){
				strcpy(str[5-baris],"4. L4 =    -   ");
				str[5-baris][8]=(tlist[6]/100)+'0';str[5-baris][9]=((tlist[6]%100)/10)+'0';str[5-baris][10]=(tlist[6]%10)+'0';
				str[5-baris][12]=(tlist[7]/100)+'0';str[5-baris][13]=((tlist[7]%100)/10)+'0';str[5-baris][14]=(tlist[7]%10)+'0';
			}	 
			if((baris>=3) && (baris<=6)){
				strcpy(str[6-baris],"5. L5 =    -   ");
				str[6-baris][8]=(tlist[8]/100)+'0';str[6-baris][9]=((tlist[8]%100)/10)+'0';str[6-baris][10]=(tlist[8]%10)+'0';
				str[6-baris][12]=(tlist[9]/100)+'0';str[6-baris][13]=((tlist[9]%100)/10)+'0';str[6-baris][14]=(tlist[9]%10)+'0';
			}	 
			if((baris>=4) && (baris<=7)){
				strcpy(str[7-baris],"6. L6 =    -   ");
				str[7-baris][8]=(tlist[10]/100)+'0';str[7-baris][9]=((tlist[10]%100)/10)+'0';str[7-baris][10]=(tlist[10]%10)+'0';
				str[7-baris][12]=(tlist[11]/100)+'0';str[7-baris][13]=((tlist[11]%100)/10)+'0';str[7-baris][14]=(tlist[11]%10)+'0';
			}	 
			if((baris>=5) && (baris<=7)){
				strcpy(str[8-baris],"7. L7 =    -   ");
				str[8-baris][8]=(tlist[12]/100)+'0';str[8-baris][9]=((tlist[12]%100)/10)+'0';str[8-baris][10]=(tlist[12]%10)+'0';
				str[8-baris][12]=(tlist[13]/100)+'0';str[8-baris][13]=((tlist[13]%100)/10)+'0';str[8-baris][14]=(tlist[13]%10)+'0';
			}
			if((baris>=6) && (baris<=7)){
				strcpy(str[9-baris],"8. L8 =    -   ");
				str[9-baris][8]=(tlist[14]/100)+'0';str[9-baris][9]=((tlist[14]%100)/10)+'0';str[9-baris][10]=(tlist[14]%10)+'0';
				str[9-baris][12]=(tlist[15]/100)+'0';str[9-baris][13]=((tlist[15]%100)/10)+'0';str[9-baris][14]=(tlist[15]%10)+'0';
			}	 
			if((baris>=7) && (baris<=7)){
				strcpy(str[10 - baris],"[CAN] EXIT     ");
			}
			Lcd4_Set_Cursor(1,0);Lcd4_Write_String(str[0]);
			Lcd4_Set_Cursor(2,0);Lcd4_Write_String(str[1]);
			Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
			Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
		}	
	        
                Lcd4_Set_Cursor(3,0); Lcd4_Write_Char(str[2][0]); delay_ms(50);      
                
                if (key == COR){ 
			while(key==COR){key=get_key();}	
			while(key!=COR){
				st1[0]= '0'+ tlist[2*(int)baris]/100; st1[1]= '0'+ (tlist[2*(int)baris]%100)/10;
				Lcd4_Set_Cursor(3,8);Lcd4_Write_String(st1);                                      
                                st1[0] = '0' + tlist[2*(int)baris]%10;     
                                Lcd4_Set_Cursor(3,10);Lcd4_Write_Char(st1[0]);
				st1[0]= '0'+ tlist[(2*(int)baris)+1]/100; st1[1]= '0'+ (tlist[(2*(int)baris)+1]%100)/10;
				Lcd4_Set_Cursor(3,12);Lcd4_Write_String(st1);                                             
                                st1[0] = '0'+ tlist[(2*(int)baris)+1]%10;
				Lcd4_Set_Cursor(3,14);Lcd4_Write_Char(st1[0]);
				delay_ms(50);key = get_key();
				
				switch(stateset){
					case 0:	
						Lcd4_Set_Cursor(3,8);						
						if((key>='0') && (key<='1')){	                   
                                                        if((((int)(key-'0')*100) + (tlist[2*(int)baris]%100)) <= tlist[(2*(int)baris)+1]){
							        tlist[2*(int)baris] = ((int)(key-'0')*100) + (tlist[2*(int)baris]%100);   
							        stateset=1;
                                                        }
							temp= key;
							while(key==temp){key=get_key(); }
						}
						break;
							
					case 1:	
						Lcd4_Set_Cursor(3,9);							
						if((key>='0') && (key<='9')){	                      
                                                        if((((tlist[2*(int)baris]/100)*100) + ((int)(key-'0')*10) + (tlist[2*(int)baris]%10)) <= tlist[(2*(int)baris)+1]){
							        tlist[2*(int)baris] = ((tlist[2*(int)baris]/100)*100) + ((int)(key-'0')*10) + (tlist[2*(int)baris]%10); 
							        stateset=2;
                                                        }
							temp = key;
							while(key==temp){key=get_key();}
						}
						break;
							
					case 2:	
						Lcd4_Set_Cursor(3,10);
						if((key>='0') && (key<='9')){			                
                                                        if((((tlist[2*(int)baris]/10)*10) + (key-'0')) <= tlist[(2*(int)baris)+1]){
							        tlist[2*(int)baris] = ((tlist[2*(int)baris]/10)*10) + (key-'0'); 
							        stateset=3;    
                                                        }
							temp = key;
							while(key==temp){key=get_key();}
						}
						break;
							
					case 3:
						Lcd4_Set_Cursor(3,12);
						if((key>='0') && (key<='1')){				
                                                        if(tlist[(2*(int)baris)] <= (((int)(key-'0')*100) + (tlist[(2*(int)baris)+1]%100))){		
							        tlist[(2*(int)baris)+1] = ((int)(key-'0')*100) + (tlist[(2*(int)baris)+1]%100);    
							        stateset=4;
                                                        }
							temp = key;
							while(key==temp){key=get_key();}
						}
						break;
							
					case 4:
						Lcd4_Set_Cursor(3,13);
						if((key>='0') && (key<='9')){			                                        
                                                        if(tlist[(2*(int)baris)] <= (((tlist[(2*(int)baris)+1]/100)*100) + ((int)(key -'0')*10) + (tlist[(2*(int)baris)+1]%10))){	
							        tlist[(2*(int)baris)+1] = ((tlist[(2*(int)baris)+1]/100)*100) + ((int)(key -'0')*10) + (tlist[(2*(int)baris)+1]%10);
							        stateset=5; 
                                                        }
							temp= key;
							while(key==temp){key=get_key();}
						}
						break;
								
					case 5:	
						Lcd4_Set_Cursor(3,14);
						if((key>='0') && (key<='9')){					
                                                        if(tlist[(2*(int)baris)] <= (((tlist[(2*(int)baris)+1]/10)*10) + (int)(key-'0'))){		
							        tlist[(2*(int)baris)+1] = ((tlist[(2*(int)baris)+1]/10)*10) + (int)(key-'0');	     
							        stateset=0;
                                                        }			
							temp= key;
							while(key==temp){key=get_key(); }					
						}
						break;
				}
	
				Lcd4_Write_Char('_');delay_ms(50);     
                                if(key==UP){           
			                while(key==UP){key=get_key();}
                                        if(stateset==0)
                                                stateset=5;
                                        else
                                                stateset--;
                                }
                                if(key==DOWN){           
			                while(key==DOWN){key=get_key();}
                                        if(stateset==5)
                                                stateset=0;
                                        else
                                                stateset++;
                                }
			}
			while(key==COR){key=get_key();} 
			strcpy(str[2]," . L  =    -   ");
	                str[2][0] = '1'+baris; str[2][4] = '1'+baris;
                        str[2][8]= '0'+ tlist[2*(int)baris]/100; str[2][9]= '0'+ (tlist[2*(int)baris]%100)/10; str[2][10] = '0' + tlist[2*(int)baris]%10;     
                        str[2][12]= '0'+ tlist[(2*(int)baris)+1]/100; str[2][13]= '0'+ (tlist[(2*(int)baris)+1]%100)/10; str[2][14] = '0'+ tlist[(2*(int)baris)+1]%10;
			Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
                        stateset=0;		
		}
	}
	while(key==CAN){key=get_key();}
	
        // balikin simpen tlist di listplan yg sesuai
        switch(planpilihan){
		case 1:
			for(temp=0;temp<16;temp++)
				listplan1[temp] = tlist[temp];
		break;
		case 2:
			for(temp=0;temp<16;temp++)
				listplan2[temp] = tlist[temp];
		break;
		/*case 3:
			for(temp=0;temp<16;temp++)
				listplan3[temp] = tlist[temp];
		break;
		case 4:
			for(temp=0;temp<16;temp++)
				listplan4[temp] = tlist[temp];
		break;
		case 5:
			for(temp=0;temp<16;temp++)
				listplan5[temp] = tlist[temp];
		break;
		case 6:
			for(temp=0;temp<16;temp++)
				listplan6[temp] = tlist[temp];
		break;
		case 7:
			for(temp=0;temp<16;temp++)
				listplan7[temp] = tlist[temp];
		break;
		case 8:
			for(temp=0;temp<16;temp++)
				listplan8[temp] = tlist[temp];
		break;
		case 9:
			for(temp=0;temp<16;temp++)
				listplan9[temp] = tlist[temp];
		break;
		case 10:
			for(temp=0;temp<16;temp++)
				listplan10[temp] = tlist[temp];
		break;
		case 11:
			for(temp=0;temp<16;temp++)
				listplan11[temp] = tlist[temp];
		break;
		case 12:
			for(temp=0;temp<16;temp++)
				listplan12[temp] = tlist[temp];
		break;
		case 13:
			for(temp=0;temp<16;temp++)
				listplan13[temp] = tlist[temp];
		break;
		case 14:
			for(temp=0;temp<16;temp++)
				listplan14[temp] = tlist[temp];
		break;
		case 15:
			for(temp=0;temp<16;temp++)
				listplan15[temp] = tlist[temp];
		break;
		case 16:
			for(temp=0;temp<16;temp++)
				listplan16[temp] = tlist[temp];
		break;*/
	}
        
        baris=0;
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Pilih Plan");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("Plan:");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[COR]EDIT  [CAN]EXIT");
}

void SetProgramHarian(){		// 6. SetProgramHarian					
	progharpilihan=1;
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Pilih Program Harian");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("Prgrm Harian:  ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("1(MGG)-7(SBT),8(LBR)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[COR]EDIT  [CAN]EXIT");
	
	while (key != CAN){
		key = get_key();
		st1[0]= '0'+ progharpilihan;
		Lcd4_Set_Cursor(2,14);Lcd4_Write_Char(st1[0]);delay_ms(50);		
		Lcd4_Set_Cursor(2,14);
		if((key>='0') && (key<='9')){
			progharpilihan = key - '0';
			temp=key;
			while(key==temp){key=get_key();}
		}
		if(key==COR){
			while(key==COR){key=get_key();} 
			SetProgramHarianPilih();
		}
		Lcd4_Write_Char('_');delay_ms(50);
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();delay_ms(50);  
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[2] Set tanggal     ");
}

void SetProgramHarianPilih(){	// 6.a. SetProgramHarianPilih
        char b=0;
	long int tprog[20];     
        char tjmllist;
	baris=0;
	
	switch(progharpilihan){
		case 1:
			for(temp=0;temp<20;temp++)
				{tprog[temp] = listproghar1[temp];}
		break;
		case 2:
			for(temp=0;temp<20;temp++)
				{tprog[temp] = listproghar2[temp];}
		break;
		/*case 3:
			for(temp=0;temp<20;temp++)
				{tprog[temp] = listproghar3[temp];}
		break;
		case 4:
			for(temp=0;temp<20;temp++)
				{tprog[temp] = listproghar4[temp];}
		break;
		case 5:
			for(temp=0;temp<20;temp++)
				{tprog[temp] = listproghar5[temp];}
		break;
		case 6:
			for(temp=0;temp<20;temp++)
				{tprog[temp] = listproghar6[temp];}
		break;
		case 7:
			for(temp=0;temp<20;temp++)
				{tprog[temp] = listproghar7[temp];}
		break;
		case 8:
			for(temp=0;temp<20;temp++)
				{tprog[temp] = listproghar8[temp];}
		break;*/
	}
	tjmllist = jmllistproghar[progharpilihan-1];
        
        Lcd4_Clear();delay_ms(50);
	
        Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Prgrm Harian [ ]");      // baris 1
	st1[0] = progharpilihan + '0';
	Lcd4_Set_Cursor(1,14);Lcd4_Write_Char(st1[0]);
	switch (progharpilihan){																	// baris 2
		case 1:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_Flash("MGG");  break;
		case 2:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_Flash("SNN");  break;
		case 3:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_Flash("SLS");  break;
		case 4:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_Flash("RAB");  break;
		case 5:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_Flash("KMS");  break;
		case 6:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_Flash("JMT");  break;
		case 7:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_Flash("SBT");  break;
		case 8:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_Flash("LBR");  break;
	}
	
        Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("[COR]EDT/SV [ENT]DEL");  // baris 2
        
        strcpy(str[2],"1.   :    PLAN:     ");                          // baris 3
        str[2][3] = '0'+ tprog[0]/100000;
        str[2][4] = '0'+ (tprog[0]%100000)/10000;
        str[2][6] = '0'+ (tprog[0]%10000)/1000;
        str[2][7] = '0'+ (tprog[0]%1000)/100;
        str[2][16] = '0'+ (tprog[0]%100)/10;
        str[2][17] = '0'+ tprog[0]%10;                      
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
        
        if(jmlholiday==0){
                Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[CAN]EXIT           ");
        }
        else{
                strcpy(str[3],"2.   :    PLAN:     ");                          // baris 3
                str[3][3] = '0'+ tprog[1]/100000;
                str[3][4] = '0'+ (tprog[1]%100000)/10000;
                str[3][6] = '0'+ (tprog[1]%10000)/1000;
                str[3][7] = '0'+ (tprog[1]%1000)/100;
                str[3][16] = '0'+ (tprog[1]%100)/10;
                str[3][17] = '0'+ tprog[1]%10;              
	        Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
        }
        
	while (key != CAN){
		key = get_key();
                Lcd4_Set_Cursor(3,0);Lcd4_Write_Char('_');
                delay_ms(50);  
                if((key==UP) ||(key==DOWN)){
			if(key==UP){
                                while(key==UP){key=get_key();}
				if(baris>0)
					{Lcd4_Clear();delay_ms(50);baris--;}
			}
			if(key==DOWN){          
                                while(key==DOWN){key=get_key();}
				if(baris<tjmllist)
					{Lcd4_Clear();delay_ms(50);baris++;}
			}
			
			if(baris==0){				    
				strcpy(str[0],"Prgrm Harian [ ]    ");   
	                        str[0][14] = progharpilihan + '0';  
	                        switch (progharpilihan){																	// baris 2
                        		case 1:  
			                        str[0][17]='M';str[0][18]='G';str[0][19]='G'; break;
		                        case 2:  
			                        str[0][17]='S';str[0][18]='N';str[0][19]='N'; break;
		                        case 3:  
			                        str[0][17]='S';str[0][18]='L';str[0][19]='S'; break;
		                        case 4:  
			                        str[0][17]='R';str[0][18]='A';str[0][19]='B'; break;
		                        case 5:  
			                        str[0][17]='K';str[0][18]='M';str[0][19]='S'; break;
		                        case 6:  
			                        str[0][17]='J';str[0][18]='M';str[0][19]='T'; break;
		                        case 7:  
			                        str[0][17]='S';str[0][18]='B';str[0][19]='T'; break;
                        		case 8:  
			                        str[0][17]='L';str[0][18]='B';str[0][19]='R'; break;
                        	}
			}
                        if((baris>=0) && (baris<=1)){
				strcpy(str[1 - baris],"[COR]EDT/SV [ENT]DEL");
			}
			for(i=0;i<=tjmllist;i++){  
                                if(((i + 2 - baris) >= 0) && ((i + 2 - baris) <=3)){
                                        strcpy(str[i + 2 - baris]," .   :    PLAN:     ");
                                        str[i + 2 - baris][0]  = i + '1';
                                        str[i + 2 - baris][3]  = '0'+ tprog[i]/100000;
                                        str[i + 2 - baris][4]  = '0'+ (tprog[i]%100000)/10000;
                                        str[i + 2 - baris][6]  = '0'+ (tprog[i]%10000)/1000;
                                        str[i + 2 - baris][7]  = '0'+ (tprog[i]%1000)/100;
                                        str[i + 2 - baris][16] = '0'+ (tprog[i]%100)/10;
                                        str[i + 2 - baris][17] = '0'+ tprog[i]%10;
                                }
                        }
			if(baris==tjmllist){
				strcpy(str[3],"[CAN]EXIT           ");
			} 
			Lcd4_Set_Cursor(1,0);Lcd4_Write_String(str[0]);
			Lcd4_Set_Cursor(2,0);Lcd4_Write_String(str[1]);
			Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
			Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
		}		        
                Lcd4_Set_Cursor(3,0);Lcd4_Write_Char(str[2][0]);
                delay_ms(50);
	                    
                if(key==COR){     
                        while(key==COR){key=get_key();}   
                        while(key != COR){ 
                                st1[0] = '0'+ tprog[baris]/100000;st1[1] = '0'+ (tprog[baris]%100000)/10000;
                                Lcd4_Set_Cursor(3,3);Lcd4_Write_String(st1);			
                                st1[0] = '0'+ (tprog[baris]%10000)/1000;st1[1] = '0'+ (tprog[baris]%1000)/100;
                                Lcd4_Set_Cursor(3,6);Lcd4_Write_String(st1);			
                                st1[0] = '0'+ (tprog[baris]%100)/10;st1[1] = '0'+ tprog[baris]%10;
                                Lcd4_Set_Cursor(3,16);Lcd4_Write_String(st1);
                                delay_ms(50);							
                                key=get_key();
                                
                                switch(stateset){
					case 0:	
						Lcd4_Set_Cursor(3,3);	   
                                                if(((tprog[baris]%100000)/10000 >= 0) && ((tprog[baris]%100000)/10000 <= 3)){					
						        if((key>='0') && (key<='2')){	
							        for(i=0;i<tjmllist;i++){
							                if(i!=baris){
							                        if((((long int)(key-'0')*100000) + (tprog[baris] % 100000))/100 == tprog[i]/100)
			        						        b=1;
				        				}
								}
								if(b==0){
								        tprog[baris] = ((long int)(key-'0')*100000) + (tprog[baris] % 100000);
							                stateset=1;
								}
								temp= key;
								while(key==temp){key=get_key();}
								b=0;
                                                        }
						}						
                                                else if(((tprog[baris]%100000)/10000 >= 4) && ((tprog[baris]%100000)/10000 <= 9)){					
						        if((key>='0') && (key<='1')){	
							        for(i=0;i<tjmllist;i++){
							                if(i!=baris){
							                        if((((long int)(key-'0')*100000) + (tprog[baris] % 100000))/100 == tprog[i]/100)
			        						        b=1;
				        				}
								}
								if(b==0){
								        tprog[baris] = ((long int)(key-'0')*100000) + (tprog[baris] % 100000);
							                stateset=1;
								}
								temp= key;
								while(key==temp){key=get_key();}
								b=0;
                                                        }
						}							
						break;
					case 1:	
						Lcd4_Set_Cursor(3,4);						
                                                if(((tprog[baris]/100000) >= 0) && ((tprog[baris]/100000) <= 1)){			
						        if((key>='0') && (key<='9')){	         
							        for(i=0;i<tjmllist;i++){
							                if(i!=baris){
							                        if(((tprog[baris]-(tprog[baris]%100000)) + ((long int)(key-'0')*10000) + (tprog[baris]%10000))/100 == tprog[i]/100)
			        						        b=1;
				        				}
								}
								if(b==0){
							                tprog[baris] = (tprog[baris]-(tprog[baris]%100000)) + ((long int)(key-'0')*10000) + (tprog[baris]%10000);
							                stateset=2;
								}
								temp= key;
								while(key==temp){key=get_key();}
								b=0;
						        }               
                                                }                    						
                                                else if((tprog[baris]/100000) == 2){			
						        if((key>='0') && (key<='3')){	         
							        for(i=0;i<tjmllist;i++){
							                if(i!=baris){
							                        if(((tprog[baris]-(tprog[baris]%100000)) + ((long int)(key-'0')*10000) + (tprog[baris]%10000))/100 == tprog[i]/100)
			        						        b=1;
				        				}
								}
								if(b==0){
							                tprog[baris] = (tprog[baris]-(tprog[baris]%100000)) + ((long int)(key-'0')*10000) + (tprog[baris]%10000);
							                stateset=2;
								}
								temp= key;
								while(key==temp){key=get_key();}
								b=0;
						        }               
                                                }
						break;
					case 2:	
						Lcd4_Set_Cursor(3,6);
						if((key>='0') && (key<='5')){			
						        for(i=0;i<tjmllist;i++){
						                if(i!=baris){
						                        if(((tprog[baris]-(tprog[baris]%10000)) + ((long int)(key-'0')*1000) + (tprog[baris]%1000))/100 == tprog[i]/100)
			        					        b=1;
				        			}
							}
							if(b==0){
							        tprog[baris] = (tprog[baris]-(tprog[baris]%10000)) + ((long int)(key-'0')*1000) + (tprog[baris]%1000);
						                stateset=3;
							}
							temp= key;
							while(key==temp){key=get_key();}
							b=0;	                     
						}
						break;
					case 3:
						Lcd4_Set_Cursor(3,7);
						if((key>='0') && (key<='9')){				
						        for(i=0;i<tjmllist;i++){
						                if(i!=baris){
						                        if(((tprog[baris]-(tprog[baris]%1000)) + ((long int)(key-'0')*100) + (tprog[baris]%100))/100 == tprog[i]/100)
			        					        b=1;
				        			}
							}
							if(b==0){
							        tprog[baris] = (tprog[baris]-(tprog[baris]%1000)) + ((long int)(key-'0')*100) + (tprog[baris]%100);
						                stateset=4;
							}
							temp= key;
							while(key==temp){key=get_key();}
							b=0;	                 
						}
						break;
					case 4:	
						Lcd4_Set_Cursor(3,16);    
                                                if((tprog[baris]%10) == 0){
						        if(key=='1'){			
							        tprog[baris] = (tprog[baris] - (tprog[baris] % 100)) + ((long int)(key-'0') * 10) + (tprog[baris]%10);
							        temp= key;
							        while(key==temp){key=get_key();}
							        stateset=5;
						        }      
                                                }       
                                                else if(((tprog[baris]%10) >= 1) && ((tprog[baris]%10) <= 6)){
						        if((key>='0') && (key<='1')){			
							        tprog[baris] = (tprog[baris] - (tprog[baris] % 100)) + ((long int)(key-'0') * 10) + (tprog[baris]%10);
							        temp= key;
							        while(key==temp){key=get_key();}
							        stateset=5;
						        }      
                                                }
                                                else if(((tprog[baris]%10) >= 7) && ((tprog[baris]%10) <= 9)){
						        if(key=='1'){			
							        tprog[baris] = (tprog[baris] - (tprog[baris] % 100)) + ((long int)(key-'0') * 10) + (tprog[baris]%10);
							        temp= key;
							        while(key==temp){key=get_key();}
							        stateset=5;
						        }      
                                                }
						break;
					case 5:
						Lcd4_Set_Cursor(3,17);          
                                                if((tprog[baris]%100)/10 == 0){
						        if((key>='1') && (key<='9')){				
							        tprog[baris] = (tprog[baris] - (tprog[baris] % 10)) + ((long int)(key-'0'));
							        temp= key;
							        while(key==temp){key=get_key();}
							        stateset=0;
						        }                          
                                                }                                 
                                                else if((tprog[baris]%100)/10 == 1){
						        if((key>='0') && (key<='6')){				
							        tprog[baris] = (tprog[baris] - (tprog[baris] % 10)) + ((long int)(key-'0'));
							        temp= key;
							        while(key==temp){key=get_key();}
							        stateset=0;
						        }                          
                                                }
						break;
				}
				Lcd4_Write_Char('_');delay_ms(50);	
                                if(key==UP){           
			                while(key==UP){key=get_key();}
                                        if(stateset==0)
                                                stateset=5;
                                        else
                                                stateset--;
                                }
                                if(key==DOWN){           
			                while(key==DOWN){key=get_key();}
                                        if(stateset==5)
                                                stateset=0;
                                        else
                                                stateset++;
                                }     
			}                            
                        while(key==COR){key=get_key();}    
                        st1[0] = '0'+ tprog[baris]/100000;st1[1] = '0'+ (tprog[baris]%100000)/10000;
                        Lcd4_Set_Cursor(3,3);Lcd4_Write_String(st1);			
                        st1[0] = '0'+ (tprog[baris]%10000)/1000;st1[1] = '0'+ (tprog[baris]%1000)/100;
                        Lcd4_Set_Cursor(3,6);Lcd4_Write_String(st1);			
                        st1[0] = '0'+ (tprog[baris]%100)/10;st1[1] = '0'+ tprog[baris]%10;
                        Lcd4_Set_Cursor(3,16);Lcd4_Write_String(st1);
                        
                        if((baris==tjmllist) && (tprog[baris]!=0) && (tjmllist<20)){
                                tjmllist++;                          
                                strcpy(str[3]," . 00:00  PLAN: 00  ");
                                str[3][0] = tjmllist + '1';
                                Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
                        }
                        stateset=0;
                }
                
                if(key==ENT){     
                        while(key==ENT){key=get_key();} 
                        if(baris!=tjmllist){
                                if(tjmllist<20){
                                        for(i=baris;i<tjmllist;i++){
                                                tprog[i] = tprog[i+1];
                                        }                          
                                } 
                                else{    
                                        for(i=baris;i<19;i++){
                                                tprog[i] = tprog[i+1];
                                        }                
                                        tprog[19]=0; 
                                }
                        }
                                                                    
                        tjmllist--;   
                        strcpy(str[2]," .   :    PLAN:     ");
                        str[2][0] = baris + '1'; 
                        str[2][3] = '0'+ tprog[baris]/100000;
                        str[2][4] = '0'+ (tprog[baris]%100000)/10000;
                        str[2][6] = '0'+ (tprog[baris]%10000)/1000;
                        str[2][7] = '0'+ (tprog[baris]%1000)/100;
                        str[2][16] = '0'+ (tprog[baris]%100)/10;
                        str[2][17] = '0'+ tprog[baris]%10;
                        Lcd4_Set_Cursor(3,0);Lcd4_Write_String(str[2]);
                        
                        if(baris<tjmllist){              
                                strcpy(str[3]," .   :    PLAN:     ");
                                str[3][0] = baris + '2';        
                                str[3][3] = '0'+ tprog[(long int)baris+1]/100000;
                                str[3][4] = '0'+ (tprog[(long int)baris+1]%100000)/10000;
                                str[3][6] = '0'+ (tprog[(long int)baris+1]%10000)/1000;
                                str[3][7] = '0'+ (tprog[(long int)baris+1]%1000)/100;
                                str[3][16] = '0'+ (tprog[(long int)baris+1]%100)/10;
                                str[3][17] = '0'+ tprog[(long int)baris+1]%10;       
                                Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
                        }                               
                        else{                                                        
                                strcpy(str[3],"[CAN]EXIT           ");
                                Lcd4_Set_Cursor(4,0);Lcd4_Write_String(str[3]);
                        }
                }
                
	}
	while(key==CAN){key=get_key();}
	switch(progharpilihan){
		case 1:
			for(temp=0;temp<20;temp++)
				{listproghar1[temp] = tprog[temp];}
		break;
		case 2:
			for(temp=0;temp<20;temp++)
				{listproghar2[temp] = tprog[temp];}
		break;
		/*case 3:
			for(temp=0;temp<20;temp++)
				{listproghar3[temp] = tprog[temp];}
		break;
		case 4:
			for(temp=0;temp<20;temp++)
				{listproghar4[temp] = tprog[temp];}
		break;
		case 5:
			for(temp=0;temp<20;temp++)
				{listproghar5[temp] = tprog[temp];}
		break;
		case 6:
			for(temp=0;temp<20;temp++)
				{listproghar6[temp] = tprog[temp];}
		break;
		case 7:
			for(temp=0;temp<20;temp++)
				{listproghar7[temp] = tprog[temp];}
		break;
		case 8:
			for(temp=0;temp<20;temp++)
				{listproghar8[temp] = tprog[temp];}
		break;*/
	}
	jmllistproghar[progharpilihan-1] = tjmllist;
        baris=0;
	Lcd4_Clear();delay_ms(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_Flash("Pilih Program Harian");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_Flash("Prgrm Harian:  ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_Flash("1(MGG)-7(SBT),8(LBR)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_Flash("[COR]EDIT  [CAN]EXIT");
}

void UpdateProgramHarian(){
        int tglbln;
        tglbln = (((int)tgl) * 100) + bln;
	for(i=0;i<jmlholiday;i++){
                if(tglbln == holiday[i])
                        proghar = 8;
        }                           
        if (proghar!=8)
                proghar = hr;
}

void UpdatePlan(){
        long int tlistproghar[20];
        char tjml; 
        int selisihmin = 10000; 
        char n = 0;
        
        switch(proghar){
		case 1:
			for(temp=0;temp<20;temp++)
				{tlistproghar[temp] = listproghar1[temp];}
		break;
		case 2:
			for(temp=0;temp<20;temp++)
				{tlistproghar[temp] = listproghar2[temp];}
		break;
		/*case 3:
			for(temp=0;temp<20;temp++)
				{tlistproghar[temp] = listproghar3[temp];}
		break;
		case 4:
			for(temp=0;temp<20;temp++)
				{tlistproghar[temp] = listproghar4[temp];}
		break;
		case 5:
			for(temp=0;temp<20;temp++)
				{tlistproghar[temp] = listproghar5[temp];}
		break;
		case 6:
			for(temp=0;temp<20;temp++)
				{tlistproghar[temp] = listproghar6[temp];}
		break;
		case 7:
			for(temp=0;temp<20;temp++)
				{tlistproghar[temp] = listproghar7[temp];}
		break;
		case 8:
			for(temp=0;temp<20;temp++)
				{tlistproghar[temp] = listproghar8[temp];}
		break;*/
	}
        tjml =  jmllistproghar[proghar-1];
        for(i=0;i<tjml;i++){
                if((((int)jam*100) + (int)mnt) >= (tlistproghar[i]/100)){
                        n=1;
                        if((((jam*100) + mnt) - (tlistproghar[i]/100)) < selisihmin){
                                selisihmin = (((int)jam*100) + (int)mnt) - (tlistproghar[i]/100);
                                wktmulai = tlistproghar[i]/100;
                                plan = tlistproghar[i]%100;
                        }
                }
        }    
        if (n==0)
                plan=16;
}

void UpdateLampu(){
        char tlistplan[16];   
        tempo=0;
        
        switch(plan){
		case 1:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan1[temp];
		break;
		case 2:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan2[temp];
		break;
		/*case 3:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan3[temp];
		break;
		case 4:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan4[temp];
		break;
		case 5:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan5[temp];
		break;
		case 6:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan6[temp];
		break;
		case 7:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan7[temp];
		break;
		case 8:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan8[temp];
		break;
		case 9:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan9[temp];
		break;
		case 10:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan10[temp];
		break;
		case 11:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan11[temp];
		break;
		case 12:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan12[temp];
		break;
		case 13:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan13[temp];
		break;
		case 14:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan14[temp];
		break;
		case 15:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan15[temp];
		break;
		case 16:
			for(temp=0;temp<16;temp++)
				tlistplan[temp] = listplan16[temp];
		break;*/
	}
	
        for(temp=0;temp<16;temp++){
                if(tlistplan[temp]>tempo)
                        tempo = tlistplan[temp];
        }                                       
        
        dtktempo = ((((long int)jam * 3600) + ((long int)mnt * 60) + (long int)dtk) - (((long int)wktmulai/100)* 3600 + ((long int)wktmulai%100)*60)) % tempo;

        if((tlistplan[0]<=dtktempo) && (dtktempo<=tlistplan[1]))
                lampu |= 1  << 0;
        else
                lampu &= ~(1 << 0);
        if((tlistplan[2]<=dtktempo) && (dtktempo<=tlistplan[3]))
                lampu |= 1  << 1;
        else
                lampu &= ~(1 << 1);
        if((tlistplan[4]<=dtktempo) && (dtktempo<=tlistplan[5]))
                lampu |= 1  << 2;
        else
                lampu &= ~(1 << 2);
        if((tlistplan[6]<=dtktempo) && (dtktempo<=tlistplan[7]))
                lampu |= 1  << 3;
        else
                lampu &= ~(1 << 3);
        if((tlistplan[8]<=dtktempo) && (dtktempo<=tlistplan[9]))
                lampu |= 1  << 4;
        else
                lampu &= ~(1 << 4);
        if((tlistplan[10]<=dtktempo) && (dtktempo<=tlistplan[11]))
                lampu |= 1  << 5;
        else
                lampu &= ~(1 << 5);
        if((tlistplan[12]<=dtktempo) && (dtktempo<=tlistplan[13]))
                lampu |= 1  << 6;
        else
                lampu &= ~(1 << 6);
        if((tlistplan[14]<=dtktempo) && (dtktempo<=tlistplan[15]))
                lampu |= 1  << 7;
        else
                lampu &= ~(1 << 7);
}

char READ_SWITCHES(void){	
	#define DELAY 50	

	RowA = 0; RowB = 1; RowC = 1; RowD = 1; 	//Test Row A

	if (C1 == 0) { delay_ms(DELAY); while (C1==0); return '7'; }
	if (C2 == 0) { delay_ms(DELAY); while (C2==0); return '8'; }
	if (C3 == 0) { delay_ms(DELAY); while (C3==0); return '9'; }
	if (C4 == 0) { delay_ms(DELAY); while (C4==0); return '/'; }	//COR

	RowA = 1; RowB = 0; RowC = 1; RowD = 1; 	//Test Row B

	if (C1 == 0) { delay_ms(DELAY); while (C1==0); return '4'; }
	if (C2 == 0) { delay_ms(DELAY); while (C2==0); return '5'; }
	if (C3 == 0) { delay_ms(DELAY); while (C3==0); return '6'; }
	if (C4 == 0) { delay_ms(DELAY); while (C4==0); return 'x'; }	//MEN
	
	RowA = 1; RowB = 1; RowC = 0; RowD = 1; 	//Test Row C

	if (C1 == 0) { delay_ms(DELAY); while (C1==0); return '1'; }
	if (C2 == 0) { delay_ms(DELAY); while (C2==0); return '2'; }
	if (C3 == 0) { delay_ms(DELAY); while (C3==0); return '3'; }
	if (C4 == 0) { delay_ms(DELAY); while (C4==0); return '-'; } 	//UP
	
	RowA = 1; RowB = 1; RowC = 1; RowD = 0; 	//Test Row D

	if (C1 == 0) { delay_ms(DELAY); while (C1==0); return 'm'; }	//CAN
	if (C2 == 0) { delay_ms(DELAY); while (C2==0); return '0'; }	
	if (C3 == 0) { delay_ms(DELAY); while (C3==0); return '='; }	//ENT
	if (C4 == 0) { delay_ms(DELAY); while (C4==0); return '+'; }	//DOWN

	return 'n';           	// Means no key has been pressed
}

char get_key(void){
	key = 'n';              //assume no key pressed

	key = READ_SWITCHES();   //scan the keys again and again

	return key;                  //when key pressed then return its value
}