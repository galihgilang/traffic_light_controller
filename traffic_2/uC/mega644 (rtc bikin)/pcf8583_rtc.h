#define ACK     1
#define NACK    0
#define Adresse_Schreiben   0xA0             // Die Adresse A0 für Schreiben, wenn Pin A0 am PCF8583 auf GND liegt
#define Adresse_Lesen       0xA1             // Die Adresse A1 für Lesen, wenn Pin A0 am PCF8583 auf GND leigt
//
//#define i2c_init  I2C_init 
//#define i2c_start I2C_start
//#define i2c_stop  I2C_stop
//#define i2c_read  I2C_read
//#define i2c_write I2C_write

struct Time{
    char seconds;
    char minutes;
    char hours;
};

 struct Date {
        char day;
        char month;
        char year;
        char weekDay;
};

void Set_Time( unsigned char hours, unsigned char minutes, unsigned char seconds)
{
	unsigned char temp=0;	
	//0x02	time
	//0x0A	time alarm
   i2c_start();      // Issue start signal
   i2c_write(0xA0 | 0);  // Address PCF8583, see PCF8583 datasheet
   i2c_write(0x02);     // Start from address 0 (configuration memory location) 
   temp= ((seconds/10)<<4)+(seconds%10);
   i2c_write(temp);   
   temp= ((minutes/10)<<4)+(minutes%10);   
   i2c_write(temp);   
   temp= ((hours/10)<<4)+(hours%10);
   i2c_write(temp);   
   i2c_stop();       // Issue stop signal                                       
   //delay_ms(10);
}

   //--------------------- Reads time and date information from RTC (PCF8583)
void Read_Time(unsigned char * hours, unsigned char * minutes, unsigned char * seconds) {
  unsigned char temp=0;
  i2c_start();               // Issue start signal
  i2c_write(0xA0);           // Address PCF8583, see PCF8583 datasheet
  i2c_write(0x02);        // Start from address 2
  i2c_start();               // Issue repeated start signal
  i2c_write(0xA1);           // Address PCF8583 for reading R/W=1
  temp= i2c_read(ACK);
  *seconds = 10*(temp>>4) + (temp&0x0F);    // Read seconds byte
  temp= i2c_read(ACK);
  *minutes = 10*(temp>>4) + (temp&0x0F);    // Read minutes byte
  temp= i2c_read(NACK);
  *hours   = 10*(temp>>4) + (temp&0x0F);    // Read hours byte
  i2c_stop();                // Issue stop signal   
  //delay_ms(10);
}

void Set_Date( unsigned char day, unsigned char date, unsigned char month, unsigned int int_year)
{
	unsigned char temp=0;
    unsigned char year= int_year%4;	
	//0x02	time
	//0x0A	time alarm
   i2c_start();      // Issue start signal
   i2c_write(0xA0);  // Address PCF8583, see PCF8583 datasheet
   i2c_write(0x05);     // Start from address 0 (configuration memory location)
   temp= 	((date/10)<<4)+(date%10) +
   			(year<<6);
   i2c_write(temp);   
   temp= ((month/10)<<4)+(month%10)+ ((day-1)<<5);   
   i2c_write(temp);     
   i2c_stop();       // Issue stop signal 
   delay_ms(10);
}

   //--------------------- Reads time and date information from RTC (PCF8583)
void Read_Date(unsigned char *day, unsigned char *date, unsigned char *month, unsigned int *int_year)
{
  unsigned char temp=0;
  unsigned char year;    
  unsigned char mod= (*int_year%4);  
  
  i2c_start();               // Issue start signal
  i2c_write(0xA0);           // Address PCF8583, see PCF8583 datasheet
  i2c_write(0x05);        // Start from address 2
  i2c_start();               // Issue repeated start signal
  i2c_write(0xA1);           // Address PCF8583 for reading R/W=1
  temp= i2c_read(ACK);
  *date = ((temp&0x30)>>4)*10 + (temp&0x0F);    // Read seconds byte
  year= ((temp&0xC0)>>6);    // Read hours byte
  temp= i2c_read(NACK);
  *month   = ((temp&0x10)>>4)*10+temp&0x0F;    // Read hours byte
  *day= (temp>>5)+1;  
  i2c_stop();                // Issue stop signal   
        
  if(mod != year){
    *int_year= *int_year + 1;    
  } 
  delay_ms(10);
}

//void writeByte(char address, char d)
//{
//   i2c_start();
//   i2c_write(Adresse_Schreiben);
//   i2c_write(address);
//   i2c_write(d);
//   i2c_start();
//}
//
//char readByte(char address)
//{
//   char var;
//   i2c_start();
//   i2c_write(Adresse_Schreiben);
//   i2c_write(address);
//   i2c_start();
//   i2c_write(Adresse_Lesen);
//   var = i2c_read(0) ;
//   i2c_stop();
//   return var;
//}
//
//void pauseCounting()
//{
//   char tmp;
//   tmp = readByte(0x00);
//   tmp = tmp | 0x80;
//   writeByte(0x00,tmp);
//}
//void enableCounting()
//{
//   unsigned char tmp;
//   tmp = readByte(0x00);
//   tmp = tmp ^ 0x80;
//   writeByte(0x00,tmp);
//}
