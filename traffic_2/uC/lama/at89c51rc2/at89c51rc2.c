#define COR 	'/'
#define MEN 	'x'
#define UP 		'-'
#define DOWN 	'+'
#define CAN 	'm'
#define ENT 	'='

void StartUp();				// 1
void Idle();				// 2
void InputSetting();		// 3
void Monitor();				// 4
void InputKeypad();			// 5
void InputKompSer();		// 6
void InputKompInt();		// 7
void SetHoliday();			// 8
void SetTanggal();			// 9
void SetWaktu();			// 10
void SetPlan();				// 11
void SetPlanPilih();		// 12
void SetProgramHarian();	// 13
void SetProgramHarianPilih();	// 14
void SetStartUp();			// 15
void UpdateProgramHarian();	// 16
void UpdatePlan();			// 17
void UpdateLampu();			// 18
char READ_SWITCHES(void);	// 18
char get_key(void);			// 20

/*----------------- Variabel ------------------*/
char key='n';
char *str[4];
char st1[3];
char temp=61;
char baris=0;
char stateset=0;
char progharpilihan;
char planpilihan;

char jam = 23, mnt = 6, dtk = 0, bln = 1, tgl = 12, hr = 3;		// RTC, EEPROM
int thn = 2013;
char dtkstartup = 2;											// EEPROM
//int holiday[20];
//int listproghar1[70];
char listplan1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
char listplan2[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
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

char proghar = 1;		// RAM
char plan = 1;
char lampu = 0;

void main(){
	Lcd4_Init();
	StartUp();
	
	while (1){
		Idle();			
	}
}

void StartUp(){		
	temp = dtkstartup;
	
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("TRAFFIC TLPCO-08 SG");	 
	
	while (temp > 0){ 	
		Lcd4_Set_Cursor(2,0);Lcd4_Write_String("START UP:");
		st1[0] = 48 + (temp / 10); st1[1] = 48 + (temp % 10);
		Lcd4_Set_Cursor(2,10);Lcd4_Write_String(st1);
		
		temp--;
		Delay(1000);
	} 
	Delay(1000);
	Lcd4_Clear();Delay(50);
} 

void Idle(){
	temp=61;
	Lcd4_Clear();Delay(50);
	
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("TELEPICO TLPCO-08 SG");	 					// baris 1
	
	Lcd4_Set_Cursor(2,4); Lcd4_Write_String(",");									// baris 2
	
	Lcd4_Set_Cursor(3,2);Lcd4_Write_String(":");
	Lcd4_Set_Cursor(3,5);Lcd4_Write_String(":");
	Lcd4_Set_Cursor(3,9); Lcd4_Write_String("S:");									// baris 3
	Lcd4_Set_Cursor(3,14); Lcd4_Write_String("P:");
	
   	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[1] Set [2] Monitor");					// baris 4
	
	while((key != '1') && (key != '2')){
		if(temp != dtk){
			temp=dtk;
			UpdateProgramHarian();UpdatePlan();UpdateLampu();
			
			switch (hr){																	// baris 2
				case 1:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_String("MGG");  break;
				case 2:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_String("SNN");  break;
				case 3:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_String("SLS");  break;
				case 4:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_String("RAB");  break;
				case 5:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_String("KMS");  break;
				case 6:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_String("JMT");  break;
				case 7:  
					Lcd4_Set_Cursor(2,1);Lcd4_Write_String("SBT");  break;
			}
			st1[0] = 48 + (tgl / 10); st1[1] = 48 + (tgl % 10);
			Lcd4_Set_Cursor(2,6);Lcd4_Write_String(st1);
			switch (bln){
				case 1:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("JAN");  break;
				case 2:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("FEB");  break;
				case 3:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("MAR");  break;
				case 4:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("APR");  break;
				case 5:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("MEI");  break;
				case 6:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("JUN");  break;
				case 7:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("JUL");  break;
				case 8:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("AGS");  break;
				case 9:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("SEP");  break;
				case 10:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("OKT");  break;
				case 11:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("NOV");  break;
				case 12:  
					Lcd4_Set_Cursor(2,9);Lcd4_Write_String("DES");  break;
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
		key = get_key();
	}
	switch (key){
		case '1':	while(key=='1'){key=get_key();}InputSetting(); break;
		case '2':	while(key=='2'){key=get_key();}Monitor(); break;
	}
}

void InputSetting(){	
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("Input Setting");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[1] Keypad");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[2] Komputer (ser)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[3] Komputer (int)");
	
	while (key != CAN){
		key = get_key();
		
		switch (key){
			case '1': while(key=='1'){key=get_key();}InputKeypad(); break;
			case '2': while(key=='2'){key=get_key();}InputKompSer(); break;
			case '3': while(key=='3'){key=get_key();}InputKompInt(); break;
		} 
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();Delay(50);
}

void Monitor(){					
	temp = 61;
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("Monitor");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("RED");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("GRE");
	
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
		}
		key = get_key();
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();Delay(50);
}

void InputKeypad(){				
	baris = 0;
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[2] Set tanggal     ");
	
	while (key != CAN){
		key = get_key();
		
		if((key==UP) ||(key==DOWN)){
			if(key==UP){
				if(baris>0)
					baris--;
			}
			if(key==DOWN){
				if(baris<4)
					baris++;
			}
			
			if((baris>=0) && (baris<=0))				    
				str[0 - baris]="MAIN MENU [1]-[6]   ";
			if((baris>=0) && (baris<=1))
				str[1 - baris]="[CAN]EXIT           ";
			if((baris>=0) && (baris<=2))
				str[2 - baris]="[1] Set waktu       ";
			if((baris>=0) && (baris<=3))
				str[3 - baris]="[2] Set tanggal     ";
			if((baris>=1) && (baris<=4))
				str[4 - baris]="[3] Set hari libur  ";
			if((baris>=2) && (baris<=4))
				str[5 - baris]="[4] Set startup     ";
			if((baris>=3) && (baris<=4))
				str[6 - baris]="[5] Set PLAN        ";
			if((baris>=4) && (baris<=4))
				str[7 - baris]="[6] Set prog harian ";
			
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
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("Input Setting");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[1] Keypad");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[2] Komputer (ser)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[3] Komputer (int)");
}

void InputKompSer(){
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("Komputer (serial)");
}

void InputKompInt(){
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("Komputer (internet)");
}

void SetWaktu(){				// 1. SetWaktu					
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,3);Lcd4_Write_String("SET WAKTU");
	Lcd4_Set_Cursor(2,2);Lcd4_Write_String(":  :");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[COR]EDIT/SAVE");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[CAN]EXIT");
	
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
				Delay(50);
				key = get_key();
				
				switch(stateset){
					case 0:	
						Lcd4_Set_Cursor(2,0);						
						if((key>='0') && (key<='9')){	
							jam = (jam % 10) + ((key-'0') *10);							
							temp= key;
							while(key==temp){key=get_key();}
							stateset=1;
						}								
						break;
					case 1:	
						Lcd4_Set_Cursor(2,1);							
						if((key>='0') && (key<='9')){	
							jam = (jam - (jam % 10)) + (key-'0');							
							temp= key;
							while(key==temp){key=get_key();}
							stateset=2;
						}
						break;
					case 2:	
						Lcd4_Set_Cursor(2,3);
						if((key>='0') && (key<='9')){			
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
						if((key>='0') && (key<='9')){			
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
				Lcd4_Write_Char('_');Delay(50);
			}	
			while(key==COR){key=get_key();}
			stateset=0;		
		}																		
	}
	while(key==CAN){key = get_key();}	
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[2] Set tanggal     ");
}

void SetTanggal(){				// 2. SetTanggal				
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,3);Lcd4_Write_String("SET TANGGAL");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String(" ,   /  /");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[COR]EDIT/SAVE");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[CAN]EXIT");
	
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
				Delay(50);
				key = get_key();
				
				switch(stateset){
					case 0:	
						Lcd4_Set_Cursor(2,0);						
						if((key>='0') && (key<='9')){	
							hr = key-'0';							
							temp= key;
							while(key==temp){key=get_key();}
							stateset=1;
						}								
						break;
					case 1:	
						Lcd4_Set_Cursor(2,3);							
						if((key>='0') && (key<='9')){	
							tgl = (tgl % 10) + ((key-'0') *10);							
							temp= key;
							while(key==temp){key=get_key();}
							stateset=2;
						}
						break;
					case 2:	
						Lcd4_Set_Cursor(2,4);
						if((key>='0') && (key<='9')){			
							tgl = (tgl - (tgl % 10)) + (key-'0');					
							temp= key;
							while(key==temp){key=get_key();}
							stateset=3;
						}
						break;
					case 3:
						Lcd4_Set_Cursor(2,6);
						if((key>='0') && (key<='9')){						
							bln = (bln % 10) + ((key-'0') *10);							
							temp= key;
							while(key==temp){key=get_key();}
							stateset=4;
						}
						break;
					case 4:
						Lcd4_Set_Cursor(2,7);
						if((key>='0') && (key<='9')){			
							bln = (bln - (bln % 10)) + (key-'0');					
							temp= key;
							while(key==temp){key=get_key();}
							stateset=5;
						}
						break;
					case 5:	
						Lcd4_Set_Cursor(2,9);
						if((key>='0') && (key<='9')){							
							thn = (thn % 1000) + ((key-'0')*1000);				
							temp= key;
							while(key==temp){key=get_key();}
							stateset=6;								
						}
						break;
					case 6:	
						Lcd4_Set_Cursor(2,10);
						if((key>='0') && (key<='9')){							
							thn = (thn - (thn%1000)) + ((key-'0')*100) + (thn%100);				
							temp= key;
							while(key==temp){key=get_key();}
							stateset=7;								
						}
						break;
					case 7:	
						Lcd4_Set_Cursor(2,11);
						if((key>='0') && (key<='9')){							
							thn = (thn - (thn % 100)) + ((key-'0')*10) + (thn%10);				
							temp= key;
							while(key==temp){key=get_key();}
							stateset=8;								
						}
						break;
					case 8:	
						Lcd4_Set_Cursor(2,12);
						if((key>='0') && (key<='9')){							
							thn = (thn-(thn%10)) + (key-'0');				
							temp= key;
							while(key==temp){key=get_key();}
							stateset=0;								
						}
						break;
				}
				Lcd4_Write_Char('_');Delay(50);
			}	
			while(key==COR){key=get_key();}
			stateset=0;		
		}																		
	}
	while(key==CAN){key = get_key();}	
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[2] Set tanggal     ");
}

