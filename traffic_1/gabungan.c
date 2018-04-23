#include <REGX51.H>
#include <stdio.h>

// ****************** START Deklarasi Pin & Register ******************
#define IDLE 1				// State	: IDLE = 1, COUNTDOWN = 2
#define COUNTDOWN 2
#define VALID 1				// Kondisi	: VALID = 1, INVALID = 0
#define INVALID 0
#define MERAH 0xFE 			// Sinyal	: MERAH = 0xFE, HIJAU = 0xFD, KUNING = 0xFC
#define HIJAU 0xFD 
#define KUNING 0xFC   
#define PORT_RATUSAN P1		// 7segment	: RATUSAN = PORT1, PULUHAN = PORT2, SATUAN = PORT0
#define PORT_PULUHAN P2
#define PORT_SATUAN P0

sfr T2CON = 0xC8;			// Deklarasi register
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2 = 0xCC;
sfr TH2 = 0xCD;
sbit TF2 = T2CON^7;
// ******************* END Deklarasi Pin & Register *******************


// ***************** START Deklarasi Variabel Global ******************
// variabel sub-fungsi main 1
int a=0, b=0;				// nilai yg disimpan saat sinyal P3_2 atau P3_3 aktif
int sa=5464, sb=5464;		// nilai yg ditampilkan saat sinyal P3_2 atau P3_3 aktif
int stategalih;				// state sub-fungsi main 1
int init=0;
int in7seg=5464;			// input 7segment
int l=0;
// variabel sub-fungsi main 2
int uart_data_status= 0;	
int counter_status= 0;
int countnum= 0;
int signal_id= 0;
unsigned char buffer[4]={0x00,0x00,0x00,0x00};
// ****************** END Deklarasi Variabel Global *******************


// ********************** START Deklarasi Fungsi **********************
void sevseg(void);
void uart_init(void);
void uart_putc(char c);
void uart_puts(char *s);
void i2s(int i,char *s);
void uart_puti(int i);
void display(unsigned int num);
int countdown(unsigned int startnumber, int signal_id);
unsigned char intto7s(unsigned int input); 
// *********************** END Deklarasi Fungsi ***********************


// *********************** START Fungsi timer_s ***********************
// Membuat delay 1 detik
void timer_s(unsigned int sec)
{
	int i;
	for(i=0;i<20*sec;i++) {	
		TH2=0x4C;
		TL2=0x03;
		T2CON = 0x05;		// mengaktifkan timer
		while(TF2==0);	 	// 50ms, pembagi clock 12
		T2CON = 0x01;
	}
}
// ************************ END Fungsi timer_s ************************


// ********************* START Fungsi timer0_ISR **********************
// Interrupt Timer0 untuk LED indikator
void timer0_ISR (void) interrupt 1
{	 
	TH0=0x4B;
	TL0=0xFF;
	l++;
	if(l==20){
		P3_7 = ~P3_7;
		l=0;
	}
}
// ********************** END Fungsi timer0_ISR ***********************


// ********************* START Fungsi serial_isr **********************
// Interrupt UART (serial)
void serial_isr (void) interrupt 4
{
	char data_rx = '\0';        // character buffer 

	if (RI == 1)        
	{
		data_rx = SBUF;   
 
		buffer[3]= buffer[2];
		buffer[2]= buffer[1];
		buffer[1]= buffer[0];
		buffer[0]= data_rx;

		if(buffer[3] == 0xFF){
			if(buffer[2]==MERAH){
				signal_id= MERAH;
				countnum= ((unsigned int)buffer[1]<<8) | buffer[0];
				uart_data_status= VALID;
			}else if(buffer[2]==HIJAU){
				signal_id= HIJAU;
				countnum= ((unsigned int)buffer[1]<<8) | buffer[0];
				uart_data_status= VALID;
			}else if(buffer[2]==KUNING){
				signal_id= KUNING;
				countnum= ((unsigned int)buffer[1]<<8) | buffer[0];
				uart_data_status= VALID;
			}
		}
	}

	RI = 0;        // clear the received interrupt flag
	TI = 0;        // signal that there's a new character to send 
}
// ********************** END Fungsi serial_isr ***********************


