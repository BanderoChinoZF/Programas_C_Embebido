// Interfacing PIC16F877A with DHT11 sensor CCS C code


//LCD module connections
#define LCD_RS_PIN PIN_B0
#define LCD_RW_PIN PIN_B1
#define LCD_ENABLE_PIN PIN_B2
#define LCD_DATA4 PIN_B3
#define LCD_DATA5 PIN_B4
#define LCD_DATA6 PIN_B5
#define LCD_DATA7 PIN_B6
//End LCD module connections

#include <16F877A.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP                       
#use delay(clock = 8000000)
#include <lcd.c>
#use fast_io(D)
#BIT Data_Pin = 0x08.0
#BIT Data_Pin_Direction = 0x88.0
        // Connection pin between DHT11 and mcu

char message1[] = "Temp = 00.0 C  ";
char message2[] = "RH   = 00.0 %  ";
short Time_out;

unsigned int8 T_byte1, T_byte2, RH_byte1, RH_byte2, CheckSum ;

void start_signal(){
  Data_Pin_Direction=0;
  Data_Pin = 0;
  delay_ms(25);
  Data_Pin = 1;
  delay_us(30);
  Data_Pin_Direction =1;
}
short check_response(){
  delay_us(40);
  if(!Data_Pin){                // Read and test if connection pin is low
    delay_us(80);
    if(Data_Pin){               // Read and test if connection pin is high
      delay_us(50);
      return 1;
    }
  }
}
unsigned int8 Read_Data(){
  unsigned int8 i, k, _data = 0;        // k is used to count 1 bit reading duration
  if(Time_out)
    break;
  for(i = 0; i < 8; i++){
    k = 0;
    while(!Data_Pin){           // Wait until DHT11 pin get raised
      k++;
      if(k > 100){
        Time_out = 1;
        break;
      }
      delay_us(1);
    }
    delay_us(30);
    if(!Data_Pin)
      bit_clear(_data, (7 - i));        // Clear bit (7 - i)
    else{
      bit_set(_data, (7 - i));          // Set bit (7 - i)
      while(Data_Pin){          // Wait until DHT11 pin goes low
        k++;
        if(k > 100){
        Time_out = 1;
        break;
      }
      delay_us(1);}
    }
  }
  return _data;
}
void main(){
  lcd_init();                                 // Initialize LCD module
  lcd_putc('\f');                             // LCD clear
  int x=1;
  
  while(TRUE){
    delay_ms(1000);
    Time_out = 0;
    Start_signal();
    
    if(check_response()){                     // If there is a response from sensor
      RH_byte1 = Read_Data();                 // read RH byte1
      RH_byte2 = Read_Data();                 // read RH byte2
      T_byte1 = Read_Data();                  // read T byte1
      T_byte2 = Read_Data();                  // read T byte2
      Checksum = Read_Data();                 // read checksum
      if(Time_out){                           // If reading takes long time
        lcd_putc('\f');                       // LCD clear
        lcd_gotoxy(5, 1);                     // Go to column 5 row 1
        lcd_putc("Time out!");
      }
      else{
       if(CheckSum == ((RH_Byte1 + RH_Byte2 + T_Byte1 + T_Byte2) & 0xFF)){
         message1[7]  = T_Byte1/10  + 48;
         message1[8]  = T_Byte1%10  + 48;
         message1[10] = T_Byte2/10  + 48;
         message2[7]  = RH_Byte1/10 + 48;
         message2[8]  = RH_Byte1%10 + 48;
         message2[10] = RH_Byte2/10 + 48;
         message1[11] = 223;   // Degree symbol
         
         /*for(int i = 15;i>=0;i--)
         {
            x++;
            lcd_gotoxy(1,1);
            printf(LCD_PUTC, "\f");
            lcd_gotoxy(i,2);
            printf(lcd_putc,"EL CLIMA ACTUAL EN OAXACA ES:");
            delay_ms(20);
            printf(LCD_PUTC, "\f");
            if (x==47)
            {
               break;
            };
         }*/
         
         lcd_gotoxy(1,1);
         printf(lcd_putc,"BIENVENIDOS EL");
         lcd_gotoxy(1,2);
         printf(lcd_putc,"CLIMA ESTA A:");
         delay_ms(650);
         printf(LCD_PUTC, "\f");
         
         
         lcd_putc('\f');
         lcd_gotoxy(1, 1);                     // Go to column 1 row 1
         printf(lcd_putc, message1);           // Display message1
         lcd_gotoxy(1, 2);                     // Go to column 1 row 2
         printf(lcd_putc, message2);           // Display message2
       }
       else{
         lcd_putc('\f');                       // LCD clear
         lcd_gotoxy(1, 1);                     // Go to column 1 row 1
         lcd_putc("Checksum Error!");
       }
      }
    }
    else {
      lcd_putc('\f');                          // LCD clear
      lcd_gotoxy(3, 1);                        // Go to column 3 row 1
      lcd_putc("No response");
      lcd_gotoxy(1, 2);                        // Go to column 1 row 2
      lcd_putc("from the sensor");
    }
  
  }
}