void SetHoliday(){				// 3. SetHoliday						
	Lcd4_Clear();Delay(50);	
	
	while(key != CAN){				
		key=get_key();
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[2] Set tanggal     ");
}

void SetStartUp(){				// 4. SetStartUp				
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,2);Lcd4_Write_String("SET STARTUP");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("Waktu Start Up:");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[COR]EDIT/SAVE");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[CAN]EXIT");
	
	while(key != CAN){		
		st1[0]= '0'+ dtkstartup/10;st1[1]= '0'+ dtkstartup%10;
		Lcd4_Set_Cursor(2,16);Lcd4_Write_String(st1);
		
		key = get_key();
		
		if(key == COR){
			while(key==COR){key=get_key();}
			while (key != COR){									
				key = get_key();
				st1[0]= '0'+ dtkstartup/10;st1[1]= '0'+ dtkstartup%10;
				Lcd4_Set_Cursor(2,16);Lcd4_Write_String(st1);Delay(50);
				
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
				Lcd4_Write_Char('_');Delay(50);
			}
			while(key==COR){key=get_key();} 
			stateset=0;
		}			
	}
	while(key==CAN){key = get_key();}	
	Lcd4_Clear();Delay(50);	
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[2] Set tanggal     ");
}

void SetPlan(){					// 5. SetPlan							
	planpilihan=1;
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0); Lcd4_Write_String("Pilih Plan");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("Plan:");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[COR]EDIT  [CAN]EXIT");
	
	while(key != CAN){		
		key = get_key();
		st1[0]= '0'+ planpilihan/10;st1[1]= '0'+ planpilihan%10;
		Lcd4_Set_Cursor(2,6);Lcd4_Write_String(st1);Delay(50);
				
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
		Lcd4_Write_Char('_');Delay(50);
		
		if(key==COR){
			while(key==COR){key=get_key();} 
			stateset=0;
			SetPlanPilih();
		}
	}		
	stateset=0;
	while(key==CAN){key=get_key();}
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[2] Set tanggal     ");
}