// ************************ START Fungsi main *************************
// Program Utama
void main (void) {
	int state;		// state sub-fungsi main 2
	P0 = 0x00;		// PORT 0, 1, 2 diset sebagai output
	P1 = 0x00;
	P2 = 0x00;
	P3_7 = 0;
	
	EA = 1;			// enable global interrupt
	
	TMOD = 0x01; 	// timer 0 digunakan untuk LED indikator, timer 1 digunakan untuk UART
	TH0=0x4B;
	TL0=0xFF;
	ET0=1;
	TR0=1;
	
	// START Sub-Fungsi main 1: data dari P3_2 atau P3_3
	if(P3_6==1){
		sevseg();
		while((P3_2==0) && (P3_3==0)){}
	
		if(P3_2==1)
			stategalih=2;
		else if(P3_3==1)
			stategalih=4;
	
		while(1){
			if(stategalih==1){			// P3_3 non-aktif, menunggu P3_2 aktif		
				in7seg=5464;
				sevseg();
				while(P3_2==0){}
				stategalih=2;
			}		
			else if(stategalih==2){		// P3_2 aktif
				if(init<2){				// P3_2 aktif pertama kali
					// tidak menampilkan apa2 (), menyimpan nilai a 
					while(P3_2==1){
						sevseg();
						timer_s(1);
						a++;			// CountUp a
					}
					init++;
				}
				else{					// P3_2 aktif bkn pertama kali
					// menampilkan sa (nilai sblmnya), menyimpan nilai a utk tampilan selanjutnya
					while(P3_2==1){
						in7seg = sa;	// menampilkan sa (nilai sblmnya)
						sevseg();
						timer_s(1);
						a++;			// CountUp a
						if(sa>0)
							sa--;		// CountDown sa
						else
							sa=0;
					}
				}
				sa=a;
				a=0;
				stategalih=3;
			}
			else if(stategalih==3){		// P3_2 non-aktif, menunggu P3_3 aktif
				in7seg=5464;
				sevseg();
				while(P3_3==0){}
				stategalih=4;
			}
			else if(stategalih==4){		// P3_3 aktif		
				if(init<2){				// P3_3 aktif pertama kali
					// tidak menampilkan apa2 (), menyimpan nilai b 
					while(P3_3==1){
						sevseg();
						timer_s(1);
						b++;			// CountUp b
					}
					init++;
				}
				else{					// P3_3 aktif bkn pertama kali
					// menampilkan sb (nilai sblmnya), menyimpan nilai b utk tampilan selanjutnya
					while(P3_3==1){
						in7seg = sb;	// menampilkan sb (nilai sblmnya)
						sevseg();
						timer_s(1);
						b++;			// CountUp b
						if(sb>0)
							sb--;		// CountDown sb
						else
							sb=0;
					}
				}
				sb=b;
				b=0;
				stategalih=1;
			}
		}
	}
	// END Sub-fungsi main 1
	
	// START Sub-fungsi main 2: data dari UART
	else {
		ES = 1;		//	enable interrupt serial
		uart_init();
		
		PORT_RATUSAN= 0xFF;
		PORT_PULUHAN= 0xFF;
		PORT_SATUAN= 0xFF;
		
		state= IDLE;
		uart_data_status= INVALID;
		counter_status= INVALID;
		
		while (1){
			switch(state){
				case IDLE		:	if(uart_data_status == VALID){	// menunggu data serial yg VALID
										state= COUNTDOWN;	
										ES  = 0;
										uart_data_status= INVALID;	//reset
									}
									break;
				case COUNTDOWN	:	counter_status= countdown(countnum, signal_id);
									if(counter_status == 1){		//selesai melakukukan countdown
										state= IDLE;
										ES  = 1;                
										counter_status= INVALID;	//reset
									}
									break;
			}		
		}
	}
	// END Sub-fungsi main 2
}
// ************************* END Fungsi main **************************


// ************************* START Fungsi i2s *************************
// Convert Integer to String
void i2s(int i,char *s){
	char sign;short len;char *p;
	sign='+';len=0;p=s;
	if(i<0){sign='-';i=-i;}
	do{*s=(i%10)+'0';s++;len++;i/=10;}while(i!=0);
	if(sign=='-'){*s='-';s++;len++;}
	for(i=0;i<len/2;i++){p[len]=p[i];p[i]=p[len-1-i];p[len-1-i]=p[len];}
	p[len]=0;
}
// ************************** END Fungsi i2s **************************


