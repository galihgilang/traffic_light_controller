void main(void){
	int state;
	uart_init();

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


void uart_init(void){	// Set UART Baud Rate to 9600 bps
	PCON&=0x7F;		// Clear SMOD of PCON, No Double Baud Rate
	TMOD&=0xAF;TMOD|=0x20;	// Set Timer1 to Mode 2 (8-bit auto reload) for Baud Rate Generation
	TH1=0xFD;		// Set Baud Rate to 9600 bps for 11.0592M Hz
	SM0=0;SM1=1;	// Set UART to Mode 1 (8-bit UART)
	REN=1;			// Set REN of SCON to Enable UART Receive
	TR1=1;			// Set TR1 of TCON to Start Timer1
	TI=0;RI=0;		// Set TI/RI of SCON to Get Ready to Send/Receive
}

void uart_putc(char c){		// Put Character to UART
	SBUF=c;
	while(TI==0);TI=0;
}

void uart_puts(char *s){	// Put String to UART, Require uart_putc()
	while(*s!=0){uart_putc(*s);s++;}
}

void i2s(int i,char *s){	// Convert Integer to String
	char sign;short len;char *p;
	sign='+';len=0;p=s;
	if(i<0){sign='-';i=-i;}
	do{*s=(i%10)+'0';s++;len++;i/=10;}while(i!=0);
	if(sign=='-'){*s='-';s++;len++;}
	for(i=0;i<len/2;i++){p[len]=p[i];p[i]=p[len-1-i];p[len-1-i]=p[len];}
	p[len]=0;
}

void uart_puti(int i){	// Put Integer to UART, Require i2s(),uart_puts()
	char s[7];
	i2s(i,s);uart_puts(s);
}

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

int countdown(unsigned int startnumber, int signal_id){
	unsigned int ig;
	for(ig=startnumber;ig>0;ig--){
		display(i);
		timer_s(1);
	}
	display(0);
	return 1;
}

unsigned char intto7s(unsigned int input) { 
	unsigned char output;
	if(input == 1){ 
		output = ~0x06;	//0b00000110 - g f e d c b a
	} else if(input == 2){ 
		output = ~0x5B;	//0b01011011 
	} else if(input == 3){ 
		output = ~0x4F; 	//0b01001111 
	} else if(input == 4){ 
		output = ~0x66;	//0b01100110 
	} else if(input == 5){ 
		output = ~0x6D;  //0b01101101 
	} else if(input == 6){ 
		output = ~0x7D; 	//0b01111101 
	} else if(input == 7){  
		output = ~0x07;	//0b00000111 
	} else if(input == 8){ 
		output = ~0xEF; 	//0b01111111 
	} else if(input == 9){ 
		output = ~0x6F;	//0b01101111 
	} else if(input == 0){ 
		output = ~0x3F;	//0b00111111 
	}
	return output;
}