void SetPlanPilih(){			// 5.a. SetPlanPilih
	char tlist[16];
	char tstr[20];
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
	
	Lcd4_Clear();Delay(50);
	
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("Plan-");			// baris 1
	st1[0]= '0'+ planpilihan/10;st1[1]= '0'+ planpilihan%10;st1[2]=0;
	Lcd4_Set_Cursor(1,5);Lcd4_Write_String(st1);
	
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[COR] EDIT/SAVE");	// baris 2
	
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("1. L1:     -    ");	// baris 3
	st1[0] = (tlist[0]/100) + '0'; st1[1] = ((tlist[0]%100)/10) + '0';st1[2] = (tlist[0]%10) + '0';
	Lcd4_Set_Cursor(3,7);Lcd4_Write_String(st1);
	st1[0] = (tlist[1]/100) + '0'; st1[1] = ((tlist[1]%100)/10) + '0'; st1[2] = (tlist[1]%10) + '0';
	Lcd4_Set_Cursor(3,13);Lcd4_Write_String(st1);
	
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("2. L2:     -    ");	// baris 4
	st1[0] = (tlist[2]/100) + '0'; st1[1] = ((tlist[2]%100)/10) + '0'; st1[2] = (tlist[2]%10) + '0';
	Lcd4_Set_Cursor(4,7);Lcd4_Write_String(st1);
	st1[0] = (tlist[3]/100) + '0'; st1[1] = ((tlist[3]%100)/10) + '0'; st1[2] = (tlist[3]%10) + '0';
	Lcd4_Set_Cursor(4,13);Lcd4_Write_String(st1);
	
	while (key != CAN){
		key = get_key();
		
	}
	while(key==CAN){key=get_key();}
	baris=0;st1[2]=0;
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0); Lcd4_Write_String("Pilih Plan");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("Plan:");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[COR]EDIT  [CAN]EXIT");
}