// ********************** START Fungsi uart_init **********************
// Inisialisasi UART: Baud Rate 9600 bps
void uart_init(void){	
	PCON&=0x7F;		// Clear SMOD of PCON, No Double Baud Rate
	TMOD&=0xAF;
	TMOD|=0x20;		// Set Timer1 to Mode 2 (8-bit auto reload) for Baud Rate Generation
	TH1=0xFD;		// Set Baud Rate to 9600 bps for 11.0592M Hz
	SM0=0;SM1=1;	// Set UART to Mode 1 (8-bit UART)
	REN=1;			// Set REN of SCON to Enable UART Receive
	TR1=1;			// Set TR1 of TCON to Start Timer1
	TI=0;RI=0;		// Set TI/RI of SCON to Get Ready to Send/Receive
}
// *********************** END Fungsi uart_init ***********************


// ********************** START Fungsi uart_putc **********************
// Put Character into UART
void uart_putc(char c){
	SBUF=c;
	while(TI==0);TI=0;
}
// *********************** END Fungsi uart_putc ***********************


// ********************** START Fungsi uart_puts **********************
// Put String into UART
void uart_puts(char *s){
	while(*s!=0){uart_putc(*s);s++;}
}
// *********************** END Fungsi uart_puts ***********************


// ********************** START Fungsi uart_puti **********************
// Put Integer into UART
void uart_puti(int i){
	char s[7];
	i2s(i,s);uart_puts(s);
}
// *********************** END Fungsi uart_puti ***********************


// *********************** START Fungsi intto7s ***********************
// Convert 1 Digit Integer to 7segment Pin Configuration
unsigned char intto7s(unsigned int input) { 
	unsigned char output;
	if(input == 1){ 
		output = ~0x06;		//0b00000110 - g f e d c b a
	} else if(input == 2){ 
		output = ~0x5B;		//0b01011011 
	} else if(input == 3){ 
		output = ~0x4F; 	//0b01001111 
	} else if(input == 4){ 
		output = ~0x66;		//0b01100110 
	} else if(input == 5){ 
		output = ~0x6D;  	//0b01101101 
	} else if(input == 6){ 
		output = ~0x7D; 	//0b01111101 
	} else if(input == 7){  
		output = ~0x07;		//0b00000111 
	} else if(input == 8){ 
		output = 0x00; 		//0b01111111 
	} else if(input == 9){ 
		output = ~0x6F;		//0b01101111 
	} else if(input == 0){ 
		output = ~0x3F;		//0b00111111 
	}
	return output;
}
// ************************ END Fungsi intto7s ************************


// *********************** START Fungsi sevenseg **********************
// Convert in7seg to Each 7segment Pin Configuration
// in7seg = input 7segment
void sevseg() {
	int ssat, spul, srat;
	
	if(in7seg==5464)										// in7seg melebihi batas integer
		P0=P1=P2=0xFF;
	else{
		if ((in7seg > 199) && (in7seg < 5400)){				// Jika 199 < in7seg < 5400, in7seg = 199
			ssat=9;
			spul=9;
			srat=1;}
		
		else {												// in7seg <= 199
			ssat = in7seg % 10;
			spul = ((in7seg % 100) - (in7seg % 10))/10;
			srat = (in7seg - (in7seg % 100))/100;}
		
		PORT_RATUSAN = intto7s(srat);
		PORT_PULUHAN = intto7s(spul);
		PORT_SATUAN = intto7s(ssat);
	}
}
// ************************ END Fungsi sevenseg ***********************


// ************************ START Fungsi display **********************
// Mengirimkan num (integer) melalui uart, mengkonfigurasi num pada 7segment
void display(unsigned int num){	
	unsigned int temp;
	uart_puti(num);
	uart_putc('\r');
	
	temp= (num/100);
	if(temp>=0){
		PORT_RATUSAN= intto7s(temp);
	}
	temp= ((num%100)/10);
	if(temp>=0){
		PORT_PULUHAN= intto7s(temp);
	}
	temp= (num%10);
	if(temp>=0){
		PORT_SATUAN= intto7s(temp);
	}
}
// ************************* END Fungsi display ***********************


// *********************** START Fungsi countdown *********************
// Hitung mundur dari startnumber, sembari mengaplikasikan fungsi display setiap terjadi perubahan
int countdown(unsigned int startnumber, int signal_id){
	unsigned int ig;
	for(ig=startnumber;ig>0;ig--){
		display(ig);
		timer_s(1);
	}
	display(0);
	return 1;
}
// ************************ END Fungsi countdown **********************