void SetProgramHarian(){		// 6. SetProgramHarian					
	progharpilihan=1;
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("Pilih Program Harian");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("Prgrm Harian:  ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("1(MGG) - 7(SBT)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[COR]EDIT  [CAN]EXIT");
	
	while (key != CAN){
		key = get_key();
		st1[0]= '0'+ progharpilihan;
		Lcd4_Set_Cursor(2,14);Lcd4_Write_Char(st1[0]);Delay(50);		
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
		Lcd4_Write_Char('_');Delay(50);
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();Delay(50);  
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("MAIN MENU [1]-[6]   ");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("[CAN]EXIT           ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("[1] Set waktu       ");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[2] Set tanggal     ");
}

void SetProgramHarianPilih(){	// 6.a. SetProgramHarianPilih
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("Prgrm Harian [ ]");
	st1[0] = progharpilihan + '0';
	Lcd4_Set_Cursor(1,14);Lcd4_Write_Char(st1[0]);
	switch (progharpilihan){																	// baris 2
		case 1:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_String("MGG");  break;
		case 2:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_String("SNN");  break;
		case 3:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_String("SLS");  break;
		case 4:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_String("RAB");  break;
		case 5:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_String("KMS");  break;
		case 6:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_String("JMT");  break;
		case 7:  
			Lcd4_Set_Cursor(1,17);Lcd4_Write_String("SBT");  break;
	}
	
	while (key != CAN){
		key = get_key();
	}
	while(key==CAN){key=get_key();}
	Lcd4_Clear();Delay(50);
	Lcd4_Set_Cursor(1,0);Lcd4_Write_String("Pilih Program Harian");
	Lcd4_Set_Cursor(2,0);Lcd4_Write_String("Prgrm Harian:  ");
	Lcd4_Set_Cursor(3,0);Lcd4_Write_String("1(MGG) - 7(SBT)");
	Lcd4_Set_Cursor(4,0);Lcd4_Write_String("[COR]EDIT  [CAN]EXIT");
}

void UpdateProgramHarian(){
	/*if(tgl,bln == holiday)
		proghar = 8;
	else*/
		proghar = hr;
}

void UpdatePlan(){
}

void UpdateLampu(){
}

char READ_SWITCHES(void){	
	#define DELAY 50	

	RowA = 0; RowB = 1; RowC = 1; RowD = 1; 	//Test Row A

	if (C1 == 0) { Delay(DELAY); while (C1==0); return '7'; }
	if (C2 == 0) { Delay(DELAY); while (C2==0); return '8'; }
	if (C3 == 0) { Delay(DELAY); while (C3==0); return '9'; }
	if (C4 == 0) { Delay(DELAY); while (C4==0); return '/'; }	//COR

	RowA = 1; RowB = 0; RowC = 1; RowD = 1; 	//Test Row B

	if (C1 == 0) { Delay(DELAY); while (C1==0); return '4'; }
	if (C2 == 0) { Delay(DELAY); while (C2==0); return '5'; }
	if (C3 == 0) { Delay(DELAY); while (C3==0); return '6'; }
	if (C4 == 0) { Delay(DELAY); while (C4==0); return 'x'; }	//MEN
	
	RowA = 1; RowB = 1; RowC = 0; RowD = 1; 	//Test Row C

	if (C1 == 0) { Delay(DELAY); while (C1==0); return '1'; }
	if (C2 == 0) { Delay(DELAY); while (C2==0); return '2'; }
	if (C3 == 0) { Delay(DELAY); while (C3==0); return '3'; }
	if (C4 == 0) { Delay(DELAY); while (C4==0); return '-'; } 	//UP
	
	RowA = 1; RowB = 1; RowC = 1; RowD = 0; 	//Test Row D

	if (C1 == 0) { Delay(DELAY); while (C1==0); return 'm'; }	//CAN
	if (C2 == 0) { Delay(DELAY); while (C2==0); return '0'; }	
	if (C3 == 0) { Delay(DELAY); while (C3==0); return '='; }	//ENT
	if (C4 == 0) { Delay(DELAY); while (C4==0); return '+'; }	//DOWN

	return 'n';           	// Means no key has been pressed
}

char get_key(void){
	key = 'n';              //assume no key pressed

	key = READ_SWITCHES();   //scan the keys again and again

	return key;                  //when key pressed then return its value
}